#include "mdpoublie.h"
#include "ui_mdpoublie.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

mdpoublie::mdpoublie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mdpoublie)
{
    ui->setupUi(this);
    // Initially hide password fields and their labels
    ui->mdp1->setVisible(false);
    ui->mdp2->setVisible(false);
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
     ui->pushButton_2->setVisible(false);
     connect(ui->pushButton, &QPushButton::clicked, this, &mdpoublie::on_pushButton_clicked);
     connect(ui->pushButton_2, &QPushButton::clicked, this, &mdpoublie::on_pushButton_2_clicked);

}

mdpoublie::~mdpoublie()
{
    delete ui;
}

void mdpoublie::on_pushButton_clicked()
{
    QString id = ui->id->text();        // Get ID
    QString salary = ui->salaire->text(); // Get Salary

    if (id.isEmpty() || salary.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill both ID and Salary fields.");
        return;
    }
    if (verifyForgotPassword(id, salary)) {
        QMessageBox::information(this, "Verification", "ID and Salary verified successfully!");

        // Make password fields and labels visible
        ui->mdp1->setVisible(true);
        ui->mdp2->setVisible(true);

        ui->pushButton_2->setEnabled(true);
        ui->pushButton_2->setVisible(true);

        // Disable ID and salary fields after successful verification
        ui->id->setEnabled(false);
        ui->salaire->setEnabled(false);

        // Hide and disable the verify button
        ui->pushButton->setVisible(false);  // Hide the button
        ui->pushButton->setEnabled(false); // Disable the button to prevent clicks
    } else {
        QMessageBox::warning(this, "Error", "Invalid ID or Salary. Please try again.");
    }

}


void mdpoublie::on_pushButton_2_clicked()
{
    QString newPassword = ui->mdp1->text();       // Get New Password
    QString retypePassword = ui->mdp2->text(); // Get Retype Password
    QString id = ui->id->text();                         // ID remains available after verification

    // Validate passwords
    if (newPassword.isEmpty() || retypePassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all password fields.");
        return;
    }

    if (newPassword != retypePassword) {
        QMessageBox::warning(this, "Error", "Passwords do not match. Please try again.");
        return;
    }

    if (newPassword.length() < 6) {
        QMessageBox::warning(this, "Error", "Password must be at least 6 characters long.");
        return;
    }

    // Reset password in the database
    resetPassword(id, newPassword);
    QMessageBox::information(this, "Success", "Password reset successfully!");

    accept();  // Close dialog
}





bool mdpoublie::verifyForgotPassword(const QString &id, const QString &salary)
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM EMPLOYE WHERE IDEM = :id AND SALAIRE = :salary");
    query.bindValue(":id", id);
    query.bindValue(":salary", salary);

    if (!query.exec()) {
        qDebug() << "Query execution failed: " << query.lastError().text();
        return false;
    }

    return query.next();  // Return true if the ID and salary match a record
}

void mdpoublie::resetPassword(const QString &id, const QString &newPassword)
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET MOT_DE_PASSE = :newPassword WHERE IDEM = :id");
    query.bindValue(":newPassword", newPassword);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Password reset query failed: " << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to reset password: " + query.lastError().text());
    }
}

