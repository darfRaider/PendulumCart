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
**  along with this program.  If not, see http://www.gnu.org/licenses/.   ** **                                                                        **
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

 // setGeometry(250, 250, 800, 500); // (hPos, vPos, width, height)

  setupRealtimeDataDemo(ui->customPlot);
  setupRealtimeDataDemo(ui->customPlot2);

  setWindowTitle("QCustomPlot RealTimeDataPlot");
  statusBar()->clearMessage();
  ui->customPlot->replot();

  // Initialize variables
  isRunning = false;
  // Add new fields
  for(int i = 0; i < N_TEST_FIELDS; i++){ // Start with valid choice
      MainWindow::entriesValidityTest[i] = true;
  }

  // Set some system related stuff
  ui->plotStateNr->setMaximum(Pendulum2d::Nstates-1);

  // fill up state description for plot
  for(int i = 0; i < Pendulum2d::Nstates; i++){
      QString s = str2qstr(Pendulum2d::getStateUnit(i));
      ui->systemStates->insertItem(i, s);
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}

// Move the following to another file
QString MainWindow::str2qstr(std::string s){
    return QString::fromUtf8(s.c_str());
}

double MainWindow::getMax(std::vector<double>& vec){
    return *std::max_element(vec.begin(), vec.end());
}

double MainWindow::getMin(std::vector<double>& vec){
    return *std::min_element(vec.begin(), vec.end());
}

///////////////////////////////////////////////////

// This function is used to setup the look of the graph
void MainWindow::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
  // include this section to fully disable antialiasing for higher performance:

  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
 // font.setStyleStrategy(QFont::Antialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);

  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
  //customPlot->addGraph(); // red line
  //customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%h:%m:%s");
  customPlot->xAxis->setTicker(timeTicker);
  customPlot->axisRect()->setupFullAxesBox();
  //customPlot->yAxis->setRange(-1.2, 1.2);
  
  // make left and bottom axes transfer their ranges to right and top axes:
  //connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  //connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
//  realtimeDataSlot();
  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  //dataTimer.setTimerType(Qt::PreciseTimer);
  //connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
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
    //ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
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
          .arg(ui->customPlot->graph(0)->data()->size())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}


// TODO: add these in external file
void setXlabels(const QCustomPlot* plt, const std::string xLabel){
    QString xl = QString::fromUtf8(xLabel.c_str());
    plt->xAxis->setLabel(xl);
}

void setYlabels(const QCustomPlot* plt, const std::string yLabel){
    QString yl = QString::fromUtf8(yLabel.c_str());
    plt->yAxis->setLabel(yl);
}

void setAxis(const QCustomPlot* plt, const double axisLimits[4]){
    plt->xAxis->setRange(axisLimits[0],axisLimits[1]);
    plt->yAxis->setRange(axisLimits[2],axisLimits[3]);
}

void axisEqual(QCustomPlot* plt){
    plt->replot();
    int pxX = plt->width();
    double xMax = plt->xAxis->range().upper;
    double xMin = plt->xAxis->range().lower;
    double xRatio = (xMax-xMin)/pxX;

    int pxY = plt->height();
    double yMax = plt->yAxis->range().upper;
    double yMin = plt->yAxis->range().lower;
    double yRatio = (yMax-yMin)/pxY;
    // (newXmax - xMin)/pxX == yRatio
    if(xRatio < yRatio){
        // Scale xAxis
        double newXmax = yRatio*pxX + xMin;
        double axis[] = {xMin, newXmax, yMin, yMax};
        setAxis(plt, axis);
    }
    else {
        // Scale yAxis
        double newYmax = xRatio*pxY + yMin;
        double axis[] = {xMin, xMax, yMin, newYmax};
        setAxis(plt, axis);
    }
    plt->replot();
}

void drawCircle(QCustomPlot* plt, double xc, double yc, double r){
    double PI = acos(-1);
    int N = 10;
    QCPCurve *circ = new QCPCurve(plt->xAxis, plt->yAxis);
    QVector<QCPCurveData> circleData(N+1);
    double delta = 2.0*PI/N;
    for(int i = 0; i < N; i++){
        double phi = i*delta;
        circleData[i] = QCPCurveData(i, cos(phi)*r + xc, sin(phi)*r + yc);
    }
    circleData[N] = circleData[0];
    circ->data()->set(circleData,true);
}

void rotateVectors(QVector<double>& x, QVector<double>& y, double a){
    int N = x.size();
    double sa = sin(a);
    double ca = cos(a);
    for(int i = 0; i < N; i++){
        double xv, yv;
        xv = x[i];
        yv = y[i];
        x[i] = xv*ca-yv*sa;
        y[i] = xv*sa+yv*ca;
    }
}

void drawRect(QCustomPlot* plt, double xc, double yc, double w, double h, double alpha = 0){
    QCPCurve *rect = new QCPCurve(plt->xAxis, plt->yAxis);
    double h2 = h/2.0;
    double w2 = w/2.0;
    QVector<double> x = {w2+xc,-w2+xc,-w2+xc,w2+xc,w2+xc};
    QVector<double> y = {h2+yc,h2+yc,-h2+yc,-h2+yc,h2+yc};
    if(alpha != 0){
        rotateVectors(x, y, alpha);
    }
    QBrush shadowBrush (QColor(0,0,0), Qt::Dense5Pattern);


    rect->setBrush(shadowBrush);
    rect->setData(x,y);
}

