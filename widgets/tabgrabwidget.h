#ifndef TABGRABWIDGET_H
#define TABGRABWIDGET_H

#include <QLabel>
namespace tnk {

class TabGrabWidget : public QLabel
{
    Q_OBJECT
public:
    explicit TabGrabWidget(QWidget *parent = nullptr);

    int index() const;
    void setIndex(int index);

protected:
    int m_index;
};
}

#endif // TABGRABWIDGET_H
