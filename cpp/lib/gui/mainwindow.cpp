/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2018 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 25.06.18                                             **
**          Version: 2.0.1                                                **
****************************************************************************/

/************************************************************************************************************
**                                                                                                         **
**  This is the example code for QCustomPlot.                                                              **
**                                                                                                         **
**  It demonstrates basic and some advanced capabilities of the widget. The interesting code is inside     **
**  the "setup(...)Demo" functions of MainWindow.                                                          **
**                                                                                                         **
**  In order to see a demo in action, call the respective "setup(...)Demo" function inside the             **
**  MainWindow constructor. Alternatively you may call setupDemo(i) where i is the index of the demo       **
**  you want (for those, see MainWindow constructor comments). All other functions here are merely a       **
**  way to easily create screenshots of all demos for the website. I.e. a timer is set to successively     **
**  setup all the demos and make a screenshot of the window area and save it in the ./screenshots          **
**  directory.                                                                                             **
**                                                                                                         **
*************************************************************************************************************/

#include "mainwindow.h"
#include "lib/gui/ui_mainwindow.h"

// Initialize static variables
bool MainWindow::entriesValidityTest[N_TEST_FIELDS] = {0};
bool MainWindow::isRunning = false;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  setGeometry(250, 250, 800, 500); // (hPos, vPos, width, height)
  setupRealtimeDataDemo(ui->customPlot);
  Pendulum2d p(10, 10, 1);
  Pendulum2d::TState x0 = {1,1,1,1};
//  p.setInitialCondition(x0);
  setWindowTitle("QCustomPlot RealTimeDataPlot");
  statusBar()->clearMessage();
  ui->customPlot->replot();

  // Initialize variables
  isRunning = false;
  for(int i = 0; i < N_TEST_FIELDS; i++){ // Start with valid choice
      MainWindow::entriesValidityTest[i] = true;
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
  demoName = "Real Time Data Demo";
  
  // include this section to fully disable antialiasing for higher performance:

  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);

  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
  customPlot->addGraph(); // red line
  customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%h:%m:%s");
  customPlot->xAxis->setTicker(timeTicker);
  customPlot->axisRect()->setupFullAxesBox();
  customPlot->yAxis->setRange(-1.2, 1.2);
  
  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
//  realtimeDataSlot();
  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  dataTimer.setTimerType(Qt::PreciseTimer);
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  //dataTimer.start(10); // Interval 0 means to refresh as fast as possible
}

void MainWindow::startSimulationPushedSlot()
{
    return;

}


void MainWindow::realtimeDataSlot()
{
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static int frameCount = 0;
  static double lastPointKey = 0;
  //std::cout << key  << std::endl;
  //std::cout << Qt::PreciseTimer << std::endl;
  if (key-lastPointKey > 0.002 || frameCount == 0) // at most add point every 2 ms
  {
    // add data to lines:
    ui->customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
    ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
    // rescale value (vertical) axis to fit the current data:
    //ui->customPlot->graph(0)->rescaleValueAxis();
    //ui->customPlot->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
  ui->customPlot->replot();
  
  // calculate frames per second:
  static double lastFpsKey;

  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}

void MainWindow::plotData()
{
    for(double t  = 0; t < 10; t+=0.01){
        ui->customPlot->graph(0)->addData(t,sin(t*2.0*3.1315/10.0));
    }
         ui->customPlot->xAxis->setRange(0, 10, Qt::AlignLeft);
  ui->customPlot->replot();
 //   ui->customPlot->replot();
  /*
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static int frameCount = 0;
  static double lastPointKey = 0;
  //std::cout << key  << std::endl;
  //std::cout << Qt::PreciseTimer << std::endl;
  if (key-lastPointKey > 0.002 || frameCount == 0) // at most add point every 2 ms
  {
    // add data to lines:
    ui->customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
    ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
    // rescale value (vertical) axis to fit the current data:
    */// ui->customPlot->graph(0)->rescaleValueAxis(true);  
     //    ui->customPlot->xAxis->setRange(0, 8, Qt::AlignRight);
         /*
    //ui->customPlot->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
                                                            
  ui->customPlot->replot();

  // calculate frames per second:
  static double lastFpsKey;

  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
  */
}

/*
void MainWindow::on_buttonStartSimulation_clicked()
{
    if( isRunning ){
        ui->buttonStartSimulation->setText("Start");
        dataTimer.stop(); // Interval 0 means to refresh as fast as possible
        isRunning = false;
    }
    else {
        ui->buttonStartSimulation->setText("Stop");
        dataTimer.start(10); // Interval 0 means to refresh as fast as possible
        isRunning = true;
    }
}
*/

void MainWindow::on_buttonIntegrate_clicked()
{
    if(!valuesAreValid(MainWindow::entriesValidityTest)){
        ui->statusBar->showMessage("Integration failed",5000);
    }
    else {
        Pendulum2d::TInput zero = 0;
        std::vector<Pendulum2d::TInput>* inputVector = new std::vector<Pendulum2d::TInput>;
        for(int i = 0; i < 100; i++){
            (*inputVector).push_back(zero);
        }
        std::vector<Pendulum2d::TState>* resvec = new std::vector<Pendulum2d::TState>;
        double M = ui->inputMassPendulum->text().toDouble();
        double m = ui->inputMassCart->text().toDouble();
        double L = ui->inputLengthPendulum->text().toDouble();

        double systemTimestep = ui->inputSimulationTimestep->text().toDouble();
        double integratorTimestep = ui->inputIntegratorTimestep->text().toDouble();

        pPendulum = new Pendulum2d(m,M,L);
        //pPendulum->setInputSequence(inputVector);
		Pendulum2d::TState x0 = {0,0,0,0};
        pIntegrator = new IntegratorSimpleStep<Pendulum2d::TState>(x0, integratorTimestep);
        pIntegrator->integrate(resvec);
    }
}

void MainWindow::on_inputMassCart_textEdited(const QString &arg1)
{
    MainWindow::entriesValidityTest[IDX_MASS_CART] = isValidEntry(ui->inputMassCart);
}

void MainWindow::on_inputMassPendulum_textEdited(const QString &arg1)
{
    MainWindow::entriesValidityTest[IDX_MASS_PENDULUM] = isValidEntry(ui->inputMassPendulum);
}

void MainWindow::on_inputLengthPendulum_textEdited(const QString &arg1)
{
    MainWindow::entriesValidityTest[IDX_LENGTH] = isValidEntry(ui->inputLengthPendulum);
}

void MainWindow::on_inputSimulationTime_textEdited(const QString &arg1)
{
    MainWindow::entriesValidityTest[IDX_SIM_TIME] = isValidEntry(ui->inputSimulationTime);
}

void MainWindow::on_inputSimulationTimestep_textEdited(const QString &arg1)
{
    MainWindow::entriesValidityTest[IDX_SIM_TIMESTEP] = isValidEntry(ui->inputSimulationTimestep);
}

void MainWindow::on_inputIntegratorTimestep_textEdited(const QString &arg1)
{
    MainWindow::entriesValidityTest[IDX_INT_TIMESTEP] = isValidEntry(ui->inputIntegratorTimestep);
}

void MainWindow::on_buttonStartSimulation_clicked()
{
    /*
    if( isRunning ){
        ui->buttonStartSimulation->setText("Start");
        isRunning = false;
    }
    else {
        ui->buttonStartSimulation->setText("Stop");
        isRunning = true;
    }
    */
    
    plotData();
}
