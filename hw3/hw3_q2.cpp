/*Author: Lin*/
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <time.h>

void printKeyword();
void printIdent();
void printNumber();
void printDecNumber();
void printOctNumber();
void printHexNumber();

int main(){
	/*init random*/
	srand(time(NULL));

	/*init var*/
	int count=0;
	int random;

	scanf("%d", &count);

	while(count!=0){
		random=rand()%3;
		switch(random){
			case 0:
				printKeyword();
				break;
			case 1:
				printIdent();
				break;
			case 2:
				printNumber();
				break;
		}

		printf(" ");
		count--;
	}
	printf("\n");


	return 0;
}

void printKeyword(){
	int random = rand()%7;

	switch(random){
		case 0:
			printf("auto");
			break;
		case 1:
			printf("break");
			break;
		case 2:
			printf("case");
			break;
		case 3:
			printf("char");
			break;
		case 4:
			printf("const");
			break;
		case 5:
			printf("continue");
			break;
		case 6:
			printf("default");
			break;
	}

	return;
}

void printIdent(){
	int random = rand()%53;

	if(random<26)	
		printf("%c", (char)(random+65));	//A-Z
	else if(random>=26 && random < 52)
		printf("%c", (char)(random-26+97));	//a-z
	else if(random==52)
		printf("_");

	random = rand()%2;
	while(random){
		random = rand()%63;

		if(random<26)	
			printf("%c", (char)(random+65));	//A-Z
		else if(random>=26 && random < 52)
			printf("%c", (char)(random-26+97));	//a-z
		else if(random==52)
			printf("_");
		else if(random>52 && random<63)
			printf("%d", (random-53));			//0-9

		random = rand()%2;
	}

	
	return;
}

void printNumber(){
	int random=rand()%3;
	switch(random){
		case 0:
			printDecNumber();
			break;
		case 1:
			printOctNumber();
			break;
		case 2:
			printHexNumber();
			break;
	}

	return;
}

void printDecNumber(){
	int random = rand()%9+1;
	printf("%d", random);

	random = rand()%2;

	/*0:結束 1:繼續*/
	while(random){
		random = rand()%10;
		printf("%d", random);		//0-9

		random = rand()%2;
	}

	
	return;
}

void printOctNumber(){
	printf("0");

	int random = rand()%2;

	/*0:結束 1:繼續*/
	while(random){
		random = rand()%8;
		printf("%d", random);		//0-7

		random = rand()%2;
	}

	
	return;
}

void printHexNumber(){
	printf("0");
	int random = rand()%2;

	if(random)
		printf("x");
	else
		printf("X");

	random = rand()%2;

	/*0:結束 1:繼續*/
	while(random){
		random = rand()%20;
		if(random<10)
			printf("%d", random);					//0-9
		else if(random>=10 && random<15)
			printf("%c", (char)(random-10+65));		//A-F
		else
			printf("%c", (char)(random-15+97));		//a-f

		random = rand()%2;
	}

	return;
}