#include <QObject>

class Simulator : public QObject
{
  Q_OBJECT

    public:
  
  //Construcor
  Simulator();

  void _simprintf(char * str, ...);

  public slots:

  //recieve this to start the simulation
  void simStart();

  //recieve this to stop the simulation
  void simStop();

 signals:
  
  void appendConsole(const QString &txt);


 private:
  //state of the simulator
  bool simRunning;

  //UI master object
  QMainWindow *window;
  
};
