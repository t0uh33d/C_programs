#include<stdio.h>
float logx[11]={0,0,0.30102,0.4771,0.6020,0.69897,0.7781,0.845,0.903,0.9542,1};
float powof[6]={1,10,100,1000,10000,100000};
int antilog[11]={1,10,2,2,3,4,5,6,7,8,9};
float findlog(float,int,int);
float findroot(float);
float findantilog(float);
main()
{
 int c=0,i,z;
 float sqrt,x,logVal;
 scanf("%f",&x);
 int y=x;
 while(y=y/10)
  c++;
 logVal=findlog(x,powof[c],c);
 sqrt=findroot(logVal); 
 printf("%f",sqrt);
}

float findlog(float x,int pow,int c)
{
 x=x/pow;
 int z=x;
 x=(x-z)/10;
 x=logx[z]+x+c;
 return x;
}

float findroot(float x)
{
 float antilog,root;
 x=x*0.5;
 int y=x;
 x=x-y;
 y=powof[y];
 antilog=findantilog(x);
 root=antilog*y;
 return root;
}

float findantilog(float x)
{
 int z=x;
 x=x-z;
 int y=x*10;
 float alog;
 if(y==6||y==9)
 {
   if(y==6)
   {
    if(x>0.602&&x<0.6989)
     alog=4+(x-0.602)*10;
    else
     alog=5+(x-0.6989)*10;
   }
   else
   {
    if(x>0.9030&&x<0.9542)
     alog=8+(x-0.9030)*10;
    else
     alog=9+(x-0.9542)*10;
   }
 }
 else
  alog=antilog[y]+((x-logx[y-1])*5);
 return alog;
}
