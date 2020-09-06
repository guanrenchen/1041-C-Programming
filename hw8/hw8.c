#include <stdio.h>
#include <stdlib.h>

int i;
//loop var

int X, Y, IP[5];
//X : significant bits in decimal (8)
//Y : significant bits in decimal (12)
//IP[] : temporary storage for IP/prefix

unsigned long long int begin, end;
unsigned long long int rdtsc()
{
	unsigned long long int a;
	asm volatile("rdtsc":"=A"(a));
	return a;
}

struct node{
	int IP[5];
	struct node *next;
};
typedef struct node node;

void init_db(node *db1[], node *db2[], node *db3[])
{
	for(i=0; i<256; i++)
		db1[i]=NULL;
	for(i=0; i<4096; i++)
	{
		db2[i]=NULL;
		db3[i]=NULL;
	}
	return;
}

node *insr(node *list, int IP[])
{
	node *prev, *cur, *new=malloc(sizeof(node));
	
	for(i=0; i<5; i++)
		new->IP[i]=IP[i];
	new->next=NULL;
	//set new node
	
	if(list==NULL)
		return new;

	for(prev=NULL, cur=list; cur!=NULL && IP[4]<cur->IP[4]; prev=cur, cur=cur->next);
	//descendiing order(number of prefix)

	if(prev==NULL)
	{
		new->next=list;
		return new;
	}
	if(cur==NULL)
	{
		prev->next=new;
		return list;
	}
	prev->next=new;
	new->next=cur;	
	return list;
}

void file_insr(FILE *f, node *db1[], node *db2[], node *db3[], FILE *csv)
{
	while(fscanf(f,"%d.%d.%d.%d/%d",&IP[0],&IP[1],&IP[2],&IP[3],&IP[4])!=EOF)
	{
		X=IP[0];
		Y=IP[0]*16+(IP[1]&240)/16;
		
		begin=rdtsc();
		if(IP[4]<=15) 
			db1[X]=insr(db1[X], IP);
		else if(IP[4]<=24) 
			db2[Y]=insr(db2[Y], IP);
		else 
			db3[Y]=insr(db3[Y], IP);
		end=rdtsc();
		
		if(csv!=NULL)
			fprintf(csv,"%llu\n",end-begin);
	}
	return;
}

void srch(node *list, int IP[], int m[])
{
	node *cur;
	int p, q, match;
	
	for(cur=list; cur!=NULL; cur=cur->next)
	{
		match=1;
		p=cur->IP[4]/8;
		q=8-(cur->IP[4]%8);
		
		for(i=0; i<p; i++)
			if(IP[i]!=cur->IP[i])
				{match=0; break;}

		if(match && (IP[p]>>q)==(cur->IP[p]>>q))
		{
			for(i=0; i<5; i++)
				m[i]=cur->IP[i];	
			break;
		}
	}
	return;
}

void file_srch(FILE *f, node *db1[], node *db2[], node *db3[], FILE *rslt, FILE *csv)
{
	int m[5];
	//m[] : storage for match
		
	while(fscanf(f,"%d.%d.%d.%d",&IP[0],&IP[1],&IP[2],&IP[3])!=EOF)
	{
		X=IP[0];
		Y=IP[0]*16+(IP[1]&240)/16;
		
		for(i=0; i<5; i++) 
			m[i]=-1;

		begin=rdtsc();
		srch(db3[Y], IP, m);
		if(m[0]==-1)
			srch(db2[Y], IP, m);
		if(m[0]==-1)
			srch(db1[X], IP, m);
		if(m[0]==-1)
			for(i=0; i<5; i++)
				m[i]=0;	
		end=rdtsc();

		fprintf(rslt,"%d.%d.%d.%d/%d\n",m[0],m[1],m[2],m[3],m[4]);
		fprintf(csv,"%llu\n",end-begin);
	}
	return;
}

node *delt(node *list, int IP[])
{
	node *cur, *prev;
	
	for(prev=NULL, cur=list; cur!=NULL && !(cur->IP[0]==IP[0] && cur->IP[1]==IP[1] && cur->IP[2]==IP[2] && cur->IP[3]==IP[3] && cur->IP[4]==IP[4]); prev=cur, cur=cur->next);
	
	if(cur==NULL)
		return list;  
	if(prev==NULL)
		list=list->next;       
	else
		prev->next=cur->next;  
	
	free(cur);
	return list;
}

void file_delt(FILE *f, node *db1[], node *db2[], node *db3[], FILE *csv)
{
	while(fscanf(f,"%d.%d.%d.%d/%d",&IP[0],&IP[1],&IP[2],&IP[3],&IP[4])!=EOF)
	{
		X=IP[0];
		Y=IP[0]*16+(IP[1]&240)/16;	

		begin=rdtsc();
		if(IP[4]<=15)
			db1[X]=delt(db1[X], IP);
		else if(IP[4]<=24)
			db2[Y]=delt(db2[Y], IP);
		else
			db3[Y]=delt(db3[Y], IP);	
		end=rdtsc();

		fprintf(csv,"%llu\n",end-begin);
	}
	return;
}

int main(int argc, char *argv[])
{
	FILE *f_data=fopen("IPv4_400k.txt", "r"),
	     *f_srch=fopen("IPv4_search.txt", "r"),
	     *f_insr=fopen("IPv4_insert.txt", "r"),
	     *f_delt=fopen("IPv4_delete.txt", "r"),
	     *f_rslt=fopen("result.txt", "w"),
	     *csv_srch=fopen("search.csv","w"),
	     *csv_insr=fopen("insert.csv","w"),
	     *csv_delt=fopen("delete.csv","w");
	//csv : for generating graphs

	if(f_data==NULL || f_srch==NULL || f_insr==NULL || f_delt==NULL)
	{
		printf("ERROR\n"); 
		return 0;
	}

	node *db1[256], *db2[4096], *db3[4096];
	init_db(db1, db2, db3);
	
	file_insr(f_data, db1, db2, db3, NULL);
	file_srch(f_srch, db1, db2, db3, f_rslt, csv_srch);
	file_insr(f_insr, db1, db2, db3, csv_insr);
	file_delt(f_delt, db1, db2, db3, csv_delt);

	fclose(f_data);
	fclose(f_srch);
	fclose(f_insr);
	fclose(f_delt);
	fclose(f_rslt);
	fclose(csv_srch);
	fclose(csv_insr);
	fclose(csv_delt);
	return 0;
}
