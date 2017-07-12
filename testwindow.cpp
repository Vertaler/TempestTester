#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);
//    ui->graphicsView->resize(this->geometry().width(), this->geometry().height());
}

TestWindow::~TestWindow()
{
    delete ui;
}
