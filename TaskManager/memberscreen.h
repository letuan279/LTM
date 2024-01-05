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

private:
    Ui::MemberScreen *ui;
};

#endif // MEMBERSCREEN_H
