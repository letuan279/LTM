/********************************************************************************
** Form generated from reading UI file 'loginscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINSCREEN_H
#define UI_LOGINSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginScreen
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btn_login;
    QPushButton *moveto_register;
    QLineEdit *input_login_username;
    QLineEdit *input_login_password;

    void setupUi(QWidget *LoginScreen)
    {
        if (LoginScreen->objectName().isEmpty())
            LoginScreen->setObjectName("LoginScreen");
        LoginScreen->resize(852, 425);
        groupBox = new QGroupBox(LoginScreen);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(260, 90, 311, 221));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 60, 67, 17));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 110, 67, 17));
        btn_login = new QPushButton(groupBox);
        btn_login->setObjectName("btn_login");
        btn_login->setGeometry(QRect(20, 150, 271, 25));
        moveto_register = new QPushButton(groupBox);
        moveto_register->setObjectName("moveto_register");
        moveto_register->setGeometry(QRect(20, 180, 271, 25));
        input_login_username = new QLineEdit(groupBox);
        input_login_username->setObjectName("input_login_username");
        input_login_username->setGeometry(QRect(110, 60, 181, 25));
        input_login_password = new QLineEdit(groupBox);
        input_login_password->setObjectName("input_login_password");
        input_login_password->setGeometry(QRect(110, 110, 181, 25));
        input_login_password->setEchoMode(QLineEdit::Password);

        retranslateUi(LoginScreen);

        QMetaObject::connectSlotsByName(LoginScreen);
    } // setupUi

    void retranslateUi(QWidget *LoginScreen)
    {
        LoginScreen->setWindowTitle(QCoreApplication::translate("LoginScreen", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("LoginScreen", "Login", nullptr));
        label->setText(QCoreApplication::translate("LoginScreen", "username", nullptr));
        label_2->setText(QCoreApplication::translate("LoginScreen", "password", nullptr));
        btn_login->setText(QCoreApplication::translate("LoginScreen", "login", nullptr));
        moveto_register->setText(QCoreApplication::translate("LoginScreen", "Don't Have an account ? Register now ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginScreen: public Ui_LoginScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINSCREEN_H
