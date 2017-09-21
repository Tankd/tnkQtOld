#include "traywidget.h"

#include <QMenu>
#include <QApplication>
#include <QDesktopWidget>
#include <QCloseEvent>

namespace tnk {

QWidget* TrayWidget::m_selfWidget = 0;

TrayWidget::TrayWidget(QWidget *parent) : QWidget(parent)
{
    m_selfWidget = this;
    setWindowFlags( Qt::FramelessWindowHint |
                    Qt::WindowStaysOnTopHint
                    );

    QMenu *menu = new QMenu();


    menu->addAction("Show", this, SLOT(show()));
    menu->addAction("Quit", QApplication::instance(), SLOT(quit()));

    m_systray = new QSystemTrayIcon();
    m_systray->setContextMenu( menu);
    m_systray->setIcon( QIcon(":/logo.jpg"));
    m_systray->show();

    this->setStyleSheet(
                "QPushButton:checked{ background-color: rgb(255, 0, 0);}");

    hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);

}

TrayWidget::~TrayWidget()
{
    delete m_systray;
}

void TrayWidget::showEvent(QShowEvent *event)
{
    this->raise();
    QRect geom = QApplication::desktop()->screenGeometry();
    this->move( geom.width() - this->width(), (geom.height() - this->height()) * 0.5f);
}


void TrayWidget::closeEvent(QCloseEvent *event)
{    
    event->ignore();
    this->hide();
}



LRESULT TrayWidget::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        switch (wParam)
        {
        // Pass KeyDown/KeyUp messages for Qt class to logicize
        case WM_KEYDOWN:
            if(PKBDLLHOOKSTRUCT(lParam)->vkCode == VK_F2)
            {

                m_selfWidget->setVisible( !m_selfWidget->isVisible());
                m_selfWidget->raise();
            }
            break;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

QSystemTrayIcon *TrayWidget::systray() const
{
    return m_systray;
}

}
