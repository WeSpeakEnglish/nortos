#include <iostream>
#include <chrono>
#include <random>
#include <future>
#include <unistd.h>
#include "nortos.h"

using namespace std;

random_device dev;
mt19937 rng(dev());
uniform_int_distribution<mt19937::result_type> dist1_1000(1,1000);

fQ F1(16);
fQ F2(12);
fQ F3(18);

void SomeTestFunctionOne(void){
  static int i = 0;
  cout << "SomeTestFunctionOne #"<< i++ << endl;
}

void SomeTestFunctionTwo(void){
  static int i = 0;
  cout << "SomeTestFunctionTwo #"<< i++ << endl;
}

void SomeTestFunctionThree(void){
  static int i = 0;
  cout << "SomeTestFunctionThree #"<< i++ << endl;
}

volatile int FlagStop = 0;

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;


void Timer1() {
  while(!FlagStop){
    F1.push(SomeTestFunctionOne);
    sleep_for(milliseconds(dist1_1000(rng)));
  }
}

void Timer2() {
  while(!FlagStop){
    F2.push(SomeTestFunctionTwo);
    sleep_for(milliseconds(dist1_1000(rng)));
  }
}

void Timer3() {
  while(!FlagStop){
    F3.push(SomeTestFunctionThree);
    sleep_for(milliseconds(dist1_1000(rng)));
  }
}

int main()
{
  auto Q_one = async(launch::async, &Timer1);
  auto Q_two = async(launch::async, &Timer2);
  auto Q_three = async(launch::async, &Timer3);

  for(;;){
      F1.pull();
      F2.pull();
      F3.pull();
      usleep(10000);
  }

  return 0;
}
