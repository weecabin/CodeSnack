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
  Heading(float initialValue,float rudder, float turnRate, float sampleInterval)
  {
    heading = initialValue;
    this->rudder=rudder;
    this->turnRate=turnRate; // degrees per second per 1 deg of rudder
    interval = sampleInterval;
  }
  void SetRudder(float degrees)
  {
    rudder=degrees;
  }
  float GetHeading()
  {
    heading += rudder*turnRate*interval;
    heading = FixHeading(heading);
    return heading;
  }
  private:
  float heading;
  float rudder;
  float turnRate;
  float interval;
};

int main() {
    float target=2;
    float interval=.5;
    PIDCtrl p(2,0,0,interval,10);
    Heading h(5,0,.1,interval);
    println("time\terror\thead");
    for (int i=0;i<50;i++)
    {
      print(i*interval);print("\t");
      print(HeadingError(target,h.GetHeading()));
      print("\t");
      p.NextError(-HeadingError(target,h.GetHeading()));
      h.SetRudder(p.Correction());
      println(h.GetHeading());
    }
    return 0;
}

