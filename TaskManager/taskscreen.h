#ifndef TASKSCREEN_H
#define TASKSCREEN_H

#include <QDialog>

namespace Ui {
class taskscreen;
}

class taskscreen : public QDialog
{
    Q_OBJECT

public:
    explicit taskscreen(QWidget *parent = nullptr);
    ~taskscreen();

private:
    Ui::taskscreen *ui;
};

#endif // TASKSCREEN_H
