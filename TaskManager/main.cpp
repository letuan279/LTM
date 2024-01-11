// #include "mainwindow.h"

#include <QApplication>
#include <QThread>
#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QMessageBox>
#include <QtWidgets>

#include "loginscreen.h"
#include "registerscreen.h"
#include "projectlistscreen.h"
#include "projectdetails.h"
#include "projectform.h"
#include "memberform.h"
#include "taskform.h"

#include "call.h"

using namespace std;

// Define type
struct Account {
    string id;
    string username;
    string password;
    string session;
};
struct Project {
    string id;
    string name;
    string id_owner;
    string owner;
};
struct Task {
    string id;
    string id_project;
    string id_manager;
    string name;
    string status;
    string id_assign;
    string comment;
    string start_date;
    string end_date;
};

// Data
Account acc = {"", "", "", ""};
std::vector<Project> projects;
Project currProject;
std::vector<Task> currTask;
std::vector<Account> currMember;

void notify(const int& success, const string& content) {
    string status;
    if (success) status = "[SUCCESS] ";
    else status = "[ERROR] ";

    QLabel *notify = new QLabel();
    notify->setText(QString::fromStdString(status + content));
    notify->show();

    QTimer *timer = new QTimer();
    timer->setSingleShot(true);

    QObject::connect(timer, &QTimer::timeout, [notify, timer]() {
        notify->hide();
        notify->deleteLater();
        timer->deleteLater();
    });

    timer->start(2000);
}

void getAllProjectList(const QWidget& screen) {
    std::string res = performGetProjectList(acc.session);
    QString jsonString = QString::fromStdString(res);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    if (!jsonDoc.isNull()) {
        if (jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            int success = jsonObj["success"].toInt();
            QString message = jsonObj["message"].toString();
            if (!success) {
                QMessageBox::critical(nullptr, "Error", message);
            } else {
                QJsonArray dataArr = jsonObj["data"].toArray();
                QTableView *tableView = screen.findChild<QTableView*>("project_list");
                QStandardItemModel *model = new QStandardItemModel();

                model->setHorizontalHeaderLabels({ "ProjectId", "Name", "Owner", "Action" });

                qDebug() << "Loading projects : " << dataArr.size();

                for (int i = 0; i < dataArr.size(); i++) {
                    QJsonObject prjObj = dataArr[i].toObject();
                    Project prjN;
                    prjN.id = prjObj["id"].toString().toStdString();
                    prjN.name = prjObj["name"].toString().toStdString();
                    prjN.id_owner = prjObj["id_owner"].toString().toStdString();

                    std::string user_res = performGetUserById(prjN.id_owner);
                    QString jsonString = QString::fromStdString(user_res);
                    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
                    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                        QJsonObject jsonObj = jsonDoc.object();
                        int success = jsonObj["success"].toInt();
                        if (success) {
                            QJsonObject jsonData = jsonObj["data"].toObject();
                            string owner = jsonData["username"].toString().toStdString();
                            if (!owner.empty()) prjN.owner = owner;
                        }
                    }

                    projects.push_back(prjN);

                    QStandardItem *idItem = new QStandardItem(QString::fromStdString(prjN.id));
                    QStandardItem *nameItem = new QStandardItem(QString::fromStdString(prjN.name));
                    QString owner = prjN.id_owner == acc.id ? QString::fromStdString("You") : QString::fromStdString(prjN.owner);
                    QStandardItem *ownerItem = new QStandardItem(owner);
                    model->setItem(i, 0, idItem);
                    model->setItem(i, 1, nameItem);
                    model->setItem(i, 2, ownerItem);
                }

                tableView->setModel(model);
            }
        }
    }
}

