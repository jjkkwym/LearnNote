# Freertos

## 基本要素
FreeRTOS中的基础要素包括任务（Task）、调度器（Scheduler）、信号量（Semaphore）、事件组（Event Group）和队列（Queue），它们是构建实时多任务系统的核心组件。

1. 任务（Task）：任务是FreeRTOS中最基本的执行单位。每个任务都是一个独立的函数，具有自己的优先级和堆栈空间。任务可以通过创建、挂起、恢复、删除等操作进行管理。FreeRTOS使用任务管理器来协调不同优先级的任务之间的执行顺序。

2. 调度器（Scheduler）：调度器是FreeRTOS的核心部分，负责任务的调度和切换。调度器采用优先级抢占式调度算法，根据任务的优先级和调度策略决定任务何时运行。调度器会保存任务的上下文，并在任务切换时进行恢复，从而实现任务之间的切换。

3. 信号量（Semaphore）：信号量是一种用于任务同步和资源管理的机制。FreeRTOS提供了二进制信号量和计数信号量两种类型。通过使用信号量，任务可以获取或释放资源，并进行互斥访问和同步操作。

4. 事件组（Event Group）：事件组是一种用于任务通信和同步的机制。它可以用来等待和设置特定的事件。任务可以等待一个或多个事件的发生，并在事件发生时被唤醒继续执行。事件组提供了一种有效的方式来实现任务之间的通信和控制。

5. 队列（Queue）：队列是一种用于任务之间通信的机制，实现了生产者-消费者模型。任务可以将消息或数据项发送到队列中，另一个任务可以从队列中接收这些消息或数据项。队列可以在不同优先级的任务之间进行数据传递并实现解耦。

除了以上基础要素之外，FreeRTOS还提供了定时器（Timer）、软件定时器（Software Timer）、互斥锁（Mutex）、软件中断（Software Interrupt）等功能和机制，以满足不同的应用需求。

这些基础要素及其相关的API函数和配置选项，构成了FreeRTOS的核心功能，使得开发者可以方便地创建和管理多任务系统，实现实时性、可靠性和可移植性。

## 二值信号量

二值信号量（Binary Semaphore）是一种特殊类型的信号量，其取值范围只有两个：0和1。它主要用于同步任务的执行，特别是在某个任务需要等待另一个任务完成后才能继续执行的情况下。

使用二值信号量时，信号量可以有两个状态：

1. 0：表示资源不可用或被占用，任务需要等待。
2. 1：表示资源可用或空闲，任务可以继续执行。

二值信号量可以通过以下API来操作：

- `xSemaphoreCreateBinary()`：创建一个二值信号量。初始状态下，它将被设置为不可用（0）。
- `xSemaphoreGive()`：将二值信号量的值设置为1，表示资源可用。
- `xSemaphoreTake()`：尝试获取二值信号量。如果信号量的值为1，则任务可以继续执行，同时将信号量的值设置为0；如果信号量的值为0，则任务将被阻塞，直到信号量的值被设置为1。
- `xSemaphoreGiveFromISR()`和`xSemaphoreTakeFromISR()`：用于在中断服务程序（ISR）中操作二值信号量。

下面是一个使用二值信号量的示例：

```c
SemaphoreHandle_t binarySemaphore;

// 在任务初始化函数中创建二值信号量
binarySemaphore = xSemaphoreCreateBinary();
if (binarySemaphore == NULL) {
    // 二值信号量创建失败
    // 处理错误情况
}

void Task1(void *pvParameters) {
    // 一些任务处理
    // ...

    // 设置二值信号量为可用状态
    xSemaphoreGive(binarySemaphore);

    // 继续执行其他任务
    // ...
}

void Task2(void *pvParameters) {
    // 等待二值信号量变为可用
    if (xSemaphoreTake(binarySemaphore, portMAX_DELAY) == pdTRUE) {
        // 二值信号量变为可用
        // 继续执行任务
    }
}

void setup() {
    // 创建任务1和任务2
    xTaskCreate(Task1, "Task1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task2, "Task2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

    // 启动调度器
    vTaskStartScheduler();
}

void loop() {
    // 主循环中不需要做任何操作
}
```

在上面的示例中，Task1任务先执行，并在某个时刻通过`xSemaphoreGive()`将二值信号量设置为可用状态。接着，Task2任务等待二值信号量变为可用，通过`xSemaphoreTake()`尝试获取信号量。只有当Task1执行了`xSemaphoreGive()`后，Task2才能继续执行。

