#include "memberform.h"
#include "ui_memberform.h"

MemberForm::MemberForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MemberForm)
{
    ui->setupUi(this);
}

MemberForm::~MemberForm()
{
    delete ui;
}

void MemberForm::on_buttonBox_accepted()
{
    emit handleAccept();
}


void MemberForm::on_buttonBox_rejected()
{
    emit handleReject();
}

