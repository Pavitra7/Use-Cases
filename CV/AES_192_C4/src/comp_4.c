#include <stdio.h>

void do_comp_4(void)
{

char a1[100];
int i=0;
printf("Enter the string");
while(a1[i]!=NULL)

{
	scanf(&a[i]);
	i++;
}
printf("Entered reverse string is");
while (i>0)
{
	printf("%c", a[--i]);
}
int a[100][100],b[100][100];
for (int k=0;k<99;k++)
{
for(int l=0;l<99;l++)
	a[k][l]=b[k][l]*50;
	a[k+1][l+1]=b[k][l]+b[k+1][l+1];
	a[k+1][l+1]=a[k][l]-a[k+1][l+1];
}




}