#ifndef CHATSCREEN_H
#define CHATSCREEN_H

#include <QDialog>

namespace Ui {
class chatscreen;
}

class chatscreen : public QDialog
{
    Q_OBJECT

public:
    explicit chatscreen(QWidget *parent = nullptr);
    ~chatscreen();

private:
    Ui::chatscreen *ui;
};

#endif // CHATSCREEN_H
