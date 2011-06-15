#include <QThread>
#include "core.h"

class SimSatThread : public QThread
{
 public:
  SimSatThread();
  void run();
  void setRunState(bool running);
 private:
  long long cycles;
  bool isRunning;
}
