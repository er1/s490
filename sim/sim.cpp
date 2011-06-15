#include "sim.h"

int main(int argc, char *argv[])
{
  printf("\tCSat Simulator loaded.\n");

  QApplication app(argc, argv);

  Simulator * sim = new Simulator(); 

  return app.exec();

  //core_start();
 
}


