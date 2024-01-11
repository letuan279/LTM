#include "projectdetails.h"
#include "ui_projectdetails.h"

ProjectDetails::ProjectDetails(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProjectDetails)
{
    ui->setupUi(this);
}

ProjectDetails::~ProjectDetails()
{
    delete ui;
}

void ProjectDetails::showEvent(QShowEvent *event) {
    QWidget::show();

    emit widgetShown();
}

void ProjectDetails::on_project_stackwidget_currentChanged(int arg1)
{
    emit widgetChanged(arg1);
}


void ProjectDetails::on_task_table_doubleClicked(const QModelIndex &index)
{
    QString id = index.model()->data(index.model()->index(index.row(), 0)).toString();
    emit doubleClick(id);
}

