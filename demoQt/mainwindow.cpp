#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabbedwindow.h"
#include "testwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    TabbedWidget *tab = new TabbedWidget();
    this->setCentralWidget( tab);

    tab->addWidget( new TestWidget, "test1");
    tab->addWidget( new TestWidget, "test2");
    tab->addWidget( new TestWidget, "test3");


}

MainWindow::~MainWindow()
{
    delete ui;
}