// **********************************************

//////////////////////////////
void MainWindow::plotData(int graphID, std::vector<double>& x, std::vector<double>& y, const std::string xLabel, const std::string yLabel)
{
    //TODO: use plt as input argument
  QCustomPlot* plt = ui->customPlot;

  plt->graph(graphID)->data()->clear();
  double xMin, xMax, yMin, yMax;
  xMin = getMin(x);
  xMax = getMax(x);
  yMin = getMin(y);
  yMax = getMax(y);
  const double limits[] = {xMin, xMax, yMin, yMax};
  const int N = x.size();

  for(int i = 0; i < N; i++){
     ui->customPlot->graph(graphID)->addData(x[i],y[i]);
  }
  setXlabels(plt, xLabel);
  setYlabels(plt, yLabel);
  setAxis(plt, limits);
  plt->replot();

  drawRect(ui->customPlot2,0,0,4,2,0.5);
  drawCircle(ui->customPlot2,1,1,0.5);
  const double axis[] = {-2,2,-3,3};
  setAxis(ui->customPlot2,axis);
  axisEqual(ui->customPlot2);
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
    if(!valuesAreValid(MainWindow::entriesValidityTest)){
        ui->statusBar->showMessage("Integration failed",5000);
    }
    else {
        ui->statusBar->showMessage("Integrating...");
        Pendulum2d::TInput zero = 0;
        std::vector<Pendulum2d::TInput>* inputVector = new std::vector<Pendulum2d::TInput>;
        for(int i = 0; i < 100; i++){
            (*inputVector).push_back(zero);
        }
        std::vector<Pendulum2d::TState>* resvec = new std::vector<Pendulum2d::TState>;
        std::vector<double>* tout = new std::vector<double>();

        double M = ui->inputMassPendulum->text().toDouble();
        double m = ui->inputMassCart->text().toDouble();
        double L = ui->inputLengthPendulum->text().toDouble();

        double systemTimestep = ui->inputSimulationTimestep->text().toDouble();
        double simulationTime = ui->inputSimulationTime->text().toDouble();
        double integratorTimestep = ui->inputIntegratorTimestep->text().toDouble();


        pPendulum = new Pendulum2d(m,M,L);


        Simulator<Pendulum2d, IntegratorSimpleStep<Pendulum2d>>::config cfg;
        cfg.dT_integrator = integratorTimestep;
        cfg.dT_inputSequence = systemTimestep;
        cfg.tSimulation = simulationTime;
        cfg.x0 = {0,0,0.25,0};
        pSimulator = new Simulator<Pendulum2d, IntegratorSimpleStep<Pendulum2d>>(pPendulum, cfg);
        pSimulator->simulate(resvec, tout);
        int n = (*resvec).size();
        this->res = resvec;
        this->tout = tout;
        //delete resvec;
        //delete tout;
        //pPendulum->setInputSequence(inputVector);
        //pIntegrator = new IntegratorSimpleStep<Pendulum2d>(x0, integratorTimestep);
        //pIntegrator->integrate(10.0, resvec);
        //TODO : free memory
    }
    int stateToPlot = ui->plotStateNr->value();
    std::vector<double>* state = TSimulator::getStateVector(stateToPlot, this->res);
    plotData(0, *tout, *state, "Time (s)", Pendulum2d::getStateUnit(stateToPlot));
    ui->statusBar->showMessage("Finished...",5000);

    //delete pPendulum;
    //delete pSimulator;

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
    
    //plotData();
}

void MainWindow::on_inputInputType_currentIndexChanged(int index)
{
    // Indices: 0: Zero-input
    //          1: Constant input
    //          2: Sinusoidal input
    switch(index){
        case 0:
            ui->inputInputAmplitude->setEnabled(false);
            ui->inputInputFrequency->setEnabled((false));
            ui->inputInputPhase->setEnabled(false);
        break;

        case 1:
            ui->inputInputAmplitude->setEnabled(true);
            ui->inputInputFrequency->setEnabled((false));
            ui->inputInputPhase->setEnabled(false);
        break;

        case 2:
            ui->inputInputAmplitude->setEnabled(true);
            ui->inputInputFrequency->setEnabled((true));
            ui->inputInputPhase->setEnabled(true);
        break;
    }
}

void MainWindow::on_plotStateNr_valueChanged(int stateToPlot)
{
    std::vector<double>* state = TSimulator::getStateVector(stateToPlot, this->res);
    plotData(0, *tout, *state, "Time (s)", Pendulum2d::getStateUnit(stateToPlot));
}

void MainWindow::on_systemStates_currentRowChanged(int stateToPlot)
{
    std::vector<double>* state = TSimulator::getStateVector(stateToPlot, this->res);
    plotData(0, *tout, *state, "Time (s)", Pendulum2d::getStateUnit(stateToPlot));
}
