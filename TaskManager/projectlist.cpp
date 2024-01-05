#include "projectlist.h"
#include "ui_projectlist.h"

ProjectList::ProjectList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProjectList)
{
    ui->setupUi(this);
}

ProjectList::~ProjectList()
{
    delete ui;
}

void ProjectList::on_testBtn_clicked()
{
    qDebug() << "test";
}

