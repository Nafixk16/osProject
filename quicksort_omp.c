#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<omp.h>
// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
    //#pragma omp parallel for
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
double quickSort(int arr[], int low, int high)
{
    int pi;
      double clock3, clock1,clock2,cpu_time_used;
    if (low < high)
    {
         
         pi = partition(arr, low, high);
clock3=omp_get_wtime();    
     #pragma omp parallel  
         {
          
              
           #pragma omp sections nowait
           {
                #pragma omp section
                quickSort(arr, low, pi - 1);
                #pragma omp section
                quickSort(arr, pi + 1, high);
            }
        }
      
    }
        clock1=omp_get_wtime(); 
	// #pragma omp barrier
         clock2=clock1-clock3;
      // printf("cpu burst time=>%f",clock2);
        
       return clock2;   
}

/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    double cpu_time_used;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("n");
}

// Driver program to test above functions
int main()
{
    //clock_t start,end;
    int num;
    double clock1,clock2,clock3,cpu_time_used;
    printf("\nEnter the num of element u want to sort=>");
    scanf("%d",&num);	
    int arr[num];
    for(int j=0;j<num;j++)
    {
	arr[j]=(rand()/1000000);
		
    }
    int n = sizeof(arr)/sizeof(arr[0]);
    //start=clock();
    
    clock2 =quickSort(arr, 0, n-1);
  //  end=clock();
     
 // printf("Sorted array: n");
   //printArray(arr, n);
   // cpu_time_used = (double)( (end - start))/ CLOCKS_PER_SEC;  
    
   // printf("cpu burst time=>%f",cpu_time_used);
  
 printf("cpu burst time=>%f",clock2); 
  printf("\n");  
 return 0;
}
