#include "taskscreen.h"
#include "ui_taskscreen.h"

taskscreen::taskscreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::taskscreen)
{
    ui->setupUi(this);
}

taskscreen::~taskscreen()
{
    delete ui;
}
