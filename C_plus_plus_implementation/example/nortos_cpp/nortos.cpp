// NORTOS: The simplisity matter! By Aleksei Tertychnyi, 2015, WTFPL licenced
#include "nortos.h"

fQ::fQ(int sizeQ){ // initialization of Queue
  fQueue = new fP[sizeQ];
  last = 0;
  first = 0;
  lengthQ = sizeQ;
}

fQ::~fQ(){ // initialization of Queue
  delete [] fQueue;
}

int fQ::push(fP pointerF){ // push element from the queue
  if ((last+1)%lengthQ == first){
            return 1;
  }
  fQueue[last++] = pointerF;
  last = last%lengthQ;
  return 0;
}

int fQ::pull(void){ // pull element from the queue
  if (last != first){
  fQueue[first++]();
  first = first%lengthQ;
  return 0;
  }
  else{
   return 1;
  }
}


