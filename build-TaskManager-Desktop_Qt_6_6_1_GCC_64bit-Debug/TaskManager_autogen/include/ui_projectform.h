/********************************************************************************
** Form generated from reading UI file 'projectform.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTFORM_H
#define UI_PROJECTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_ProjectForm
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *input_project_name;

    void setupUi(QDialog *ProjectForm)
    {
        if (ProjectForm->objectName().isEmpty())
            ProjectForm->setObjectName("ProjectForm");
        ProjectForm->resize(400, 152);
        buttonBox = new QDialogButtonBox(ProjectForm);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(40, 100, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(ProjectForm);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 10, 141, 17));
        label_2 = new QLabel(ProjectForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 50, 111, 17));
        input_project_name = new QLineEdit(ProjectForm);
        input_project_name->setObjectName("input_project_name");
        input_project_name->setGeometry(QRect(130, 50, 251, 25));

        retranslateUi(ProjectForm);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ProjectForm, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ProjectForm, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ProjectForm);
    } // setupUi

    void retranslateUi(QDialog *ProjectForm)
    {
        ProjectForm->setWindowTitle(QCoreApplication::translate("ProjectForm", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ProjectForm", "Create new project", nullptr));
        label_2->setText(QCoreApplication::translate("ProjectForm", "Project's name: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectForm: public Ui_ProjectForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTFORM_H
