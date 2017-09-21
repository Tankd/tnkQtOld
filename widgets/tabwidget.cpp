#include "tabwidget.h"

#include "tabbar.h"

#include <QDebug>

namespace tnk {

TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent)
{
    this->setTabBar( new TabBar);
    this->setMovable( true);
}

void TabWidget::addView(QWidget *widget, const QString& title)
{
    if( title.isEmpty() == false)
        widget->setWindowTitle( title);

    this->addTab( widget, widget->windowTitle());
}

void TabWidget::detachView(int index, TabWidget *newTabWidget)
{    
    QWidget* w = this->widget( index);
    qDebug() << this->count();
    this->removeTab( index);
    qDebug() << this->count();

    newTabWidget->addView( w);

    if( count() == 0)
        this->close();
}

void TabWidget::detachView(int index, QPoint pos)
{    
    QWidget* w = this->widget( index);
    this->removeTab( index);
    createNewWindow(pos, w);

    if( count() == 0)
        this->close();
}

void TabWidget::createNewWindow(QPoint pos, QWidget *child)
{
    TabWidget* tab = new TabWidget();
    tab->move( pos);
    tab->resize( this->size());
    tab->addView( child);
    tab->show();
}

}
