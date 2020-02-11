#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <random>

#include "nortos.h"

#define Q_SIZE_FAST 16

using namespace std;

 random_device dev;
 mt19937 rng(dev());
 uniform_int_distribution<mt19937::result_type> dist1_1000(1,1000);

void SomeTestFunctionOne(void){
 static int i = 0;
 cout << "I is SomeTestFunctionOne #"<< i++ << endl;
}

void SomeTestFunctionTwo(void){
 static int i = 0;
 cout << "I is SomeTestFunctionTwo #"<< i++ << endl;
}

void SomeTestFunctionThree(void){
 static int i = 0;
 cout << "I is SomeTestFunctionThree #"<< i++ << endl;
}

 volatile int FlagStop = 0;

 using namespace std::this_thread; // sleep_for, sleep_until
 using namespace std::chrono;

unsigned long _stdcall Timer1(void*) {
  while(!FlagStop){
  F_push(SomeTestFunctionOne);
  sleep_for(milliseconds(dist1_1000(rng)));
  }
  return 0;
}

unsigned long _stdcall Timer2(void*) {
  while(!FlagStop){
  F_push(SomeTestFunctionTwo);
  sleep_for(milliseconds(dist1_1000(rng)));
  }
  return 0;
}

unsigned long _stdcall Timer3(void*) {
  while(!FlagStop){
  F_push(SomeTestFunctionThree);
  sleep_for(milliseconds(dist1_1000(rng)));
  }
  return 0;
}

int main()
{

    cout << "Queue Test" << endl;
    sleep_for(milliseconds(1));

    pFastQueueIni();
    cout << "Queue Init" << endl;

    DWORD tid;
    CreateThread(NULL, 0, Timer1, NULL, 0, &tid);
    CreateThread(NULL, 0, Timer2, NULL, 0, &tid);
    CreateThread(NULL, 0, Timer3, NULL, 0, &tid);
    for(;;){

        F_pull()();
    }

    return 0;
}
