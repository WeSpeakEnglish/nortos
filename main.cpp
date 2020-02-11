#include <iostream>
#include <chrono>
#include <thread>
#include "nortos.h"

#define Q_SIZE_FAST 16

using namespace std;



void SomeTestFunction(void){
 static int i = 0;
 cout << i++ << endl;
}

int main()
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;

    cout << "Queue Test" << endl;
    sleep_for(seconds(1));
    pFastQueueIni();
    cout << "Queue Init" << endl;

    for(int i =0; i<100; i++){
        F_push(SomeTestFunction);
        sleep_for(seconds(1));
        F_pull()();
    }

    return 0;
}
