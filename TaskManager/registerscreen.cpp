#include "registerscreen.h"
#include "ui_registerscreen.h"

#include <QMessageBox>

RegisterScreen::RegisterScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterScreen)
{
    ui->setupUi(this);
}

RegisterScreen::~RegisterScreen()
{
    delete ui;
}

void RegisterScreen::on_moveto_login_clicked()
{
    emit moveToLoginClicked();
}


void RegisterScreen::on_btn_register_clicked()
{
    QString username = ui->input_register_username->text();
    QString password = ui->input_register_password->text();
    QString cf_password = ui->input_register_confirm_password->text();

    // Check
    if(password != cf_password) {
        QMessageBox::critical(nullptr, "Error", "Password and Confirm Password not match");
        return;
    }

    emit registerButtonClicked(username, password);

    // Clear text
    ui->input_register_username->setText("");
    ui->input_register_password->setText("");
    ui->input_register_confirm_password->setText("");
    return;
}

