#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <ctype.h>
#include <string.h>

int i, j;

int rand_ans(int n, int p, int answer[])
{
	srand(time(0));
	//uses time as the seed of rand()
	//does not generate the same set of rand()

	for(i=0; i<p; i++){ 
		do{
			answer[i]=rand()%n+1;
			for(j=0; j<i; j++){ 
 				if (answer[i]==answer[j]){ 
 					answer[i]=0; 
 					break; 
 				}			 
 			}	 
 		}while(answer[i]==0); 
 	} 
	//generates the answer randomly
	//numbers do not repeat
}

int print_answer(int p, int answer[])
{
	for(i=0; i<p; i++) 
		printf("%d", answer[i]);
	printf("\n\n\n");
}

int scan_digits(char temp[], int guess[])
{
	for(i=0, j=0; i<strlen(temp); i++){
		if(isdigit(temp[i])){
			guess[j]=temp[i]-48;
			j++;
		} 
	}
	//scans the digits in the temp[]
	//put the digits in the guess[]

	return j;
}

int calc_h_x(int n, int p, int answer[], int guess[], int h, int x)
{
	int a_count[n+1], g_count[n+1];

	for(i=0; i<p; i++)
		if(guess[i]==answer[i]) 
			h++;
	//calculates the number of H

	for(i=1; i<=n; i++){
		a_count[i]=0;
		g_count[i]=0;
		
		for(j=0; j<p; j++){
			if(i==answer[j])
				a_count[i]++;
			if(i==guess[j])
				g_count[i]++;
		}
		
		if(a_count[i]>g_count[i]) 
			x+=g_count[i];
		else 
			x+=a_count[i];
	}

	x-=h;
	//calculates the number of X

	printf("%dH%2dX\n\n\n", h, x);

	return h;
}

int main(int argc, char *argv[]) 
{
	int n=*argv[1]-48, p=*argv[2]-48;
	int answer[p], guess[p];
	int h=0, x, digit_count;
	char temp[50];

	if(n<p){
		printf("\nINVALID INPUT\n\n\n");
		return 0;
	}

	printf("\n\n\n");
	printf("-------------MASTERMIND-------------\n");
	printf("------TYPE \"answer\" FOR ANSWER------\n");
	printf("------TYPE  \"exit\"  TO... EXIT------\n\n");
	
	rand_ans(n, p, answer);
	
	while(h!=p)
	{
		h=0, x=0;

		printf("GUESS %d NUMBERS FROM 1 TO %d : \n", p, n);
		scanf("%s", temp);
		
		if(!strcmp("answer", temp)){
			print_answer(p, answer);
			continue;
		}
		if(!strcmp("exit", temp))
			break;
		
		digit_count = scan_digits(temp, guess);
		
		if(digit_count<p){
			printf("NOT ENOUGH DIGITS\n\n\n");
			continue;
		}
		if(digit_count>p){
			printf("TOO MANY DIGITS\n\n\n");
			continue;
		}
		
		h = calc_h_x(n, p, answer, guess, h, x);
	}
	//the main part of the game
		
	if(h==p)
		printf("===========CONGRATULATION===========\n\n\n");
	else		    
		printf("\n\n=========THANKS FOR PLAYING=========\n\n\n");
	
	return 0;
}

