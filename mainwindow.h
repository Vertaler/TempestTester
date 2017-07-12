#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "testoptions.h"
#include "testwindow.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    TestOptions options;
    TestWindow *testWindow;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slotStartTestClicked();

signals:
    void testStarted(TestOptions& options);

};

#endif // MAINWINDOW_H
