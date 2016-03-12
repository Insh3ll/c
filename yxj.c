#include <stdio.h>
void main()
{
	struct t
	{
		char c;
		char *s;
		int x;
	} a[]={{'A',"123",0},{'B',"321",1}},*p=a;

	printf("%s\n",(p++->s++));
}
