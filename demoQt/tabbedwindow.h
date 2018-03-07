#ifndef TABBEDWINDOW_H
#define TABBEDWINDOW_H

#include <QMainWindow>
#include <QDockWidget>

class TabbedWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit TabbedWidget(QWidget *parent = nullptr);

    void addWidget( QWidget *widget, const QString& title)
    {

        auto dock = new QDockWidget(title, this);
        dock->setFeatures(
                    QDockWidget::DockWidgetMovable |
                    QDockWidget::DockWidgetFloatable);

        dock->setWidget( widget);
        this->addDockWidget(Qt::TopDockWidgetArea, dock);

        if( m_widgets.count())
        this->tabifyDockWidget(m_widgets.at(0), dock);

        m_widgets << dock;
    }

private:
    QList< QDockWidget*> m_widgets;
};

#endif // TABBEDWINDOW_H