二值信号量在许多多任务应用程序中都有很大的用途，可以确保任务按照特定的顺序和条件进行执行，实现任务之间的同步和互斥。

## 信号量

FreeRTOS中的信号量（Semaphore）是一种用于任务同步和资源管理的机制。它允许任务在获取资源之前进行等待，并在资源可用时进行通知，从而实现任务之间的互斥和同步操作。

FreeRTOS提供了两种类型的信号量：二进制信号量（Binary Semaphore）和计数信号量（Counting Semaphore）。

1. 二进制信号量（Binary Semaphore）：二进制信号量只有两个状态，可以取值0或1。它用于控制对单个资源的访问，通常用于互斥访问共享资源的场景。一个任务可以获取二进制信号量，当资源可用时，信号量值为1；当资源不可用时，信号量值为0。另一个任务可以通过释放二进制信号量来通知该资源现在可以被获取。

2. 计数信号量（Counting Semaphore）：计数信号量是一个可以取值大于等于0的整数。它用于控制对多个资源的访问，通常用于限制可用资源的数量。任务可以获取计数信号量，每次获取会使信号量值减1。当信号量值为0时，表示资源已经全部被占用，进一步的任务获取将会阻塞。当资源被释放时，信号量值增加，被阻塞的任务可以继续获取资源。

在FreeRTOS中，使用信号量的一般步骤如下：

1. 创建信号量：使用`xSemaphoreCreateBinary()`函数创建二进制信号量，或使用`xSemaphoreCreateCounting()`函数创建计数信号量。这些函数会返回一个`SemaphoreHandle_t`类型的信号量句柄。

2. 获取信号量：使用`xSemaphoreTake()`函数获取信号量。对于二进制信号量，无论信号量值是0还是1，任务会立即获取信号量。对于计数信号量，如果信号量值大于0，则任务可以获取信号量；如果信号量值等于0，则任务会被阻塞等待。

3. 释放信号量：使用`xSemaphoreGive()`函数释放信号量。对于二进制信号量，信号量值会被设置为1。对于计数信号量，信号量值会增加。

需要注意的是，执行信号量操作时要遵守正确的顺序和逻辑关系，以避免出现竞态条件或死锁等问题。

通过使用信号量，任务可以实现对共享资源的安全访问、任务之间的互斥操作以及线程同步等功能。这使得FreeRTOS的信号量成为一种重要的工具，用于在嵌入式系统中管理和控制任务的并发操作。

## freertos不同任务数据如何传递

FreeRTOS 是一种实时操作系统，其任务之间通过消息传递、信号量、锁等机制进行通信和同步。下面介绍两种常用机制：

消息传递机制
消息传递是一种在任务之间进行数据传递的常用方式。每个任务都可以定义一个消息队列，其他任务可以向该队列发送消息，也可以从队列中接收消息。消息队列支持异步操作，即发送消息不需要等待接收端处理完成。

使用消息传递机制进行数据传递的步骤如下：

创建一个消息队列：使用 xQueueCreate 函数创建一个消息队列。
发送消息：使用 xQueueSend 函数向队列发送消息。
接收消息：使用 xQueueReceive 函数从队列中接收消息。
示例代码：

InsertCopy
// 创建一个消息队列
QueueHandle_t myQueue = xQueueCreate(MY_QUEUE_LENGTH, sizeof(int));

// 发送消息
int message = 42;
xQueueSend(myQueue, &message, portMAX_DELAY);

// 接收消息
int receivedMessage;
xQueueReceive(myQueue, &receivedMessage, portMAX_DELAY);
信号量机制
信号量是一种可以控制对共享资源的访问的机制。每个任务都可以定义一个信号量，用于控制对共享资源的访问。当一个任务完成时，它可以释放一个信号量，使得其他任务可以继续访问该资源。

使用信号量机制进行数据传递的步骤如下：

创建一个信号量：使用 xSemaphoreCreateMutex 函数创建一个信号量。
锁定信号量：使用 xSemaphoreTake 函数锁定信号量，表示当前任务正在使用该资源。
释放信号量：使用 xSemaphoreGive 函数释放信号量，表示当前任务不再需要该资源。
示例代码：

InsertCopy
// 创建一个信号量
SemaphoreHandle_t mySemaphore = xSemaphoreCreateMutex();

