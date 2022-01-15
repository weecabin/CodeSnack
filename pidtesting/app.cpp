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
  void Init(float initialValue,float initialRudder)
  {
    heading = initialValue;
    rudder=initialRudder;
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
    float maxRudder=30.0;
    float turnRate=.1;// (deg/sec)/rudderdeg
    float target=10.0;
    float interval=1;
    float windRate=0;
    float kp=5;
    float ki=.9;
    float kd=0;
    PIDCtrl p(kp,ki,kd,interval,20);
    Heading h(initialHeading,initialRudder,maxRudder,turnRate,windRate);
    if (false)
    {
    for (float kp=0;kp<=5;kp+=.2)
      for (float ki=0;ki<=5;ki+=.2)
        for(float kd=0;kd>=-5;kd-=.2)
        {
          p.SetCoefficients(kp,ki,kd);
          h.Init(initialHeading,initialRudder);
          float heading;
          for (int i=0;i<30;i++)
          {
            float time =i*interval;
            heading = h.GetHeading(time);
            p.NextError(-HeadingError(target,heading));
            h.SetRudder(p.Correction());
          }
          float err = abs(heading-target);
          if (p.DeltaError()<0.1 && err<0.1)
          {
            print(heading);print("/");print(target);print(" ");println(err);
            print("kp,ki,kd: ");print(kp);print(",");print(ki);print(",");print(kd);
            print(" DeltaErr: ");print(p.DeltaError());print(" heading: ");println(heading);
          }
        }
      }
      else
      {
        p.SetCoefficients(2.8,0,0);
        h.Init(initialHeading,initialRudder);
        print("Heading Target: ");println(target);
        println("time\terror\trudder\thead");
       for (int i=0;i<40;i++)
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
      print("Integral: ");println(p.Integral());
      p.Print();
    }
    return 0;
}

