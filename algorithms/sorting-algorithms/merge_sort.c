#include<stdio.h>

void array_scan(int*,int);
void array_print(int*,int,int);
void merge_sort(int*,int,int);
void merge(int*,int,int,int);
void swap(int*,int,int);
void insert_sort(int* arr,int l,int r);

int main()
{
 int n; //taking array size
 scanf("%d",&n); // storing the size at address of n 
 int arr[n]; // initializing an array of size n
 array_scan(arr,n); // array element input
 merge_sort(arr,0,n-1); // merge sort funcion takes in extreme indices
 array_print(arr,0,n-1); // print array takes in extreme indices
}

void merge_sort(int* arr,int l,int r)
{
 if(l>=r) return; // base condition for recursive call
 int mid = (l+r)/2; // finding the middle of the array to divide the array 
 merge_sort(arr,l,mid); // calling merge sort on the left part of the array 
 merge_sort(arr,mid+1,r); // calling merge sort on the right part of the array 
 merge(arr,l,mid,r); // sorting and merging the same array with use of insertion sort
}

void merge(int* arr,int l,int mid,int r)
{
 int i,j;
 for(i=l,j=mid+1;i<mid+1;i++)
 {
  if(arr[i]>arr[j])
  {
   swap(arr,i,j);
   insert_sort(arr,mid+1,r);
  }
 }
}

void insert_sort(int* arr,int l,int r)
{
 int i;
 for(i=l;i<r;i++)
 {
  if(arr[i+1] < arr[i])
   swap(arr,i,i+1);
  else 
   break;
 }
}

void swap(int* arr,int idx1,int idx2)
{
 int tmp = arr[idx1];
 arr[idx1] = arr[idx2];
 arr[idx2] = tmp;
}

void array_scan(int* arr,int n)
{
 int i;
 for(i=0;i<n;i++) 
  scanf("%d",&arr[i]);
}

void array_print(int* arr,int l,int r)
{
 int i;
 for(i=l;i<=r;i++)
  printf("%d ",arr[i]);
 printf("\n");
}
