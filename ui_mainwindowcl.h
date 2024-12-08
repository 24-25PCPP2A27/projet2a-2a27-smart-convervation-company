/********************************************************************************
** Form generated from reading UI file 'mainwindowcl.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWCL_H
#define UI_MAINWINDOWCL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindowcl
{
public:
    QFrame *verticalFrame_2;
    QVBoxLayout *verticalLayout_14;
    QFrame *verticalFrame_6;
    QVBoxLayout *verticalLayout_15;
    QWidget *horizontalWidget_33;
    QHBoxLayout *horizontalLayout_15;
    QPushButton *pushButton_9;
    QWidget *horizontalWidget_34;
    QHBoxLayout *horizontalLayout_16;
    QPushButton *EmploiesRoomsOpen_5;
    QWidget *horizontalWidget_35;
    QHBoxLayout *horizontalLayout_53;
    QPushButton *ClientsRoomsOpen_5;
    QWidget *horizontalWidget_36;
    QHBoxLayout *horizontalLayout_54;
    QPushButton *VehiculeRoomsOpen_5;
    QWidget *horizontalWidget_37;
    QHBoxLayout *horizontalLayout_55;
    QLabel *label_92;
    QPushButton *PartenairesRoomsOpen_5;
    QWidget *horizontalWidget_38;
    QHBoxLayout *horizontalLayout_56;
    QLabel *label_93;
    QPushButton *CommandeRoomsOpen_5;
    QFrame *line_5;
    QWidget *horizontalWidget_39;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *pushButton_10;
    QWidget *horizontalWidget_40;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *LineEdit_AIChat_5;
    QWidget *main_menu;
    QVBoxLayout *verticalLayout_16;
    QStackedWidget *stackedWidget;
    QWidget *messages_page_4;
    QWidget *widget_12;
    QLineEdit *nom;
    QLineEdit *idCl_4;
    QLineEdit *prnom;
    QLineEdit *mail;
    QLineEdit *nbrphone;
    QLineEdit *age;
    QTableView *tableView;
    QLineEdit *nb_service_recu;
    QComboBox *comboBox;
    QLineEdit *search_bar;
    QLineEdit *id;
    QDateEdit *date_inscription;
    QLabel *label_13;
    QLabel *label_14;
    QComboBox *gender;
    QDateEdit *DATE_RECEPTION_DATE;
    QDateEdit *DATE_CONSERVATION_DATE;
    QLabel *DATE_RECEPTION_4;
    QLabel *DATE_CONSERVATION_4;
    QLabel *label_15;
    QLabel *label_36;
    QPushButton *pdf;
    QPushButton *excel;
    QPushButton *ajouter;
    QPushButton *modifier;
    QPushButton *pushButton_31;
    QPushButton *pushButton_62;
    QPushButton *gostat;
    QPushButton *gocalendar;
    QPushButton *supprimer;
    QWidget *page;
    QLabel *stat_gender;
    QPushButton *back;
    QWidget *Calendar_page_4;
    QPushButton *goback;
    QCalendarWidget *calendarWidget;
    QLabel *ID_client_label_cal;
    QLabel *NOM_client_label_cal;
    QLabel *PRENOM_client_label_cal;
    QLabel *EMAIL_client_label_cal;
    QLabel *TELEPHONE_client_label_cal;
    QLabel *SEX_client_label_cal;
    QLabel *AGE_client_label_cal;
    QLabel *D_RECEPTION_client_label_cal;
    QLabel *D_CONSERVATION_client_label_cal;

    void setupUi(QDialog *mainwindowcl)
    {
        if (mainwindowcl->objectName().isEmpty())
            mainwindowcl->setObjectName(QStringLiteral("mainwindowcl"));
        mainwindowcl->resize(1419, 857);
        verticalFrame_2 = new QFrame(mainwindowcl);
        verticalFrame_2->setObjectName(QStringLiteral("verticalFrame_2"));
        verticalFrame_2->setGeometry(QRect(-6, -10, 291, 831));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(verticalFrame_2->sizePolicy().hasHeightForWidth());
        verticalFrame_2->setSizePolicy(sizePolicy);
        verticalFrame_2->setMaximumSize(QSize(300, 16777215));
        verticalFrame_2->setStyleSheet(QLatin1String("QFrame{\n"
"	\n"
"border-top-left-radius: 20px;\n"
"border-bottom-left-radius: 20px;\n"
"}\n"
"\n"
"QPushButton:enabled{\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"	\n"
"	background-color: rgb(153, 153, 230);\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"\n"
"\n"
"QPushButton:disabled{\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"background: transparent;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #A9A9A9	;\n"
"\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
""));
        verticalLayout_14 = new QVBoxLayout(verticalFrame_2);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalFrame_6 = new QFrame(verticalFrame_2);
        verticalFrame_6->setObjectName(QStringLiteral("verticalFrame_6"));
        verticalFrame_6->setStyleSheet(QLatin1String("background-color: rgb(105, 156, 77);\n"
"border-color: rgb(0, 85, 0);"));
        verticalLayout_15 = new QVBoxLayout(verticalFrame_6);
        verticalLayout_15->setSpacing(16);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(-1, 28, -1, -1);
        horizontalWidget_33 = new QWidget(verticalFrame_6);
        horizontalWidget_33->setObjectName(QStringLiteral("horizontalWidget_33"));
        horizontalWidget_33->setMaximumSize(QSize(16777215, 49));
        horizontalWidget_33->setStyleSheet(QStringLiteral(""));
        horizontalLayout_15 = new QHBoxLayout(horizontalWidget_33);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        pushButton_9 = new QPushButton(horizontalWidget_33);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setStyleSheet(QLatin1String("\n"
"width: 140px;\n"
"height: 25px;\n"
"\n"
"font-family: 'Manrope';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 18px;\n"
"line-height: 25px;\n"
""));

        horizontalLayout_15->addWidget(pushButton_9);


        verticalLayout_15->addWidget(horizontalWidget_33);

        horizontalWidget_34 = new QWidget(verticalFrame_6);
        horizontalWidget_34->setObjectName(QStringLiteral("horizontalWidget_34"));
        horizontalWidget_34->setMaximumSize(QSize(16777215, 49));
        horizontalWidget_34->setStyleSheet(QLatin1String("\n"
"width: 140px;\n"
"height: 25px;\n"
"\n"
"font-family: 'Manrope';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 18px;\n"
"line-height: 25px;\n"
"/* identical to box height */\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
""));
        horizontalLayout_16 = new QHBoxLayout(horizontalWidget_34);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        EmploiesRoomsOpen_5 = new QPushButton(horizontalWidget_34);
        EmploiesRoomsOpen_5->setObjectName(QStringLiteral("EmploiesRoomsOpen_5"));
        EmploiesRoomsOpen_5->setStyleSheet(QStringLiteral(""));

        horizontalLayout_16->addWidget(EmploiesRoomsOpen_5);


        verticalLayout_15->addWidget(horizontalWidget_34);

        horizontalWidget_35 = new QWidget(verticalFrame_6);
        horizontalWidget_35->setObjectName(QStringLiteral("horizontalWidget_35"));
        horizontalWidget_35->setMaximumSize(QSize(16777215, 49));
        horizontalWidget_35->setStyleSheet(QLatin1String("\n"
"width: 140px;\n"
"height: 25px;\n"
"\n"
"font-family: 'Manrope';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 18px;\n"
"line-height: 25px;\n"
"/* identical to box height */\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
""));
        horizontalLayout_53 = new QHBoxLayout(horizontalWidget_35);
        horizontalLayout_53->setObjectName(QStringLiteral("horizontalLayout_53"));
        ClientsRoomsOpen_5 = new QPushButton(horizontalWidget_35);
        ClientsRoomsOpen_5->setObjectName(QStringLiteral("ClientsRoomsOpen_5"));
        ClientsRoomsOpen_5->setStyleSheet(QStringLiteral(""));

        horizontalLayout_53->addWidget(ClientsRoomsOpen_5);


        verticalLayout_15->addWidget(horizontalWidget_35);

        horizontalWidget_36 = new QWidget(verticalFrame_6);
        horizontalWidget_36->setObjectName(QStringLiteral("horizontalWidget_36"));
        horizontalWidget_36->setMaximumSize(QSize(16777215, 49));
        horizontalWidget_36->setStyleSheet(QLatin1String("\n"
"width: 140px;\n"
"height: 25px;\n"
"\n"
"font-family: 'Manrope';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 18px;\n"
"line-height: 25px;\n"
"/* identical to box height */\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
""));
        horizontalLayout_54 = new QHBoxLayout(horizontalWidget_36);
        horizontalLayout_54->setObjectName(QStringLiteral("horizontalLayout_54"));
        VehiculeRoomsOpen_5 = new QPushButton(horizontalWidget_36);
        VehiculeRoomsOpen_5->setObjectName(QStringLiteral("VehiculeRoomsOpen_5"));
        VehiculeRoomsOpen_5->setStyleSheet(QStringLiteral(""));

        horizontalLayout_54->addWidget(VehiculeRoomsOpen_5);


        verticalLayout_15->addWidget(horizontalWidget_36);

        horizontalWidget_37 = new QWidget(verticalFrame_6);
        horizontalWidget_37->setObjectName(QStringLiteral("horizontalWidget_37"));
        horizontalWidget_37->setMaximumSize(QSize(16777215, 49));
        horizontalWidget_37->setStyleSheet(QLatin1String("\n"
"width: 140px;\n"
"height: 25px;\n"
"\n"
"font-family: 'Manrope';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 18px;\n"
"line-height: 25px;\n"
"/* identical to box height */\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
""));
        horizontalLayout_55 = new QHBoxLayout(horizontalWidget_37);
        horizontalLayout_55->setObjectName(QStringLiteral("horizontalLayout_55"));
        label_92 = new QLabel(horizontalWidget_37);
        label_92->setObjectName(QStringLiteral("label_92"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_92->sizePolicy().hasHeightForWidth());
        label_92->setSizePolicy(sizePolicy1);
        label_92->setMinimumSize(QSize(24, 24));
        label_92->setMaximumSize(QSize(24, 24));
        label_92->setStyleSheet(QStringLiteral("background-image: url(:/public/icons/public/icons/users.png);"));

        horizontalLayout_55->addWidget(label_92);

        PartenairesRoomsOpen_5 = new QPushButton(horizontalWidget_37);
        PartenairesRoomsOpen_5->setObjectName(QStringLiteral("PartenairesRoomsOpen_5"));
        PartenairesRoomsOpen_5->setStyleSheet(QStringLiteral(""));

        horizontalLayout_55->addWidget(PartenairesRoomsOpen_5);


        verticalLayout_15->addWidget(horizontalWidget_37);

        horizontalWidget_38 = new QWidget(verticalFrame_6);
        horizontalWidget_38->setObjectName(QStringLiteral("horizontalWidget_38"));
        horizontalWidget_38->setMaximumSize(QSize(16777215, 49));
        horizontalWidget_38->setStyleSheet(QLatin1String("\n"
"width: 140px;\n"
"height: 25px;\n"
"\n"
"font-family: 'Manrope';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 18px;\n"
"line-height: 25px;\n"
"/* identical to box height */\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
""));
        horizontalLayout_56 = new QHBoxLayout(horizontalWidget_38);
        horizontalLayout_56->setObjectName(QStringLiteral("horizontalLayout_56"));
        label_93 = new QLabel(horizontalWidget_38);
        label_93->setObjectName(QStringLiteral("label_93"));
        sizePolicy1.setHeightForWidth(label_93->sizePolicy().hasHeightForWidth());
        label_93->setSizePolicy(sizePolicy1);
        label_93->setMinimumSize(QSize(24, 24));
        label_93->setMaximumSize(QSize(24, 24));
        label_93->setStyleSheet(QStringLiteral("background-image: url(:/public/icons/public/icons/users.png);"));

        horizontalLayout_56->addWidget(label_93);

        CommandeRoomsOpen_5 = new QPushButton(horizontalWidget_38);
        CommandeRoomsOpen_5->setObjectName(QStringLiteral("CommandeRoomsOpen_5"));
        CommandeRoomsOpen_5->setStyleSheet(QStringLiteral(""));

        horizontalLayout_56->addWidget(CommandeRoomsOpen_5);


        verticalLayout_15->addWidget(horizontalWidget_38);

        line_5 = new QFrame(verticalFrame_6);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setStyleSheet(QLatin1String("\n"
"\n"
"position: absolute;\n"
"width: 218px;\n"
"height: 0px;\n"
"left: 116px;\n"
"top: 535px;\n"
"\n"
"border: 1px solid #C4C4C4;\n"
""));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout_15->addWidget(line_5);

        horizontalWidget_39 = new QWidget(verticalFrame_6);
        horizontalWidget_39->setObjectName(QStringLiteral("horizontalWidget_39"));
        horizontalWidget_39->setMaximumSize(QSize(16777215, 49));
        horizontalWidget_39->setStyleSheet(QStringLiteral(""));
        horizontalLayout_17 = new QHBoxLayout(horizontalWidget_39);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        pushButton_10 = new QPushButton(horizontalWidget_39);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setStyleSheet(QLatin1String("\n"
"width: 140px;\n"
"height: 25px;\n"
"\n"
"font-family: 'Manrope';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 18px;\n"
"line-height: 25px;\n"
""));

        horizontalLayout_17->addWidget(pushButton_10);


        verticalLayout_15->addWidget(horizontalWidget_39);

        horizontalWidget_40 = new QWidget(verticalFrame_6);
        horizontalWidget_40->setObjectName(QStringLiteral("horizontalWidget_40"));
        horizontalWidget_40->setMaximumSize(QSize(16777215, 49));
        horizontalLayout_5 = new QHBoxLayout(horizontalWidget_40);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        LineEdit_AIChat_5 = new QLineEdit(horizontalWidget_40);
        LineEdit_AIChat_5->setObjectName(QStringLiteral("LineEdit_AIChat_5"));
        LineEdit_AIChat_5->setMinimumSize(QSize(0, 43));
        LineEdit_AIChat_5->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"border-radius: 5px;\n"
"color:black;"));

        horizontalLayout_5->addWidget(LineEdit_AIChat_5);


        verticalLayout_15->addWidget(horizontalWidget_40);


        verticalLayout_14->addWidget(verticalFrame_6);

        main_menu = new QWidget(mainwindowcl);
        main_menu->setObjectName(QStringLiteral("main_menu"));
        main_menu->setGeometry(QRect(310, 20, 1081, 831));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(13);
        font.setBold(true);
        font.setWeight(75);
        main_menu->setFont(font);
        main_menu->setStyleSheet(QLatin1String("#info_frame QLabel,\n"
"#info_frame QLineEdit,\n"
"#info_frame QComboBox,\n"
"#function_frame QPushButton,\n"
"QHeaderView::section {\n"
"    font-family: 'Segoe UI Semibold';\n"
"    font-size: 12px;\n"
"}\n"
"\n"
"/* Styles for input fields and combo boxes inside info_frame */\n"
"#info_frame QLineEdit,\n"
"#info_frame QComboBox {\n"
"    padding: 4px 5px;\n"
"    border: 1px solid #838383;\n"
"    border-radius: 2px;\n"
"}\n"
"\n"
"/* Focus styles for input fields and combo boxes */\n"
"#info_frame QLineEdit:focus,\n"
"#info_frame QComboBox:focus {\n"
"    border-color: #0055ff;\n"
"}\n"
"\n"
"\n"
"QComboBox::drop-down{\n"
"background:transparent;\n"
"border:none;\n"
"margin-right:5px;\n"
"}\n"
"\n"
"\n"
"#result_frame{\n"
"border-radius:5px;\n"
"background-color:#fff;\n"
"}\n"
"\n"
"QTableWidget{\n"
"border-radius:3px;\n"
"border: 1px solid #f0f0f0;\n"
"}\n"
"\n"
"\n"
"QHeaderView::section{\n"
"border:none;\n"
"border-bottom: 1px solid #d0c6ff;\n"
"text-align:left;\n"
"padding: 3px 5px;\n"
"\n"
"}\n"
"\n"
""
                        "QTableWidget::item{\n"
"border-bottom:1px solid #d0c6ff;\n"
"color:#000;\n"
"padding-left:3px;\n"
"}\n"
"\n"
"\n"
"#function_frame QPushButton {\n"
"    font-size: 14px;\n"
"    padding: 5px 10px;\n"
"    border: 2px solid #f0f0f0;\n"
"    border-radius: 5px;\n"
"    background-color: #84a8f7;\n"
"}\n"
"\n"
"\n"
"/*#function_frame#delete_btn{\n"
"background-color:#ff8183;\n"
"}*/\n"
"\n"
"#function_frame QPushButton:hover{\n"
"border-color:#4c96f7;\n"
"font-size:15px;\n"
"}\n"
"\n"
"#function_frame#delete_btn:hover {\n"
"border-color:#dc004;\n"
"}\n"
"\n"
"\n"
"\n"
"#delete_btn {\n"
"    background-color: #ff0000; /* Default background color */\n"
"    color: white; /* Text color */\n"
"    border-radius: 5px; /* Rounded corners */\n"
"    padding: 5px 10px; /* Padding for the button */\n"
"}\n"
"\n"
"#delete_btn:hover {\n"
"    background-color: #dc0003; /* Change background on hover */\n"
"}\n"
"\n"
"\n"
"\n"
""));
        verticalLayout_16 = new QVBoxLayout(main_menu);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        stackedWidget = new QStackedWidget(main_menu);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        QFont font1;
        font1.setFamily(QStringLiteral("Segoe UI Black"));
        font1.setBold(true);
        font1.setWeight(75);
        stackedWidget->setFont(font1);
        stackedWidget->setStyleSheet(QStringLiteral(""));
        messages_page_4 = new QWidget();
        messages_page_4->setObjectName(QStringLiteral("messages_page_4"));
        QFont font2;
        font2.setPointSize(12);
        messages_page_4->setFont(font2);
        widget_12 = new QWidget(messages_page_4);
        widget_12->setObjectName(QStringLiteral("widget_12"));
        widget_12->setGeometry(QRect(0, 0, 1131, 821));
        widget_12->setStyleSheet(QLatin1String("QWidget#widget_8{\n"
"\n"
"    position: absolute;\n"
"    width: 3389.75px;\n"
"    height: 2997.84px;\n"
"    left: 2152.95px;\n"
"    top: 895.79px;\n"
"   \n"
"	background-color: rgba(114, 192, 78, 50);\n"
"    border: 5px solid;\n"
"	border-color: rgba(114, 192, 78, 70);\n"
"\n"
"    border-radius: 30.5383px;\n"
"}"));
        nom = new QLineEdit(widget_12);
        nom->setObjectName(QStringLiteral("nom"));
        nom->setGeometry(QRect(140, 90, 141, 31));
        nom->setStyleSheet(QLatin1String("QWidget {\n"
"    border-radius: 8px;\n"
"    background-color: #f8f9fa; /* Light grey background */\n"
"    border: 1px solid #ddd; /* Light border */\n"
"}\n"
""));
        idCl_4 = new QLineEdit(widget_12);
        idCl_4->setObjectName(QStringLiteral("idCl_4"));
        idCl_4->setGeometry(QRect(830, 580, 141, 31));
        idCl_4->setStyleSheet(QLatin1String("QWidget {\n"
"    border-radius: 8px;\n"
"    background-color: #f8f9fa; /* Light grey background */\n"
"    border: 1px solid #ddd; /* Light border */\n"
"}\n"
""));
        prnom = new QLineEdit(widget_12);
        prnom->setObjectName(QStringLiteral("prnom"));
        prnom->setGeometry(QRect(310, 90, 131, 31));
        prnom->setStyleSheet(QLatin1String("QWidget {\n"
"    border-radius: 8px;\n"
"    background-color: #f8f9fa; /* Light grey background */\n"
"    border: 1px solid #ddd; /* Light border */\n"
"}\n"
""));
        mail = new QLineEdit(widget_12);
        mail->setObjectName(QStringLiteral("mail"));
        mail->setGeometry(QRect(140, 160, 141, 31));
        mail->setStyleSheet(QLatin1String("QWidget {\n"
"    border-radius: 8px;\n"
"    background-color: #f8f9fa; /* Light grey background */\n"
"    border: 1px solid #ddd; /* Light border */\n"
"}\n"
""));
        nbrphone = new QLineEdit(widget_12);
        nbrphone->setObjectName(QStringLiteral("nbrphone"));
        nbrphone->setGeometry(QRect(470, 90, 141, 31));
        nbrphone->setStyleSheet(QLatin1String("QWidget {\n"
"    border-radius: 8px;\n"
"    background-color: #f8f9fa; /* Light grey background */\n"
"    border: 1px solid #ddd; /* Light border */\n"
"}\n"
""));
        age = new QLineEdit(widget_12);
        age->setObjectName(QStringLiteral("age"));
        age->setGeometry(QRect(310, 160, 141, 31));
        age->setStyleSheet(QLatin1String("QWidget {\n"
"    border-radius: 8px;\n"
"    background-color: #f8f9fa; /* Light grey background */\n"
"    border: 1px solid #ddd; /* Light border */\n"
"}\n"
""));
        tableView = new QTableView(widget_12);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(130, 390, 931, 271));
        nb_service_recu = new QLineEdit(widget_12);
        nb_service_recu->setObjectName(QStringLiteral("nb_service_recu"));
        nb_service_recu->setGeometry(QRect(470, 160, 151, 31));
        nb_service_recu->setStyleSheet(QLatin1String("QWidget {\n"
"    border-radius: 8px;\n"
"    background-color: #f8f9fa; /* Light grey background */\n"
"    border: 1px solid #ddd; /* Light border */\n"
"}\n"
""));
        comboBox = new QComboBox(widget_12);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(640, 700, 161, 41));
        search_bar = new QLineEdit(widget_12);
        search_bar->setObjectName(QStringLiteral("search_bar"));
        search_bar->setGeometry(QRect(270, 700, 151, 41));
        id = new QLineEdit(widget_12);
        id->setObjectName(QStringLiteral("id"));
        id->setGeometry(QRect(990, 340, 61, 31));
        date_inscription = new QDateEdit(widget_12);
        date_inscription->setObjectName(QStringLiteral("date_inscription"));
        date_inscription->setGeometry(QRect(300, 240, 131, 31));
        label_13 = new QLabel(widget_12);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(310, 210, 141, 20));
        label_14 = new QLabel(widget_12);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(140, 210, 56, 16));
        gender = new QComboBox(widget_12);
        gender->setObjectName(QStringLiteral("gender"));
        gender->setGeometry(QRect(140, 240, 141, 31));
        DATE_RECEPTION_DATE = new QDateEdit(widget_12);
        DATE_RECEPTION_DATE->setObjectName(QStringLiteral("DATE_RECEPTION_DATE"));
        DATE_RECEPTION_DATE->setGeometry(QRect(460, 240, 131, 31));
        DATE_CONSERVATION_DATE = new QDateEdit(widget_12);
        DATE_CONSERVATION_DATE->setObjectName(QStringLiteral("DATE_CONSERVATION_DATE"));
        DATE_CONSERVATION_DATE->setGeometry(QRect(620, 240, 131, 31));
        DATE_RECEPTION_4 = new QLabel(widget_12);
        DATE_RECEPTION_4->setObjectName(QStringLiteral("DATE_RECEPTION_4"));
        DATE_RECEPTION_4->setGeometry(QRect(470, 210, 141, 20));
        DATE_CONSERVATION_4 = new QLabel(widget_12);
        DATE_CONSERVATION_4->setObjectName(QStringLiteral("DATE_CONSERVATION_4"));
        DATE_CONSERVATION_4->setGeometry(QRect(620, 210, 151, 20));
        label_15 = new QLabel(widget_12);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(330, 10, 251, 61));
        QFont font3;
        font3.setFamily(QStringLiteral("Times New Roman"));
        font3.setPointSize(22);
        font3.setBold(false);
        font3.setItalic(true);
        font3.setWeight(50);
        label_15->setFont(font3);
        label_15->setStyleSheet(QStringLiteral("color: rgb(0, 115, 0);"));
        label_36 = new QLabel(widget_12);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(850, 350, 131, 24));
        QFont font4;
        font4.setBold(true);
        font4.setWeight(75);
        label_36->setFont(font4);
        label_36->setStyleSheet(QStringLiteral("color: rgb(0, 115, 0);"));
        pdf = new QPushButton(widget_12);
        pdf->setObjectName(QStringLiteral("pdf"));
        pdf->setGeometry(QRect(40, 540, 81, 51));
        pdf->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        QIcon icon;
        icon.addFile(QStringLiteral("../chaima88/chaima08/chaimaf/crud yassine/Atelier_Connexion/im/picture_as_pdf_24dp_5F6368_FILL0_wght400_GRAD0_opsz24.png"), QSize(), QIcon::Normal, QIcon::Off);
        pdf->setIcon(icon);
        excel = new QPushButton(widget_12);
        excel->setObjectName(QStringLiteral("excel"));
        excel->setGeometry(QRect(40, 610, 81, 51));
        excel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        excel->setIcon(icon);
        ajouter = new QPushButton(widget_12);
        ajouter->setObjectName(QStringLiteral("ajouter"));
        ajouter->setGeometry(QRect(130, 320, 121, 51));
        QFont font5;
        font5.setFamily(QStringLiteral("Lucida Bright"));
        font5.setBold(true);
        font5.setWeight(87);
        ajouter->setFont(font5);
        ajouter->setStyleSheet(QLatin1String("QPushButton{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"background: #72C14E;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton:hover{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"\n"
"background: #80DB56;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"height: 24px;\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #CDFFB6;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"co"
                        "lor: #72C04E;\n"
"\n"
"}\n"
"QPushButton:disabled{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #A9A9A9	;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #72C04E;\n"
"\n"
"}"));
        modifier = new QPushButton(widget_12);
        modifier->setObjectName(QStringLiteral("modifier"));
        modifier->setGeometry(QRect(380, 320, 131, 51));
        modifier->setFont(font5);
        modifier->setStyleSheet(QLatin1String("QPushButton{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"background: #72C14E;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton:hover{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"\n"
"background: #80DB56;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"height: 24px;\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #CDFFB6;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"co"
                        "lor: #72C04E;\n"
"\n"
"}\n"
"QPushButton:disabled{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #A9A9A9	;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #72C04E;\n"
"\n"
"}"));
        pushButton_31 = new QPushButton(widget_12);
        pushButton_31->setObjectName(QStringLiteral("pushButton_31"));
        pushButton_31->setGeometry(QRect(130, 690, 131, 51));
        pushButton_31->setFont(font5);
        pushButton_31->setStyleSheet(QLatin1String("QPushButton{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"background: #72C14E;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton:hover{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"\n"
"background: #80DB56;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"height: 24px;\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #CDFFB6;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"co"
                        "lor: #72C04E;\n"
"\n"
"}\n"
"QPushButton:disabled{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #A9A9A9	;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #72C04E;\n"
"\n"
"}"));
        pushButton_62 = new QPushButton(widget_12);
        pushButton_62->setObjectName(QStringLiteral("pushButton_62"));
        pushButton_62->setGeometry(QRect(500, 690, 131, 51));
        pushButton_62->setFont(font5);
        pushButton_62->setStyleSheet(QLatin1String("QPushButton{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"background: #72C14E;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton:hover{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"\n"
"background: #80DB56;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"height: 24px;\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #CDFFB6;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"co"
                        "lor: #72C04E;\n"
"\n"
"}\n"
"QPushButton:disabled{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #A9A9A9	;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #72C04E;\n"
"\n"
"}"));
        gostat = new QPushButton(widget_12);
        gostat->setObjectName(QStringLiteral("gostat"));
        gostat->setGeometry(QRect(870, 100, 151, 54));
        gostat->setFont(font5);
        gostat->setStyleSheet(QLatin1String("QPushButton{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"background: #72C14E;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton:hover{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"\n"
"background: #80DB56;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"height: 24px;\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #CDFFB6;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"co"
                        "lor: #72C04E;\n"
"\n"
"}\n"
"QPushButton:disabled{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #A9A9A9	;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #72C04E;\n"
"\n"
"}"));
        gocalendar = new QPushButton(widget_12);
        gocalendar->setObjectName(QStringLiteral("gocalendar"));
        gocalendar->setGeometry(QRect(870, 20, 151, 54));
        gocalendar->setFont(font5);
        gocalendar->setStyleSheet(QLatin1String("QPushButton{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"background: #72C14E;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton:hover{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"\n"
"background: #80DB56;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"height: 24px;\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #CDFFB6;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"co"
                        "lor: #72C04E;\n"
"\n"
"}\n"
"QPushButton:disabled{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #A9A9A9	;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #72C04E;\n"
"\n"
"}"));
        supprimer = new QPushButton(widget_12);
        supprimer->setObjectName(QStringLiteral("supprimer"));
        supprimer->setGeometry(QRect(620, 320, 131, 51));
        supprimer->setFont(font5);
        supprimer->setStyleSheet(QLatin1String("QPushButton{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"background: #72C14E;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton:hover{\n"
"padding: 16px 500px;\n"
"\n"
"\n"
"\n"
"\n"
"background: #80DB56;\n"
"border-radius: 4px;\n"
"\n"
"\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"height: 24px;\n"
"\n"
"\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #FFFFFF;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #CDFFB6;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"co"
                        "lor: #72C04E;\n"
"\n"
"}\n"
"QPushButton:disabled{/* Property 1=Variant3 */\n"
"\n"
"\n"
"padding: 16px 24px;\n"
"\n"
"position: absolute;\n"
"\n"
"left: 20px;\n"
"top: 172px;\n"
"\n"
"background: #A9A9A9	;\n"
"\n"
"border-radius: 4px;\n"
"\n"
"\n"
"/* Se Connecter */\n"
"\n"
"\n"
"height: 24px;\n"
"\n"
"font-family: 'Titillium Web';\n"
"font-style: normal;\n"
"font-weight: 700;\n"
"font-size: 16px;\n"
"line-height: 24px;\n"
"\n"
"color: #72C04E;\n"
"\n"
"}"));
        stackedWidget->addWidget(messages_page_4);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stat_gender = new QLabel(page);
        stat_gender->setObjectName(QStringLiteral("stat_gender"));
        stat_gender->setGeometry(QRect(210, 130, 711, 451));
        back = new QPushButton(page);
        back->setObjectName(QStringLiteral("back"));
        back->setGeometry(QRect(510, 600, 141, 41));
        back->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #6200ea;\n"
