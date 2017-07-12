#include "mainwindow.h"
#include "testwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotStartTestClicked(){
    TestWindow* tw = new TestWindow();
    tw->setWindowFlags(Qt::Window);
    tw->showFullScreen();
}
