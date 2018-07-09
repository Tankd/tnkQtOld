#include "tabbedwidget.h"

TabbedWidget::TabbedWidget(QWidget *parent) : QTabWidget(parent)
{
    setMovable( true);
    setTabsClosable( true);

}
