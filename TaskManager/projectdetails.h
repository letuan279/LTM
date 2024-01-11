#ifndef PROJECTDETAILS_H
#define PROJECTDETAILS_H

#include <QWidget>

namespace Ui {
class ProjectDetails;
}

class ProjectDetails : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectDetails(QWidget *parent = nullptr);
    ~ProjectDetails();

signals:
    void widgetShown();
    void widgetChanged(const int& index);
    void doubleClick(const QString& id);
    void closeApp();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_project_stackwidget_currentChanged(int arg1);

    void on_task_table_doubleClicked(const QModelIndex &index);

private:
    Ui::ProjectDetails *ui;
};

#endif // PROJECTDETAILS_H
