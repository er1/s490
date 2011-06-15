#include "sim.h"

Simulator *sim;

int main(int argc, char *argv[])
{
  printf("\tCSat Simulator loaded.\n");

  QApplication app(argc, argv);

  sim = new Simulator(); 

  return app.exec();

  //core_start();
 
}


