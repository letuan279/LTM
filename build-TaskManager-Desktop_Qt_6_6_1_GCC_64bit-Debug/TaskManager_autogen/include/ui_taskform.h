/********************************************************************************
** Form generated from reading UI file 'taskform.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKFORM_H
#define UI_TASKFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QComboBox *comboBox;
    QLabel *label_4;
    QDateEdit *dateEdit;
    QLabel *label_5;
    QDateEdit *dateEdit_2;
    QLabel *label_6;
    QComboBox *comboBox_2;
    QTextEdit *textEdit;
    QLabel *label_7;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *TaskForm)
    {
        if (TaskForm->objectName().isEmpty())
            TaskForm->setObjectName("TaskForm");
        TaskForm->resize(480, 379);
        label = new QLabel(TaskForm);
        label->setObjectName("label");
        label->setGeometry(QRect(190, 10, 67, 17));
        label_2 = new QLabel(TaskForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 50, 67, 17));
        lineEdit = new QLineEdit(TaskForm);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(100, 50, 201, 25));
        label_3 = new QLabel(TaskForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 90, 67, 17));
        comboBox = new QComboBox(TaskForm);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(100, 90, 121, 25));
        label_4 = new QLabel(TaskForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 130, 81, 17));
        dateEdit = new QDateEdit(TaskForm);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(100, 130, 121, 26));
        label_5 = new QLabel(TaskForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 170, 71, 17));
        dateEdit_2 = new QDateEdit(TaskForm);
        dateEdit_2->setObjectName("dateEdit_2");
        dateEdit_2->setGeometry(QRect(100, 170, 121, 26));
        label_6 = new QLabel(TaskForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(40, 210, 67, 17));
        comboBox_2 = new QComboBox(TaskForm);
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(100, 210, 121, 25));
        textEdit = new QTextEdit(TaskForm);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(100, 250, 331, 70));
        label_7 = new QLabel(TaskForm);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 250, 81, 17));
        buttonBox = new QDialogButtonBox(TaskForm);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(260, 340, 166, 25));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(TaskForm);

        QMetaObject::connectSlotsByName(TaskForm);
    } // setupUi

    void retranslateUi(QWidget *TaskForm)
    {
        TaskForm->setWindowTitle(QCoreApplication::translate("TaskForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("TaskForm", "Task form", nullptr));
        label_2->setText(QCoreApplication::translate("TaskForm", "Name", nullptr));
        label_3->setText(QCoreApplication::translate("TaskForm", "Status", nullptr));
        label_4->setText(QCoreApplication::translate("TaskForm", "Start date", nullptr));
        label_5->setText(QCoreApplication::translate("TaskForm", "End date", nullptr));
        label_6->setText(QCoreApplication::translate("TaskForm", "Assign", nullptr));
        label_7->setText(QCoreApplication::translate("TaskForm", "Comment", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskForm: public Ui_TaskForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKFORM_H
