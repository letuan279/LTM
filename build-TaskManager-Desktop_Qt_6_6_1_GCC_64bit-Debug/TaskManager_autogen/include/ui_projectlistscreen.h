/********************************************************************************
** Form generated from reading UI file 'projectlistscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTLISTSCREEN_H
#define UI_PROJECTLISTSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectListScreen
{
public:
    QTableView *project_list;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_5;
    QLabel *username_head;
    QPushButton *logout_btn;
    QPushButton *create_project_btn;

    void setupUi(QWidget *ProjectListScreen)
    {
        if (ProjectListScreen->objectName().isEmpty())
            ProjectListScreen->setObjectName("ProjectListScreen");
        ProjectListScreen->resize(810, 607);
        project_list = new QTableView(ProjectListScreen);
        project_list->setObjectName("project_list");
        project_list->setGeometry(QRect(10, 80, 785, 511));
        layoutWidget_2 = new QWidget(ProjectListScreen);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(10, 0, 781, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName("label_6");

        horizontalLayout->addWidget(label_6);

        horizontalSpacer_5 = new QSpacerItem(248, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        username_head = new QLabel(layoutWidget_2);
        username_head->setObjectName("username_head");

        horizontalLayout->addWidget(username_head);

        logout_btn = new QPushButton(layoutWidget_2);
        logout_btn->setObjectName("logout_btn");

        horizontalLayout->addWidget(logout_btn);

        create_project_btn = new QPushButton(ProjectListScreen);
        create_project_btn->setObjectName("create_project_btn");
        create_project_btn->setGeometry(QRect(10, 40, 80, 25));

        retranslateUi(ProjectListScreen);

        QMetaObject::connectSlotsByName(ProjectListScreen);
    } // setupUi

    void retranslateUi(QWidget *ProjectListScreen)
    {
        ProjectListScreen->setWindowTitle(QCoreApplication::translate("ProjectListScreen", "Form", nullptr));
        label_6->setText(QCoreApplication::translate("ProjectListScreen", "Project Management", nullptr));
        username_head->setText(QCoreApplication::translate("ProjectListScreen", "Tuan", nullptr));
        logout_btn->setText(QCoreApplication::translate("ProjectListScreen", "Logout", nullptr));
        create_project_btn->setText(QCoreApplication::translate("ProjectListScreen", "create", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectListScreen: public Ui_ProjectListScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTLISTSCREEN_H
