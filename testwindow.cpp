#include "testwindow.h"
#include "ui_testwindow.h"
#include "backgroundgenerator.h"

#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
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

    blackBackground = QBrush(Qt::black);



}

TestWindow::~TestWindow()
{
    timer.stop();
    delete ui;
}

void TestWindow::Update()
{
    BackgroundGenerator backgroundGenerator;

    fewLineBackground = backgroundGenerator.GenerateBackground(screenWidth, screenHeight, options.getMinLineCount().Value(), options.getFillingType());
    lotLineBackground = backgroundGenerator.GenerateBackground(screenWidth, screenHeight, options.getMaxLineCount().Value(), options.getFillingType());
    fullBackground = backgroundGenerator.GenerateBackground(screenWidth, screenHeight, 0, options.getFillingType());

    timer.start((int)(1000 * options.getPeriod().Value()));
}


void TestWindow::slotTestStarted(TestOptions &options){

    this->options = options;

    stage = OFF;
    myScene->setBackgroundBrush(blackBackground);
    Update();
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

void TestWindow::keyPressEvent(QKeyEvent* e)
{
    if(e->key() == Qt::Key_Space){
        switch(stage){
            case OFF:
                myScene->setBackgroundBrush(fewLineBackground);
                stage = FEW_LINES;
                break;
            case FEW_LINES:
            case LOT_LINES:
                myScene->setBackgroundBrush(fullBackground);
                stage = FULL;
                break;
            case FULL:
                myScene->setBackgroundBrush(blackBackground);
                stage = OFF;
                break;
            default:
                break;
        }

    } else if(e->key() == Qt::Key_Escape){
        timer.stop();
        hide();
    } else if(e->key() == Qt::Key_Q){
        options.getMinLineCount().Inc();
    }else if(e->key() == Qt::Key_A){
        options.getMinLineCount().Dec();
    }else if(e->key() == Qt::Key_W){
        options.getMaxLineCount().Inc();
    }else if(e->key() == Qt::Key_S){
        options.getMaxLineCount().Dec();
    }else if(e->key() == Qt::Key_E){
        options.getPeriod().Dec();
    }else if(e->key() == Qt::Key_D){
        options.getPeriod().Inc();
    }else if(e->key() == Qt::Key_Tab){
        options.setFillingType((FillingType)((int)options.getFillingType()^1));//TODO Сделать по-нормальному
    }
    Update();
}

