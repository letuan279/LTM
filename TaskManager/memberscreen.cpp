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

void MemberScreen::on_send_message_btn_clicked()
{
    QString message = ui->lineEdit->text();
    ui->textEdit->append(message);
    ui->lineEdit->clear();
}

