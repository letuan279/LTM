#ifndef PROJECTLISTSCREEN_H
#define PROJECTLISTSCREEN_H

#include <QWidget>

namespace Ui {
class ProjectListScreen;
}

class ProjectListScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectListScreen(QWidget *parent = nullptr);
    ~ProjectListScreen();

signals:
    void widgetShown();
    void doubleClick(const QString& id);

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_project_list_doubleClicked(const QModelIndex &index);

private:
    Ui::ProjectListScreen *ui;
};

#endif // PROJECTLISTSCREEN_H
