/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Jilben Brito
| Language: c
|
| To Compile: javac pa02.java
| gcc -o pa02 pa02.c
| g++ -o pa02 pa02.cpp
| go build pa02.go
| python pa02.py //Caution - expecting input parameters
|
| To Execute: java -> java pa02 inputFile.txt 8
| or c++ -> ./pa02 inputFile.txt 8
| or c -> ./pa02 inputFile.txt 8
| or go -> ./pa02 inputFile.txt 8
| or python-> python3 pa02.py inputFile.txt 8
| where inputFile.txt is an ASCII input file
| and the number 8 could also be 16 or 32
| which are the valid checksum sizes, all
| other values are rejected with an error message
| and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Spring 2024
| Instructor: McAlpin
| Due Date: per assignment
|
+=============================================================================*/

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//Defines
#define MAXSIZE 10000

//Function Prototypes
void fillInputArr(FILE* file, char inputArr[]);
int idxInputArr(char inputArr[]);
unsigned long doChecksum(int idx, char inputArr[], int bit);
void padInputArr(char inputArr[], int idx, int bit);
void printArr(char arr[], int idx);
double power(int x, int y);

//Main
int main(int argc, char** argv){

    if((strcmp(argv[2], "8") != 0) && (strcmp(argv[2], "16") != 0) && (strcmp(argv[2], "32") != 0)){
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        exit(1);
    }

    FILE *file; 
    char fileInput[MAXSIZE];

    file = fopen(argv[1], "r");

    int checkSumSize = atoi(argv[2]);

    fillInputArr(file, fileInput);

    int characterCnt = idxInputArr(fileInput);

    if(characterCnt%(checkSumSize/8) != 0){
        padInputArr(fileInput, characterCnt, checkSumSize);
        characterCnt = idxInputArr(fileInput);
    }

    long checksum = doChecksum(characterCnt, fileInput, checkSumSize);

    printf("\n");
    printArr(fileInput, characterCnt);
    printf("\n");
    printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, checksum, characterCnt);

}

void fillInputArr(FILE* file, char inputArr[]){

    int idx = 0;
    int ch;

    while((ch = fgetc(file)) != EOF){ 
            inputArr[idx] = ch;
            idx++;
        }

    inputArr[idx] = '\0';
}

int idxInputArr(char inputArr[]){

    int idx = 0;

    for(int i = 0; i < MAXSIZE; i++){
        if(inputArr[i] != '\0'){
            idx++;
        }
        else{
            break;
        }
    }
    return idx;
}

unsigned long doChecksum(int idx, char inputArr[], int bit){

    unsigned long checksum = 0;

    if(bit == 8){
        for(int i = 0; i < idx; i++){
            checksum += inputArr[i];
        }
        return checksum%256;
    }

    if(bit == 16){
        unsigned long g1 = 0, g2 = 0;

        unsigned long mod = power(2, bit);

        for(int i = 0; i < idx; i++){
            if(i%2 == 0){
                g1 += inputArr[i];
            }
            else
                g2 += inputArr[i];
        }

        return ((g1<<8) + g2)%mod;
    }

    if(bit == 32){
        unsigned long g1 = 0, g2 = 0, g3 = 0, g4 = 0;

        for(int i = 0; i < idx; i++){
            if(i%4 == 0){
                g1 += inputArr[i];
            }
            else if(i%4 == 1){
                g2 += inputArr[i];
            }
            else if(i%4 == 2){
                g3 += inputArr[i];
            } 
            else if(i%4 == 3){
                g4 += inputArr[i];
            }
        }

        unsigned long mod = power(2, bit);

        return ((g1<<24) + (g2<<16) + (g3<<8) + g4)%mod;
    }

    return 0;
}

void padInputArr(char inputArr[], int idx, int bit){

    int i;

    int pad = (bit/8) - (idx%(bit/8));

    for(i = 0; i < pad; i++){
        inputArr[idx + i] = 'X';
    }
    inputArr[idx + i] = '\0';
}

void printArr(char arr[], int idx){

    int ch;
    for(int i = 0; i < idx; i++){
        if(i%80 != 0 || i == 0){
            if(arr[i] != '\0'){
                printf("%c", arr[i]);
            }
            else{
                break;
            }
        }
        else{
            printf("\n");
            if(arr[i] != '\0')
                printf("%c", arr[i]);
        }
    }

}

double power(int x, int y){

    double res = 1;
    for(int i = 0; i < y; i++){
        res = res*x;
    }
    return res;
}

/*=============================================================================
| I Jilben Brito (5512370) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+============================================================================*/