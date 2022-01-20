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
#include <cmath>
#include "../cslib/MyDefines.h"
#include "../cslib/Map.h"
#include <vector>
  
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
enum LoopType {proportional,differential};
void PrintMapValue(float key,std::vector<float> value)
{
  print(key);print("=");print(value[0]);print(",");print(value[1]);print(",");println(value[2]);
}
int main() {
    float initialHeading=0;
    float initialRudder=0;
    float maxRudder=30.0;
    float turnRate=.1;// (deg/sec)/rudderdeg
    float target=10.0;
    float interval=1;
    float windRate=1;
    PIDCtrl p(0,0,0,interval,10);
    int testLoopLen = 40;
    Heading h(initialHeading,initialRudder,maxRudder,turnRate,windRate);
    float kp1=1;
    float ki1=0;
    float kd1=0;
    LoopType lt = differential;;
    //LoopType lt = proportional;
    float maxPidDelta;
    float maxHeadErr;
    if (lt==proportional)
    {
      maxPidDelta = .001;
      maxHeadErr = 5;
    }
    else
    {
      maxPidDelta = .001;
      maxHeadErr = .001;
    }
    Map<float,std::vector<float>> mf;
    if (true)
    {
    int count=0;
    for (float kp=0;kp<=5;kp+=.2)
      for (float ki=0;ki<=5;ki+=.2)
        for(float kd=0;kd>=-5;kd-=.2)
        {
          p.SetCoefficients(kp,ki,kd);
          h.Init(initialHeading,initialRudder);
          float heading;
          for (int i=0;i<testLoopLen;i++)
          {
            float time =i*interval;
            heading = h.GetHeading(time);
            p.NextError(-HeadingError(target,heading));
            if (lt==differential)
              h.SetRudder(h.GetRudder()+p.Correction());
            else
              h.SetRudder(p.Correction());
          }
          float piddelta = p.DeltaError();
          float headerr = std::abs(target-heading);
          if ((piddelta<maxPidDelta) && (headerr<maxHeadErr))
          {
            count++;
            //print(heading);print("/");print(target);print(" ");println(headerr);
            print("kp,ki,kd: ");print(kp);print(",");print(ki);print(",");print(kd);
            print(" DeltaErr: ");print(piddelta);print(" heading: ");println(heading);
            kp1=kp;
            kd1=kd;
            ki1=ki;
            std::vector<float> v{kp,ki,kd};
            mf.AddSorted(piddelta,v);
          }
        }
        print("Optimized PID Count: ");println(count);
      }
      if (mf.Size()>0)
      {
        print("\noptimized kp:");print(mf[0][0]);
        print(",ki:");print(mf[0][1]);
        print(",kd:");println(mf[0][2]);
        
        print("LoopType: ");
        if (lt==proportional)
          println("Proportional");
        else
          println("differential");
        //print("Using kp,ki,kd: ");print(kp1);print(",");print(ki1);print(",");println(kd1);
        //p.SetCoefficients(kp1,ki1,kd1);
        p.SetCoefficients(mf[0][0],mf[0][1],mf[0][2]);
        h.Init(initialHeading,initialRudder);
        print("Target Heading: ");println(target);
        print("Initial Heading: ");println(initialHeading);
        print("Wind Rate(deg/sec): ");println(windRate);
        println("time\tPIDdx\terror\trudder\thead");
       for (int i=0;i<testLoopLen;i++)
       {
        float time = i*interval;
        float heading = h.GetHeading(time);
        print(time);
        print("\t");print(p.DeltaError());
        print("\t");print(HeadingError(target,heading));
        print("\t");print(h.GetRudder());
        print("\t");println(heading);
        p.NextError(-HeadingError(target,heading));
        if (lt==differential)
          h.SetRudder(h.GetRudder()+p.Correction());
        else
          h.SetRudder(p.Correction());
      }
      if (ki1!=0)
        print("PID Integral Term: ");println(p.Integral());
      print("PID Dataset Delta: ");println(p.DeltaError());
      p.Print();
    }
    println("best 10 pid parameters...");
    mf.List(PrintMapValue,10);
    return 0;
}



