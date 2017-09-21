#ifndef TRAYWIDGET_H
#define TRAYWIDGET_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <qt_windows.h>
namespace tnk {

class TrayWidget : public QWidget
{
    Q_OBJECT

signals:
        void hooked();
public:
    explicit TrayWidget(QWidget *parent = nullptr);
    virtual ~TrayWidget();

    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    QSystemTrayIcon *systray() const;

private:
    QSystemTrayIcon *m_systray;
     HHOOK hhkLowLevelKybd;
     static QWidget* m_selfWidget;

protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
};

}
#endif // TRAYWINDOW_H
