#include "sim.h"

int main(int argc, char *argv[])
{
  printf("\tCSat Simulator loaded.\n");

  QApplication app(argc, argv);
  QMainWindow *window = new QMainWindow();
  Ui::MainWindow ui;
  ui.setupUi(window);

  window->show();
  return app.exec();

  //core_start();
 
}


