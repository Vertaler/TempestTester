#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include "testoptions.h"
#include "bounded.h"


namespace Ui {
class TestWindow;

}

enum TestStage{
    OFF,
    FEW_LINES,
    LOT_LINES,
    FULL
};

class TestWindow : public QDialog
{
    Q_OBJECT

private:
    QBrush fewLineBackground;
    QBrush lotLineBackground;
    QBrush blackBackground;
    QBrush fullBackground;

    TestOptions options;
    QTimer timer;
    TestStage stage;

    Ui::TestWindow *ui;
    QGraphicsScene* myScene;

    int screenWidth;
    int screenHeight;

    uchar* fewLineData;
    uchar* lotLineData;
    uchar* fullBackgroundData;

    QGraphicsTextItem* hint;

    void checkScreenSize();
public:
    explicit TestWindow(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent* e);
    void Update();
    ~TestWindow();

public slots:
    void slotTestStarted(TestOptions& options);
    void slotTimerTrigger();

};

#endif // TESTWINDOW_H
