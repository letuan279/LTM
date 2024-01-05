#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>

namespace Ui {
class LoginScreen;
}

class LoginScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LoginScreen(QWidget *parent = nullptr);
    ~LoginScreen();

signals:
    void moveToRegisterClicked();
    void loginButtonClicked(const QString& username, const QString& password);

private slots:
    void on_moveto_register_clicked();
    void on_btn_login_clicked();

private:
    Ui::LoginScreen *ui;
};

#endif // LOGINSCREEN_H
