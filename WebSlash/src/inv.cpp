#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include "inv.h"

#define MAX_HOARD 50
#define MAX_NAME_LEN 60



int initInv(){
    char invBuff [MAX_NAME_LEN];

    FILE* invDef;
    invDef = fopen ("../gameFiles/invDefault.txt","r");
    FILE* plyrInv;
    plyrInv = fopen ("../playerFiles/playerInv.txt","w");

    if (plyrInv == NULL || invDef == NULL){
        fclose (invDef);
        fclose (plyrInv);
        printf("Error 49: Unable to Init inv");
        getch();
        return 0;
    }
    else
        while(fgets(invBuff, MAX_NAME_LEN-1,invDef) != NULL){
            fprintf(plyrInv,invBuff);
        }
    fclose (invDef);
    fclose (plyrInv);
    return 1;
}

void dispInv (){
    FILE* invFile;
    invFile = fopen("../playerFiles/playerInv.txt","r");
    char invStore [MAX_NAME_LEN];

    if (invFile==NULL){
        printf("{Critical error 50}");
        getch();
        fclose(invFile);
        return;
    }

    for(int i = 0; i < MAX_HOARD; i++){
        if (fgets(invStore, MAX_NAME_LEN-1,invFile) != NULL)
            printf("%s \n", invStore);
        else
            exit;
    }

    fclose(invFile);
}

void addToInv (char*, int itemClass){

}