// 锁定信号量
xSemaphoreTake(mySemaphore, portMAX_DELAY);

// 释放信号量
xSemaphoreGive(mySemaphore);
这两种机制都可以用于在任务之间进行数据传递，具体使用哪种机制取决于具体的应用场景和需求。

## RTOS和裸机开发的区别

RTOS 和裸机开发的核心区别在于：

任务管理：RTOS 支持多任务并发，每个任务可以分配不同的优先级，系统可以实现任务的调度和管理。而裸机开发通常只支持单任务，没有任务调度和管理机制。
内存管理：RTOS 需要管理任务之间的共享内存，如消息队列、信号量等，这些内存需要分配和管理。而裸机开发通常不需要管理共享内存，因为只有一个任务在运行，内存分配较为简单。
调度机制：RTOS 采用调度机制，根据任务的优先级和调度权来分配 CPU 时间。而裸机开发通常不需要进行任务调度，因为只有一个任务在运行，不需要进行任务切换。
通信机制：RTOS 支持多种通信机制，如消息传递、信号量、锁等，任务之间可以通过这些机制进行通信和同步。而裸机开发通常只支持硬件通信，如串口、SPI 等。
实时性：RTOS 具有更高的实时性和灵活性，因为其具有任务调度和管理机制，可以实现任务的异步处理和并发控制。而裸机开发通常只支持顺序执行，没有任务调度和管理机制，无法实现任务的异步处理和并发控制。
兼容性：RTOS 和裸机开发在某些方面可能存在兼容性问题，例如在某些情况下，RTOS 可能需要使用特定的编译器和工具链，而裸机开发可能不需要。
总之，RTOS 和裸机开发的核心区别在于任务管理、内存管理、调度机制、通信机制、实时性和兼容性等方面。RTOS 支持多任务并发、任务调度和管理、多种通信机制等，而裸机开发只支持单任务、硬件通信等。


## 二值信号量和互斥量的区别

信号量一般用来进行资源管理和任务同步，FreeRTOS中信号量又分为二值信号量、计数型信号量、互斥信号量和递归互斥信号量，不同的信号量其应用场景不同。

1. 信号量简介
信号量常常用于控制对共享资源的访问和任务同步

2. 二值信号量
二值信号量通常用于互斥访问或同步，二值信号量和互斥信号量非常类似，但是还是有一些细微的差别，互斥信号量拥有优先级继承机制，二值信号量没有优先级继承。因此二值信号另更适合用于同步(任务与任务或任务与中断的同步)，而互斥信号量适合用于简单的互斥访问，

和队列一样，信号量 API 函数允许设置一个阻塞时间，阻塞时间是当任务获取信号量的时候由于信号量无效从而导致任务进入阻塞态的最大时钟节拍数

二值信号量其实就是一个只有一个队列项的队列，这个特殊的队列要么是满的，要么是空的，这不正好就是二值的吗？ 任务和中断使用这个特殊队列不用在乎队列中存的是什么消息，只需要知道这个队列是满的还是空的。可以利用这个机制来完成任务与中断之间的同步。

3. 互斥信号量
互斥信号量其实就是一个拥有优先级继承的二值信号量，互斥信号量适合用于那些需要互斥访问的应用中。在互斥访问中互斥信号量相当于一个钥匙，当任务想要使用资源的时候就必须先获得这个钥匙，当使用完资源以后就必须归还这个钥匙，这样其他的任务就可以拿着这个钥匙去使用资源。

当一个互斥信号量正在被一个低优先级的任务使用，而此时有个高优先级的任务也尝试获取这个互斥信号量的话就会被阻塞。不过这个高优先级的任务会将低优先级任务的优先级提升到与自己相同的优先级，这个过程就是优先级继承。优先级继承尽可能的降低了高优先级任务处于阻塞态的时间，并且将已经出现的“优先级翻转”的影响降到最低。

- 互斥信号量有优先级继承的机制，所以只能用在任务中，不能用于中断服务函数。
- 中断服务函数中不能因为要等待互斥信号量而设置阻塞时间进入阻塞态。

