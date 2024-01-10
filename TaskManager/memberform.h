#ifndef MEMBERFORM_H
#define MEMBERFORM_H

#include <QDialog>

namespace Ui {
class MemberForm;
}

class MemberForm : public QDialog
{
    Q_OBJECT

public:
    explicit MemberForm(QWidget *parent = nullptr);
    ~MemberForm();

signals:
    void handleAccept();
    void handleReject();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::MemberForm *ui;
};

#endif // MEMBERFORM_H
