
/* ws2812 */
#include "main.hpp"

extern esp_global_variable *esp;

#define NUM_LEDS 1
#define DATA_PIN 48
CRGB leds[NUM_LEDS];

int ws2812_setup()
{
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);


    return 0;
}


int ws2812_loop()
{
    leds[0] = CRGB::White; 
    FastLED.show(); 
    delay(500);

    leds[0] = CRGB::Green; 
    FastLED.show(); 
    delay(500);

    return 0;
}


// ws2812线程函数
void ws2812_TASK(void *param)
{
    ws2812_setup();

    while (true)
    {
        ws2812_loop();
        
        vTaskDelay(100 / portTICK_PERIOD_MS);        
    }
}



// 创建StartFunction1Task线程执行function1任务
TaskHandle_t TASK_HandleWS2812 = NULL;
void StartWS2812Task()
{

    xTaskCreate(
        ws2812_TASK,     /* 任务函数 */
        "ws2812 Thread", /* 任务名 */
        4 * 1024,               /* 任务栈大小，根据需要自行设置*/
        NULL,                   /* 参数，入参为空 */
        10,                     /* 优先级 */
        &TASK_HandleWS2812);       /* 任务句柄 */
}
