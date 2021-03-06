#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <random>
#include <future>

#include "nortos.h"

#define Q_SIZE_FAST 16

using namespace std;

random_device dev;
mt19937 rng(dev());
uniform_int_distribution<mt19937::result_type> dist1_1000(1,1000);

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
    F1_push(SomeTestFunctionOne);
    sleep_for(milliseconds(dist1_1000(rng)));
  }
}

void Timer2() {
  while(!FlagStop){
    F2_push(SomeTestFunctionTwo);
    sleep_for(milliseconds(dist1_1000(rng)));
  }
}

void Timer3() {
  while(!FlagStop){
    F3_push(SomeTestFunctionThree);
    sleep_for(milliseconds(dist1_1000(rng)));
  }
}
#define COUNT_LIMIT 1000000
int main()
{
  unsigned long count =0 ;

  F1_QueueIni();
  F2_QueueIni();
  F3_QueueIni();

  auto Q_one = async(launch::async, &Timer1);
  auto Q_two = async(launch::async, &Timer2);
  auto Q_three = async(launch::async, &Timer3);


  for(;;){
    switch(++count%3){
    case 0:
      F1_pull()();
      break;
    case 1:
      F2_pull()();
      break;
    case 2:
      F3_pull()();
      break;
    }
  }

  return 0;
}
