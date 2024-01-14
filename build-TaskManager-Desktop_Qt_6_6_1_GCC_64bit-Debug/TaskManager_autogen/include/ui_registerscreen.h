/********************************************************************************
** Form generated from reading UI file 'registerscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERSCREEN_H
#define UI_REGISTERSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterScreen
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btn_register;
    QPushButton *moveto_login;
    QLineEdit *input_register_username;
    QLineEdit *input_register_password;
    QLabel *label_3;
    QLineEdit *input_register_confirm_password;

    void setupUi(QWidget *RegisterScreen)
    {
        if (RegisterScreen->objectName().isEmpty())
            RegisterScreen->setObjectName("RegisterScreen");
        RegisterScreen->resize(849, 425);
        groupBox = new QGroupBox(RegisterScreen);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(230, 70, 391, 271));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 60, 67, 17));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 110, 67, 17));
        btn_register = new QPushButton(groupBox);
        btn_register->setObjectName("btn_register");
        btn_register->setGeometry(QRect(50, 200, 281, 25));
        moveto_login = new QPushButton(groupBox);
        moveto_login->setObjectName("moveto_login");
        moveto_login->setGeometry(QRect(50, 230, 281, 25));
        input_register_username = new QLineEdit(groupBox);
        input_register_username->setObjectName("input_register_username");
        input_register_username->setGeometry(QRect(170, 60, 181, 25));
        input_register_password = new QLineEdit(groupBox);
        input_register_password->setObjectName("input_register_password");
        input_register_password->setGeometry(QRect(170, 110, 181, 25));
        input_register_password->setEchoMode(QLineEdit::Password);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 160, 131, 16));
        input_register_confirm_password = new QLineEdit(groupBox);
        input_register_confirm_password->setObjectName("input_register_confirm_password");
        input_register_confirm_password->setGeometry(QRect(170, 160, 181, 25));
        input_register_confirm_password->setEchoMode(QLineEdit::Password);

        retranslateUi(RegisterScreen);

        QMetaObject::connectSlotsByName(RegisterScreen);
    } // setupUi

    void retranslateUi(QWidget *RegisterScreen)
    {
        RegisterScreen->setWindowTitle(QCoreApplication::translate("RegisterScreen", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("RegisterScreen", "Register", nullptr));
        label->setText(QCoreApplication::translate("RegisterScreen", "username", nullptr));
        label_2->setText(QCoreApplication::translate("RegisterScreen", "password", nullptr));
        btn_register->setText(QCoreApplication::translate("RegisterScreen", "register", nullptr));
        moveto_login->setText(QCoreApplication::translate("RegisterScreen", "Already have an account? Login instead ", nullptr));
        label_3->setText(QCoreApplication::translate("RegisterScreen", "confirm password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterScreen: public Ui_RegisterScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERSCREEN_H
