// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)
#include "../cslib/PIDCtrl.h"
#include "../cslib/Navigation.h"
#include <iostream>

#define println(x)(std::cout<<x<<"\n")
#define print(x)(std::cout<<x)
  
class Heading
{
  public:
  // initialValue: initial heading
  // rudder: Initial rudder position
  // turnRate: (degrees/sec)/degree of rudder setting
  // sampleInterval: time between samples
  Heading(float initialValue,float initialRudder, float turnRate)
  {
    heading = initialValue;
    rudder=initialRudder;
    this->turnRate=turnRate; // degrees per second per 1 deg of rudder
    time = 0;
  }
  void SetRudder(float degrees)
  {
    rudder=degrees;
  }
  float GetHeading(float time)
  {
    if (this->time==time)
      return heading;
    float interval = time-this->time;
    this->time=time;
    heading += rudder*turnRate*interval;
    heading = FixHeading(heading);
    return heading;
  }
  private:
  float heading;
  float rudder;
  float turnRate;
  float time;
};

int main() {
    float initialHeading=355;
    float initialRudder=0;
    float turnRate=.1;// (deg/sec)/rudderdeg
    float target=5;
    float interval=1;
    float kp=5;
    float ki=0;
    float kd=0;
  
    PIDCtrl p(kp,ki,kd,interval,10);
    Heading h(initialHeading,initialRudder,turnRate);
    println("time\terror\thead");
    for (int i=0;i<50;i++)
    {
      float time = i*interval;
      float heading = h.GetHeading(time);
      print(time);
      print("\t");print(HeadingError(target,heading));
      print("\t");println(heading);
      p.NextError(-HeadingError(target,heading));
      h.SetRudder(p.Correction());
    }
    return 0;
}

