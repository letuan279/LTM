/********************************************************************************
** Form generated from reading UI file 'taskscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKSCREEN_H
#define UI_TASKSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_taskscreen
{
public:
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_8;
    QPushButton *pushButton_16;
    QFrame *line_7;
    QHBoxLayout *horizontalLayout_13;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_10;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QPushButton *pushButton_19;
    QSpacerItem *verticalSpacer_4;
    QFrame *line_8;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_20;
    QTableView *tableView_4;

    void setupUi(QDialog *taskscreen)
    {
        if (taskscreen->objectName().isEmpty())
            taskscreen->setObjectName("taskscreen");
        taskscreen->resize(796, 566);
        verticalLayout_13 = new QVBoxLayout(taskscreen);
        verticalLayout_13->setObjectName("verticalLayout_13");
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName("verticalLayout_11");
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_7 = new QLabel(taskscreen);
        label_7->setObjectName("label_7");

        horizontalLayout_11->addWidget(label_7);

        horizontalSpacer_7 = new QSpacerItem(448, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_7);

        label_8 = new QLabel(taskscreen);
        label_8->setObjectName("label_8");

        horizontalLayout_11->addWidget(label_8);

        pushButton_16 = new QPushButton(taskscreen);
        pushButton_16->setObjectName("pushButton_16");

        horizontalLayout_11->addWidget(pushButton_16);


        verticalLayout_11->addLayout(horizontalLayout_11);

        line_7 = new QFrame(taskscreen);
        line_7->setObjectName("line_7");
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        verticalLayout_11->addWidget(line_7);


        verticalLayout_13->addLayout(verticalLayout_11);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        pushButton_17 = new QPushButton(taskscreen);
        pushButton_17->setObjectName("pushButton_17");

        verticalLayout_10->addWidget(pushButton_17);

        pushButton_18 = new QPushButton(taskscreen);
        pushButton_18->setObjectName("pushButton_18");

        verticalLayout_10->addWidget(pushButton_18);

        pushButton_19 = new QPushButton(taskscreen);
        pushButton_19->setObjectName("pushButton_19");

        verticalLayout_10->addWidget(pushButton_19);

        verticalSpacer_4 = new QSpacerItem(20, 328, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_4);


        horizontalLayout_12->addLayout(verticalLayout_10);

        line_8 = new QFrame(taskscreen);
        line_8->setObjectName("line_8");
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);

        horizontalLayout_12->addWidget(line_8);


        horizontalLayout_13->addLayout(horizontalLayout_12);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName("verticalLayout_12");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalSpacer_8 = new QSpacerItem(478, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_8);

        pushButton_20 = new QPushButton(taskscreen);
        pushButton_20->setObjectName("pushButton_20");

        horizontalLayout_10->addWidget(pushButton_20);


        verticalLayout_12->addLayout(horizontalLayout_10);

        tableView_4 = new QTableView(taskscreen);
        tableView_4->setObjectName("tableView_4");

        verticalLayout_12->addWidget(tableView_4);


        horizontalLayout_13->addLayout(verticalLayout_12);


        verticalLayout_13->addLayout(horizontalLayout_13);


        retranslateUi(taskscreen);

        QMetaObject::connectSlotsByName(taskscreen);
    } // setupUi

    void retranslateUi(QDialog *taskscreen)
    {
        taskscreen->setWindowTitle(QCoreApplication::translate("taskscreen", "Dialog", nullptr));
        label_7->setText(QCoreApplication::translate("taskscreen", "    Project 1", nullptr));
        label_8->setText(QCoreApplication::translate("taskscreen", "Tuan", nullptr));
        pushButton_16->setText(QCoreApplication::translate("taskscreen", "Logout", nullptr));
        pushButton_17->setText(QCoreApplication::translate("taskscreen", "Member", nullptr));
        pushButton_18->setText(QCoreApplication::translate("taskscreen", "Task", nullptr));
        pushButton_19->setText(QCoreApplication::translate("taskscreen", "Chat", nullptr));
        pushButton_20->setText(QCoreApplication::translate("taskscreen", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class taskscreen: public Ui_taskscreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKSCREEN_H
