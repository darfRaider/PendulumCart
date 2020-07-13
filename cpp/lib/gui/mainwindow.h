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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <iostream>

#include <math.h>
#include "qcustomplot.h"
#include "util.hpp"
#include "Pendulum2d.hpp"
#include "IntegratorSimpleStep.hpp"
#include "Simulator.hpp"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void setupRealtimeDataDemo(QCustomPlot *customPlot);
  void plotData(std::vector<double>& x, std::vector<double>& y);

private slots:
  void realtimeDataSlot();
  
  void startSimulationPushedSlot();

  void on_buttonIntegrate_clicked();

  void on_inputMassCart_textEdited(const QString &arg1);

  void on_inputMassPendulum_textEdited(const QString &arg1);

  void on_inputLengthPendulum_textEdited(const QString &arg1);

  void on_inputSimulationTime_textEdited(const QString &arg1);

  void on_inputSimulationTimestep_textEdited(const QString &arg1);

  void on_inputIntegratorTimestep_textEdited(const QString &arg1);

  void on_buttonStartSimulation_clicked();

private:
  Ui::MainWindow *ui;
  QString demoName;
  QTimer dataTimer;
  QCPItemTracer *itemDemoPhaseTracer;
  int currentDemoIndex;

  // Variables to check validity
  static bool isRunning;
  static bool entriesValidityTest[N_TEST_FIELDS];


  Pendulum2d* pPendulum;
  Simulator<Pendulum2d, IntegratorSimpleStep<Pendulum2d>>* pSimulator;
  //  Integrator<Pendulum2d> * pIntegrator;
};

#endif // MAINWINDOW_H
