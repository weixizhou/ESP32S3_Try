
/* 函数进入 不执行其他操作 */

#include "main.hpp"


void setup()
{

    esp_main(); // 函数入口

}


void loop()
{

    esp_loop(); // 主程序循环，用于输出日志

    vTaskDelay(100 / portTICK_PERIOD_MS);

}
