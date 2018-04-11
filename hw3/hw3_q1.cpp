/*Author: Lin*/
#include<cstdio>
#include<cstdlib>
#include<string.h>
#include<regex.h>

typedef struct tWord{
	char name[32];
	int type;
	struct tWord* next;
}word;
typedef struct twordHead{
	struct tWord* start;
	struct tWord* end;
	int n;
}wordHead;

void addNode(char* tempStr, wordHead* wordList);
void getType(int type);
void printList(wordHead* wordList);

void identifyWord(word* node);

int main(){
	/*init file*/
	FILE* fp;

	/*init linked list head*/
	wordHead* wordList = (wordHead *) malloc(sizeof(wordHead)) ;
	wordList->start = NULL;
	wordList->end = NULL;
	wordList->n = 0;

	/*init var*/
	char buffer[1024];
	int flag=0;

	/*開檔*/
	if((fp=fopen("exampleFile.txt", "r")) == NULL){
		printf("讀檔錯誤\n");
		return 0;
	}

	/*讀檔*/
	while(fgets(buffer, 1024, fp) != NULL){
		/*過濾換行*/
		if(buffer[strlen(buffer)-1] == '\n')
			buffer[strlen(buffer)-1] = '\0';

		/*切空格*/
		char* tempStr = strtok(buffer, " ");
		while(tempStr != NULL){
			/*將str加入linked list*/
			addNode(tempStr, wordList);
			
			/*切空格*/
			tempStr = strtok(NULL, " ");
		}
	}

	/*輸出結果*/
	printList(wordList);

	return 0;
}

void addNode(char* tempStr, wordHead* wordList){
	/*init linked list node*/
	word* node = (word*) malloc(sizeof(word));
	node->type = 0;
	node->next = NULL;

	/*srting copy*/
	strcpy(node->name, tempStr);

	/*連接linked list*/
	if(wordList->n==0){
		wordList->start = node;
		wordList->end = node;
		wordList->n++;
	}
	else{
		wordList->end->next = node;
		wordList->end = node;
		wordList->n++;
	}

	/*偵測型態*/
	identifyWord(node);
}

void identifyWord(word* node){
	/*init regex*/
	regex_t preg;
	int cflags = REG_EXTENDED;
	regmatch_t pmatch[1];
    size_t nmatch = 1;

    /*identify 整數*/
	if( regcomp(&preg, "(^[0-9]*$|^0[xX][0-9a-fA-F]+$)", cflags) != 0 ) {
        printf("regex compile error!\n");
        //return 1;
    }
    if( regexec( &preg , node->name , nmatch , pmatch , 0 ) == 0){
    	node->type = 3;
    	return;
    }

    regfree(&preg);

    /*identify 關鍵字*/
    char keyword[] = "^(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)$";
    if( regcomp(&preg, keyword, cflags) != 0 ) {
        printf("regex compile error!\n");
        //return 1;
    }
    if( regexec( &preg , node->name , nmatch , pmatch , 0 ) == 0){
    	node->type = 1;
    	return;
    }

    regfree(&preg);


    /*identify 識別字*/
	if( regcomp(&preg, "^[a-zA-Z_][a-zA-Z0-9_]{0,30}$", cflags) != 0 ) {
        printf("regex compile error!\n");
        //return 1;
    }
    if( regexec( &preg , node->name , nmatch , pmatch , 0 ) == 0){
    	node->type = 2;
    	return;
    }

    return;
}

void getType(int type){
	switch(type){
		case 1:
			printf("關鍵字:");
			break;
		case 2:
			printf("識別字:");
			break;
		case 3:
			printf("整數常數:");
			break;
		default:
			printf("錯誤:");
			break;
	}
}

void printList(wordHead* wordList){
	word* pNode;
	pNode = wordList->start;
	while(pNode != NULL){
		getType(pNode->type);
		printf("%s\n", pNode->name);
		pNode = pNode->next;
	}
}