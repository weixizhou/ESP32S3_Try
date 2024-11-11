
/* 用于外设 */
#include "main.hpp"


/* 外设初始化 */
int setup_ctrl()
{

    StartFunction1Task(); // 开启function_dev_1线程

    return 0;
}


/* 外设主循环 */
int loop_ctrl()
{
    return 0;
}

