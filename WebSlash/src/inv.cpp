#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include "inv.h"
#include "LevelGen.h"
#include "plyr.h"

#define MAX_HOARD 50
#define MAX_NAME_LEN 60

#define WEAPON_FLAG 1
#define ARMOR_FLAG 2



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

int alreadyEquipped(int itemClass){
    FILE* invFile;
    invFile = fopen ("../playerFiles/playerInv.txt","r");
    char invBuff [MAX_NAME_LEN];
    int eqFlag, itemClas;

    for(int i = 0; i < MAX_HOARD; i++){
        if (fgets(invBuff, MAX_NAME_LEN-1,invFile) != NULL){
            sscanf(invBuff, "%*s %*i %*i %i %i",&eqFlag,&itemClas);
            if (eqFlag && itemClass == itemClas){
                printf("\nSorry you already have one of that type equipped.");
                getch();
                return 1;
            }
        }
    }
    return 0;
}

int equipItem (player *playr, int itemNum){
    FILE* invTemp;
    invTemp = fopen ("../playerFiles/invTemp.txt","w");
    FILE* invFile;
    invFile = fopen ("../playerFiles/playerInv.txt","r");
    char invBuff_Name [MAX_NAME_LEN];
    int atk, def, itemClass, eqFlag;

    char invBuff [MAX_NAME_LEN];

    for(int i = 0; i < MAX_HOARD; i++){
        if (i != itemNum){
            if (fgets(invBuff, MAX_NAME_LEN-1,invFile) != NULL){
                fprintf(invTemp,invBuff);
            }
            else
                exit;
        } else {
            if (fgets(invBuff, MAX_NAME_LEN-1,invFile) != NULL){
                sscanf(invBuff, "%s %i %i %i %i",invBuff_Name, &atk, &def, &eqFlag,&itemClass);
                if(itemClass == WEAPON_FLAG && !eqFlag && alreadyEquipped(WEAPON_FLAG)){
                    playr->addAtkBon(atk);
                } else if (itemClass == ARMOR_FLAG && !eqFlag && alreadyEquipped(ARMOR_FLAG)){
                    playr->addDefBon(def);
                }
                sprintf(invBuff,"%s %i %i %i %i",invBuff_Name, atk, def, 1, itemClass);
                fprintf(invTemp,"%s\n",invBuff);
            }
            else
                exit;

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

    printf("\n\n- Item Equipped - ");
    getch();
    return 1;
}

int unEquipItem (player *playr, int itemNum){
    FILE* invTemp;
    invTemp = fopen ("../playerFiles/invTemp.txt","w");
    FILE* invFile;
    invFile = fopen ("../playerFiles/playerInv.txt","r");
    char invBuff_Name [MAX_NAME_LEN];
    int atk, def, itemClass, eqFlag;

    char invBuff [MAX_NAME_LEN];

        for(int i = 0; i < MAX_HOARD; i++){
        if (i != itemNum){
            if (fgets(invBuff, MAX_NAME_LEN-1,invFile) != NULL){
                fprintf(invTemp,invBuff);
            }
            else
                exit;
        } else {
            if (fgets(invBuff, MAX_NAME_LEN-1,invFile) != NULL){
                sscanf(invBuff, "%s %i %i %i %i",invBuff_Name, &atk, &def, &eqFlag, &itemClass);
                if(itemClass == WEAPON_FLAG && eqFlag){
                    playr->addAtkBon(-atk);
                } else if (itemClass == ARMOR_FLAG && eqFlag){
                    playr->addDefBon(-def);
                }
                sprintf(invBuff,"%s %i %i %i %i",invBuff_Name, atk, def, 0, itemClass);
                fprintf(invTemp,"%s\n",invBuff);
            }
            else
                exit;

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

    printf("\n\n- Item UnEquipped - ");
    getch();
    return 1;
}

int invCommands (player *playr){
    char inp;

    printf("Equip : e\tDestroy : d\tUnequip : u\tExit : Anything else\n\n");
    inp = getch();
    if (inp == 'd'){
        printf("Which Item Do You Want to Destroy?");
        inp = getch();
        destroyItem(inp-'a');
    } else if (inp == 'e'){
        printf("Which Item Do You Want to Equip?");
        inp = getch();
        equipItem(playr ,inp-'a');
    } else if (inp == 'u'){
        printf("Which Item Do You Want to UnEquip?");
        inp = getch();
        unEquipItem(playr ,inp-'a');
    }
    return 1;
}

void dispInv (player *playr){
    FILE* invFile;
    invFile = fopen("../playerFiles/playerInv.txt","r");
    char invBuff [MAX_NAME_LEN];
    char invBuff_Name [MAX_NAME_LEN];
    int invBuffAtk, invBuffDef;

    if (invFile==NULL){
        printf("{Critical error 50}");
        getch();
        fclose(invFile);
        return;
    }

    system("cls");
    printf("\t\t\t Inventory\n_____________________________________________________________________\n\tItem Name\n");
    for(int i = 0; i < MAX_HOARD; i++){
        if (fgets(invBuff, MAX_NAME_LEN-1,invFile) != NULL){
            sscanf(invBuff, "%s %i %i", invBuff_Name, &invBuffAtk, &invBuffDef);
            printf("%c - %s \n", 'a'+i, invBuff_Name);
        }
        else
            exit;
    }
    fclose(invFile);

    invCommands(playr);
}

void addToInv (char *item, int itemNum){
    FILE* invFile;
    invFile = fopen("../playerFiles/playerInv.txt","a");
    fprintf(invFile,"%s %i", item, itemNum);

    fclose(invFile);
}

const char* weaponNameGen(char *itemName, int itemClass, int max_atk){
    const char* prefix[] = {"Sword", "Halberd", "Blade", "Dagger", "Brick", "Shovel", "Sharp-Stick", "Staff" };
    const char* suffix[] = {"Sharpness", "Gouging", "No-Return", "Badassery", "De-Boning", "Fortitude", "Your-Mother"};


    if (itemClass == 1){
        sprintf(itemName,"%s-of-%s %i %i", prefix[rb(0,3)], suffix[rb(0,7)], rb(1,max_atk), 0);
        return itemName;
    } else if (itemClass == 2) {
        sprintf(itemName,"%s-of-%s %i %i", prefix[rb(4,6)], suffix[rb(0,7)], rb(1,max_atk), 0);
        return itemName;
    } else if (itemClass == 3) {
        sprintf(itemName,"%s-of-%s %i %i", prefix[7], suffix[rb(0,7)], rb(1,max_atk), 0);
        return itemName;
    }
}

const char* armorNameGen(char *itemName, int itemClass, int max_def){
    const char* prefix[] = {"Robe", "Mail", "Cap", "SnapBack", "Helm", "Chest-Plate", "Cuirass", "Jeans", "Chaps", "Legs", "Socks", "Boots"};
    const char* suffix[] = {"Swiftness", "Protection", "Horrid-Fashion", "Darkness", "Awesomeness", "Fortitude", "Your-older-sibling"};

    if (itemClass == 1){
        sprintf(itemName,"%s-of-%s %i %i", prefix[rb(0,1)], suffix[rb(0,6)], 0, rb(1,max_def));
        return itemName;
    } else if (itemClass == 2) {
        sprintf(itemName,"%s-of-%s %i %i", prefix[rb(2,4)], suffix[rb(0,6)], 0, rb(1,max_def));
        return itemName;
    } else if (itemClass == 3) {
        sprintf(itemName,"%s-of-%s %i %i", prefix[rb(5,6)], suffix[rb(0,6)], 0, rb(1,max_def));
        return itemName;
    } else if (itemClass == 4) {
        sprintf(itemName,"%s-of-%s %i %i", prefix[rb(7,9)], suffix[rb(0,6)], 0, rb(1,max_def));
        return itemName;
    } else if (itemClass == 5) {
        sprintf(itemName,"%s-of-%s %i %i", prefix[rb(10,11)], suffix[rb(0,6)], 0, rb(1,max_def));
        return itemName;
    }
}


void makeStartInv(){
    FILE* invFile;
    invFile = fopen("../playerFiles/playerInv.txt","w");
    char itemName[MAX_NAME_LEN];
    fprintf(invFile,"%s %i %i\n", weaponNameGen(itemName, rb(1,3), 2),0,WEAPON_FLAG);
    fprintf(invFile,"%s %i %i\n", armorNameGen(itemName, rb(1,5), 2),0,ARMOR_FLAG);

    fclose(invFile);
}

void addRandToInv(int type){
    FILE* invFile;
    invFile = fopen("../playerFiles/playerInv.txt","a");
    char itemName[MAX_NAME_LEN];
    if (type == 1)
    fprintf(invFile,"%s %i %i\n", weaponNameGen(itemName, rb(1,3), 5),0,WEAPON_FLAG);
    else
    fprintf(invFile,"%s %i %i\n", armorNameGen(itemName, rb(1,5), 5),0,ARMOR_FLAG);

    fclose(invFile);
}




