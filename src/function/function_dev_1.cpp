
/* 功能 1 */
#include "main.hpp"

extern esp_global_variable *esp;

int funtion_dev_1_setup()
{
    return 0;
}


int funtion_dev_1_loop()
{
    esp->sys_time = millis(); // 获取系统时间

    #ifdef INFO
        Serial.printf("sys_time: %d\n", esp->sys_time);
    #endif

    return 0;
}


// function1线程函数
void funtion_dev_1_TASK(void *param)
{
    funtion_dev_1_setup();

    while (true)
    {
        funtion_dev_1_loop();
        
        vTaskDelay(100 / portTICK_PERIOD_MS);        
    }
}



// 创建StartFunction1Task线程执行function1任务
TaskHandle_t TASK_HandleFunctiondev1 = NULL;
void StartFunction1Task()
{

    xTaskCreate(
        funtion_dev_1_TASK,     /* 任务函数 */
        "funtion_dev_1 Thread", /* 任务名 */
        4 * 1024,               /* 任务栈大小，根据需要自行设置*/
        NULL,                   /* 参数，入参为空 */
        10,                     /* 优先级 */
        &TASK_HandleFunctiondev1);       /* 任务句柄 */
}
