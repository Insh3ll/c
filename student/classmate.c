#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//添加函数声明
void watch();
void add();
void find();
//结构体定义
struct student
{
	int num;
	char name[20];
	char sex[10];
	char birthday[10];
	char tel[15];
	char address[30];
};
//主函数
main()
{
	int flag=4;
	while(flag)
	{
		printf("选择操作：查看（1）,添加（2）,查找（3），退出（0）\n");
		scanf("%d",&flag);
		system ("clear");
		switch(flag)
		{
			case 1:watch();break;
			case 2:add();break;
			case 3:find();break;
			case 0:exit(0);break;
			default:printf("输入错误！！\n");
		}
	}
}
void watch()//查看记录
{
	FILE *fp;
	struct student stu;
	if((fp=fopen("stulist","rb"))==NULL)
	{ printf("打开文件失败或数据记录为空\n");exit(0); }
	printf("学号 姓名      性别 生日      电话           地址\n");
	while(fread(&stu,sizeof(struct student),1,fp)==1)
		printf("%-5d%-10s%-5s%-10s%-15s%s\n",stu.num,stu.name,stu.sex,stu.birthday,stu.tel,stu.address);
	fclose(fp);
	
}
void add()//添加记录
{
	FILE *fp;
	struct student stu;
	if((fp=fopen("stulist","ab"))==NULL)
	{ printf("打开文件失败");exit(0); }
	printf("学号：");scanf("%d",&stu.num);
	printf("姓名：");scanf("%s",stu.name);
	printf("性别：");scanf("%s",stu.sex);
	printf("生日：");scanf("%s",stu.birthday);
	printf("电话：");scanf("%s",stu.tel);
	printf("地址：");scanf("%s",stu.address);
	if(fwrite(&stu,sizeof(struct student),1,fp)!=1)
		printf("写入失败");
	fclose(fp);
}
void find()//查找记录
{
	FILE *fp;
	struct student stu;
	int num;
	printf("请输入查找的学号：");
	scanf("%d",&num);
	if((fp=fopen("stulist","rb"))==NULL)
	{ printf("打开文件失败");exit(0); }
	while(!feof(fp))
	{
		fread(&stu,sizeof(struct student),1,fp);
		if(stu.num==num)
		{
			printf("学号 姓名      性别 生日      电话           地址\n");
			printf("%-5d%-10s%-5s%-10s%-15s%s\n",stu.num,stu.name,stu.sex,stu.birthday,stu.tel,stu.address);
			break;
		}
	}
	if(feof(fp)==1)
		printf("该学号未找到");
	
}













