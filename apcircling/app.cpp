// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)
#include "../cslib/Scheduler.h"
#include "../cslib/Navigation.h"
#include "../cslib/MyDefines.h"

enum TurnDirection {left,right};
class Circle
{
  public:
  Circle()
  {
    Config();
  }
  void Config(int totalSeconds=240, int segments=20)
  {
    this->segments=segments;
    interval = 1000*totalSeconds/segments;
  }
  void Start(unsigned long millis, float initialHeading, TurnDirection turn)
  {
    nextTurnTime = millis + interval;
    heading=initialHeading;
    deltaHeading =(turn==left?-1:1) * 360.0/(float)segments;
  }
  void Stop()
  {
    nextTurnTime=0;
  }
  bool NewHeading(unsigned long millis, float &heading) 
  {
    if (nextTurnTime==0 || millis<nextTurnTime)
      return false;
    heading = this->heading = FixHeading(this->heading+=deltaHeading);
    nextTurnTime+=interval;
    return true;
  }
  private:
  int segments;
  unsigned int interval;
  unsigned long nextTurnTime=0;
  float heading;
  float deltaHeading;
};

MyTime ms;
float targetheading=0;
Circle circ;

void CircleTask()
{
  if (circ.NewHeading(ms.millis(),targetheading))
  {
    print(ms.millis());print(": ");println(targetheading);
  }
}

void KillCircle()
{
  println("KillCircle");
  circ.Stop();
}

int main()
{
  Scheduler s(2);
  s.AddTask(new FunctionTask(CircleTask,.1));
 // s.AddTask(new FunctionTask(KillCircle,30,1));
  circ.Start(ms.millis(),targetheading,right);
  s.Run(120);
}