"    color: white;\n"
"    border-radius: 6px;\n"
"    padding: 10px 24px;\n"
"    font-size: 14px;\n"
"    letter-spacing: 1px;\n"
"    text-transform: uppercase;\n"
"    transition: background-color 0.3s ease;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3700b3;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #30009c;\n"
"}"));
        stackedWidget->addWidget(page);
        Calendar_page_4 = new QWidget();
        Calendar_page_4->setObjectName(QStringLiteral("Calendar_page_4"));
        goback = new QPushButton(Calendar_page_4);
        goback->setObjectName(QStringLiteral("goback"));
        goback->setGeometry(QRect(470, 660, 141, 41));
        goback->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #6200ea;\n"
"    color: white;\n"
"    border-radius: 6px;\n"
"    padding: 10px 24px;\n"
"    font-size: 14px;\n"
"    letter-spacing: 1px;\n"
"    text-transform: uppercase;\n"
"    transition: background-color 0.3s ease;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3700b3;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #30009c;\n"
"}"));
        calendarWidget = new QCalendarWidget(Calendar_page_4);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setGeometry(QRect(410, 30, 661, 561));
        calendarWidget->setStyleSheet(QLatin1String("QCalendarWidget {\n"
" color: rgb(255, 105, 105);\n"
"    background-color: rgb(255, 105, 105);\n"
"}\n"
"QCalendarWidget QMenu\n"
"{\n"
"	background-color: rgb(255, 105, 105);\n"
"color: rgb(255, 105, 105);\n"
"}\n"
"QCalendarWidget QToolButton {\n"
"/*text color*/\n"
"    color: rgb(20, 30, 70); \n"
"/*background color*/\n"
"	background-color: rgb(255, 105, 105);\n"
"}\n"
"\n"
"QCalendarWidget QToolButton:hover {\n"
"    background-color: rgb(255, 105, 105);\n"
"    color: rgb(255, 105, 105); \n"
"}\n"
"\n"
"QCalendarWidget QToolButton:selected {\n"
"    background-color: rgb(255, 105, 105);\n"
"    color: rgb(255, 105, 105); \n"
"}\n"
"QCalendarWidget QAbstractItemView {\n"
"    selection-background-color: rgb(255, 105, 105); /* Set the color for the selection bar */\n"
"color: rgb(20, 30, 70);\n"
"}\n"
"QCalendarWidget QWidget#qt_calendar_navigationbar {\n"
"    background-color: rgb(255, 105, 105);\n"
"}\n"
"\n"
""));
        ID_client_label_cal = new QLabel(Calendar_page_4);
        ID_client_label_cal->setObjectName(QStringLiteral("ID_client_label_cal"));
        ID_client_label_cal->setGeometry(QRect(60, 30, 350, 40));
        QFont font6;
        font6.setFamily(QStringLiteral("Calibri"));
        font6.setPointSize(17);
        font6.setBold(true);
        font6.setWeight(75);
        ID_client_label_cal->setFont(font6);
        ID_client_label_cal->setStyleSheet(QStringLiteral("color : rgb(116, 226, 145);"));
        NOM_client_label_cal = new QLabel(Calendar_page_4);
        NOM_client_label_cal->setObjectName(QStringLiteral("NOM_client_label_cal"));
        NOM_client_label_cal->setGeometry(QRect(60, 90, 350, 40));
        QFont font7;
        font7.setPointSize(12);
        font7.setBold(true);
        font7.setWeight(75);
        NOM_client_label_cal->setFont(font7);
        PRENOM_client_label_cal = new QLabel(Calendar_page_4);
        PRENOM_client_label_cal->setObjectName(QStringLiteral("PRENOM_client_label_cal"));
        PRENOM_client_label_cal->setGeometry(QRect(60, 150, 350, 40));
        PRENOM_client_label_cal->setFont(font7);
        EMAIL_client_label_cal = new QLabel(Calendar_page_4);
        EMAIL_client_label_cal->setObjectName(QStringLiteral("EMAIL_client_label_cal"));
        EMAIL_client_label_cal->setGeometry(QRect(60, 210, 350, 40));
        EMAIL_client_label_cal->setFont(font7);
        TELEPHONE_client_label_cal = new QLabel(Calendar_page_4);
        TELEPHONE_client_label_cal->setObjectName(QStringLiteral("TELEPHONE_client_label_cal"));
        TELEPHONE_client_label_cal->setGeometry(QRect(60, 270, 351, 40));
        TELEPHONE_client_label_cal->setFont(font7);
        SEX_client_label_cal = new QLabel(Calendar_page_4);
        SEX_client_label_cal->setObjectName(QStringLiteral("SEX_client_label_cal"));
        SEX_client_label_cal->setGeometry(QRect(60, 330, 350, 40));
        SEX_client_label_cal->setFont(font7);
        AGE_client_label_cal = new QLabel(Calendar_page_4);
        AGE_client_label_cal->setObjectName(QStringLiteral("AGE_client_label_cal"));
        AGE_client_label_cal->setGeometry(QRect(60, 390, 350, 40));
        AGE_client_label_cal->setFont(font7);
        D_RECEPTION_client_label_cal = new QLabel(Calendar_page_4);
        D_RECEPTION_client_label_cal->setObjectName(QStringLiteral("D_RECEPTION_client_label_cal"));
        D_RECEPTION_client_label_cal->setGeometry(QRect(60, 450, 350, 40));
        D_RECEPTION_client_label_cal->setFont(font7);
        D_CONSERVATION_client_label_cal = new QLabel(Calendar_page_4);
        D_CONSERVATION_client_label_cal->setObjectName(QStringLiteral("D_CONSERVATION_client_label_cal"));
        D_CONSERVATION_client_label_cal->setGeometry(QRect(70, 510, 350, 40));
        D_CONSERVATION_client_label_cal->setFont(font7);
        stackedWidget->addWidget(Calendar_page_4);

        verticalLayout_16->addWidget(stackedWidget);


        retranslateUi(mainwindowcl);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mainwindowcl);
    } // setupUi

    void retranslateUi(QDialog *mainwindowcl)
    {
        mainwindowcl->setWindowTitle(QApplication::translate("mainwindowcl", "Dialog", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("mainwindowcl", "Dashboard", Q_NULLPTR));
        EmploiesRoomsOpen_5->setText(QApplication::translate("mainwindowcl", "Employ\303\251s", Q_NULLPTR));
        ClientsRoomsOpen_5->setText(QApplication::translate("mainwindowcl", "Clients", Q_NULLPTR));
        VehiculeRoomsOpen_5->setText(QApplication::translate("mainwindowcl", "Produits", Q_NULLPTR));
        label_92->setText(QString());
        PartenairesRoomsOpen_5->setText(QApplication::translate("mainwindowcl", "Equipements", Q_NULLPTR));
        label_93->setText(QString());
        CommandeRoomsOpen_5->setText(QApplication::translate("mainwindowcl", "Traitements", Q_NULLPTR));
        pushButton_10->setText(QApplication::translate("mainwindowcl", "D\303\251connecter", Q_NULLPTR));
        nom->setText(QString());
        nom->setPlaceholderText(QApplication::translate("mainwindowcl", "NOM", Q_NULLPTR));
        idCl_4->setText(QString());
        idCl_4->setPlaceholderText(QApplication::translate("mainwindowcl", "IDCl", Q_NULLPTR));
        prnom->setText(QString());
        prnom->setPlaceholderText(QApplication::translate("mainwindowcl", "PRENOM", Q_NULLPTR));
        mail->setText(QString());
        mail->setPlaceholderText(QApplication::translate("mainwindowcl", "EMAIL", Q_NULLPTR));
        nbrphone->setText(QString());
        nbrphone->setPlaceholderText(QApplication::translate("mainwindowcl", "T\303\251l\303\251phone", Q_NULLPTR));
        age->setText(QString());
        age->setPlaceholderText(QApplication::translate("mainwindowcl", "Age", Q_NULLPTR));
        nb_service_recu->setText(QString());
        nb_service_recu->setPlaceholderText(QApplication::translate("mainwindowcl", "Nombre de service re\303\247u", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("mainwindowcl", "select option", Q_NULLPTR)
         << QApplication::translate("mainwindowcl", "Prenom", Q_NULLPTR)
         << QApplication::translate("mainwindowcl", "Id_Client", Q_NULLPTR)
         << QApplication::translate("mainwindowcl", "Anciennet\303\251", Q_NULLPTR)
        );
        id->setText(QString());
        label_13->setText(QApplication::translate("mainwindowcl", "Date inscription", Q_NULLPTR));
        label_14->setText(QApplication::translate("mainwindowcl", "Sexe", Q_NULLPTR));
        gender->clear();
        gender->insertItems(0, QStringList()
         << QApplication::translate("mainwindowcl", "Male", Q_NULLPTR)
         << QApplication::translate("mainwindowcl", "Female", Q_NULLPTR)
        );
        DATE_RECEPTION_4->setText(QApplication::translate("mainwindowcl", "Date r\303\251ception", Q_NULLPTR));
        DATE_CONSERVATION_4->setText(QApplication::translate("mainwindowcl", "Date conservation", Q_NULLPTR));
        label_15->setText(QApplication::translate("mainwindowcl", "    Clients", Q_NULLPTR));
        label_36->setText(QApplication::translate("mainwindowcl", "ID Client Selected :", Q_NULLPTR));
        pdf->setText(QApplication::translate("mainwindowcl", "PDF", Q_NULLPTR));
        excel->setText(QApplication::translate("mainwindowcl", "EXCEL", Q_NULLPTR));
        ajouter->setText(QApplication::translate("mainwindowcl", "AJOUTER", Q_NULLPTR));
        modifier->setText(QApplication::translate("mainwindowcl", "MODIFIER", Q_NULLPTR));
        pushButton_31->setText(QApplication::translate("mainwindowcl", "RECHERCHE", Q_NULLPTR));
        pushButton_62->setText(QApplication::translate("mainwindowcl", "TRI", Q_NULLPTR));
        gostat->setText(QApplication::translate("mainwindowcl", "STATISTIQUES", Q_NULLPTR));
        gocalendar->setText(QApplication::translate("mainwindowcl", "CALENDRIER", Q_NULLPTR));
        supprimer->setText(QApplication::translate("mainwindowcl", "SUPPRIMER", Q_NULLPTR));
        stat_gender->setText(QString());
        back->setText(QApplication::translate("mainwindowcl", "Go Back", Q_NULLPTR));
        goback->setText(QApplication::translate("mainwindowcl", "Go Back", Q_NULLPTR));
        ID_client_label_cal->setText(QApplication::translate("mainwindowcl", "TextLabel", Q_NULLPTR));
        NOM_client_label_cal->setText(QApplication::translate("mainwindowcl", "TextLabel", Q_NULLPTR));
        PRENOM_client_label_cal->setText(QApplication::translate("mainwindowcl", "TextLabel", Q_NULLPTR));
        EMAIL_client_label_cal->setText(QApplication::translate("mainwindowcl", "TextLabel", Q_NULLPTR));
        TELEPHONE_client_label_cal->setText(QApplication::translate("mainwindowcl", "TextLabel", Q_NULLPTR));
        SEX_client_label_cal->setText(QApplication::translate("mainwindowcl", "TextLabel", Q_NULLPTR));
        AGE_client_label_cal->setText(QApplication::translate("mainwindowcl", "TextLabel", Q_NULLPTR));
        D_RECEPTION_client_label_cal->setText(QApplication::translate("mainwindowcl", "TextLabel", Q_NULLPTR));
        D_CONSERVATION_client_label_cal->setText(QApplication::translate("mainwindowcl", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mainwindowcl: public Ui_mainwindowcl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWCL_H
