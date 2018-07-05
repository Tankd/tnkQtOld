#include "jsoneditdialog.h"
#include "ui_jsoneditdialog.h"

#include "common/jsonobject.h"
#include "common/utils.h"
#include "external/QJsonModel/qjsonmodel.h"


JsonEditDialog::JsonEditDialog(const QString &fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JsonEditDialog), m_fileName( fileName)
{
    ui->setupUi(this);

    m_model = new QJsonModel(this);
    m_model->load( fileName);

    ui->treeView->setModel( m_model);

}

JsonEditDialog::~JsonEditDialog()
{
    delete ui;
}


void JsonEditDialog::on_buttonBox_accepted()
{
    tnk::utils::toFile(m_fileName, m_model->json().toJson());
    close();
}

void JsonEditDialog::on_buttonBox_rejected()
{
    this->close();
}
