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
