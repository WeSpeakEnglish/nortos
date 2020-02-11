// NORTOS: The simplisity matter! By Aleksei Tertychnyi, 2015, WTFPL licenced

#ifndef _NORTOS_H
#define _NORTOS_H
#define Q_SIZE_FAST 16

void pFastQueueIni(void); // initialization of Queue
int F_push(void (*pointerQ)(void) ); // push element from the queue
void (*F_pull(void))(void); // pull element from the queue

volatile int F_last; // number of last element of fast-speed queue
int F_first; // number of first element of fast-speed queue

void SimpleF(){;};

void (*pFastQueue[Q_SIZE_FAST])();

inline void pFastQueueIni(void){ // initialization of Queue
  F_last = 0;
  F_first = 0;
}

inline int F_push(void (*pointerQ)(void) ){ // push element from the queue
  if ((F_last+1)%Q_SIZE_FAST == F_first)return 1;
  pFastQueue[F_last++] = pointerQ;
  F_last%=Q_SIZE_FAST;
  return 0;
}

inline void (*F_pull(void))(void){ // pull element from the queue
  void (*pullVar)(void);
  if (F_last == F_first)return SimpleF;
  pullVar = pFastQueue[F_first++];
  F_first%=Q_SIZE_FAST;
  return pullVar;
}
#endif
