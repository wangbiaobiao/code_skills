#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//环境变量被保存在了全局变量 __environ，通过这个变量来读取环境变量信息
extern char ** _environ;

void get_all_env(void)
{
    char **p = _environ;
    while(*p) {
        printf("%s\n", *p);
        p++;
    }
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[], char* envp[])
{
    //方法一：在C API级别，环境变量作为第三个参数传递给main。
    while( *envp ) {
        printf("%s\n", *envp);
        envp++;
    }
    
    //方法二：全局变量 __environ
    get_all_env();
    
    return 0;
}