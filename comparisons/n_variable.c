#include<stdio.h>
#include<stdlib.h>
char* charset(int n);
void swap(int*,char*,int);
void printresult(int*,char*,int);
main()
{
 int n,*val,i;
 char *ch;
 scanf("%d",&n);
 ch=charset(n);
 val=(int*) malloc(sizeof(int)*n);
 for(i=0;i<n;i++)
  scanf("%d",(val+i));
 swap(val,ch,n);
 printresult(val,ch,n);
}

char* charset(int n)
{
 int i;
 char *ch;
 ch=(char*) malloc(sizeof(char)*n);
 for(i=0;i<n;i++)
  *(ch+i)='a'+i;
 return ch;
}

void swap(int* val,char* ch,int n)
{
 int i,j;
 for(i=0;i<n;i++)
 {
  for(j=0;j<n-i-1;j++)
  {
   if(*(val+j) < *(val+j+1))
   {
    int temp;
    char temp1;
    temp=*(val+j);
    *(val+j)=*(val+j+1);
    *(val+j+1)=temp;
    temp1=*(ch+j);
    *(ch+j)=*(ch+j+1);
    *(ch+j+1)=temp1;
   }
  }
 }
}

void printresult(int* val,char* ch,int n)
{
 int i;
 for(i=0;i<n;i++)
 {
  if(i==0)
  printf("%c",*(ch+i));
  else if(*(val+i-1)>*(val+i))
  printf(">%c",*(ch+i));
  else
  printf("==%c",*(ch+i));
 }
}
