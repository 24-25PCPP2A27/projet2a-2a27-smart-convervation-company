#include "mainwindowcl.h"
#include "ui_mainwindowcl.h"

mainwindowcl::mainwindowcl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwindowcl)
{
    ui->setupUi(this);
}

mainwindowcl::~mainwindowcl()
{
    delete ui;
}
