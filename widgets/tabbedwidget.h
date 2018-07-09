#ifndef TABBEDWIDGET_H
#define TABBEDWIDGET_H

#include <QMainWindow>
#include <QDockWidget>

class TabbedWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit TabbedWidget(QWidget *parent = nullptr);


public slots:
    void addView( QWidget* widget)
    {
        this->addTab( widget, widget->windowIcon(), widget->windowTitle());

        connect( widget, &QWidget::windowIconChanged, this, &TabbedWidget::on_widgetIconChanged);
        connect( widget, &QWidget::windowTitleChanged, this, &TabbedWidget::on_widgetTitleChanged);

    }



private slots:
    void on_widgetIconChanged( const QIcon &icon){
        QWidget* widget = reinterpret_cast<QWidget*>(sender());
        int index = this->indexOf( widget);
        this->setTabIcon( index, widget->windowIcon());
    }

    void on_widgetTitleChanged( const QString &title){
        QWidget* widget = reinterpret_cast<QWidget*>(sender());
        int index = this->indexOf( widget);
        this->setTabText( index, widget->windowTitle());
    }


private:


};

#endif // TABBEDWIDGET_H
