#ifndef PROJECTLISTSCREEN_H
#define PROJECTLISTSCREEN_H

#include <QDialog>

namespace Ui {
class projectlistscreen;
}

class projectlistscreen : public QDialog
{
    Q_OBJECT

public:
    explicit projectlistscreen(QWidget *parent = nullptr);
    ~projectlistscreen();

private:
    Ui::projectlistscreen *ui;
};

#endif // PROJECTLISTSCREEN_H
