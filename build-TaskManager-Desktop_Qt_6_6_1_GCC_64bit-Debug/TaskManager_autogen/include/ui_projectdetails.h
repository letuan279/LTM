/********************************************************************************
** Form generated from reading UI file 'projectdetails.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTDETAILS_H
#define UI_PROJECTDETAILS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectDetails
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_7;
    QPushButton *member_btn;
    QPushButton *task_btn;
    QPushButton *chat_btn;
    QSpacerItem *verticalSpacer_3;
    QFrame *line_5;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_10;
    QStackedWidget *project_stackwidget;
    QWidget *member;
    QTableView *member_table;
    QLabel *label;
    QPushButton *add_member_btn;
    QWidget *chat;
    QWidget *task;
    QTableView *task_table;
    QLabel *label_2;
    QPushButton *add_task_btn;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_6;
    QFrame *line_6;

    void setupUi(QWidget *ProjectDetails)
    {
        if (ProjectDetails->objectName().isEmpty())
            ProjectDetails->setObjectName("ProjectDetails");
        ProjectDetails->resize(877, 643);
        layoutWidget = new QWidget(ProjectDetails);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(8, 46, 851, 581));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        member_btn = new QPushButton(layoutWidget);
        member_btn->setObjectName("member_btn");

        verticalLayout_7->addWidget(member_btn);

        task_btn = new QPushButton(layoutWidget);
        task_btn->setObjectName("task_btn");

        verticalLayout_7->addWidget(task_btn);

        chat_btn = new QPushButton(layoutWidget);
        chat_btn->setObjectName("chat_btn");

        verticalLayout_7->addWidget(chat_btn);

        verticalSpacer_3 = new QSpacerItem(20, 328, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_3);


        horizontalLayout_9->addLayout(verticalLayout_7);

        line_5 = new QFrame(layoutWidget);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout_9->addWidget(line_5);


        horizontalLayout_8->addLayout(horizontalLayout_9);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");

        verticalLayout_8->addLayout(horizontalLayout_10);

        project_stackwidget = new QStackedWidget(layoutWidget);
        project_stackwidget->setObjectName("project_stackwidget");
        member = new QWidget();
        member->setObjectName("member");
        member_table = new QTableView(member);
        member_table->setObjectName("member_table");
        member_table->setGeometry(QRect(20, 30, 711, 501));
        label = new QLabel(member);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 10, 101, 17));
        add_member_btn = new QPushButton(member);
        add_member_btn->setObjectName("add_member_btn");
        add_member_btn->setGeometry(QRect(640, 0, 89, 25));
        project_stackwidget->addWidget(member);
        chat = new QWidget();
        chat->setObjectName("chat");
        project_stackwidget->addWidget(chat);
        task = new QWidget();
        task->setObjectName("task");
        task_table = new QTableView(task);
        task_table->setObjectName("task_table");
        task_table->setGeometry(QRect(20, 30, 711, 501));
        label_2 = new QLabel(task);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(360, 10, 41, 17));
        add_task_btn = new QPushButton(task);
        add_task_btn->setObjectName("add_task_btn");
        add_task_btn->setGeometry(QRect(640, 0, 89, 25));
        project_stackwidget->addWidget(task);

        verticalLayout_8->addWidget(project_stackwidget);


        horizontalLayout_8->addLayout(verticalLayout_8);

        layoutWidget_2 = new QWidget(ProjectDetails);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(7, 0, 851, 38));
        verticalLayout_9 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName("label_5");

        horizontalLayout_11->addWidget(label_5);

        horizontalSpacer_6 = new QSpacerItem(448, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_6);

        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName("label_6");

        horizontalLayout_11->addWidget(label_6);


        verticalLayout_9->addLayout(horizontalLayout_11);

        line_6 = new QFrame(layoutWidget_2);
        line_6->setObjectName("line_6");
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout_9->addWidget(line_6);


        retranslateUi(ProjectDetails);

        project_stackwidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(ProjectDetails);
    } // setupUi

    void retranslateUi(QWidget *ProjectDetails)
    {
        ProjectDetails->setWindowTitle(QCoreApplication::translate("ProjectDetails", "Form", nullptr));
        member_btn->setText(QCoreApplication::translate("ProjectDetails", "Member", nullptr));
        task_btn->setText(QCoreApplication::translate("ProjectDetails", "Task", nullptr));
        chat_btn->setText(QCoreApplication::translate("ProjectDetails", "Chat", nullptr));
        label->setText(QCoreApplication::translate("ProjectDetails", "MEMBER", nullptr));
        add_member_btn->setText(QCoreApplication::translate("ProjectDetails", "Add", nullptr));
        label_2->setText(QCoreApplication::translate("ProjectDetails", "TASK", nullptr));
        add_task_btn->setText(QCoreApplication::translate("ProjectDetails", "Add", nullptr));
        label_5->setText(QCoreApplication::translate("ProjectDetails", "    Project 1", nullptr));
        label_6->setText(QCoreApplication::translate("ProjectDetails", "Tuan", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectDetails: public Ui_ProjectDetails {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTDETAILS_H
