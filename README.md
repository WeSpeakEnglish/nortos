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

Push from ever you want to push and whatever you want (for interruptions with different priorities better to use separate queues) - the pattern is in header - U will understand it easy.
Make your high priority interrupts fast like never before!
Pull from the main process (lowest priority) instead of waiting and in any round - utilize you time properly, all your tasks pushed from whatever you did will be done!

Make multitask and even multithread (by accosting queues to different cores) unbelievable easy, fast way on the platforms, on which you couldn’t even dream about multitask. Wait by doing!
#PRE#
When it is necessary to perform several tasks simultaneously on a microcontroller with a single core, we usually think about using RTOS. RTOS usually takes up several additional kilobytes of memory. At the same time, for simple and not very simple applications, RTOS can add more complexity, even with debugging the application. 
# 2#
Most RTOS use a proactive planning algorithm. By using an interrupt, the currently running process is paused and the scheduler is called to determine which process should run next. Processes get a certain amount of CPU time in small chunks. The total length of time got by a process depends on its priority. All processes are usually an infinite loop.
# 3#
On the next slide, let's look at an example of how a single task is interrupted, saving and switching of a context. As you can see, switching between tasks requires several additional operations on the part of the operating system.
Is there a way to do multitasking without RTOS? Is it possible to perform dozens of different tasks at the same time on simple microcontrollers without the help of RTOS? Today we will look at an approach that will allow you to perform many tasks at the same time, while additionally using a very small amount of microcontroller memory. An approach that allows you to keep interrupting procedures fast and at the same time control multitasking in a simple and transparent way.

# 4#
Here are a few application points that suggest using this approach:
•	if the real-time response is not required and can be delayed by a few micro or milliseconds. In most tasks, instant response to events does not play a big role (for example, if the door starts to open after one millisecond, or the LED light up after few milliseconds, or pressing the button will work after few milliseconds, this will not play a big role, and sometimes, on the contrary, reading events with a delay is more reliable, for example, in the case of rattling of a contact)
•	when the seamless process is more important than the so-called real-time response, if we do not want our process to be suddenly interrupted for a significant time to give the time slot to another process, as in the case of RTOS
•	if no RTOS is ported to your platform, for example, in the case of very small and cheap microcontrollers, an old ones, or you do not have enough time to study RTOS in depth
•	if you want a simple way to get multitasking that is at the same time controlled
•	if you do not have free resources to deploy RTOS

# 5#
1.	Divide all your functions into groups: fast (in one pass), slow-to-complete, and middle functions
2.	Create a queue of pointers to these functions for each type
3.	Execute the fastest functions instead of waiting inside the middle functions
4.	Use the medium and fast ones for the waiting inside slow procedures.

Try to leave only linear instructions between waiting, such as: mathematical calculations, entering values into memory, setting and reading pins state, etc. (instructions that do not require waiting). This slide shows a schematic representation of a slow function, a medium function, and a small function, and three queues of pointers to these functions (FIFO)

# 6 #
Let's have a look at examples. 
Examples of fast tasks that run within microseconds, or within a few milliseconds
- a quick calculations
- transferring data from an array
- setting instructions for DMA
- Instructions which usually used inside an interrupt
- read status of the inputs and setting outputs 
Examples of middle tasks:
- reading of a peripheral  devices , for example, of an ADC by polling (SPI, I2C, UART) with waiting for a response (temperature, barometric, gas sensors)
- difficult calculations (FFT,IFFT, trigonometric calculations)
- waiting for a large amount of data to be transmitted
- waiting for the result averaging (ADC, keys rattling)
Examples of slow tasks:
- waiting for the user's response to an event, such as a key press
- waiting for the modem to respond to AT-commands during communication with a remote device, transmitting and receiving data via Wi-Fi to or from a remote server 
- update information on the display

#7#
An example of the simplest implementation in C language. As you can see, there are only a few lines of code, and this, in general, is enough to deploy a multitasking system. Here is declared the queue to a function pointers. The functions contain only a few lines. On function add a function pointer to a queue, another one takes the pointer from the queue. There is also a waiting function here – later we will see how to use it. Here's all you need to use a single queue. If you need more queues, you could do the same for others. All the queues are content-independent. And only one header file, containing all the staff needed.

#8 Fast, slow and medium in some IOT#
We see a fragment of a slow task that uses waiting on the middle queue.

# 9 Fast, slow and medium in some IOT II#
Picture related to the same device, we see how the fast queue wait function is used and how tasks are added to the slow queue.
The wait functions pull pointers from the corresponding queues for a certain amount of time and dereference them by executing procedures. At the top of the slide, we see adding slow tasks to the queue, as well as a fragment of a function that uses waiting on the fast queue. This function is also called inside a slow task. 


