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

private:
    Ui::ProjectForm *ui;
};

#endif // PROJECTFORM_H
