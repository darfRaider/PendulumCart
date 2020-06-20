#include <boost/numeric/odeint.hpp>
#include <vector>
#include <math.h>
#include <iostream>
//#include <eigen3/Eigen/Core>
//#include <qt5/QtCore/qglobal.h>
//#include <qt5/QtCore/qnamespace.h>
//#include <qt5/QtGui/qpainter.h>
//#include <QtWidgets/QtWidgets>
#include "Pendulum2d.hpp"
#include "IntegratorSimpleStep.hpp"

typedef IntegratorSimpleStep<Pendulum2d::TState, Pendulum2d> TIntegrator;
typedef Pendulum2d::TState TState;
typedef Pendulum2d::TInput TInput;
double M = 1.0;
double m = 1.0;
double L = 1.0;
double timestep = 0.01; // Fixed integrator timestep
double Ts = 0.05;
double u = 0.0;

using namespace boost::numeric::odeint;
int main() {
	std::vector<TInput> inputs;	
	for(int j = 0; j<100; j++){
		inputs.push_back(0);
	}
  Pendulum2d::TState x0 = {0, 0, 0.25, 0};
  Pendulum2d* system = new Pendulum2d(m, M, L, Ts);
  system->setInitialCondition(x0);
	system->setInputSequence(inputs);

	TIntegrator integrator = TIntegrator(system,timestep);
  std::vector<Pendulum2d::TState>* res = new std::vector<Pendulum2d::TState>;

	integrator.integrate(res);
  
	std::cout << "Program ended..." << std::endl;
//  char** test = new char*();
//
//  int te = 1;
//  QApplication qa(te,test);
//  QWidget w;
//  w.show();
//  QPainter painter;
//  painter.setPen(Qt::blue);
//  //painter.setFont(QFont("Arial", 30));
//  //painter.drawText(rect(), Qt::AlignCenter, "Qt");
//  painter.fillRect(0, 0, 100, 100, Qt::white);
  return 0;
}
