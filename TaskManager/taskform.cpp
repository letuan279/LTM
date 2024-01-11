#include "taskform.h"
#include "ui_taskform.h"

using namespace std;

TaskForm::TaskForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskForm)
{
    ui->setupUi(this);

    // Set default values
    ui->dateEdit->setDate(QDateTime::currentDateTime().date());
    ui->dateEdit_2->setDate(QDateTime::currentDateTime().date());

    // Set status combobox values
    ui->comboBox->addItem("TODO");
    ui->comboBox->addItem("PROCESS");
    ui->comboBox->addItem("DONE");

    ui->comboBox->setCurrentIndex(0);

    ui->comboBox_2->addItem("");
    ui->comboBox_2->setCurrentIndex(0);
}

TaskForm::~TaskForm()
{
    delete ui;
}

void TaskForm::on_buttonBox_accepted()
{
    QString name = ui->lineEdit->text();
    QString status = ui->comboBox->currentText();
    QDate startDate = ui->dateEdit->date();
    QDate endDate = ui->dateEdit_2->date();
    QString comment = ui->textEdit->toPlainText();
    QString idAssign = ui->comboBox_2->currentText();

    string nameStr = name.isEmpty() ? "" : name.toStdString();
    string statusStr = status.isEmpty() ? "" : status.toStdString();
    string startDateStr = startDate.toString("yyyy-MM-dd").toStdString();
    string endDateStr = endDate.toString("yyyy-MM-dd").toStdString();
    string commentStr = comment.isEmpty() ? "" : comment.toStdString();
    string idAssignStr = idAssign.isEmpty() ? "" : idAssign.toStdString();

    emit handleAccept(nameStr, statusStr, startDateStr, endDateStr, commentStr, idAssignStr);
}


void TaskForm::on_buttonBox_rejected()
{
    emit handleReject();
}
