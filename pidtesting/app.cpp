// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)
#include "../cslib/PIDCtrl.h"
#include "../cslib/Navigation.h"
#include <iostream>
#include <iomanip>

#define println(x)(std::cout<<std::setprecision(3)<<x<<"\n")
#define print(x)(std::cout<<std::setprecision(3)<<x)
  
class Heading
{
  public:
  // initialValue: initial heading
  // rudder: Initial rudder position
  // turnRate: (degrees/sec)/degree of rudder setting
  // sampleInterval: time between samples
  Heading(float initialValue,float initialRudder,float maxRudder, float turnRate, float windRate=0)
  {
    heading = initialValue;
    rudder=initialRudder;
    this->maxRudder=maxRudder;
    this->turnRate=turnRate; // degrees per second per 1 deg of rudder
    time = 0;
    this->windRate=windRate;
  }
  void SetRudder(float degrees)
  {
    rudder=degrees;
    if (rudder>maxRudder && rudder<180)rudder=maxRudder;
    else if (rudder<(360-maxRudder) && rudder>180)rudder=360-maxRudder;
  }
  float GetRudder()
  {
    return rudder;
  }
  float GetHeading(float time)
  {
    if (this->time==time)
      return heading;
    float interval = time-this->time;
    this->time=time;
    heading += rudder*turnRate*interval + windRate*interval;
    heading = FixHeading(heading);
    return heading;
  }
  private:
  float heading;
  float rudder;
  float maxRudder;
  float turnRate;
  float time;
  float windRate;
};

int main() {
    float initialHeading=0;
    float initialRudder=0;
    float maxRudder=30;
    float turnRate=.1;// (deg/sec)/rudderdeg
    float target=10;
    float interval=1;
    float windRate=.5;
    float kp=5;
    float ki=0;
    float kd=0;
  
    PIDCtrl p(kp,ki,kd,interval,20);
    Heading h(initialHeading,initialRudder,maxRudder,turnRate,windRate);
    println("time\terror\trudder\thead");
    for (int i=0;i<50;i++)
    {
      float time = i*interval;
      float heading = h.GetHeading(time);
      print(time);
      print("\t");print(HeadingError(target,heading));
      print("\t");print(h.GetRudder());
      print("\t");println(heading);
      p.NextError(-HeadingError(target,heading));
      h.SetRudder(p.Correction());
    }
    return 0;
}

