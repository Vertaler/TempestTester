#include "testwindow.h"
#include "ui_testwindow.h"

#include <QDesktopWidget>

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

void TestWindow::slotTestStarted(TestOptions &options){
//    QDesktopWidget widget;
    QRect mainScreenSize =  QApplication::desktop()->screenGeometry();
    screenHeight = mainScreenSize.height();
    screenWidth = mainScreenSize.width();
    ui->graphicsView->resize(screenWidth, screenHeight);

}
