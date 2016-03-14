#include <stdio.h>
void main()
{
	void func(int,int);
	int nd;
	printf("Input the number!: ");
	scanf("%d",&nd);
	func(nd,sizeof(nd)*2);
	putchar('\n');
}

void func(int n,int i)
{
	if(i!=1)
		func(n>>4,--i);
	printf("%x",n&15);
}
