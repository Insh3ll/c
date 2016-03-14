#include <stdio.h>
#include <pthread.h> //线程函数的头文件 编译链接时加上-lpthread
#include <unistd.h> //sleep()的头文件

void print_msg(char *ptr);

void main()
{
	pthread_t th1,th2;
	int i,j;
	char *msg1 = "do sth1\n";
	char *msg2 = "do sth2\n";
	pthread_create(&th1,NULL,(void *)(&print_msg),(void *)msg1);
	pthread_create(&th2,NULL,(void *)(&print_msg),(void *)msg2);
	sleep(1);
}


void print_msg(char *ptr)
{
	int retval;
	int id=pthread_self();
	printf("Thread ID: %x\n",id);
	printf("%s",ptr);
	pthread_exit(&retval);
}
