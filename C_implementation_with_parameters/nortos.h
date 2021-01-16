// NORTOS: The simplicity matter! By Aleksei Tertychnyi, 2015, WTFPL licenced
#ifndef _NORTOS_H
#define _NORTOS_H

#define Q_SIZE_FAST 16

extern void F1_QueueIni(void); // initialization of Queue
extern int F1_push(void (*pointerQ)(void) ); // push element into the queue
extern void (*F1_pull(void))(void); // pull element from the queue


// ------ 8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----
extern void F2_QueueIni(void); // initialization of Queue
extern int F2_push(void (*pointerQ)(void) ); // push element into the queue
extern void (*F2_pull(void))(void); // pull element from the queue


// ------ 8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----
extern void F3_QueueIni(void); // initialization of Queue
extern int F3_push(void (*pointerQ)(void) ); // push element into the queue
extern void (*F3_pull(void))(void); // pull element from the queue


// ------ 8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----
struct fParams {
  int IntVar;
  float FloatVar;
};

extern void FP_QueueIni(void); // initialization of Queue
extern int FP_push(void (*pointerQ)(struct fParams *), struct fParams * parameterQ);
extern void FP_pull(void); // pull element into the queue


#endif
