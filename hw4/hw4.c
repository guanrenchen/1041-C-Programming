#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,j;

int main(int argc, char *argv[]) 
{
	int n=atoi(argv[1]), x=atoi(argv[2]);
	int a[n], da[n];
	float f[n], df[n];
	
	if(!(x==0 || x==1) || n<1)
	{
		printf("\nINVALID INPUT\n\n\n");
		return 0;
	}

	srand(time(0)); 
	
	if(x==0)
	{
		for(i=0; i<n; i++)
			a[i]=rand()%10000;
		
		printf("\n\nBEFORE SORTING : \n");	
		print_array_int(a, n);	
	
		quicksort_int(a, 0, n-1);
		
		for(i=0, j=n-1; i<n; i++, j--)
			da[j]=a[i];
		//sort in descending order
		
		printf("\n\nAFTER SORTING : \n");
		print_array_int(da, n);
	}
	
	if(x==1)
	{
		for(i=0; i<n; i++)
			f[i]=rand()/(RAND_MAX/10000.0);
			
		printf("\n\nBEFORE SORTING : \n");	
		print_array_float(f, n);	
	
		quicksort_float(f, 0, n-1);
		
		for(i=0, j=n-1; i<n; i++, j--)
			df[j]=f[i];
		//sort in descending order
		
		printf("\n\nAFTER SORTING : \n");
		print_array_float(df, n);
	}
	
	printf("\n\n\n");
	return 0;
}

int print_array_int(int a[],int n)
{
	for(i=0, j=0; i<n; i++, j++)
	{
		if(j/10>(j-1)/10)
			printf("\n");
		printf("%5d", a[i]);
	}
}

int print_array_float(float f[],int n)
{
	for(i=0, j=0; i<n; i++, j++)
	{
		if(j/10>(j-1)/10)
			printf("\n");
		printf("%8.2f", f[i]);
	}
}

int quicksort_int(int a[], int low, int high)
{
	int middle;
	
	if(low>=high) return;
	middle=split_int(a, low, high);
	quicksort_int(a, low, middle-1);
	quicksort_int(a, middle+1, high);
}

int split_int(int a[], int low, int high)
{
	int part_element=a[low];
	
	for(;;)
	{
		while(low<high && part_element<=a[high])
			high--;
		if(low>=high) break;
		a[low++]=a[high];
		
		while(low<high && a[low]<=part_element)
			low++;
		if(low>=high) break;
		a[high--]=a[low];
	}
	
	a[high]=part_element;
	return high;
}

int quicksort_float(float a[], int low, int high)
{
	float middle;
	
	if(low>=high) return;
	middle=split_float(a, low, high);
	quicksort_float(a, low, middle-1);
	quicksort_float(a, middle+1, high);
}

int split_float(float a[], int low, int high)
{
	float part_element=a[low];
	
	for(;;)
	{
		while(low<high && part_element<=a[high])
			high--;
		if(low>=high) break;
		a[low++]=a[high];
		
		while(low<high && a[low]<=part_element)
			low++;
		if(low>=high) break;
		a[high--]=a[low];
	}
	
	a[high]=part_element;
	return high;
}
