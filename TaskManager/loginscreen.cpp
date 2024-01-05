#include "loginscreen.h"
#include "ui_loginscreen.h"

#include <QDebug>

using namespace std;

LoginScreen::LoginScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginScreen)
{
    ui->setupUi(this);
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::on_moveto_register_clicked()
{
    emit moveToRegisterClicked();
}


void LoginScreen::on_btn_login_clicked()
{
    QString username = ui->input_login_username->text();
    QString password = ui->input_login_password->text();

    emit loginButtonClicked(username, password);

    // Clear text
    ui->input_login_username->setText("");
    ui->input_login_password->setText("");
}

