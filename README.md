# nortos
NO Any RTOS needed  you will see.... coming very soon
# use with easy
All what U should know:

Initialization: 

pFastQueueIni();

Push your Function:

F_push(SomeTestFunction); // push 

Pull your Function:

F_pull()();

Push from ever you want to push and whatever you want (for interruptions with different priorities better to use separate queues) - the pattern is in header - U will understand it easy
Make your high priority interrupts fast like never before!
Pull from the main process (lowest priority) instead of waiting and in any round - utilize you time properly, all your tasks pushed from whatever you did will be done!

Make multitask and even multithread (by accosting queues to different cores) unbelievable easy, fast way on the platforms, on which you couldn’t even dream about multitask. Wait by doing!
