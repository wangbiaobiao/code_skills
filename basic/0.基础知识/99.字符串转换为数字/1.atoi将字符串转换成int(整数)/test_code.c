#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    #include <stdlib.h>
    
    int atoi (const char * str);
    
    atoi() 函数会扫描参数 str 字符串，跳过前面的空白字符（例如空格，tab缩进等，可以通过 isspace() 函数来检测），
    直到遇上数字或正负符号才开始做转换，而再遇到非数字或字符串结束时('\0')才结束转换，并将结果返回。

    返回值:返回转换后的整型数；如果 str 不能转换成 int 或者 str 为空字符串，那么将返回 0。
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char str10[30] = "123456";  //10进制数
    char str10_2[30] = "123456 Hello world";  //10进制数
    char str10_3[30] = "-321";  //10进制数

    printf("%s: %d\n", str10, atoi(str10));
    printf("%s: %d\n", str10_2, atoi(str10_2));
    printf("%s: %d\n", str10_3, atoi(str10_3));
    printf("\n");
    
    return 0;
}