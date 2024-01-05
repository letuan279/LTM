#include "memberscreen.h"
#include "ui_memberscreen.h"

MemberScreen::MemberScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MemberScreen)
{
    ui->setupUi(this);
}

MemberScreen::~MemberScreen()
{
    delete ui;
}
