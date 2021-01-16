// NORTOS: The simplisity matter! By Aleksei Tertychnyi, 2015, WTFPL licenced
#ifndef _NORTOS_H
#define _NORTOS_H
#include <mutex>          // std::mutex

typedef void(*FunctionPointer)(void);

class fQ {
private:
    std::atomic<int> first;
    std::atomic<int> last;
    FunctionPointer * fQueue;
    int lengthQ;
    std::mutex mtx;
public:
    fQ(int sizeQ);
    ~fQ();
    int push(FunctionPointer);
    int pull(void);
};

fQ::fQ(int sizeQ){ // initialization of Queue
  fQueue = new FunctionPointer[sizeQ];
  last = 0;
  first = 0;
  lengthQ = sizeQ;
}

fQ::~fQ(){ // initialization of Queue
  delete [] fQueue;
}

int fQ::push(FunctionPointer pointerF){ // push element from the queue
 mtx.lock();
  if ((last+1)%lengthQ == first){
        mtx.unlock();
        return 1;
  }
  fQueue[last++] = pointerF;
  last = last%lengthQ;
  mtx.unlock();
  return 0;
}

int fQ::pull(void){ // pull element from the queue
 mtx.lock();
  if (last != first){
  fQueue[first++]();
  first = first%lengthQ;
   mtx.unlock();
  return 0;
  }
  else{
   mtx.unlock();
   return 1;
  }
}

// ------ 8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----

#endif
