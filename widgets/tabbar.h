#ifndef TABBAR_H
#define TABBAR_H

#include <QTabBar>
namespace tnk {

class TabGrabWidget;

class TabBar : public QTabBar
{
    Q_OBJECT
public:
    TabBar(QWidget* parent = 0);

public:
    virtual QSize sizeHint() const;

    int tabWidth() const;
    void setTabWidth(int tabWidth);

protected:
    int m_tabWidth;
    TabGrabWidget* m_grab;

protected:
    virtual QSize tabSizeHint(int index) const;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};
}
#endif // TABBAR_H
