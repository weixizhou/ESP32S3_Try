
/* 用于创建主应用 */
#include "main.hpp"

// 将全局变量放入esp_global_variable结构体中，使用指针esp访问全局变量
esp_global_variable _esp_, *esp = &_esp_;

// 设置loop任务栈大小 8 * 1024
SET_LOOP_TASK_STACK_SIZE(8 * 1024);


static int setup_power()
{
    return 0;
}

static int loop_power()
{
    return 0;
}


/* 开关机线程函数 */
void TASK_POWER(void *param)
{
    setup_power();
    
    while (true)
    {
        loop_power();

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

}


/* 外设线程函数 */
void TASK_Ctrl(void *param)
{
	setup_ctrl();

	while (true)
	{
		loop_ctrl();

        vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}


/* 业务线程函数 */
void TASK_Home(void *param)
{
	setup_home();
	
	while (true)
	{
		loop_home();

        vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}


/* 函数入口 */
int esp_main()
{

    /* 电源线程 移至核心1运行 */
    xTaskCreatePinnedToCore(
        TASK_POWER,             /* 任务函数 */
        "Power Thread",         /* 任务名 */
        8 * 1024,               /* 任务栈大小，根据需要自行设置*/
        NULL,                   /* 参数，入参为空 */
        3,                      /* 优先级 */
        &esp->TASK_HandlePOWER, /* 任务句柄 */
        1                       /* 选择运行核心 */
    );

    /* 外设线程 默认核心0运行 */
    xTaskCreate(
        TASK_Ctrl,              /* 任务函数 */
        "Crtl Thread",          /* 任务名 */
        8 * 1024,               /* 任务栈大小，根据需要自行设置*/
        NULL,                   /* 参数，入参为空 */
        2,                      /* 优先级 */
        &esp->TASK_HandleCtrl); /* 任务句柄 */

    /* 业务线程 默认核心0运行 */
    xTaskCreate(
        TASK_Home,              /* 任务函数 */
        "Home Thread",          /* 任务名 */
        8 * 1024,               /* 任务栈大小，根据需要自行设置*/
        NULL,                   /* 参数，入参为空 */
        1,                      /* 优先级 */
        &esp->TASK_HandleHome); /* 任务句柄 */

}


/* 主程序循环，用于输出日志 */
int esp_loop()
{
    vTaskDelay(100 / portTICK_PERIOD_MS);
}
