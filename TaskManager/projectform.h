#ifndef PROJECTFORM_H
#define PROJECTFORM_H

#include <QDialog>

namespace Ui {
class ProjectForm;
}

class ProjectForm : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectForm(QWidget *parent = nullptr);
    ~ProjectForm();

signals:
    void handleAccept();
    void handleReject();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ProjectForm *ui;
};

#endif // PROJECTFORM_H
