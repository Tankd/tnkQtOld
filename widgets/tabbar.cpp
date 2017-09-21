#include "tabbar.h"

#include <QMouseEvent>
#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QApplication>

#include "tabgrabwidget.h"
#include "tabwidget.h"
namespace tnk {

TabBar::TabBar(QWidget *parent)
    :QTabBar( parent), m_grab(0)
{
    setAcceptDrops(true);
    setTabWidth(128);
}

QSize TabBar::sizeHint() const
{
    return QSize(qMin(this->count() * m_tabWidth, parentWidget()->width()), 32);
}

QSize TabBar::tabSizeHint(int index) const
{
    return QSize(m_tabWidth, 32);
}

int TabBar::tabWidth() const
{
    return m_tabWidth;
}

void TabBar::setTabWidth(int tabWidth)
{
    m_tabWidth = tabWidth;
}

void TabBar::mousePressEvent(QMouseEvent *event)
{
    if(m_grab)
        return;

    int index = this->tabAt( event->pos());
    QWidget* widget =  reinterpret_cast<TabWidget*>( parentWidget())->widget(index);

    if( widget == 0)
        return;

    QPixmap pixmap = widget->grab().scaledToWidth(128);
    m_grab = new TabGrabWidget();
    m_grab->setPixmap( pixmap);
    m_grab->setIndex( index);

    QTabBar::mousePressEvent( event);
}

void TabBar::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_grab)
        return;

    m_grab->show();
    m_grab->move( event->globalPos()+QPoint(-64, 10));

    QTabBar::mouseMoveEvent( event);
}

void TabBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(!m_grab)
        return;

    QWidget *w = dynamic_cast<QWidget*>(
                QApplication::widgetAt( event->globalPos()));

    if( w)
    {
        if(w != this && w != parentWidget())
        {


            QString className = w->metaObject()->className();

            if( className == "TabWidget")
            {
                reinterpret_cast<TabWidget*>( parentWidget())->detachView(
                            m_grab->index(),
                            reinterpret_cast<TabWidget*>( w));
            }
            else if( className == "TabBar")
            {
                reinterpret_cast<TabWidget*>( parentWidget())->detachView(
                            m_grab->index(),
                            reinterpret_cast<TabWidget*>( w->parentWidget()));
            }
        }
    }
    else
    {
        reinterpret_cast<TabWidget*>( parentWidget())->detachView( m_grab->index(), event->globalPos());
    }

    delete m_grab;
    m_grab = 0;

    QTabBar::mouseReleaseEvent( event);
}

}
