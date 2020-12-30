// NORTOS: The simplicity matter! By Aleksei Tertychnyi, 2015, WTFPL licenced

#ifndef _NORTOS_H
#define _NORTOS_H
#define Q_SIZE_FAST 16


void F1_QueueIni(void); // initialization of Queue
int F1_push(void (*pointerQ)(void) ); // push element from the queue
void (*F1_pull(void))(void); // pull element from the queue

volatile int F1_last; // number of last element of fast-speed queue
int F1_first; // number of first element of fast-speed queue

void SimpleF1(){;};

void (*F1_Queue[Q_SIZE_FAST])();

inline void F1_QueueIni(void){ // initialization of Queue
  F1_last = 0;
  F1_first = 0;
}

inline int F1_push(void (*pointerQ)(void) ){ // push element from the queue
  if ((F1_last+1)%Q_SIZE_FAST == F1_first)return 1;
  F1_Queue[F1_last++] = pointerQ;
  F1_last%=Q_SIZE_FAST;
  return 0;
}

inline void (*F1_pull(void))(void){ // pull element from the queue
  void (*pullVar)(void);
  if (F1_last == F1_first)return SimpleF1;
  pullVar = F1_Queue[F1_first++];
  F1_first%=Q_SIZE_FAST;
  return pullVar;
}

// ------ 8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----
void F2_QueueIni(void); // initialization of Queue
int F2_push(void (*pointerQ)(void) ); // push element from the queue
void (*F2_pull(void))(void); // pull element from the queue

volatile int F2_last; // number of last element of fast-speed queue
int F2_first; // number of first element of fast-speed queue

void SimpleF2(){;};

void (*F2_Queue[Q_SIZE_FAST])();

inline void F2_QueueIni(void){ // initialization of Queue
  F2_last = 0;
  F2_first = 0;
}

inline int F2_push(void (*pointerQ)(void) ){ // push element from the queue
  if ((F2_last+1)%Q_SIZE_FAST == F2_first)return 1;
  F2_Queue[F2_last++] = pointerQ;
  F2_last%=Q_SIZE_FAST;
  return 0;
}

inline void (*F2_pull(void))(void){ // pull element from the queue
  void (*pullVar)(void);
  if (F2_last == F2_first)return SimpleF2;
  pullVar = F2_Queue[F2_first++];
  F2_first%=Q_SIZE_FAST;
  return pullVar;
}
// ------ 8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----
void F3_QueueIni(void); // initialization of Queue
int F3_push(void (*pointerQ)(void) ); // push element from the queue
void (*F3_pull(void))(void); // pull element from the queue

volatile int F3_last; // number of last element of fast-speed queue
int F3_first; // number of first element of fast-speed queue

void SimpleF3(){;};

void (*F3_Queue[Q_SIZE_FAST])();

inline void F3_QueueIni(void){ // initialization of Queue
  F3_last = 0;
  F3_first = 0;
}

inline int F3_push(void (*pointerQ)(void) ){ // push element from the queue
  if ((F3_last+1)%Q_SIZE_FAST == F3_first)return 1;
  F3_Queue[F3_last++] = pointerQ;
  F3_last%=Q_SIZE_FAST;
  return 0;
}

inline void (*F3_pull(void))(void){ // pull element from the queue
  void (*pullVar)(void);
  if (F3_last == F3_first)return SimpleF3;
  pullVar = F3_Queue[F3_first++];
  F3_first%=Q_SIZE_FAST;
  return pullVar;
}
// ------ 8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----
struct fParams {
  int IntVar;
  float FloatVar;
};

void FP_QueueIni(void); // initialization of Queue
int FP_push(void (*pointerQ)(void), struct fParams * parameterQ); // push element from the queue
void FP_pull(void); // pull element from the queue

volatile int FP_last; // number of last element of fast-speed queue
int FP_first; // number of first element of fast-speed queue

void SimpleFP(){;};

void (*FP_Queue[Q_SIZE_FAST])(struct fParams *);
struct fParams PARAMS_array[Q_SIZE_FAST];

inline void FP_QueueIni(void){ // initialization of Queue
  FP_last = 0;
  FP_first = 0;
}

inline int FP_push(void (*pointerQ)(struct fParams *), struct fParams * parameterQ){ // push element from the queue
  if ((FP_last+1)%Q_SIZE_FAST == FP_first)return 1;
  FP_Queue[FP_last] = pointerQ;
  PARAMS_array[FP_last++] = *parameterQ;
  FP_last%=Q_SIZE_FAST;
  return 0;
}

inline void FP_pull(void){ // pull element from the queue
  void (*pullVar)(struct fParams *);
  struct fParams * Params;
  if (FP_last == FP_first)return;
  Params = &PARAMS_array[FP_first];
  pullVar = FP_Queue[FP_first++];
  FP_first %= Q_SIZE_FAST;
  pullVar(Params);
}
#endif
