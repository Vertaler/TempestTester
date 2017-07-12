#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QDialog>
#include "testoptions.h"

namespace Ui {
class TestWindow;
}

enum TestStage{
    OFF,
    BLINK,
    STABLE
};

class TestWindow : public QDialog
{
    Q_OBJECT

private:
    Ui::TestWindow *ui;
    int screenWidth;
    int screenHeight;

public:
    explicit TestWindow(QWidget *parent = 0);
    ~TestWindow();

public slots:
    void slotTestStarted(TestOptions& options);

};

#endif // TESTWINDOW_H
