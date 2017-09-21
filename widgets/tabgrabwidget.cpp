#include "tabgrabwidget.h"
namespace tnk {

TabGrabWidget::TabGrabWidget(QWidget *parent) : QLabel(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
}

int TabGrabWidget::index() const
{
    return m_index;
}

void TabGrabWidget::setIndex(int index)
{
    m_index = index;
}
}
