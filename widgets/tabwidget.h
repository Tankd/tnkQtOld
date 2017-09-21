#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>

namespace tnk {

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit TabWidget(QWidget *parent = nullptr);

    void addView(QWidget* widget, const QString &title = QString());

    void detachView( int index, TabWidget *newTabWidget);
    void detachView(int index, QPoint pos);

protected:
    virtual void createNewWindow(QPoint pos, QWidget *child);
};

}

#endif // TABWIDGET_H
