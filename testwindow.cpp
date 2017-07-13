#include "testwindow.h"
#include "ui_testwindow.h"

#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>


TestWindow::TestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    QRect mainScreenSize =  QApplication::desktop()->screenGeometry();
    screenHeight = mainScreenSize.height();
    screenWidth = mainScreenSize.width();

    ui->graphicsView->resize(screenWidth, screenHeight);


    myScene = new QGraphicsScene();
    ui->graphicsView->setWindowState(Qt::WindowFullScreen);
    ui->graphicsView->setScene(myScene);
    ui-> graphicsView->setStyleSheet( "QGraphicsView { border-style: none; }" );
    myScene->setBackgroundBrush(QBrush(Qt::black));

}

TestWindow::~TestWindow()
{
    delete ui;
}

void TestWindow::slotTestStarted(TestOptions &options){



}
