#ifndef MEMBERSCREEN_H
#define MEMBERSCREEN_H

#include <QWidget>

namespace Ui {
class MemberScreen;
}

class MemberScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MemberScreen(QWidget *parent = nullptr);
    ~MemberScreen();

private slots:
    void on_send_message_btn_clicked();

private:
    Ui::MemberScreen *ui;
};

#endif // MEMBERSCREEN_H
