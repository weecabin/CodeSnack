// Verifying that I can include files from another folder

#include "../cslib/CircularBuffer.h"
#include "../cslib/Scheduler.h"
#include "../cslib/MyDefines.h"

void CircularBufferTest();
void SchedulerTest();

int main() {
    //CircularBufferTest();
    SchedulerTest();
    return 0;
}

void task1()
{
  println("task1:");
}

void SchedulerTest()
{
  println("\nScheduler Test...");
  Scheduler s(5);
  s.AddTask(new FunctionTask(task1,.1));
  s.AddTask(new ExampleTask("\tt1",.1));
  s.AddTask(new ExampleTask("\t\tt2",.2));
  s.AddTask(new ExampleTask("\t\t\tt3",.3));
  s.AddTask(new ExampleTask("\t\t\t\tt4",.4));
  s.AddTask(new ExampleTask("t5",.5)); // shouldn't go, as it would exceed 5 tsaks
  s.AddTask(new ExampleTask("t6",.5));// shouldn't go, as it would exceed 5 tsaks
  s.Run(5);
}

void CircularBufferTest()
{
  println("\nCircularBufferTest...");
  println("Created buffer of 10 floats, then added more than 10");
  println("Testing");
  CircularBuffer<float> cb;
  cb.SetSize(10);
  for (float i=1.1;i<20;i+=1.1)
  {
    print("adding: ");
    println(i);
    cb.Push(i);
  }
  println("print the contents...");
  cb.Print();
  println("remove the 5'th element");
  cb.Delete(5);
  cb.Print();
  println("insert 29.1 at the 5'th");
  cb.Insert(5,29.1);
  cb.Print();
  println("insert 39.1 at the 9'th");
  cb.Insert(9,39.1);
  cb.Print();
  println("insert 30.1 at the 10'th");
  println("nothing should happen, can't insert one past the end");
  cb.Insert(10,30.1);
  cb.Print();
}