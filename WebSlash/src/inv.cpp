#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include "inv.h"
#include "LevelGen.h"

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

int destroyItem(int itemNum){
    FILE* invTemp;
    invTemp = fopen ("../playerFiles/invTemp.txt","w");
    FILE* invFile;
    invFile = fopen ("../playerFiles/playerInv.txt","r");

    char invBuff [MAX_NAME_LEN];
    char invBuff2 [MAX_NAME_LEN];

    for(int i = 0; i < MAX_HOARD; i++){
        if (i != itemNum){
            if (fgets(invBuff, MAX_NAME_LEN-1,invFile) != NULL){
                fprintf(invTemp,invBuff);
            }
            else
                exit;
        } else {
            fgets(invBuff, MAX_NAME_LEN-1,invFile);
        }
    }
    fclose(invTemp);
    fclose(invFile);

    invTemp = fopen ("../playerFiles/invTemp.txt","r");
    invFile = fopen ("../playerFiles/playerInv.txt","w");

    for(int i = 0; i < MAX_HOARD; i++){
            if (fgets(invBuff, MAX_NAME_LEN-1,invTemp) != NULL)
                fprintf(invFile,invBuff);
            else
                exit;
    }
    fclose(invTemp);
    fclose(invFile);

    printf("- Item Destroyed - ");
    getch();
    return 1;
}

int invCommands (){
    char inp;

    printf("Equip : e\tDestroy : d\tExit : Anything else\n\n");
    inp = getch();
    if (inp == 'd'){
        printf("Which Item Do You Want to Destroy?");
        inp = getch();
        destroyItem(inp-'a');
    }
    return 1;
}

void dispInv (){
    FILE* invFile;
    invFile = fopen("../playerFiles/playerInv.txt","r");
    char invBuff [MAX_NAME_LEN];

    if (invFile==NULL){
        printf("{Critical error 50}");
        getch();
        fclose(invFile);
        return;
    }

    system("cls");
    printf("\t\t\t Inventory\n_____________________________________________________________________\n");
    for(int i = 0; i < MAX_HOARD; i++){
        if (fgets(invBuff, MAX_NAME_LEN-1,invFile) != NULL)
            printf("%c - %s \n", 'a'+i, invBuff);
        else
            exit;
    }
    fclose(invFile);

    invCommands();
}

void addToInv (char *item, int itemNum){
    FILE* invFile;
    invFile = fopen("../playerFiles/playerInv.txt","a");
    fprintf(invFile,"%s %i", item, itemNum);

    fclose(invFile);
}

const char* weaponNameGen(char *itemName, int itemClass){
    const char* prefix[] = {"Sword", "Halberd", "Blade", "Dagger", "Brick", "Shovel", "Sharp Stick", "Staff" };
    const char* suffix[] = {"Sharpness", "Gouging", "No Return", "Badassery", "De-Boning", "Fortitude", "Your Mother"};


    if (itemClass == 1){
        sprintf(itemName,"%s of %s", prefix[rb(0,3)], suffix[rb(0,7)]);
        return itemName;
    } else if (itemClass == 2) {
        sprintf(itemName,"%s of %s", prefix[rb(4,6)], suffix[rb(0,7)]);
        return itemName;
    } else if (itemClass == 3) {
        sprintf(itemName,"%s of %s", prefix[7], suffix[rb(0,7)]);
        return itemName;
    }
}

const char* armorNameGen(char *itemName, int itemClass){
    const char* prefix[] = {"Robe", "Mail", "Cap", "SnapBack", "Helm", "Chest Plate", "Cuirass", "Jeans", "Chaps", "Legs", "Socks", "Boots"};
    const char* suffix[] = {"Swiftness", "Protection", "Horrid Fashion", "Darkness", "Awesomeness", "Fortitude", "Your older sibling"};

    if (itemClass == 1){
        sprintf(itemName,"%s of %s", prefix[rb(0,1)], suffix[rb(0,6)]);
        return itemName;
    } else if (itemClass == 2) {
        sprintf(itemName,"%s of %s", prefix[rb(2,4)], suffix[rb(0,6)]);
        return itemName;
    } else if (itemClass == 3) {
        sprintf(itemName,"%s of %s", prefix[rb(5,6)], suffix[rb(0,6)]);
        return itemName;
    } else if (itemClass == 4) {
        sprintf(itemName,"%s of %s", prefix[rb(7,9)], suffix[rb(0,6)]);
        return itemName;
    } else if (itemClass == 5) {
        sprintf(itemName,"%s of %s", prefix[rb(10,11)], suffix[rb(0,6)]);
        return itemName;
    }
}


void addRandToInv(){
    FILE* invFile;
    invFile = fopen("../playerFiles/playerInv.txt","w");
    char itemName[MAX_NAME_LEN];
    fprintf(invFile,"%s %i\n", weaponNameGen(itemName, rb(1,3)), 1);
    fprintf(invFile,"%s %i\n", armorNameGen(itemName, rb(1,5)), 1);

    fclose(invFile);
}




