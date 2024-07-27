#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"


int main(){
    printf("***********************\n");
    printf("ROOM MANAGEMENT SYSTEM\n");
    printf("   Simple C Program\n");
    printf("***********************\n");

    while (1){
        int choice;

        printf("------------------\n");
        printf("1. Add a Room.\n");
        printf("2. Remove a Room.\n");
        printf("3. Update a Room\n");
        printf("4. View the Rooms\n");
        printf("5. Modify Room Members\n");
        printf("6. About this System\n");
        printf("7. Exit\n");

        printf("------------------\n");
        printf("Enter a choice: ");
        scanf("%d", &choice);
        getchar();
        printf("------------------\n");

        switch(choice){
            case 1:
                infoRoom();
                break;
            case 2:
                deleteRoom();
                break;
            case 3:
                updateRoom();
                break;
            case 4:
                viewRooms();
                break;
            case 5:
                modMember();
                break;
            case 6:
                aboutSystem();
                break;
            default:
                printf("Exiting the system...\n");
                exit(0);
        }
    }

    return 0;
}

void aboutSystem(){
    printf("---------------------------------------------------------\n");
    printf("ROOM MANAGEMENT SYSTEM\n");
    printf("Simple C program for managing rooms and their members.\n");
    printf("Developed by Kharl with the help of CHAT GPT and ONLINE WORLD.\n");
    printf("Version: 1.0\n");
    printf("---------------------------------------------------------\n");
}
