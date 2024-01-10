#ifndef REGISTERSCREEN_H
#define REGISTERSCREEN_H

#include <QWidget>

namespace Ui {
class RegisterScreen;
}

class RegisterScreen : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterScreen(QWidget *parent = nullptr);
    ~RegisterScreen();

signals:
    void moveToLoginClicked();
    void registerButtonClicked(const QString& username, const QString& password);
private slots:
    void on_moveto_login_clicked();
    void on_btn_register_clicked();

private:
    Ui::RegisterScreen *ui;
};

#endif // REGISTERSCREEN_H
