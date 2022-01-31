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
  
  }
  void Start(unsigned long millis, float initialHeading, TurnDirection turn, int totalSeconds, int segments)
  {
    interval = 1000*totalSeconds/segments;
    nextTurnTime = millis + interval;
    heading=initialHeading;
    deltaHeading =(turn==left?-1:1) * 360.0/(float)segments;
  }
  void Stop()
  {
    nextTurnTime==0;
  }
  float NewHeading(unsigned long millis)
  {
    if (nextTurnTime==0 || millis<nextTurnTime)
      return heading;
    heading+=deltaHeading;
    heading=FixHeading(heading);
    nextTurnTime+=interval;
    return heading;
  }
  private:
  unsigned int interval;
  unsigned long nextTurnTime=0;
  float heading;
  float deltaHeading;
};

MyTime ms;
float lastHeading=0;

Circle circ;

void Circle()
{
  float nextHeading = circ.NewHeading(ms.millis());
  if (nextHeading!=lastHeading)
  {
    print(ms.millis());print(": ");println(nextHeading);
    lastHeading=nextHeading;
  }
}

int main() 
{
  
  Scheduler s(2);
  s.AddTask(new FunctionTask(Circle,1));
  circ.Start(ms.millis(),lastHeading,left,180,18);
  s.Run(200);
}
