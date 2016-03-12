#include <stdio.h>
#include <malloc.h>
main()
{
	union {int k;char i[2];} *s,a;
	int *p;
	s=&a;
	p=s;
	s->i[0]=0x39;
	s->i[1]=0x38;
	printf("union=%dbyte\n",sizeof(a));
	printf("%x\n",s->k);
	printf("i[0]=%x,i[1]=%x\n",s->i[0],s->i[1]);
	printf("*p=%x\n",*p);
	printf("int=%dbyte\n",sizeof(int));
	printf("char=%dbyte\n",sizeof(char));
}
