#include <stdio.h>
#include <malloc.h>
void main()
{
	FILE *fp;
	char *pstr=(char *)malloc(sizeof(char)*80);
	fp=fopen("t.txt","r");
	fgets(pstr,4,fp);
	puts(pstr);
	fclose(fp);
	free(pstr);
}
