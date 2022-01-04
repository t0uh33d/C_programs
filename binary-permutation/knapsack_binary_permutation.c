#include<stdio.h>
#include<math.h>
void binknapsack(int,int,int,int*,int*);
int max=-1,wmin;
main()
{
 int n,i,x,c;
 printf("No of items : ");
 scanf("%d",&n);
 int weight[n],val[n];
 printf("Items weight : ");
 for(i=0;i<n;i++)
  scanf("%d",&weight[i]);
 printf("Items value : ");
 for(i=0;i<n;i++)
  scanf("%d",&val[i]);
 printf("Total capacity : ");
 scanf("%d",&c);
 x=pow(2,n);
 for(i=1;i<x;i++)
  binknapsack(n,i,c,weight,val);

 printf("Max value from given items : %d\nTotal weight of the items : %d",max,wmin);
}

void binknapsack(int n,int binum,int c,int* weight,int* val)
{
 int andnum=0x01,i,vsum=0,wsum=0;
 for(i=0;i<n;i++)
 {
  if(andnum&binum)
  {
   vsum+=val[i];
   wsum+=weight[i];
  }
  andnum=andnum<<1;
 }
 if(vsum>max&&wsum<=c)
 {
   max=vsum;
   wmin=wsum;
 }
}




