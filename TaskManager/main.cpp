// #include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

#include "loginscreen.h"
#include "registerscreen.h"
#include "projectlist.h"

#include "call.h"

using namespace std;

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
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Data
    Account acc = {"", "", "", ""};
    // Project projects;

    // Screen
    LoginScreen loginScreen;
    RegisterScreen registerScreen;
    ProjectList projectListScreen;

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

        qDebug() << res;

    });

    loginScreen.show();

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
