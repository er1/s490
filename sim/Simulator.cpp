#include "Simulator.h"

Simulator::Simulator()
{
  //we start in the non running state
  simRunning = false;

  //create our main window object
  window = new QMainWindow();

  Ui::MainWindow ui;
  ui.setupUi(window);

  //connect the our slots to the signals we want
  QObject::connect(window->btnStart, SIGNAL(clicked()), this, SLOT(simStart()));
  QObject::connect(window->btnStop, SIGNAL(clicked()), this, SLOT(simStop()));

  QObject::connect(this, SIGNAL(appendConsole(const QString &)), window->txt_SimConsole, SLOT(simStop()));

  window->show();
}

void _simprintf(char * fmt, ...)
{
  va_ list args;
  va_ start(args,fmt);

  //create the qstring
  QString * qs = QString::vsprintf(fmt, args);
  va_ end(args);

  //send the signal
  emit appendConsole(qs);
}

void appendConsole(const QString &txt)
{
  
}

void Simulator::simStart()
{
  
}

void Simulator::simStop()
{
  
}