void getMemberList(const QWidget* screen) {
    // Get member list
    std::string member_res = performGetMemberList(acc.session, currProject.id);
    QString memberJsonString = QString::fromStdString(member_res);
    QJsonDocument memberJsonDoc = QJsonDocument::fromJson(memberJsonString.toUtf8());
    if (!memberJsonDoc.isNull()) {
        if (memberJsonDoc.isObject()) {
            QJsonObject jsonObj = memberJsonDoc.object();
            int success = jsonObj["success"].toInt();
            QString message = jsonObj["message"].toString();
            if (!success) {
                QMessageBox::critical(nullptr, "Error", message);
            } else {
                QJsonArray dataArr = jsonObj["data"].toArray();
                QTableView *tableView = screen->findChild<QTableView*>("member_table");
                QStandardItemModel *model = new QStandardItemModel();

                model->setHorizontalHeaderLabels({ "UserId", "Username", "Action" });

                qDebug() << "Loading members : " << dataArr.size();

                for (int i = 0; i < dataArr.size(); i++) {
                    QJsonObject userObj = dataArr[i].toObject();
                    Account user;
                    user.id = userObj["id"].toString().toStdString();
                    user.username = userObj["username"].toString().toStdString();

                    currMember.push_back(user);

                    QStandardItem *idItem = new QStandardItem(QString::fromStdString(user.id));
                    QStandardItem *usernameItem = new QStandardItem(QString::fromStdString(user.username));
                    model->setItem(i, 0, idItem);
                    model->setItem(i, 1, usernameItem);
                }

                tableView->setModel(model);
            }
        }
    }
}

void getTaskList(const QWidget* screen) {
    // Get task list
    std::string task_res = performGetTaskList(acc.session, currProject.id);
    QString taskJsonString = QString::fromStdString(task_res);
    QJsonDocument taskJsonDoc = QJsonDocument::fromJson(taskJsonString.toUtf8());
    if (!taskJsonDoc.isNull()) {
        if (taskJsonDoc.isObject()) {
            QJsonObject jsonObj = taskJsonDoc.object();
            int success = jsonObj["success"].toInt();
            QString message = jsonObj["message"].toString();
            if (!success) {
                QMessageBox::critical(nullptr, "Error", message);
            } else {
                QJsonArray dataArr = jsonObj["data"].toArray();
                QTableView *tableView = screen->findChild<QTableView*>("task_table");
                QStandardItemModel *model = new QStandardItemModel();

                model->setHorizontalHeaderLabels({ "TaskId", "Name", "Status", "Assignee", "Comment", "Deadline", "Action" });

                qDebug() << "Loading tasks : " << dataArr.size();

                for (int i = 0; i < dataArr.size(); i++) {
                    QJsonObject taskObj = dataArr[i].toObject();
                    Task task;
                    task.id = taskObj["id"].toString().toStdString();
                    task.id_project = taskObj["id_project"].toString().toStdString();
                    task.id_manager = taskObj["id_manager"].toString().toStdString();
                    task.name = taskObj["name"].toString().toStdString();
                    task.status = taskObj["status"].toString().toStdString();
                    task.id_assign = taskObj["id_assign"].toString().toStdString();
                    task.comment = taskObj["comment"].toString().toStdString();
                    task.start_date = taskObj["start_date"].toString().toStdString();
                    task.end_date = taskObj["end_date"].toString().toStdString();

                    currTask.push_back(task);

                    string assignee;
                    std::string user_res = performGetUserById(task.id_assign);
                    QString jsonString = QString::fromStdString(user_res);
                    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
                    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                        QJsonObject jsonObj = jsonDoc.object();
                        int success = jsonObj["success"].toInt();
                        if (success) {
                            QJsonObject jsonData = jsonObj["data"].toObject();
                            string owner = jsonData["username"].toString().toStdString();
                            if (!owner.empty()) assignee = owner;
                        }
                    }

                    QStandardItem *idItem = new QStandardItem(QString::fromStdString(task.id));
                    QStandardItem *nameItem = new QStandardItem(QString::fromStdString(task.name));
                    QStandardItem *statusItem = new QStandardItem(QString::fromStdString(task.status));
                    QStandardItem *assigneeItem = new QStandardItem(QString::fromStdString(assignee));
                    QStandardItem *commentItem = new QStandardItem(QString::fromStdString(task.comment));
                    QStandardItem *end_dateItem = new QStandardItem(QString::fromStdString(task.end_date));
                    model->setItem(i, 0, idItem);
                    model->setItem(i, 1, nameItem);
                    model->setItem(i, 2, statusItem);
                    model->setItem(i, 3, assigneeItem);
                    model->setItem(i, 4, commentItem);
                    model->setItem(i, 5, end_dateItem);
                }

                tableView->setModel(model);
            }
        }
    }
}

