#include <stdio.h>

int i;

void conv(FILE *in, FILE *out, int n, int num)
{
	int z;
	int a[n][2];
	for(i=0; i<n; i++)
	{
		a[i][0]=i*num;
		a[i][1]=0;
	}

	while(fscanf(in,"%d",&z)!=EOF)
		if(z<num*n)
			a[z/num][1]++;

	for(i=0; i<n; i++)
		fprintf(out, "%d,%d\n", a[i][0], a[i][1]);
	return;
}

int main()
{
	FILE *srch=fopen("./search.csv", "r"),
	     *insr=fopen("./insert.csv", "r"),
	     *delt=fopen("./delete.csv", "r"),
	     *dt_srch=fopen("sr.csv", "w"),
	     *dt_insr=fopen("ns.csv", "w"),
	     *dt_delt=fopen("dl.csv", "w");

	conv(srch, dt_srch, 100, 1000);
	conv(insr, dt_insr, 100, 1000);
	conv(delt, dt_delt, 100, 1000);	

	return 0;
}
