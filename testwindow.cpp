#include "testwindow.h"
#include "ui_testwindow.h"
#include "backgroundgenerator.h"
#include "utils.h"

#include <string>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QThread>


void TestWindow::checkScreenSize()
{
    QRect mainScreenSize =  QApplication::desktop()->screenGeometry();
    int newScreenHeight = mainScreenSize.height();
    int newScreenWidth = mainScreenSize.width();
    if((screenWidth != newScreenWidth) || (screenHeight != newScreenHeight) ){

        screenWidth = newScreenWidth;
        screenHeight = newScreenHeight;

        delete[] fewLineData;
        delete[] lotLineData;
        delete[] fullBackgroundData;

        int len =  4 * screenWidth * screenHeight;
        fewLineData = new uchar[len];
        lotLineData = new uchar[len];
        fullBackgroundData = new uchar[len];

    }
}

TestWindow::TestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    connect(&timer, &QTimer::timeout, this, &TestWindow::slotTimerTrigger);


    //to safe delete[] in checkScreenSize();
    fewLineData = new uchar[1];
    lotLineData = new uchar[1];
    fullBackgroundData = new uchar[1];

    checkScreenSize();

    ui->graphicsView->resize(screenWidth, screenHeight);



    myScene = new QGraphicsScene();
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    ui->graphicsView->setWindowState(Qt::WindowFullScreen);
    ui->graphicsView->setScene(myScene);
    ui-> graphicsView->setStyleSheet( "QGraphicsView { border-style: none; }" );


    hint = new QGraphicsTextItem();
    hint->setPos(0,0);
    QFont font("Calibri", 30);

    hint->setDefaultTextColor(Qt::red);
    hint->setFont(font);
    myScene->addItem(hint);

    blackBackground = QBrush(Qt::black);
}

TestWindow::~TestWindow()
{
    timer.stop();
    delete myScene;
    delete ui;
}

void TestWindow::Update()
{
    BackgroundGenerator backgroundGenerator;

    fewLineBackground = backgroundGenerator.GenerateBackground(fewLineData,screenWidth, screenHeight, options.getMinLineCount()->Value(), options.getFillingType());
    lotLineBackground = backgroundGenerator.GenerateBackground(lotLineData, screenWidth, screenHeight, options.getMaxLineCount()->Value(), options.getFillingType());
    fullBackground = backgroundGenerator.GenerateBackground(fullBackgroundData, screenWidth, screenHeight, 0, options.getFillingType());

    timer.start((int)(1000 * options.getPeriod()->Value()));
}


void TestWindow::slotTestStarted(TestOptions &options){

    this->options = options;
    checkScreenSize();

    stage = OFF;
    myScene->setBackgroundBrush(blackBackground);
    Update();
}


void TestWindow::slotTimerTrigger()
{
    hint->setPlainText("");
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
        options.getMinLineCount()->Inc();
    }else if(e->key() == Qt::Key_A){
        options.getMinLineCount()->Dec();
    }else if(e->key() == Qt::Key_W){
        options.getMaxLineCount()->Inc();
    }else if(e->key() == Qt::Key_S){
        options.getMaxLineCount()->Dec();
    }else if(e->key() == Qt::Key_E){
        options.getPeriod()->Dec();
    }else if(e->key() == Qt::Key_D){
        options.getPeriod()->Inc();
    }else if(e->key() == Qt::Key_Tab){
        options.setFillingType((FillingType)((int)options.getFillingType()^1));//TODO Сделать по-нормальному
    }
    Update();
    if(e->key() == Qt::Key_Q || e->key() == Qt::Key_A){
        myScene->setBackgroundBrush(fewLineBackground);
    }
    if(e->key() == Qt::Key_W || e->key() == Qt::Key_S){
        myScene->setBackgroundBrush(lotLineBackground);
    }
    if(e->key() == Qt::Key_E || e->key() == Qt::Key_D){
        std::string text = "Период мерцаний: " + to_string( options.getPeriod()->Value() ) + " (сек)";
        hint->setPlainText(text.data());

    }

}

