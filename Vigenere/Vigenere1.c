// Henrique Cury
// CIS3360
// Spring 2018

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char * argv[])
{
		FILE *fp;
		char testChar;
		char temp;
    int x, y = 0, i = 0, j = 0;
		int value = 0;
		int key_int = 0;
		char array[1024];
    char *word;
		fp = fopen(argv[1], "r");
		char *key = strdup(argv[2]);
		char *IV = strdup(argv[3]);
		int blockSize = strlen(key);
		if(!fp)
			return 1;
		printf("File Name: %s\n", argv[1]);
		printf("Key: %s\n", key);
		printf("IV: %s\n", IV);
    printf("Plaintext: ");

		while(temp != EOF){
			temp = fgetc(fp);
			if(isalpha(temp)||isdigit(temp)){
				temp = tolower(temp);
				if(isalpha(temp)){
					testChar = temp;
					value = testChar - 97;
					key_int = IV[i % blockSize] - 97;
					testChar = (value + key_int) % 26 + 97;
					key_int = key[i % blockSize] - 97;
					value = testChar - 97;
					testChar = (value + key_int) % 26 + 97;
					IV[i % blockSize] = testChar;
					array[i] = testChar;
				}
      //  strcat(word, &temp);
				i++;
				printf("%c", temp);
			}
		}
		printf("\n");
		printf("Ciphertext: ");

		while( i > 0 ){
			printf("%c", array[j]);
			j++;
			i--;
		}
		x = j;

		while(x % blockSize != 0){
			testChar = 'x';
			value = testChar - 97;
			key_int = IV[x % blockSize] - 97;
			testChar = (value + key_int) % 26 + 97;
			key_int = key[x % blockSize] - 97;
			value = testChar - 97;
			testChar = (value + key_int) % 26 + 97;
			IV[i % blockSize] = testChar;
			printf("%c", testChar);
			x++;
      y++;
		}

		printf("\n");
		printf("Characters in plaintext: %d\n", j);
		printf("Block size: %d\n", blockSize);
		printf("Padded characters: %d\n", y);

    //failing decryption
    for(i = 0;i < strlen(array);i++){
         if(j >= strlen(key))
             j=0;
         key_int = IV[i % blockSize] - 97;
         value = word - IV - key_int;
         // negatives
         if( value < 0)
            value = value * -1;
         printf("%c",(value % 26) + 97);
    }

    printf("\n");
    free(key);
    free(IV);
    fclose(fp);
		return 0;

}
