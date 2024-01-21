/*
 * By: Mohammad Riyan Noaman and Ebenzer Oyelade
 * Updated: November 18, 2022
 * ENGG 1410 Miniproject 1
 * Encryption and Decryption
 */




#include <stdio.h>
#include <string.h>
#include <math.h>


void encrypt();
void decrypt();


int main() {
    char userinput[2];                      //will store user input "-D" "-d" "-E" "-e"


    printf("Welcome to cryptoMagic! This program will allow you to encrypt or decrypt an ASCII file.\n");

    //ask user if they would like to encrypt or decrypt, if task is not specified --> auto encrypt
    printf("Would you like to encrypt or decrypt '-E','-D'\n");
    scanf("%s", userinput);
    if(strcmp(userinput, "-D") == 0 || strcmp(userinput,"-d") == 0){
        //if the input is equal to -D or -d, call decryption function
        printf("Decryption selected...");
        decrypt();
    } else if(strcmp(userinput,"-E") == 0 || strcmp(userinput, "-e") == 0){
        //if the input is equal to -E or -e, call encryption function
        printf("Encryption selected...");
        encrypt();
    } else{
        //if neither parameter is specified, call encryption function
        printf("Task not specified, file will be encrypted...");
        encrypt();
    }


    return 0;
}

//function for renaming files
char *streplace(char *dest, const char *str1, const char *str2, const char *str3) {
    size_t i = 0, j, k = 0;

    // replacing substring `str2` with `str3`, assuming sufficient space
    while (str1[i] != '\0') {
        for (j = 0; str2[j] != '\0'; j++) {
            if (str1[i + j] != str2[j]) {
                break;
            }
        }
        if (str2[j] == '\0' && j > 0) {
            // we have a match: copy the replacement and skip it
            i += j;
            for (j = 0; str3[j] != '\0'; j++) {
                dest[k++] = str3[j];
            }
        } else {
            // copy the byte and skip it.
            dest[k++] = str1[i++];
        }
    }
    dest[k] = '\0';  // null terminate the destination
    return dest;
}

void encrypt(){
    //file read/file open

    FILE *ptr;                                        //create file pointer for reading

    FILE *ptrW;                                       //create file pointer for writing

    char readFile[255];                              //variable to hold file name (maximum 255 characters)
    char outFile[255];                               //variable for output file
    int fileVal;                                     //variable to store file character values

    int loop = 1;                                     //boolean for while loop used for reading the file values


    //ask user for file name
    printf("\nPlease enter the file name\n");
    scanf("%s", readFile);                      //store user input as file name

    //read file extension, change to .crp
    if(!strstr(readFile, ".txt")){
        strcat(readFile, ".txt");
        streplace(outFile, readFile, "txt", "crp");
    }else
    {
        streplace(outFile, readFile, "txt", "crp");
    }

    ptr = fopen(readFile, "r");           //open file with pointer

    ptrW = fopen(outFile, "w");

    //check to see if the file has a value
    if (ptr == NULL) {
        printf("Invalid File Name");
    }else {
        //create while loop to read file and print character by character
        while (loop == 1) {


            fileVal = fgetc(ptr);                           //store each character read from the file withain the variable


            //check to see if file has ended
            if (feof(ptr)) {
                loop = 0;
            } else if(fileVal == 9){
                fprintf(ptrW, "TT");
            } else if(fileVal == 32){
                //if there is a space, print the hex value of the character (prevents encryption bug)
                fprintf(ptrW, "%x", fileVal);
            } else if(fileVal== 10) {
                //if there is a line break (<CR>) do not encrypt
                //creates a new line
                fprintf(ptrW, "%c", 13);
            }else {
                //encryption: subtract by 16
                fileVal = fileVal - 16;
                if(fileVal < 32){
                    fileVal = (fileVal - 32)+144;
                    fprintf(ptrW, "%x", fileVal);
                } else{
                fprintf(ptrW,"%x", fileVal);
                }
            }
        }

    }
    fclose(ptr);                                            //close file
    fclose(ptrW);

    printf("\n\nEncryption Completed...");
}


void decrypt(){

    FILE *ptrR,*ptrW;                                           //read and write pointers
    int loop = 1;                                               //boolean for while loop
    int first, second;                                          //used for calculating first and second hex values
    int ascii_val;                                              //used for holding the ascii value of the two hex values combined
    char readFile[255];                                         //variable to hold file name (maximum 255 characters)
    char outFile[255];                                          //variable for output file


    //ask user for file name
    printf("\nPlease enter the file name\n");
    scanf("%s", readFile);                      //store user input as file name

    //change files from .crp to .txt
    if(!strstr(readFile, "crp")){
        strcat(readFile, "crp");
        streplace(outFile, readFile, "crp", "txt");
    }else
    {
        streplace(outFile, readFile, "crp", "txt");
    }

    ptrR = fopen(readFile, "r");           //open file with pointer

    ptrW = fopen(outFile, "w");


    //check to see if the file has a value
    if (ptrR == NULL) {
        printf("Invalid File Name");
    }else{
    while (loop == 1){

        //read first hex value
        first = fgetc(ptrR);

        //check to see for a new li
        if(first == 13){
            fprintf(ptrW, "\n");
        }else {

            //make sure file value is not null
            if (feof(ptrR)) {
                loop = 0;                       //break the loop
            }


            //if the ASCII value is greater than 65, subtract with 87. Otherwise, subtract with 48
            if (first >= 65) {
                first = first - 87;
            } else {
                first = first - 48;
            }
            first = first * 16;

            //read the second value

            second = fgetc(ptrR);


            //check value of the character to decide what operator is necessary
            if (second >= 65) {
                second = second - 87;
            } else {
                second = second - 48;
            }

            //add first and second values together to get the ascii value for the first character
            //include decryption formula within the sum as well (+4/2)
            ascii_val = ((first + second) + 16);


            //if value is greater than ascii values, subtract to convert back to alphabet
            if (ascii_val > 127) {
                ascii_val = (ascii_val - 144) + 32;
            }

            if (ascii_val == -817) {
                //for end of the line
                fprintf(ptrW, "%c", 00);
            } else if (ascii_val == -35) {
                //ascii value of TT = -35, convert TT to tab
                fprintf(ptrW, "\t");

            } else if (ascii_val == 48) {
                //account for spaces, ascii value found to be 48 for spaces
                fprintf(ptrW, "%c", 32);
            } else {
                fprintf(ptrW, "%c", ascii_val);
            }

        }
    }
    fclose(ptrR);
    fclose(ptrW);

    printf("\nDecryption complete...");

    }
}