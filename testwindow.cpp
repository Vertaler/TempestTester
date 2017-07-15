#include "testwindow.h"
#include "ui_testwindow.h"
#include "backgroundgenerator.h"

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

    BackgroundGenerator backgroundGenerator;
    QBrush brush = backgroundGenerator.GenerateBackground(screenWidth, screenHeight, 5, RANDOM);
    myScene->setBackgroundBrush(brush);

}

TestWindow::~TestWindow()
{
    delete ui;
}

void TestWindow::slotTestStarted(TestOptions &options){



}
