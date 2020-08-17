// Henrique Cury
// he200230
// 3517770
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


void header(char* fileName, char* hashValue);
long hash(long unHashed);

typedef struct pList{
	char password[7]; //password from file(all are 6 letters need one for null)
	int letterInt[6];	//password letter in int
	long passwordInt;	//password in int
	int saltedValue;
	long saltedPassword;
	long hashPassword;
} pList;

int main(int argc, char *argv[]){
	header(argv[1], argv[2]);
	FILE *fp;
	fp = fopen(argv[1], "r");
	if(!fp){
		fprintf(stderr, "ERROR: File not Found\n");
		return 1;
	}
	//declaring # of passwords that can be stored
	int i, j, numPword = 0; // counter
	pList passwords[1000];
	char buff[7];
	//Stores the passwords in list
	while(fgets(buff, 7, fp) != NULL){
		if(strcmp(buff, "\n") == 0)
			fgets(buff, 7, fp);
		char *string;
		string = buff;
		strcpy(passwords[numPword].password, string);
		numPword++;
	}

	//converting to integer values
	for(i=0; i<numPword; i++){
		for(j=0; j<6; j++)
		passwords[i].letterInt[j] = (int) passwords[i].password[j];
	}

	char *numberInString;
	numberInString = malloc(sizeof(char) * 12 + 1);
	char numberInArray[2];
	//converting int to long
	for (i=0; i<numPword; i++){
		for(j=0; j<6; j++){
			strcpy(numberInArray, "");
			sprintf(numberInArray, "%d", passwords[i].letterInt[j]);
			strcat(numberInString, numberInArray);
		}
		passwords[i].passwordInt = atol(numberInString);
		strcpy(numberInString, "");
	}
	free(numberInString);

	//index, password, and unsalted ASCII
	for (i=0; i<numPword; i++)
		printf("%d:\t%s\t%ld\n", i+1,passwords[i].password,passwords[i].passwordInt);
	//
	int count = 0;
	int foundPword;
	char foundHash[8];
	for(i=0; i<numPword; i++){
		char saltedString[15];
		char hashString[8];

		for(j=0; j<1000; j++){
			sprintf(saltedString,"%03d%ld", j, passwords[i].passwordInt);
			passwords[i].saltedPassword = atol(saltedString);
			passwords[i].hashPassword = hash(passwords[i].saltedPassword);
			sprintf(hashString,"%ld", passwords[i].hashPassword);

		 //computer has vs user hash
			if(strcmp(hashString, argv[2]) == 0){
				count+=j+1;
				foundPword = i;
				passwords[i].saltedValue = j;
				strcpy(foundHash, hashString);
				break;
			}
			if(j==999)
				count+=1000;
		}

		if(strcmp(hashString, argv[2]) == 0)
				break;
	}

	// output
	if(strcmp(foundHash, argv[2]) == 0){
		printf("   Password Recovered:\n");
		printf("   Password\t\t: %s\n", passwords[foundPword].password);
		printf("   ASCII Value\t\t: %ld\n", passwords[foundPword].passwordInt);
		printf("   Salt Value\t\t: %03d\n", passwords[foundPword].saltedValue);
		printf("   Combinations Tested\t: %d\n\n", count);
	}
	else{
		printf("\n\nPassword Not Found in Dictionary\n\n");
		printf("Combinations Tested:  %d\n\n", count);
	}

	fclose(fp);
	return 0;
}


void header(char* fileName, char* hashValue){
	printf("\n");
	int i;
	printf("\n\n\tDictionary file name \t\t: %s", fileName);
	printf("\n\tSalted password hash value \t: %s\n\n", hashValue);
	printf("Index\tWord\tUnsalted ASCII equivalent\n\n");
}

long hash(long unHashed){
	int i;
	char *unHashedString;
	unHashedString = malloc(sizeof(char) * 15+1);
	char *left;
	char *right;
	long hashValue;

	//converts long integer to a string
	sprintf(unHashedString,"%015ld", unHashed);

	left = malloc(sizeof(char) * 7+1);
	right = malloc(sizeof(char) * 8+1);
	//Splits the LEFT side
	for(i=0; i<7; i++)
		left[i] = unHashedString[i];
	//Splits the RIGHT side
	for(i=7; i<15; i++)
		right[i-7] = unHashedString[i];
	hashValue = ((243 * (atol(left))) + atol(right)) % 85767489;
	free(left);
	free(right);
	free(unHashedString);
	return hashValue;
}
