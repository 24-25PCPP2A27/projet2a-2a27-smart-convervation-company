/********************************************************************************
** Form generated from reading UI file 'bienvenue.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIENVENUE_H
#define UI_BIENVENUE_H

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

class Ui_bienvenue
{
public:
    QLabel *label_2;
    QLineEdit *identifier;
    QLineEdit *password;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *rfidLabel;
    QLineEdit *post;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_3;
    QPushButton *pushButton_3;

    void setupUi(QDialog *bienvenue)
    {
        if (bienvenue->objectName().isEmpty())
            bienvenue->setObjectName(QStringLiteral("bienvenue"));
        bienvenue->resize(1182, 657);
        label_2 = new QLabel(bienvenue);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 0, 1191, 661));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/photo.png")));
        label_2->setScaledContents(true);
        identifier = new QLineEdit(bienvenue);
        identifier->setObjectName(QStringLiteral("identifier"));
        identifier->setGeometry(QRect(450, 180, 181, 41));
        password = new QLineEdit(bienvenue);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(450, 260, 181, 41));
        password->setEchoMode(QLineEdit::Password);
        label_4 = new QLabel(bienvenue);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(380, 420, 101, 16));
        label_6 = new QLabel(bienvenue);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(420, 60, 231, 81));
        label_6->setStyleSheet(QLatin1String("font: 20pt \"Sitka\";\n"
"background-color: rgb(157, 255, 177);\n"
"border-radius: 10px;"));
        rfidLabel = new QLabel(bienvenue);
        rfidLabel->setObjectName(QStringLiteral("rfidLabel"));
        rfidLabel->setGeometry(QRect(520, 410, 151, 31));
        rfidLabel->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"border-radius: 10px;"));
        post = new QLineEdit(bienvenue);
        post->setObjectName(QStringLiteral("post"));
        post->setGeometry(QRect(450, 330, 181, 41));
        post->setEchoMode(QLineEdit::Normal);
        pushButton = new QPushButton(bienvenue);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(370, 480, 131, 41));
        pushButton->setStyleSheet(QLatin1String("\n"
"background-color: rgb(85, 170, 0);\n"
"\n"
"color: rgb(255, 255, 255);\n"
"\n"
"border-radius: 10px;"));
        pushButton_2 = new QPushButton(bienvenue);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(550, 480, 121, 41));
        pushButton_2->setStyleSheet(QLatin1String("background-color: rgb(85, 170, 0);\n"
"color: rgb(255, 255, 255);\n"
"\n"
"border-radius: 10px;"));
        label = new QLabel(bienvenue);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 230, 56, 16));
        label_3 = new QLabel(bienvenue);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 10, 241, 121));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/photo2.png")));
        label_3->setScaledContents(true);
        pushButton_3 = new QPushButton(bienvenue);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(650, 260, 131, 41));
        pushButton_3->setStyleSheet(QLatin1String("\n"
"background-color: rgb(85, 170, 0);\n"
"\n"
"color: rgb(255, 255, 255);\n"
"\n"
"border-radius: 10px;"));

        retranslateUi(bienvenue);

        QMetaObject::connectSlotsByName(bienvenue);
    } // setupUi

    void retranslateUi(QDialog *bienvenue)
    {
        bienvenue->setWindowTitle(QApplication::translate("bienvenue", "Dialog", Q_NULLPTR));
        label_2->setText(QString());
        identifier->setPlaceholderText(QApplication::translate("bienvenue", "E-MAIL", Q_NULLPTR));
        password->setPlaceholderText(QApplication::translate("bienvenue", "MOT DE PASSE", Q_NULLPTR));
        label_4->setText(QApplication::translate("bienvenue", "VOTRE RFID :", Q_NULLPTR));
        label_6->setText(QApplication::translate("bienvenue", "  BIENVENUE", Q_NULLPTR));
        rfidLabel->setText(QString());
        post->setPlaceholderText(QApplication::translate("bienvenue", "POST", Q_NULLPTR));
        pushButton->setText(QApplication::translate("bienvenue", "connecter", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("bienvenue", "annuler", Q_NULLPTR));
        label->setText(QString());
        label_3->setText(QString());
        pushButton_3->setText(QApplication::translate("bienvenue", "mot de passe oublie", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class bienvenue: public Ui_bienvenue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIENVENUE_H
