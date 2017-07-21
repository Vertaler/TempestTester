#include "mainwindow.h"
#include "testwindow.h"
#include "ui_mainwindow.h"
#include "bounded.h"
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    testWindow = new TestWindow();
    testWindow->setWindowFlags(Qt::Window);

    Bounded<int>* minLineCount = new Bounded<int>(
            ui->minCountSpinbox->singleStep(),
            ui-> minCountSpinbox->maximum(),
            ui-> minCountSpinbox->minimum(),
            0
        );
    options.setMinLineCount(minLineCount);


    Bounded<int>* maxLineCount = new Bounded<int>(
            ui->maxCountSpinbox->singleStep(),
            ui-> maxCountSpinbox->maximum(),
            ui-> maxCountSpinbox->minimum(),
            0
        );
    options.setMaxLineCount(maxLineCount);

    Bounded<double>* period = new Bounded<double>(
                ui->periodSpinBox->singleStep(),
                ui->periodSpinBox->maximum(),
                ui-> periodSpinBox->minimum(),
                0.0
            );
    options.setPeriod(period);

    connect(this, &MainWindow::testStarted, testWindow, &TestWindow::slotTestStarted);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotStartTestClicked()
{
    testWindow->showFullScreen();
    options.getMaxLineCount()->Set(ui->maxCountSpinbox->value());
    options.getMinLineCount()->Set(ui-> minCountSpinbox->value());
    options.getPeriod()->Set(ui->periodSpinBox->value());
    options.setFillingType( (ui->VGA->isChecked()) ? WHITE : RANDOM ) ;
    emit testStarted(options);
}
