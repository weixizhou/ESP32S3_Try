
/* 
 * @Descripttion: for study
 * @version: 1.0
 * @author weixi zhou
 * @Date: 2024-11-10 15:22:08
*/

#include <Arduino.h>
#include "Config.hpp"


/* =======全局变量存放区======= */
typedef struct
{
    
    // 系统时间
    uint32_t sys_time = 0;

    // 外设线程句柄
    TaskHandle_t TASK_HandleCtrl = NULL;
    // 业务线程句柄
    TaskHandle_t TASK_HandleHome = NULL;
    // 电源线程句柄
    TaskHandle_t TASK_HandlePOWER = NULL;


}
esp_global_variable;



/* =======全局函数存放区======= */

int esp_main(); // 函数入口

int esp_loop(); // 工程底层主循环 但没什么用


int setup_ctrl(); // 外设线程初始化

int setup_home(); // 业务线程初始化

int loop_ctrl(); // 外设线程loop

int loop_home(); // 业务线程loop



void StartFunction1Task(); // 创建StartFunction1Task线程



// 计算帧率  用法--> CALC_FPS("输出的提示信息");
#ifdef FPS
    #define CALC_FPS(tips)                                                                                         \
        {                                                                                                          \
            static int fcnt = 0;                                                                                   \
            fcnt++;                                                                                                \
            static struct timespec ts1, ts2;                                                                       \
            clock_gettime(CLOCK_MONOTONIC, &ts2);                                                                  \
            if ((ts2.tv_sec * 1000 + ts2.tv_nsec / 1000000) - (ts1.tv_sec * 1000 + ts1.tv_nsec / 1000000) >= 1000) \
            {                                                                                                      \
                Serial.printf("%s => %d FPS \r\n", tips, fcnt);                                                    \
                ts1 = ts2;                                                                                         \
                fcnt = 0;                                                                                          \
            }                                                                                                      \
        }
#else
    #define CALC_FPS(tips)
#endif