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

