#ifndef MAINWINDOWCL_H
#define MAINWINDOWCL_H

#include <QDialog>

namespace Ui {
class mainwindowcl;
}

class mainwindowcl : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindowcl(QWidget *parent = nullptr);
    ~mainwindowcl();

private:
    Ui::mainwindowcl *ui;
};

#endif // MAINWINDOWCL_H
