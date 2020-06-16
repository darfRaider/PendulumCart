#include <boost/numeric/odeint.hpp>
#include <vector>
#include <eigen3/Eigen/Core>
#include <qt5/QtCore/qglobal.h>
#include <qt5/QtCore/qnamespace.h>
#include <qt5/QtGui/qpainter.h>
#include <QtWidgets/QtWidgets>
#include "Pendulum2d.hpp"
#include "IntegratorSimpleStep.hpp"
//typedef Eigen::Vector4d Vector;
typedef std::vector<double> Vector;

void dfdt(const Vector &vec, Vector &dfdt, const double /*t*/);
double ePot(const Vector);
double eKin(const Vector);
double sumE(const Vector);

double M = 1.0;
double m = 1.0;
double l = 1.0;
double g = 9.81;
double u = 0.0;


using namespace boost::numeric::odeint;

int main() {
  Pendulum2d::Vector x0 = {0, 0, 0.25, 0};
  Pendulum2d* p = new Pendulum2d(1,2,3);
  p->setInitialCondition(x0);
  IntegratorSimpleStep<Pendulum2d::Vector,Pendulum2d> integrator = IntegratorSimpleStep<std::vector<double>, Pendulum2d>(p);
  std::vector<Pendulum2d::Vector>* res;
  std::cout << "Before int" << std::endl;
  integrator.integrate(res, p);
  std::cout << "After int" << std::endl;
  //integrator.SomeMethod();
  Vector x(4);
  x[0] = 0;
  x[1] = 0;
  x[2] = -0.25;
  x[3] = 0;
  runge_kutta4< Vector > stepper;
//  integrate_const( stepper , dfdt , x , 0.0 , 10.0 , 0.01 );
  const double dt = 0.001;
  std::cout << "t = " << 0 << ", " << x[0] << ", " << x[1] << ", " << x[2] << ", "  << x[3] << std::endl;
  double e0 = sumE(x);
  double e1;
  for( double t=0.0 ; t<10 ; t+= dt ){
    stepper.do_step( dfdt , x , t , dt);
  }
  e1 = sumE(x);
  std::cout << "Epot = " << ePot(x) << ", Ekin = " << eKin(x) << ", sum = " << sumE(x) << ", delta = " <<  e0-e1 << std::endl;

  std::cout << "done..." << std::endl;
  char** test = new char*();

  int te = 1;
  QApplication qa(te,test);
  QWidget w;
  w.show();
  QPainter painter;
  painter.setPen(Qt::blue);
  //painter.setFont(QFont("Arial", 30));
  //painter.drawText(rect(), Qt::AlignCenter, "Qt");
  painter.fillRect(0, 0, 100, 100, Qt::white);
  return 0;
}

void dfdt(const Vector &x, Vector &res, const double /*t*/){
//  std::cout << x[0] << ", " << x[1] << ", " << x[2] << ", "  << x[3] << std::endl;
  res[0] = x[1];
  res[1] = ((M*g*sin(2*x[2]))/2.0 + M*l*pow(x[3],2)*sin(x[2]) + u)/(M*pow(sin(x[2]),2) + m);
  res[2] = x[3];
  res[3] = -(M*g*sin(x[2]) + M*l*pow(x[3],2)*sin(2*x[2])/2.0 +
             g*m*sin(x[2]) + u*cos(x[2]))/(l*(M*pow(sin(x[2]),2) + m));
}

double sumE(Vector x){
  return ePot(x)+eKin(x);
}

double ePot(Vector x){
  return (1-cos(x[2]))*l*M*g;
}

double eKin(Vector x){
  double eC = 0.5*m*x[1]*x[1];
  double vMx = x[1]+x[3]*l*cos(x[2]);
  double vMy = x[3]*l*sin(x[2]);
  double eM = 0.5*M*(vMx*vMx+vMy*vMy);
  return eC+eM;
}
