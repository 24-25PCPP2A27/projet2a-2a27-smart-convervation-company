/********************************************************************************
** Form generated from reading UI file 'mdpoublie.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MDPOUBLIE_H
#define UI_MDPOUBLIE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_mdpoublie
{
public:
    QLineEdit *salaire;
    QLineEdit *id;
    QLineEdit *mdp1;
    QLineEdit *mdp2;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *mdpoublie)
    {
        if (mdpoublie->objectName().isEmpty())
            mdpoublie->setObjectName(QStringLiteral("mdpoublie"));
        mdpoublie->resize(812, 547);
        mdpoublie->setStyleSheet(QStringLiteral("background-color: rgb(170, 255, 127);"));
        salaire = new QLineEdit(mdpoublie);
        salaire->setObjectName(QStringLiteral("salaire"));
        salaire->setGeometry(QRect(310, 180, 141, 31));
        salaire->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        id = new QLineEdit(mdpoublie);
        id->setObjectName(QStringLiteral("id"));
        id->setGeometry(QRect(310, 260, 141, 31));
        id->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        mdp1 = new QLineEdit(mdpoublie);
        mdp1->setObjectName(QStringLiteral("mdp1"));
        mdp1->setGeometry(QRect(310, 260, 141, 31));
        mdp1->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        mdp2 = new QLineEdit(mdpoublie);
        mdp2->setObjectName(QStringLiteral("mdp2"));
        mdp2->setGeometry(QRect(310, 180, 141, 31));
        mdp2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label = new QLabel(mdpoublie);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(160, 50, 491, 71));
        label->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"font: 75 20pt \"MS Shell Dlg 2\";"));
        pushButton = new QPushButton(mdpoublie);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(320, 420, 131, 51));
        pushButton->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        pushButton_2 = new QPushButton(mdpoublie);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(320, 420, 131, 51));
        pushButton_2->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));

        retranslateUi(mdpoublie);

        QMetaObject::connectSlotsByName(mdpoublie);
    } // setupUi

    void retranslateUi(QDialog *mdpoublie)
    {
        mdpoublie->setWindowTitle(QApplication::translate("mdpoublie", "Dialog", Q_NULLPTR));
        salaire->setPlaceholderText(QApplication::translate("mdpoublie", "salaire", Q_NULLPTR));
        id->setPlaceholderText(QApplication::translate("mdpoublie", "identiant", Q_NULLPTR));
        mdp1->setPlaceholderText(QApplication::translate("mdpoublie", "mot de passe", Q_NULLPTR));
        mdp2->setPlaceholderText(QApplication::translate("mdpoublie", "nouveau mdp", Q_NULLPTR));
        label->setText(QApplication::translate("mdpoublie", "      MOT DE PASSE OUBLIEE", Q_NULLPTR));
        pushButton->setText(QApplication::translate("mdpoublie", "verifier", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("mdpoublie", "conneter", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mdpoublie: public Ui_mdpoublie {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MDPOUBLIE_H
