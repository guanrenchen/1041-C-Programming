#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,j;

int cmp(const void *a, const void *b)
{
	return *(int*)b-*(int*)a;
	//qsort in descending order
}

int main(int argc, char *argv[]) 
{
	int n=atoi(argv[1]), x=atoi(argv[2]);
	int a[n], d[n];
	
	if(!(x==0 || x==1) || n<1)
	{
		printf("\nINVALID INPUT\n\n\n");
		return 0;
	}

	srand(time(0)); 
	for(i=0; i<n; i++)
		a[i]=rand()%1000000;
	
	printf("\n\nBEFORE SORTING : \n");	
	print_array(a, n, x);

	quicksort(a, 0, n-1);
	for(i=0, j=n-1; i<n; i++, j--)
		d[j]=a[i];
	for(i=0; i<n; i++)
		a[i]=d[i];
	//sort in descending order
	
	//qsort(a, n, sizeof(a[0]), cmp);
	//does the same thing as above
	//order decided by cmp

	printf("\n\nAFTER SORTING : \n");
	print_array(a, n, x);
	
	printf("\n\n\n");
	return 0;
}

int print_array(int a[],int n, int x)
{
	for(i=0, j=0; i<n; i++, j++)
	{
		if(j/10>(j-1)/10)
			printf("\n");
		if(x==0)
			printf("%6d", a[i]/100);
		if(x==1)
			printf("%8.2f", (float)a[i]/100);
	}
	//prints out the array (int/float)
}

int quicksort(int a[], int low, int high)
{
	int middle;
	
	if(low>=high) return;
	middle=split(a, low, high);
	quicksort(a, low, middle-1);
	quicksort(a, middle+1, high);
}

int split(int a[], int low, int high)
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