# 10 INTERRUPT-DRIVEN TASKS I#
This slide shows a fragment of the CubeMX program window, which is used to configure the ST microcontroller peripheral. In this case, we have the STM32F100 microcontroller. In the interrupt settings window we can see that each interrupt can be set its own priority, so interrupts with a higher priority can be preempted for a while interrupt processing functions with a lower priority. 
Priorities make it possible to implement a mechanism for nested interrupts, while subpriorities determine the sequence of processing interrupts with the same priority if they triggered in the same time.

# 11 INTERRUPT-DRIVEN TASKS II#
Let's see how we can use our approach when handling interrupts. As you can see, this slide on the left shows how all the instructions required to handle this interrupt are located inside the interrupt processing function itself. 
If we use our approach inside an interrupt handler, we simply add a pointer to a function that contains instructions that were previously inside the interrupt handler. 
Thus, our interruption will be performed as quickly as possible. At the same time, instructions will be read from the queue and executed, for example, instead of waiting for another task to run. The event for this interrupt is fixed, and its instructions will be executed, for example, instead of waiting on the fast queue in another task. 
Thus, the task execution will be somewhat delayed, and the signal on the leg will appear with a small delay. For these instructions, a delay of a few milliseconds is not critical.

# 12 INTERRUPT-DRIVEN TASKS III#
Interrupts with the same priority are executed one after the other, and interrupts with a higher priority displace interrupts with a lower priority. In this slide, in the first case, the second IRQ2 interrupt had a higher priority and replaced IRQ1. In the second case interrupts running one after the other.

# 13 INTERRUPT-DRIVEN TASKS IV#
Let's look at another example of using queues with interrupts. Here is a fragment of the function for controlling LEDs depending on the received command via UART interface. As you can see, in this case, our function task was thrown into the middle queue inside the interrupt of UART interface. At the same time, tasks for Timer interrupt are thrown into the quick queue. In this case, both interrupts have the same priority.

#14 DIFFERENT INTERRUPTION PRIORITY#
Consider an example where interrupts have different priorities. To do this, the best approach is to create separate queues for each priority. Here we see an example of throwing pointers into different queues from interrupts with different priority, and an example of reading from such queues. 


# WAITING TIME UTILIZATION#
We will see a couple of examples of how our approach allows us to eliminate expectations. In one example, the HAL_Delay(xxx) function is called in order to provide the procedure for flashing LEDs. Instead of these delays, we simply use the queue waiting function.
 In the second example, we are reading data from the comport using the polling method, and then execute a function. 
With our method, instead, we just give the command to read from the UART port and set an interrupt when the symbol is received. Inside the interrupt itself, we simply throw a pointer to a function that contains instructions for handling it. The event will be captured, and the instructions executed. We didn't wait. 

# Passing parameters to functions inside the queues.#
Sometimes an interruption should fix certain events. For example, we need to know exactly what time this interruption occurred. 
Or a function must accept some parameter. To do this, we need to pass the value of a variable along with a pointer to a function that contains instructions for handling this task. 
Here is an example of implementing this approach in C. An example of passing parameters of different types can be passing a structure containing one or more fields. 
This will make it easy to modify the queue in the future if we need to pass more parameters of different types. Structures with parameters are stored in an array parallel to the one on which the queue is built. And data is entered and read through the pointer. 
Now we can modify the structure for ourselves depending on what parameters we need to pass in our task. 
In the example on the right, two parameters are passed: one of the int type, the other of the float type. Parameters are passed through a pointer to the structure.

# 17 C++ implementation#
As you can see, implementation in C++ looks no more complicated than implementation in C. C++ implementation makes it very easy to create queues of different sizes using the constructor.

# 18 C++ implementation multithread#
This slide shows the implementation in the case of multi-threaded queue. In this case, the indexes of the first and last elements should be of the std:: atomic type, and the operations of adding and taking from the queue must be performed with a mutex lock.

# 19 Summary#
So, let's summarize what advantages this approach offers and what disadvantages it has. 
Advantages:
- not hungry to resources
- transparency and ease of debugging (the process will not be interrupted suddenly)
-easily scalable, allows to parallelize a lot of tasks
- platform independence (can be deployed even on simple microcontrollers)
- does not require additional interrupt resources
- interrupts are fast (allows you to keep instructions inside the interrupt handler as simple and fast as possible. The same time, the interrupts themselves do not interrupt a lower priority function for a long time)
- allow you to effectively utilize the waiting time (instead of waiting, you perform tasks)
- no additional overhead with copying and restoring the context (at the operating system level)
- jobs can be released or inserted in the queue at any time from any interruptions
- tasks can throw themselves into different queues
Disadvantages:
- you need to rank functions by the speed of their execution in order to throw them into the appropriate queues
- tasks are executed not immediately, but with some delay. Instant execution of tasks is also possible, but outside of queues
- in systems that have enough resources to deploy RTOS, sometimes it may be more difficult to deploy this NORTOS than just using a ready library with RTOS. 
- there is no message system between threads, however, as we have seen, it is possible to pass parameters and have global variables
