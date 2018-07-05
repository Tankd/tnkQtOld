#ifndef JSONEDITDIALOG_H
#define JSONEDITDIALOG_H

#include <QDialog>

class QJsonModel;

namespace Ui {
class JsonEditDialog;
}

class JsonEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JsonEditDialog( const QString& fileName, QWidget *parent = 0);
    ~JsonEditDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::JsonEditDialog *ui;
    QString m_fileName;
    QJsonModel *m_model;
};


#endif // JSONEDITDIALOG_H
