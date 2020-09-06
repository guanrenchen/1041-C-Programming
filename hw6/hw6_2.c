#include <stdio.h>
#include <math.h>

union uni{
	float f;
	double d;
	unsigned a;
	unsigned long long b;
};

int main(int argc, char *argv[])
{
	union uni u;
	int i;
	unsigned y=0x80000000U;
	unsigned long long z=0x8000000000000000ULL;
	char fl[32], db[64];
	
	printf("INPUT THE FLOAT NUMBER : ");
	scanf("%f", &u.f);
	u.a=*(unsigned*)&u.f;
	while(y!=0)
	{
		printf("%d", (u.a&y)!=0U);
		y>>=1;
	}
	u.a=0;
	printf("\nINPUT BINARY NUMBER TO CONVERT FLOAT NUMBER : \n");
	scanf("%s", &fl);
	for(i=0; i<32; i++)
		if(fl[i]-48==1)  u.a+=pow(2,31-i);
	printf("%e", *(float*)&u.a);
	
	printf("\n\nINPUT THE DOUBLE NUMBER : ");
	scanf("%lf", &u.d);
	u.b=*(unsigned long long*)&u.d;
	while(z!=0)
	{
		printf("%d", (u.b&z)!=0ULL);
		z>>=1;	
	} 
	u.b=0;
	printf("\nINPUT BINARY NUMBER TO CONVERT DOUBLE NUMBER : \n");
	scanf("%s", &db);
	for(i=0; i<64; i++)
		if(db[i]-48==1)  u.b+=pow(2,63-i);
	printf("%e\n", *(double*)&u.b);
	
	return 0;
}
