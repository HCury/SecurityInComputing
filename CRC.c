// Henrique Cury
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
#define size strlen(hex)
char hex[MAX], bin[MAX] = "";
char *convertHexToBin(char x[]);
void binToHex(char *pushPush);

  int main(){
  //  char *bin1 = malloc(strlen(hex) + 12 );
    int i = 0;
    char pad = '0';
    printf("Enter a hex number:");
    scanf("%s", hex);
    convertHexToBin(hex);
    //for some reason padding is not working here. Why?
    //for( i = size; i < size + 12; i++)
      //strcat(hex, pad);
    printf("%s\n", hex);
    //binToHex(hex);
    //printf("%s\n", hex);
    //binToHex(bin1);
    return 0;
}



void binToHex(char *pushPush){
  char *temp = pushPush;
  int num = 0;
  do{
    // using the ternary conditional operator here saves me some lines
      int b = *temp == '1' ? 1 : 0;
      num = (num<<1)|b;
      temp++;
  } while (*temp);
  //i decided to use %x here to get the unsigned hex value
  printf("Hex number is %X\n", num);
}

char *convertHexToBin(char x[]){
      for(int i=0; x[i]!='\0'; i++){
          switch(x[i]){
              case '0':
                  strcat(bin, "0000");
                  break;
              case '1':
                  strcat(bin, "0001");
                  break;
              case '2':
                  strcat(bin, "0010");
                  break;
              case '3':
                  strcat(bin, "0011");
                  break;
              case '4':
                  strcat(bin, "0100");
                  break;
              case '5':
                  strcat(bin, "0101");
                  break;
              case '6':
                  strcat(bin, "0110");
                  break;
              case '7':
                  strcat(bin, "0111");
                  break;
              case '8':
                  strcat(bin, "1000");
                  break;
              case '9':
                  strcat(bin, "1001");
                  break;
              case 'a':
              case 'A':
                  strcat(bin, "1010");
                  break;
              case 'b':
              case 'B':
                  strcat(bin, "1011");
                  break;
              case 'c':
              case 'C':
                  strcat(bin, "1100");
                  break;
              case 'd':
              case 'D':
                  strcat(bin, "1101");
                  break;
              case 'e':
              case 'E':
                  strcat(bin, "1110");
                  break;
              case 'f':
              case 'F':
                  strcat(bin, "1111");
                  break;
              default:
                  printf("Invalid hexadecimal input.");
          }
      }
      printf("Binary number is %s \n", bin);
      return bin;
    }