4.计数型信号量
同二值信号量一样，用户不需要关心队列中存储了什么数据，只需要关心队列是否为空即可。计数型信号量通常用于如下两个场合：
1、事件计数
在这个场合中，每次事件发生的时候就在事件处理函数中释放信号量(增加信号量的计数值)，其他任务会获取信号量
2、资源管理
在这个场合中，信号量值代表当前资源的可用数量，比如停车场当前剩余的停车位数量。一个任务要想获得资源的使用权，首先必须获取信号量，信号量获取成功以后信号量值就会减一。当信号量值为 0 的时候说明没有资源了。当一个任务使用完资源以后一定要释放信号量，释放信号量以后信号量值会加一。在这个场合中创建的计数型信号量初始值应该是资源的数量，比如停车场一共有 100 个停车位，那么创建信号量的时候信号量值就应该初始化为 100。

## RTOS内核是怎么调度的
### FreeRTOS四种任务状态
FreeRTOS的任务状态（4种）
1.运行态(Running) 2.就绪态(Ready) 3.阻塞态(Blocked) 4.挂起态(Suspended)
Running—运行态
当任务处于实际运行状态被称之为运行态，即 CPU 的使用权被这个任务占用。
Ready—就绪态
处于就绪态的任务是指那些能够运行（没有被阻塞和挂起），但是当前没有运行的任务，因为同优先级或更高优先级的任务正在运行。
Blocked—阻塞态
由于等待信号量，消息队列，事件标志组等而处于的状态被称之为阻塞态，另外任务调用延迟函数也会处于阻塞态。
Suspended—挂起态
类似阻塞态，通过调用函数 vTaskSuspend()对指定任务进行挂起，挂起后这个任务将不被执行，只有调用函数 xTaskResume()才可以将这个任务从挂起态恢复。

## freertos实时性

一个处理器核心在某一时刻只能运行一个任务，操作系统中任务调度器的责任就是决定在某一时刻究竟运行哪个任务。
实时操作系统中都要包含一个实时任务调度器，这个任务调度器与其它操作系统的最大不同是强调：严格按照优先级来分配CPU时间，并且时间片轮转不是实时调度器的一个必选项。

FreeRTOS就是一款支持多任务运行的实时操作系统，具有时间片、抢占式和合作式三种调度方式。

合作式调度，主要用在资源有限的设备上面，现在已经很少使用了。出于这个原因，后面的FreeRTOS版本中不会将合作式调度删除掉，但也不会再进行升级了。
抢占式调度，每个任务都有不同的优先级，任务会一直运行直到被高优先级任务抢占或者遇到阻塞式的 API 函数，比如 vTaskDelay。
时间片调度，每个任务都有相同的优先级，任务会运行固定的时间片个数或者遇到阻塞式的 API函数，比如vTaskDelay，才会执行同优先级任务之间的任务切换。

# 移植

要移植 FreeRTOS 到特定的 MCU 平台上，需要进行以下步骤：

1. 了解目标 MCU 平台：首先，你需要详细了解你所使用的 MCU 平台的架构、外设和特性，包括中断控制器、时钟系统和内存管理单元等，以便适配 FreeRTOS。

2. 下载 FreeRTOS：从 FreeRTOS 官方网站（www.freertos.org）下载最新版本的 FreeRTOS。

3. 配置移植文件：在 FreeRTOS 目录中，找到适合目标 MCU 平台的移植文件，如 `port` 文件夹中的 `port.c`、`portmacro.h` 和 `portasm.s` 文件。根据目标 MCU 平台的架构和特性进行相应的配置。

4. 配置内核设置：在 FreeRTOS 的 `FreeRTOSConfig.h` 文件中，根据目标 MCU 平台的需求和特性进行配置，如任务栈大小、空闲任务堆栈大小、任务优先级等。

5. 实现移植函数：根据目标 MCU 平台的要求，实现必要的移植函数，如任务切换函数、定时器驱动函数和中断服务函数等。这些函数需要与目标 MCU 平台的硬件特性相匹配。

6. 编译和链接：使用适合目标 MCU 平台的编译器和链接器，将移植文件和源代码一起编译和链接，生成可执行的代码。

7. 测试和调试：将生成的可执行代码加载到目标 MCU 平台上进行测试和调试。确保 FreeRTOS 在目标平台上正常运行，并验证任务调度、中断处理和内存管理等功能的正确性和稳定性。

8. 应用开发：一旦 FreeRTOS 移植成功，你可以开始在其上开发应用程序。通过创建任务、使用消息队列、互斥锁和信号量等功能，来构建你的实际应用。

请注意，每个 MCU 平台的移植过程可能会有所不同，上述步骤只是一个大致的指导。具体的移植步骤和细节应参考 FreeRTOS 官方文档和目标平台的硬件手册。