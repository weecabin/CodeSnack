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
  // test

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
    if (rudder>maxRudder)rudder=maxRudder;
    else if (rudder<-maxRudder)rudder=-maxRudder;
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
    float windRate=-.5;
    PIDCtrl p(0,0,0,interval,15);
    int testLoopLen = 50;
    Heading h(initialHeading,initialRudder,maxRudder,turnRate,windRate);
    float kp1=1;
    float ki1=0;
    float kd1=0;
    //LoopType lt = differential;;
    LoopType lt = proportional;
    float maxPidDelta;
    float maxHeadErr;
    if (lt==proportional)
    {
      maxPidDelta = 1;
      maxHeadErr = 1;
    }
    else
    {
      maxPidDelta = 1;
      maxHeadErr = 1;
    }
    Map<float,std::vector<float>> mf(10);
    if (true)
    {
    int count=0;
    for (float kp=-10;kp<=15;kp+=.2)
      for (float ki=-10;ki<=10;ki+=.2)
        for(float kd=10;kd>=-10;kd-=.2)
        {
          p.SetCoefficients(kp,ki,kd);
          h.Init(initialHeading,initialRudder);
          float heading;
          for (int i=0;i<testLoopLen;i++)
          {
            float time =i*interval;
            heading = h.GetHeading(time);
            p.NextError(-HeadingError(target,heading));
            if (!p.BufferIsFull())continue;
            if (lt==differential)
              h.SetRudder(h.GetRudder()+p.Correction());
            else
              h.SetRudder(p.Correction());
          }
          if (!p.BufferIsFull())continue;
          float piddelta = p.DeltaError();
          float headerr = std::abs(target-heading);
          if ((piddelta<maxPidDelta) && (headerr<maxHeadErr))
          {
            count++;
            //print(heading);print("/");print(target);print(" ");println(headerr);
            //print("kp,ki,kd: ");print(kp);print(",");print(ki);print(",");print(kd);
            //print(" DeltaErr: ");print(piddelta);print(" heading: ");println(heading);
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
        std::vector<float> opt= mf.GetValue(0);
        std::cout<<"\noptimized kp:"<<opt[0]<<",ki:"<<opt[1]<<",kd:"<<opt[2]<<"\n";
        
        print("LoopType: ");
        if (lt==proportional)
          println("Proportional");
        else
          println("differential");
        //print("Using kp,ki,kd: ");print(kp1);print(",");print(ki1);print(",");println(kd1);
        //p.SetCoefficients(kp1,ki1,kd1);
        p.SetCoefficients(mf[0][0],mf[0][1],mf[0][2]);
        print("initialized pid ");p.BufferIsFull()?println("full\n"):println("not full\n");
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
        if (!p.BufferIsFull())continue;
        if (lt==differential)
          h.SetRudder(h.GetRudder()+p.Correction());
        else
          h.SetRudder(p.Correction());
      }
      if (ki1!=0)
        print("PID Integral Term: ");println(p.Integral());
      print("PID Dataset Delta: ");println(p.DeltaError());
      p.Print();
      print("\nbest 10/");print(mf.Size());println(" pid parameters...");
      mf.List(PrintMapValue);
    }
    
    return 0;
}



