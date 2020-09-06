#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
	int n = *argv[1] - 48, p = *argv[2] - 48;
	int answer[p], guess[p];
	int h_count, x_count, a_count[n + 1], g_count[n + 1];
	char temp[50];
	int i, j;

	if(n < p){
		printf("\nINVALID INPUT\n\n\n");
		
		return 0;
	}

	srand(time(0));
	//uses time as the seed of rand()
	//does not generate the same set of rand()

	printf("\n\n\n");
	printf("-------------MASTERMIND-------------\n");
	printf("------TYPE \"answer\" FOR ANSWER------\n");
	printf("------TYPE  \"exit\"  TO... EXIT------\n\n");

	for(i = 0; i < p; i++){ 
		do{ 
 			answer[i] = rand() % n + 1; 
 			for(j = 0; j < i; j++){ 
 				if (answer[i] == answer[j]){ 
 					answer[i] = 0; 
 					break; 
 				}			 
 			}	 
 		}while(answer[i] == 0); 
 	} 
	//generates the answer randomly
	//numbers do not repeat
	
	while(h_count != p){
		h_count = 0;
		x_count = 0;
		printf("GUESS %d NUMBERS FROM 1 TO %d : \n", p, n);
		
		scanf("%s", temp);
		//store the user's guess in the temp[]

		if(strcmp("answer", temp) == 0){
			printf("\n");
			for(i = 0; i < p; i++) 
				printf("%d", answer[i]);
			printf("\n\n\n");
			continue;
		}
		//provides a way to get the answer directly
		
		if(strcmp("exit", temp) == 0)
			break;
		//provides a way to exit the game directly
		
		for(i = 0, j = 0; i < strlen(temp); i++){
			if(isdigit(temp[i])){
				guess[j] = temp[i] - 48;
				j++;
			} 
		}

		if(j < p){
			printf("\nNOT ENOUGH DIGITS\n\n\n");
			continue;
		}

		if(j > p){
			printf("\nTOO MANY DIGITS\n\n\n");
			continue;
		}
		//scans the digits in the temp[]
		//put the digits in the guess[]

		for(i = 1; i <= n; i++){
			a_count[i] = 0;
			g_count[i] = 0;
			
			for(j = 0; j < p; j++){
				if(i == answer[j])
					a_count[i]++;
				if(i == guess[j])
					g_count[i]++;
				}
			
			if(a_count[i] > g_count[i]) 
				x_count += g_count[i];
			else 
				x_count += a_count[i];
		}
		//calculates the number of X
		
		for(i = 0; i < p; i++){
			if(guess[i] == answer[i]) 
				h_count++;
		}
		//calculates the number of H
		
		x_count -= h_count;	
		
		printf("\n%3dH%3dX\n\n\n", h_count, x_count);
	}
	//the main part of the game
		
		if(h_count == p)
			printf("===========CONGRATULATION===========\n\n\n");
		else		    
			printf("\n\n=========THANKS FOR PLAYING=========\n\n\n");
	
	return 0;
}