string parseMessages(const string& res)
{
    QString jsonString = QString::fromStdString(res);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    if (!jsonDoc.isNull()) {
        if (jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            int success = jsonObj["success"].toInt();
            if (success == 1) {
                QJsonArray dataArray = jsonObj["data"].toArray();
                QString messagesString;
                for (const QJsonValue& value : dataArray) {
                    QJsonObject messageObj = value.toObject();
                    QString content = messageObj["content"].toString();
                    QString username = messageObj["username"].toString();
                    QString time = messageObj["time"].toString();
                    QString messageDetails = QString("Username: %1\nTime: %2\nContent: %3\n\n")
                                                 .arg(username, time, content);

                    messagesString.append(messageDetails);
                }
                return messagesString.toStdString();
            }
        }
    }

    return "";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    // Screen
    LoginScreen loginScreen;
    RegisterScreen registerScreen;
    ProjectListScreen projectListScreen;
    ProjectDetails projectDetailsScreen;
    ProjectForm projectFormPopup;
    MemberForm memberFormPopup;
    TaskForm taskCreateFormPopup;

    QObject::connect(&loginScreen, &LoginScreen::moveToRegisterClicked, [&]() {
        registerScreen.show();
        loginScreen.hide();
    });

    QObject::connect(&registerScreen, &RegisterScreen::moveToLoginClicked, [&]() {
        loginScreen.show();
        registerScreen.hide();
    });

    QObject::connect(&loginScreen, &LoginScreen::loginButtonClicked, [&](const QString& username, const QString& password) {
        std::string usernameStr = username.toStdString();
        std::string passwordStr = password.toStdString();
        std::string res = performLogin(usernameStr, passwordStr);

        QString jsonString = QString::fromStdString(res);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonDoc.isNull()) {
            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                int success = jsonObj["success"].toInt();
                QString message = jsonObj["message"].toString();
                if(!success){
                    QMessageBox::critical(nullptr, "Error", message);
                } else {
                    QJsonObject dataObj = jsonObj["data"].toObject();
                    acc.id = dataObj["id"].toString().toStdString();
                    acc.username = dataObj["username"].toString().toStdString();
                    acc.password = dataObj["password"].toString().toStdString();
                    acc.session = dataObj["session"].toString().toStdString();

                    QLabel *usernameHead = projectListScreen.findChild<QLabel*>("username_head");
                    usernameHead->setText(QString::fromStdString(acc.username));
                    loginScreen.hide();
                    projectListScreen.show();
                    // QMessageBox::information(nullptr, "Success", message);
                }
            }
        }
    });

    QObject::connect(&registerScreen, &RegisterScreen::registerButtonClicked, [&](const QString& username, const QString& password) {
        string usernameStr = username.toStdString();
        string passwordStr = password.toStdString();
        string res = performRegister(usernameStr, passwordStr);

        QString jsonString = QString::fromStdString(res);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonDoc.isNull()) {
            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                int success = jsonObj["success"].toInt();
                QString message = jsonObj["message"].toString();
                if(!success){
                    QMessageBox::critical(nullptr, "Error", message);
                } else {
                    registerScreen.hide();
                    loginScreen.show();
                    QMessageBox::information(nullptr, "Success", message);
                }
            }
        }
    });

    loginScreen.show();

    QObject::connect(&projectListScreen, &ProjectListScreen::widgetShown, [&]() {
        getAllProjectList(projectListScreen);
    });

    QObject::connect(&projectListScreen, &ProjectListScreen::logout, [&]() {
        string res = performLogout(acc.session);

        QString jsonString = QString::fromStdString(res);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonDoc.isNull()) {
            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                int success = jsonObj["success"].toInt();
                QString message = jsonObj["message"].toString();
                if(!success){
                    QMessageBox::critical(nullptr, "Error", message);
                } else {
                    projectListScreen.hide();
                    loginScreen.show();
                    QMessageBox::information(nullptr, "Success", message);
                }
            }
        }
    });

    QObject::connect(&projectListScreen, &ProjectListScreen::destroyed, [&]() {
        string res = performLogout(acc.session);

        QString jsonString = QString::fromStdString(res);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonDoc.isNull()) {
            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                int success = jsonObj["success"].toInt();
                QString message = jsonObj["message"].toString();
                if(!success){
                    QMessageBox::critical(nullptr, "Error", message);
                }
            }
        }
    });

    QPushButton *chatBtn = projectDetailsScreen.findChild<QPushButton*>("chat_btn"); // 0
    QPushButton *memberBtn = projectDetailsScreen.findChild<QPushButton*>("member_btn"); // 1
    QPushButton *taskBtn = projectDetailsScreen.findChild<QPushButton*>("task_btn"); // 2

    QStackedWidget *projectStackWidget = projectDetailsScreen.findChild<QStackedWidget*>("project_stackwidget");

    QWidget *chatWidget = projectDetailsScreen.findChild<QWidget*>("chat");
    QWidget *memberWidget = projectDetailsScreen.findChild<QWidget*>("member");
    QWidget *taskWidget = projectDetailsScreen.findChild<QWidget*>("task");

    int chat_index = projectStackWidget->indexOf(chatWidget);
    int member_index = projectStackWidget->indexOf(memberWidget);
    int task_index = projectStackWidget->indexOf(taskWidget);

    QPushButton *addMemberBtn = memberWidget->findChild<QPushButton*>("add_member_btn");
    QPushButton *addTaskBtn = taskWidget->findChild<QPushButton*>("add_task_btn");

    QObject::connect(chatBtn, &QPushButton::clicked, [projectStackWidget, chat_index]() {
        projectStackWidget->setCurrentIndex(chat_index);
        qDebug() << "Change to Chat Widget";
    });
    QObject::connect(memberBtn, &QPushButton::clicked, [projectStackWidget, member_index]() {
        projectStackWidget->setCurrentIndex(member_index);
        qDebug() << "Change to Member Widget";
    });
    QObject::connect(taskBtn, &QPushButton::clicked, [projectStackWidget, task_index]() {
        projectStackWidget->setCurrentIndex(task_index);
        qDebug() << "Change to Task Widget";
    });

    // Add member

    QJsonArray allMembers;
    QObject::connect(addMemberBtn, &QPushButton::clicked, [&]() {
        memberFormPopup.show();
        QComboBox *memberCombobox = memberFormPopup.findChild<QComboBox*>("input_list_member");
        memberCombobox->clear();
        memberCombobox->clearEditText();

        qDebug() << "Get all user";
        std::string user_res = performGetAllUser(acc.session, currProject.id);
        QString jsonString = QString::fromStdString(user_res);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            int success = jsonObj["success"].toInt();
            QString message = jsonObj["message"].toString();
            if (!success) {
                notify(success, message.toStdString());
            } else {
                QJsonArray userArr = jsonObj["data"].toArray();
                qDebug() << "Total: " << userArr.size();
                for (int i = 0; i < userArr.size(); i++) {
                    QJsonObject user = userArr[i].toObject();
                    qDebug() << "Adding " << user["username"].toString().toStdString();
                    allMembers.insert(i, user);
                    memberCombobox->addItem(user["username"].toString());
                }
            }
        }
    });

    QObject::connect(&memberFormPopup, &MemberForm::handleAccept, [&]() {
        QComboBox *combobox = memberFormPopup.findChild<QComboBox*>("input_list_member");
        int index = combobox->currentIndex();
        if (!allMembers[index].isNull() && allMembers[index].isObject()) {
            QJsonObject user = allMembers[index].toObject();
            std::string create_res = performAddMember(acc.session, currProject.id, user["id"].toString().toStdString());
            QString jsonString = QString::fromStdString(create_res);
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                int success = jsonObj["success"].toInt();
                QString message = jsonObj["message"].toString();

                notify(success, message.toStdString());

                if (success) {
                    getMemberList(memberWidget);
                }
            }
        }

        memberFormPopup.hide();
    });

    QObject::connect(&memberFormPopup, &MemberForm::handleReject, [&]() {
        memberFormPopup.hide();
    });

    // Add task
    QJsonArray allAssign;
    QObject::connect(addTaskBtn, &QPushButton::clicked, [&]() {
        taskCreateFormPopup.show();
        QComboBox *assignCombobox = taskCreateFormPopup.findChild<QComboBox*>("comboBox_2");
        assignCombobox->clear();
        assignCombobox->clearEditText();

        std::string user_res = performGetUserToAddTask(acc.session, currProject.id);
        QString jsonString = QString::fromStdString(user_res);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            int success = jsonObj["success"].toInt();
            QString message = jsonObj["message"].toString();
            if (!success) {
                notify(success, message.toStdString());
            } else {
                QJsonArray userArr = jsonObj["data"].toArray();
                qDebug() << "Total: " << userArr.size();
                assignCombobox->addItem("");
                for (int i = 0; i < userArr.size(); i++) {
                    QJsonObject user = userArr[i].toObject();
                    allAssign.insert(i+1, user);
                    assignCombobox->addItem(user["username"].toString());
                }
            }
        }
    });

    QObject::connect(&taskCreateFormPopup, &TaskForm::handleAccept, [&](const string& name, const string& status, const string& start_date, const string& end_date, const string& comment, const string& id_assign) {
        QComboBox *combobox = taskCreateFormPopup.findChild<QComboBox*>("comboBox_2");
        int index = combobox->currentIndex();
        if (!allAssign[index].isNull() && allAssign[index].isObject()) {
            QJsonObject assign = allAssign[index].toObject();
            std::string create_res = performAddTask(acc.session, currProject.id, name, status, start_date, end_date, comment, assign["id"].toString().toStdString());
            QString jsonString = QString::fromStdString(create_res);
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                int success = jsonObj["success"].toInt();
                QString message = jsonObj["message"].toString();

                notify(success, message.toStdString());

                if (success) {
                    getTaskList(taskWidget);
                    taskCreateFormPopup.hide();
                }
            }
        }
    });

    QObject::connect(&taskCreateFormPopup, &TaskForm::handleReject, [&]() {
        taskCreateFormPopup.hide();
    });

    QPushButton *createProjectBtn = projectListScreen.findChild<QPushButton*>("create_project_btn");

    QObject::connect(createProjectBtn, &QPushButton::clicked, [&]() {
        projectFormPopup.show();
        QLineEdit *input = projectFormPopup.findChild<QLineEdit*>("input_project_name");
        input->clear();
    });

    QObject::connect(&projectFormPopup, &ProjectForm::handleAccept, [&]() {
        QLineEdit *input = projectFormPopup.findChild<QLineEdit*>("input_project_name");
        std::string create_res = performCreateProject(acc.session, input->text().toStdString());
        QString jsonString = QString::fromStdString(create_res);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            int success = jsonObj["success"].toInt();
            QString message = jsonObj["message"].toString();

            notify(success, message.toStdString());

            if (success) {
                getAllProjectList(projectListScreen);
            }
        }

        projectFormPopup.hide();
    });

    QObject::connect(&projectFormPopup, &ProjectForm::handleReject, [&]() {
        projectFormPopup.hide();
    });

    QObject::connect(&projectListScreen, &ProjectListScreen::doubleClick, [&](const QString& id) {
        qDebug() << "Double click " << id;
        currMember.clear();
        currTask.clear();
        currProject.id.clear();
        currProject.name.clear();
        currProject.id_owner.clear();
        currProject.owner.clear();

        auto it = std::find_if(projects.begin(), projects.end(), [&](const Project& p) {
            return p.id == id.toStdString();
        });

        if (it != projects.end()) {
            currProject.id = it->id;
            currProject.name = it->name;
            currProject.id_owner = it->id_owner;
            currProject.owner = it->owner;

            projectStackWidget->setCurrentIndex(task_index);
            projectDetailsScreen.show();
        }
    });

    QObject::connect(&projectDetailsScreen, &ProjectDetails::widgetShown, [&]() {
        getMemberList(memberWidget);
        getTaskList(taskWidget);
    });


    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "TaskManager_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    return a.exec();
}


