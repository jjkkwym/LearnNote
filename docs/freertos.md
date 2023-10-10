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