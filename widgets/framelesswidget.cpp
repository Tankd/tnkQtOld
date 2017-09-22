#include "framelesswidget.h"
#include "ui_framelesswidget.h"

#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QDebug>

FramelessWidget::FramelessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FramelessWidget),
    m_contentWidget(0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window |Qt::CustomizeWindowHint);

    //shadow under window title text
    QGraphicsDropShadowEffect *textShadow = new QGraphicsDropShadowEffect;
    textShadow->setBlurRadius(2.0);
    textShadow->setColor(QColor(0,0,0));
    textShadow->setOffset(0.0);
    ui->titleLabel->setGraphicsEffect(textShadow);

    onMove = false;
}

FramelessWidget::~FramelessWidget()
{

    delete ui;
}

void FramelessWidget::setContent(QWidget *widget)
{
    if( m_contentWidget)
        ui->contentLayout->removeWidget( m_contentWidget);


    m_contentWidget = widget;

    this->resize( m_contentWidget->size());

    m_contentWidget->setParent( this);
    ui->contentLayout->addWidget( widget);
    this->setWindowTitle( widget->windowTitle());

    ui->titleLabel->setWindowIcon( widget->windowIcon());
}

void FramelessWidget::setWindowTitle(const QString &title)
{
    QWidget::setWindowTitle( title);
    ui->titleLabel->setText( title);
}

void FramelessWidget::on_minimizeButton_clicked()
{
    this->showMinimized();
}

void FramelessWidget::on_maximizeButton_clicked()
{
    if( this->isMaximized())
        this->showNormal();
    else this->showMaximized();
}

void FramelessWidget::on_closeButton_clicked()
{
    this->close();
}

void FramelessWidget::mousePressEvent(QMouseEvent *event)
{
    if(ui->titleLabel->rect().contains( event->pos()))
    {
        MouseDiff = event->pos();
        setCursor(QCursor(Qt::SizeAllCursor));
        onMove = true;
    }
}

void FramelessWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    setCursor(QCursor(Qt::ArrowCursor));
    onMove = false;
}

void FramelessWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(onMove)
    {
        QPoint p = event->globalPos();
        window()->move(p - MouseDiff);
    }
}
