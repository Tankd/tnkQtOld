#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMdiArea>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMdiArea
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
