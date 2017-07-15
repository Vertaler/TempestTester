#include "mainwindow.h"
#include "testwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    testWindow = new TestWindow();
    testWindow->setWindowFlags(Qt::Window);
    connect(this, &MainWindow::testStarted, testWindow, &TestWindow::slotTestStarted);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotStartTestClicked()
{
    testWindow->showFullScreen();
    options.maxLineCount = ui->maxCountSpinbox->value();
    options.minLineCount = ui-> minCountSpinbox->value();
    options.period = ui->periodSpinBox->value();
    emit testStarted(options);
}
