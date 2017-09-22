#ifndef FRAMELESSWIDGET_H
#define FRAMELESSWIDGET_H

#include <QWidget>

namespace Ui {
class FramelessWidget;
}

class FramelessWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FramelessWidget(QWidget *parent = 0);
    ~FramelessWidget();


    void setContent(QWidget *widget);


public slots:
    void setWindowTitle(const QString& title);

private slots:
    void on_minimizeButton_clicked();

    void on_maximizeButton_clicked();

    void on_closeButton_clicked();


protected:
    //mouvement de la fenetre
       void mousePressEvent (QMouseEvent *event);
       void mouseReleaseEvent(QMouseEvent *event);
       void mouseMoveEvent (QMouseEvent *event);

private:
    Ui::FramelessWidget *ui;
    QWidget* m_contentWidget;
    bool onMove;
     QPoint MouseDiff;
};

#endif // FRAMELESSWIDGET_H
