#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/
#define PATHNAME    "../README.md"  //路径名
#define PROJ_ID     0x6666          //整数标识符
#define SIZE        4096            //共享内存的大小

int main(int argc, char* argv[])
{
    key_t key = ftok(PATHNAME, PROJ_ID); //获取与server进程相同的key值
    if (key < 0) {
        perror("ftok");
        return 1;
    }
    int shm = shmget(key, SIZE, IPC_CREAT); //获取server进程创建的共享内存的用户层id
    if (shm < 0) {
        perror("shmget");
        return 2;
    }

    printf("key: %x\n", key); //打印key值
    printf("shm: %d\n", shm); //打印共享内存用户层id

    char* mem = shmat(shm, NULL, 0); //关联共享内存

    int i = 0;
    while (1) {
        mem[i] = 'A' + i;
        i++;
        mem[i] = '\0';
        if(i >= 26)
            break;
        sleep(1);
    }

    shmdt(mem); //共享内存去关联
    
    return 0;
}