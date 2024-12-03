#ifndef MDPOUBLIE_H
#define MDPOUBLIE_H

#include <QDialog>

namespace Ui {
class mdpoublie;
}

class mdpoublie : public QDialog
{
    Q_OBJECT

public:
    explicit mdpoublie(QWidget *parent = nullptr);
    ~mdpoublie();
    bool verifyForgotPassword(const QString &id, const QString &salary);
    void resetPassword(const QString &id, const QString &newPassword);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::mdpoublie *ui;
};

#endif // MDPOUBLIE_H
