#ifndef TASKFORM_H
#define TASKFORM_H

#include <QWidget>

using namespace std;

namespace Ui {
class TaskForm;
}

class TaskForm : public QWidget
{
    Q_OBJECT

public:
    explicit TaskForm(QWidget *parent = nullptr);
    ~TaskForm();

signals:
    void handleAccept(const string& name, const string& status, const string& start_date, const string& end_date, const string& comment, const string& id_assign);
    void handleReject();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::TaskForm *ui;
};

#endif // TASKFORM_H
