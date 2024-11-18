/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *qrcodecommande_2t;
    QWidget *tab;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_12;
    QLineEdit *id;
    QLineEdit *duree;
    QLineEdit *tmpMax;
    QLineEdit *tmpMin;
    QLineEdit *prix;
    QPushButton *pushButton;
    QComboBox *type;
    QTableView *tab_6;
    QPushButton *pushButton_3;
    QLineEdit *id_supp;
    QPushButton *suprimer;
    QWidget *tab_2;
    QTableView *tab_5;
    QPushButton *afficher;
    QLineEdit *rech_id;
    QLabel *label_6;
    QWidget *tab_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *stats_3;
    QPushButton *stats;
    QWidget *tab_4;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *id_2;
    QLineEdit *type_2;
    QLineEdit *duree_2;
    QLineEdit *tmpMax_2;
    QLineEdit *tempMin_2;
    QPushButton *modifier;
    QLabel *label_13;
    QLineEdit *prix_2;
    QWidget *tab_7;
    QLabel *label_14;
    QTableView *tab_rech;
    QPushButton *rechercher;
    QWidget *tab_8;
    QPushButton *trier;
    QLabel *label_15;
    QCheckBox *tri_duree;
    QTableView *tab_tri;
    QWidget *tab_9;
    QPushButton *qrCode;
    QLineEdit *qr_code_bar;
    QLabel *qrcodecommande_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1210, 665);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        qrcodecommande_2t = new QTabWidget(centralWidget);
        qrcodecommande_2t->setObjectName(QStringLiteral("qrcodecommande_2t"));
        qrcodecommande_2t->setGeometry(QRect(10, 70, 1161, 521));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 30, 381, 431));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 60, 191, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 100, 171, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 140, 131, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 180, 141, 20));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 230, 121, 20));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 270, 56, 16));
        id = new QLineEdit(groupBox);
        id->setObjectName(QStringLiteral("id"));
        id->setGeometry(QRect(210, 60, 113, 25));
        duree = new QLineEdit(groupBox);
        duree->setObjectName(QStringLiteral("duree"));
        duree->setGeometry(QRect(210, 140, 113, 25));
        tmpMax = new QLineEdit(groupBox);
        tmpMax->setObjectName(QStringLiteral("tmpMax"));
        tmpMax->setGeometry(QRect(210, 180, 113, 25));
        tmpMin = new QLineEdit(groupBox);
        tmpMin->setObjectName(QStringLiteral("tmpMin"));
        tmpMin->setGeometry(QRect(210, 230, 113, 25));
        prix = new QLineEdit(groupBox);
        prix->setObjectName(QStringLiteral("prix"));
        prix->setGeometry(QRect(210, 270, 113, 22));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(100, 330, 112, 34));
        type = new QComboBox(groupBox);
        type->setObjectName(QStringLiteral("type"));
        type->setGeometry(QRect(210, 100, 111, 31));
        tab_6 = new QTableView(tab);
        tab_6->setObjectName(QStringLiteral("tab_6"));
        tab_6->setGeometry(QRect(390, 40, 731, 381));
        pushButton_3 = new QPushButton(tab);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(410, 430, 112, 34));
        id_supp = new QLineEdit(tab);
        id_supp->setObjectName(QStringLiteral("id_supp"));
        id_supp->setGeometry(QRect(1000, 440, 113, 25));
        suprimer = new QPushButton(tab);
        suprimer->setObjectName(QStringLiteral("suprimer"));
        suprimer->setGeometry(QRect(810, 430, 181, 41));
        qrcodecommande_2t->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tab_5 = new QTableView(tab_2);
        tab_5->setObjectName(QStringLiteral("tab_5"));
        tab_5->setGeometry(QRect(50, 130, 811, 351));
        afficher = new QPushButton(tab_2);
        afficher->setObjectName(QStringLiteral("afficher"));
        afficher->setGeometry(QRect(50, 60, 211, 51));
        rech_id = new QLineEdit(tab_2);
        rech_id->setObjectName(QStringLiteral("rech_id"));
        rech_id->setGeometry(QRect(720, 70, 131, 41));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(630, 90, 69, 20));
        qrcodecommande_2t->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayoutWidget = new QWidget(tab_3);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(40, 20, 1061, 381));
        stats_3 = new QVBoxLayout(verticalLayoutWidget);
        stats_3->setSpacing(6);
        stats_3->setContentsMargins(11, 11, 11, 11);
        stats_3->setObjectName(QStringLiteral("stats_3"));
        stats_3->setContentsMargins(0, 0, 0, 0);
        stats = new QPushButton(tab_3);
        stats->setObjectName(QStringLiteral("stats"));
        stats->setGeometry(QRect(470, 420, 141, 51));
        qrcodecommande_2t->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        label_7 = new QLabel(tab_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 40, 171, 20));
        label_8 = new QLabel(tab_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(40, 90, 141, 20));
        label_9 = new QLabel(tab_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(18, 140, 141, 20));
        label_10 = new QLabel(tab_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(40, 190, 171, 20));
        label_11 = new QLabel(tab_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(30, 240, 121, 20));
        id_2 = new QLineEdit(tab_4);
        id_2->setObjectName(QStringLiteral("id_2"));
        id_2->setGeometry(QRect(180, 40, 113, 25));
        type_2 = new QLineEdit(tab_4);
        type_2->setObjectName(QStringLiteral("type_2"));
        type_2->setGeometry(QRect(180, 90, 113, 25));
        duree_2 = new QLineEdit(tab_4);
        duree_2->setObjectName(QStringLiteral("duree_2"));
        duree_2->setGeometry(QRect(180, 140, 113, 25));
        tmpMax_2 = new QLineEdit(tab_4);
        tmpMax_2->setObjectName(QStringLiteral("tmpMax_2"));
        tmpMax_2->setGeometry(QRect(180, 190, 113, 25));
        tempMin_2 = new QLineEdit(tab_4);
        tempMin_2->setObjectName(QStringLiteral("tempMin_2"));
        tempMin_2->setGeometry(QRect(180, 240, 113, 25));
        modifier = new QPushButton(tab_4);
        modifier->setObjectName(QStringLiteral("modifier"));
        modifier->setGeometry(QRect(110, 370, 151, 41));
        label_13 = new QLabel(tab_4);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(50, 290, 56, 16));
        prix_2 = new QLineEdit(tab_4);
        prix_2->setObjectName(QStringLiteral("prix_2"));
        prix_2->setGeometry(QRect(180, 290, 113, 22));
        qrcodecommande_2t->addTab(tab_4, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        label_14 = new QLabel(tab_7);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(30, 80, 191, 20));
        tab_rech = new QTableView(tab_7);
        tab_rech->setObjectName(QStringLiteral("tab_rech"));
        tab_rech->setGeometry(QRect(115, 160, 891, 291));
        rechercher = new QPushButton(tab_7);
        rechercher->setObjectName(QStringLiteral("rechercher"));
        rechercher->setGeometry(QRect(640, 80, 93, 28));
        qrcodecommande_2t->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        trier = new QPushButton(tab_8);
        trier->setObjectName(QStringLiteral("trier"));
        trier->setGeometry(QRect(440, 90, 121, 31));
        label_15 = new QLabel(tab_8);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(170, 90, 121, 20));
        tri_duree = new QCheckBox(tab_8);
        tri_duree->setObjectName(QStringLiteral("tri_duree"));
        tri_duree->setGeometry(QRect(320, 90, 21, 20));
        tab_tri = new QTableView(tab_8);
        tab_tri->setObjectName(QStringLiteral("tab_tri"));
        tab_tri->setGeometry(QRect(150, 150, 841, 311));
        qrcodecommande_2t->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName(QStringLiteral("tab_9"));
        qrCode = new QPushButton(tab_9);
        qrCode->setObjectName(QStringLiteral("qrCode"));
        qrCode->setGeometry(QRect(380, 430, 161, 41));
        qr_code_bar = new QLineEdit(tab_9);
        qr_code_bar->setObjectName(QStringLiteral("qr_code_bar"));
        qr_code_bar->setGeometry(QRect(550, 430, 131, 41));
        qrcodecommande_2 = new QLabel(tab_9);
        qrcodecommande_2->setObjectName(QStringLiteral("qrcodecommande_2"));
        qrcodecommande_2->setGeometry(QRect(320, 90, 461, 321));
        qrcodecommande_2t->addTab(tab_9, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1210, 30));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        qrcodecommande_2t->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Gestion des Clients", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Ajouter traitement", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "identifiant de traitement:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "type de traitement :", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "duree de traitement  :", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "temperature_max :", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "temperature_min:", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Prix:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Ajouter", Q_NULLPTR));
        type->clear();
        type->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "refrigeration", Q_NULLPTR)
         << QApplication::translate("MainWindow", "congelation", Q_NULLPTR)
         << QApplication::translate("MainWindow", "stockage sous vide", Q_NULLPTR)
        );
        pushButton_3->setText(QApplication::translate("MainWindow", "pdf", Q_NULLPTR));
        suprimer->setText(QApplication::translate("MainWindow", "suprimer", Q_NULLPTR));
        qrcodecommande_2t->setTabText(qrcodecommande_2t->indexOf(tab), QApplication::translate("MainWindow", "Ajouter", Q_NULLPTR));
        afficher->setText(QApplication::translate("MainWindow", "Afficher", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "rech", Q_NULLPTR));
        qrcodecommande_2t->setTabText(qrcodecommande_2t->indexOf(tab_2), QApplication::translate("MainWindow", "Afficher", Q_NULLPTR));
        stats->setText(QApplication::translate("MainWindow", "stats", Q_NULLPTR));
        qrcodecommande_2t->setTabText(qrcodecommande_2t->indexOf(tab_3), QApplication::translate("MainWindow", "statistique", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "identifiant de traitement:", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "type de traitement :", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "duree de traitement  :", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "temperature_max :", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "temperature_min:", Q_NULLPTR));
        modifier->setText(QApplication::translate("MainWindow", "Modifier", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "prix:", Q_NULLPTR));
        qrcodecommande_2t->setTabText(qrcodecommande_2t->indexOf(tab_4), QApplication::translate("MainWindow", "Modifier", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "identifiant du traitement", Q_NULLPTR));
        rechercher->setText(QApplication::translate("MainWindow", "rechercher", Q_NULLPTR));
        qrcodecommande_2t->setTabText(qrcodecommande_2t->indexOf(tab_7), QApplication::translate("MainWindow", "rechercher", Q_NULLPTR));
        trier->setText(QApplication::translate("MainWindow", "trier", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", " trier selon la duree:", Q_NULLPTR));
        tri_duree->setText(QString());
        qrcodecommande_2t->setTabText(qrcodecommande_2t->indexOf(tab_8), QApplication::translate("MainWindow", "Tri", Q_NULLPTR));
        qrCode->setText(QApplication::translate("MainWindow", "QrCode", Q_NULLPTR));
        qrcodecommande_2->setText(QString());
        qrcodecommande_2t->setTabText(qrcodecommande_2t->indexOf(tab_9), QApplication::translate("MainWindow", "Qr_Code", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
