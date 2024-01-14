/********************************************************************************
** Form generated from reading UI file 'chatscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATSCREEN_H
#define UI_CHATSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_chatscreen
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_8;
    QFrame *line_7;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QPushButton *pushButton_19;
    QSpacerItem *verticalSpacer_4;
    QFrame *line_8;
    QVBoxLayout *verticalLayout;
    QTableView *tableView_4;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_20;

    void setupUi(QDialog *chatscreen)
    {
        if (chatscreen->objectName().isEmpty())
            chatscreen->setObjectName("chatscreen");
        chatscreen->resize(802, 637);
        verticalLayout_3 = new QVBoxLayout(chatscreen);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_7 = new QLabel(chatscreen);
        label_7->setObjectName("label_7");

        horizontalLayout_4->addWidget(label_7);

        horizontalSpacer_6 = new QSpacerItem(498, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        label_8 = new QLabel(chatscreen);
        label_8->setObjectName("label_8");

        horizontalLayout_4->addWidget(label_8);


        verticalLayout_3->addLayout(horizontalLayout_4);

        line_7 = new QFrame(chatscreen);
        line_7->setObjectName("line_7");
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        pushButton_17 = new QPushButton(chatscreen);
        pushButton_17->setObjectName("pushButton_17");

        verticalLayout_2->addWidget(pushButton_17);

        pushButton_18 = new QPushButton(chatscreen);
        pushButton_18->setObjectName("pushButton_18");

        verticalLayout_2->addWidget(pushButton_18);

        pushButton_19 = new QPushButton(chatscreen);
        pushButton_19->setObjectName("pushButton_19");

        verticalLayout_2->addWidget(pushButton_19);

        verticalSpacer_4 = new QSpacerItem(20, 328, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);


        horizontalLayout_2->addLayout(verticalLayout_2);

        line_8 = new QFrame(chatscreen);
        line_8->setObjectName("line_8");
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_8);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        tableView_4 = new QTableView(chatscreen);
        tableView_4->setObjectName("tableView_4");

        verticalLayout->addWidget(tableView_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lineEdit_2 = new QLineEdit(chatscreen);
        lineEdit_2->setObjectName("lineEdit_2");

        horizontalLayout->addWidget(lineEdit_2);

        pushButton_20 = new QPushButton(chatscreen);
        pushButton_20->setObjectName("pushButton_20");

        horizontalLayout->addWidget(pushButton_20);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout_3);


        retranslateUi(chatscreen);

        QMetaObject::connectSlotsByName(chatscreen);
    } // setupUi

    void retranslateUi(QDialog *chatscreen)
    {
        chatscreen->setWindowTitle(QCoreApplication::translate("chatscreen", "Dialog", nullptr));
        label_7->setText(QCoreApplication::translate("chatscreen", "Project 1", nullptr));
        label_8->setText(QCoreApplication::translate("chatscreen", "Tuan", nullptr));
        pushButton_17->setText(QCoreApplication::translate("chatscreen", "Member", nullptr));
        pushButton_18->setText(QCoreApplication::translate("chatscreen", "Task", nullptr));
        pushButton_19->setText(QCoreApplication::translate("chatscreen", "Chat", nullptr));
        pushButton_20->setText(QCoreApplication::translate("chatscreen", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatscreen: public Ui_chatscreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATSCREEN_H
