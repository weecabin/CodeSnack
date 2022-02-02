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
    //println("in Config");
    this->segments=segments;
    interval = 1000*totalSeconds/segments;
  }
  void Start(unsigned long millis, float initialHeading, TurnDirection turn)
  {
    nextTurnTime = millis;
    heading=initialHeading;
    deltaHeading =(turn==left?-1:1) * 360.0/(float)segments;
    enabled=true;
  }
  void Stop()
  {
    enabled=false;
  }
  bool NewHeading(unsigned long millis, float &heading) 
  {
    if (!enabled || millis<nextTurnTime)
      return false;
    heading = this->heading = FixHeading(this->heading+=deltaHeading);
    nextTurnTime+=interval;
    return true;
  }
  private:
  bool enabled=false;
  int segments;
  unsigned long interval;
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
  println("in main");
  Scheduler s(2);
  s.AddTask(new FunctionTask(CircleTask,.01));
  s.AddTask(new FunctionTask(KillCircle,15,1));
  circ.Config(15,40);
  circ.Start(ms.millis(),targetheading,right);
  s.Run(20);
}
