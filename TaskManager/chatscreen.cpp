#include "chatscreen.h"
#include "ui_chatscreen.h"

chatscreen::chatscreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chatscreen)
{
    ui->setupUi(this);
}

chatscreen::~chatscreen()
{
    delete ui;
}
