#include <stdio.h>
#include <math.h>

int i;

int main(int argc, char *argv[])
{
	float f;
	double d;
	int a, y=0x80000000U;
	//variables for float <-> binary
	int long long b, z=0x8000000000000000ULL;
	//variables for double <-> binary
	char fl[32], db[64]; 
	//storage for binary
	
	printf("INPUT THE FLOAT NUMBER : ");
	scanf("%f", &f);
	a=*(int*)&f;
	while(y!=0)
	{
		printf("%d", (a&y)!=0U);
		y>>=1;
	}
	a=0;
	printf("\nINPUT BINARY NUMBER TO CONVERT FLOAT NUMBER : \n");
	scanf("%s", &fl);
	for(i=0; i<32; i++)
		if(fl[i]-48==1)  a+=pow(2,31-i);
	printf("%e", *(float*)&a);
	
	printf("\n\nINPUT THE DOUBLE NUMBER : ");
	scanf("%lf", &d);
	b=*(int long long*)&d;
	while(z!=0)
	{
		printf("%d", (b&z)!=0ULL);
		z>>=1;	
	} 
	b=0;
	printf("\nINPUT BINARY NUMBER TO CONVERT DOUBLE NUMBER : \n");
	scanf("%s", &db);
	for(i=0; i<64; i++)
		if(db[i]-48==1)  b+=pow(2,63-i);
	printf("%e\n", *(double*)&b);

	return 0;
}
