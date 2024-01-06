#include "projectlistscreen.h"
#include "ui_projectlistscreen.h"

projectlistscreen::projectlistscreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::projectlistscreen)
{
    ui->setupUi(this);
}

projectlistscreen::~projectlistscreen()
{
    delete ui;
}
