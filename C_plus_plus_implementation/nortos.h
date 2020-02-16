// NORTOS: The simplisity matter! By Aleksei Tertychnyi, 2015, WTFPL licenced
#ifndef _NORTOS_H
#define _NORTOS_H
#define Q_SIZE_FAST 16

typedef void(*FunctionPointer)(void);

class fQ {
private:
    unsigned int first;
    unsigned int last;
    FunctionPointer * fQueue;
    unsigned int lengthQ;
    volatile int MutexF;
public:
    fQ(unsigned int sizeQ);
    ~fQ();
    int push(FunctionPointer);
    int pull(void);
};

fQ::fQ(unsigned int sizeQ){ // initialization of Queue
  fQueue = new FunctionPointer[sizeQ];
  last = 0;
  first = 0;
  MutexF = 0;
  lengthQ = sizeQ;
}

fQ::~fQ(){ // initialization of Queue
  delete [] fQueue;
}

int fQ::push(FunctionPointer pointerF){ // push element from the queue
  while(MutexF);
  MutexF = 1;
  if ((last+1)%lengthQ == first){
        MutexF = 0;
        return 1;
  }
  fQueue[last++] = pointerF;
  last %= lengthQ;
  MutexF = 0;
  return 0;
}

int fQ::pull(void){ // pull element from the queue
  while(MutexF);
   MutexF = 1;
  if (last != first){
  fQueue[first++]();
  first%=lengthQ;
  MutexF = 0;
  return 0;
  }
  else{
      MutexF = 0;
        return 1;
  }
}

// ------ 8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----

#endif
