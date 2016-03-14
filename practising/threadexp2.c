#include <stdio.h>
#include <pthread.h> //线程函数的头文件 编译时加上-lpthread
#include <unistd.h> //sleep()函数头文件
#define MAX 10

pthread_t thread[2];
pthread_mutex_t mut;
int number=0,i;

void *thread1()
{
	printf("thread1:i'm thread 1\n");
	for(i=0;i<MAX;i++)
	{
		printf("threead1:number=%d\n",number);
		pthread_mutex_lock(&mut);
		number++;
		pthread_mutex_unlock(&mut);
		sleep(2);
	}
	printf("thread1:主函数在等我完成任务吗？\n");
	pthread_exit(NULL);
}

void *thread2()
{
	printf("thread2:i'm thread2\n");
	for(i=0;i<MAX;i++)
	{
		printf("thread2:number=%d\n",number);
		pthread_mutex_lock(&mut);
		number++;
		pthread_mutex_unlock(&mut);
		sleep(1);
	}
	printf("thread2:主函数在等我完成任务吗？\n");
	pthread_exit(NULL);
}

void thread_create(void)
{
	int tmp;
	/*创建线程*/
	if((tmp=pthread_create(&thread[0],NULL,thread1,NULL))!=0)
		printf("线程1创建失败\n");
	else
		printf("线程1被创建\n");
	if((tmp=pthread_create(&thread[1],NULL,thread2,NULL))!=0)
		printf("线程2创建失败\n");
	else
		printf("线程2被创建\n");
}

void thread_wait(void)
{
	/*等待线程结束*/
	if(thread[0]!=0)
	{
		pthread_join(thread[0],NULL);
		printf("线程1已经结束\n");
	}
	if(thread[1]!=0)
	{
		pthread_join(thread[0],NULL);
		printf("线程2已经结束\n");
	}
}

void main()
{
	pthread_mutex_init(&mut,NULL); //用默认属性初始化互斥锁
	printf("我是主线程，我正在创建线程\n");
	thread_create();
	printf("我是主线程，我在等待线程完成任务\n");
	thread_wait();
}

