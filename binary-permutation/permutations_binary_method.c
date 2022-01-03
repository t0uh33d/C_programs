#include<stdio.h>
#include<math.h>

void perm(int* arr,int n,int bnum)
{
 int free=0;
 int andnum=0x01;

 for(int j=0;j<n;j++)
 {
  if(andnum&bnum)
  {
   printf("%d ",arr[j]);
   free++;
  }
  andnum = andnum<<1;
 }

 if(!free)
   printf("[]");
 printf("\n");
}

main()
{
 int n,y;
 scanf("%d",&n);
 y = pow(2,n);
 int arr[n];
 for(int i=0;i<n;i++)
  scanf("%d",&arr[i]);
 
 printf("Combinations : \n");
 for(int i=0;i<y;i++)
 {
  perm(arr,n,i);
 }
 printf("Total combinations generated: %d",y);
}
