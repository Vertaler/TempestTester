#include "testwindow.h"
#include "ui_testwindow.h"
#include "backgroundgenerator.h"

#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QThread>

TestWindow::TestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    connect(&timer, &QTimer::timeout, this, &TestWindow::slotTimerTrigger);


    QRect mainScreenSize =  QApplication::desktop()->screenGeometry();
    screenHeight = mainScreenSize.height();
    screenWidth = mainScreenSize.width();

    ui->graphicsView->resize(screenWidth, screenHeight);


    myScene = new QGraphicsScene();
    ui->graphicsView->setWindowState(Qt::WindowFullScreen);
    ui->graphicsView->setScene(myScene);
    ui-> graphicsView->setStyleSheet( "QGraphicsView { border-style: none; }" );


    BackgroundGenerator backgroundGenerator;

    fullBackground = backgroundGenerator.GenerateBackground(screenWidth, screenHeight, 0, RANDOM);
    fewLineBackground = backgroundGenerator.GenerateBackground(screenWidth, screenHeight, 5, RANDOM);
    lotLineBackground = backgroundGenerator.GenerateBackground(screenWidth, screenHeight, 15, RANDOM);
    blackBackground = QBrush(Qt::black);

    myScene->setBackgroundBrush(fewLineBackground);

    stage = FEW_LINES;
    timer.start(500);

}

TestWindow::~TestWindow()
{
    timer.stop();
    delete ui;
}

void TestWindow::slotTestStarted(TestOptions &options){




}

void TestWindow::slotTimerTrigger()
{
    if(stage == FEW_LINES){
        stage = LOT_LINES;
        myScene->setBackgroundBrush(lotLineBackground);

    } else if(stage == LOT_LINES){
        stage = FEW_LINES;
        myScene->setBackgroundBrush(fewLineBackground);
    }
}
