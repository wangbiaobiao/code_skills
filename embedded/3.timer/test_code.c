#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include "MultiTimer.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
//实例化定时器对象
MultiTimer timer1;
MultiTimer timer2;
MultiTimer timer3;

//系统时间基准接口
uint32_t PlatformTicksGetFunc(void)
{
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    return (uint32_t)((current_time.tv_sec * 1000) + (current_time.tv_nsec / 1000000));
}

void exampleTimer1Callback(MultiTimer* timer, void *userData)
{
    printf("[T:%010d] Timer:%p callback-> %s.\r\n", PlatformTicksGetFunc(), timer, (char*)userData);
    MultiTimerStart(timer, 1000, exampleTimer1Callback, userData);
}

void exampleTimer2Callback(MultiTimer* timer, void *userData)
{
    printf("[T:%010d] Timer:%p callback-> %s.\r\n", PlatformTicksGetFunc(), timer, (char*)userData);
}

void exampleTimer3Callback(MultiTimer* timer, void *userData)
{
    printf("[T:%010d] Timer:%p callback-> %s.\r\n", PlatformTicksGetFunc(), timer, (char*)userData);
    MultiTimerStart(timer, 4567, exampleTimer3Callback, userData);
}

int main(int argc, char* argv[])
{
    //安装定时器驱动
    MultiTimerInstall(PlatformTicksGetFunc);

    //设置定时时间，超时回调处理函数， 用户上下指针，启动定时器；
    MultiTimerStart(&timer1, 1000, exampleTimer1Callback, "1000ms CYCLE timer");
    MultiTimerStart(&timer2, 5000, exampleTimer2Callback, "5000ms ONCE timer");
    MultiTimerStart(&timer3, 3456, exampleTimer3Callback, "3456ms delay start, 4567ms CYCLE timer");

    while (1)
    {
        //调用定时器后台处理函数
        MultiTimerYield();
    }

    return 0;
}