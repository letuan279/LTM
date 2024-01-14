/********************************************************************************
** Form generated from reading UI file 'memberform.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMBERFORM_H
#define UI_MEMBERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MemberForm
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_2;
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QComboBox *input_list_member;

    void setupUi(QDialog *MemberForm)
    {
        if (MemberForm->objectName().isEmpty())
            MemberForm->setObjectName("MemberForm");
        MemberForm->resize(342, 160);
        buttonBox = new QDialogButtonBox(MemberForm);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(40, 100, 281, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_2 = new QLabel(MemberForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 50, 111, 17));
        label = new QLabel(MemberForm);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 0, 141, 17));
        verticalLayoutWidget = new QWidget(MemberForm);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(140, 40, 160, 31));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        input_list_member = new QComboBox(verticalLayoutWidget);
        input_list_member->setObjectName("input_list_member");
        input_list_member->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(input_list_member);


        retranslateUi(MemberForm);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, MemberForm, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, MemberForm, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(MemberForm);
    } // setupUi

    void retranslateUi(QDialog *MemberForm)
    {
        MemberForm->setWindowTitle(QCoreApplication::translate("MemberForm", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("MemberForm", "Choose member", nullptr));
        label->setText(QCoreApplication::translate("MemberForm", "Add member", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MemberForm: public Ui_MemberForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEMBERFORM_H
