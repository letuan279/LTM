#include "projectlistscreen.h"
#include "ui_projectlistscreen.h"

ProjectListScreen::ProjectListScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProjectListScreen)
{
    ui->setupUi(this);
}

ProjectListScreen::~ProjectListScreen()
{
    delete ui;
}

void ProjectListScreen::showEvent(QShowEvent *event) {
    QWidget::show();

    emit widgetShown();
}

void ProjectListScreen::on_project_list_doubleClicked(const QModelIndex &index)
{
    QString id = index.model()->data(index.model()->index(index.row(), 0)).toString();
    emit doubleClick(id);
}


void ProjectListScreen::on_logout_btn_clicked()
{
    emit logout();
}

