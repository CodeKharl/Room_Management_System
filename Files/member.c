#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

void addMember(const char *roomName){
    Member member;
    FILE *memberRec;
    int ch;

    printf("Enter the ID of the member: ");
    while(scanf("%d", &member.id) != 1){
        printf("Invalid Input, Please enter a Valid Id Number.\n");
        while((ch = getchar()) != '\n' && ch != EOF);
    }
    while((ch = getchar()) != '\n' && ch != EOF);

    printf("Enter the Name: ");
    if(fgets(member.memberName, sizeof(member.memberName), stdin) == NULL){
        fprintf(stderr, "Error reading the name.\n");
        return;
    }
    member.memberName[strcspn(member.memberName, "\n")] = '\0';

    printf("Enter the age: ");
    while(scanf("%d", &member.age) != 1){
        printf("Invalid input! Please enter a valid age.\n");
        while((ch = getchar()) != '\n' && ch != EOF);
    }
    getchar();

    while(1){
        printf("Enter the sex (M for Male and F for Female): ");
        scanf("%1s", member.sex);
        member.sex[0] = toupper(member.sex[0]);
        member.sex[1] = '\0';

        if(member.sex[0] == 'M' || member.sex[0] == 'F'){
            break;
        }
        else{
            fprintf(stderr, "Invalid input. Please enter the valid sex.\n");
        }
        while((ch = getchar()) != '\n' && ch != EOF);
    }

    printf("Enter the Address of the member: ");
    while((ch = getchar()) != '\n' && ch != EOF);

    if(fgets(member.memberAddress, sizeof(member.memberAddress), stdin) == NULL){
        fprintf(stderr,"Error reading the address.\n");
        return;
    }
    member.memberAddress[strcspn(member.memberAddress, "\n")] = '\0';

    printf("Enter the member phone number: ");
    while(scanf("%d", &member.phoneNumber) != 1){
        printf("Invalid Input! Please enter a valid Phone Number.\n");
        while((ch = getchar()) != '\n' && ch != EOF);
    }
    while((ch = getchar()) != '\n' && ch != EOF);

    memberRec = fopen(MEMBERS_FILE, "ab");
    if(memberRec == NULL){
        fprintf(stderr, "Error opening the room_members.dat.\n");
        return;
    }

    if(fwrite(roomName, sizeof(char), MAX_ROOM_NAME, memberRec) != MAX_ROOM_NAME){
        fprintf(stderr, "Error writing room name to file.\n");
        fclose(memberRec);
        return;
    }

    if(fwrite(&member, sizeof(Member), 1, memberRec) != 1){
        fprintf(stderr, "Error writing member data to the file.\n");
        fclose(memberRec);
        return;
    }

    printf("You successfully add the member to room %s.\n", roomName);

    fclose(memberRec);
}
void removeMember(){
    Member member;
    FILE *memberRec;
    FILE *tempMemberRec;
    int idNumber;
    int found = 0;
    char currentRoom[MAX_ROOM_NAME];
    char ch;

    printf("Enter the ID Number of the member you want to remove: ");
    while(scanf("%d", &idNumber) != 1){
        printf("Invalid Input! Please enter a valid ID Number.\n");
        while((ch = getchar()) != '\n' && ch != EOF);
    }

    memberRec = fopen(MEMBERS_FILE, "rb");
    if(memberRec == NULL){
        fprintf(stderr, "Error opening the members.dat.\n");
        return;
    }

    tempMemberRec = fopen(TEMP_MEMBERS_FILE, "wb");
    if(tempMemberRec == NULL){
        fprintf(stderr, "Error opening the temporary member data file.\n");
        fclose(memberRec);
        return;
    }

    while(fread(currentRoom, sizeof(char), MAX_ROOM_NAME, memberRec) == MAX_ROOM_NAME){
            if(fread(&member, sizeof(Member), 1, memberRec) != 1){
                fprintf(stderr, "Error reading member data.\n");
                break;
            }

            if(member.id == idNumber){
                found = 1;
                printf("Found member with ID: %d\n", member.id);
            }
            else{
                fwrite(currentRoom, sizeof(char), MAX_ROOM_NAME, tempMemberRec);
                fwrite(&member, sizeof(Member), 1, tempMemberRec);
            }
        
    }

    fclose(memberRec);
    fclose(tempMemberRec);

    if(!found){
        remove(TEMP_MEMBERS_FILE);
        printf("The member was not found.\n");
        return;
    }

    printf("The member was successfully deleted.\n");

        if(remove(MEMBERS_FILE) != 0){
            fprintf(stderr, "Error deleting the original member data file.\n");
        }

        else if(rename(TEMP_MEMBERS_FILE, MEMBERS_FILE) != 0){
            fprintf(stderr, "Error renaming the temporary file.\n");
        }
    
}
void updateMember(const char *roomName){
    Member member;
    FILE *memberRec;
    FILE *tempMemberRec;
    char currentRoom[MAX_ROOM_NAME];
    int idNumber;
    int found = 0;
    int choice;
    char ch;

    printf("Enter the ID Number of Member you want to update.\n");
    while(scanf("%d", &idNumber) != 1){
        printf("Invalid Input, Please try again.\n");
        while((ch = getchar()) != '\n' && ch != EOF);
    }

    while((ch = getchar()) != '\n' && ch != EOF);

    memberRec = fopen(MEMBERS_FILE, "rb");
    if(memberRec == NULL){
        fprintf(stderr, "Error opening the members.dat");
        return;
    }

    tempMemberRec = fopen(TEMP_MEMBERS_FILE, "wb");
    if(tempMemberRec == NULL){
        fprintf(stderr, "Error opening the temporary members data file.\n");
        fclose(memberRec);
        return;
    }

    while(fread(currentRoom, sizeof(char), MAX_ROOM_NAME, memberRec) == MAX_ROOM_NAME){
        if(strcmp(currentRoom, roomName) == 0){
            if(fread(&member, sizeof(Member), 1, memberRec) != 1){
                fprintf(stderr, "Error reading the member data.\n");
                break;
            }

            if(member.id == idNumber){
                found = 1;
                printf("Found member with ID: %d\n", member.id);

                printf("Details of Members that can edit.\n");
                printf("1. Name\n");
                printf("2. Age\n");
                printf("3. Sex\n");
                printf("4. Address\n");
                printf("5. Phone Number\n");
                printf("6. Return to the main menu.\n");
                printf("Enter the you want to edit: ");

                while(scanf("%d", &choice) != 1){
                    printf("Invalid input! Please enter a valid choice.\n");
                    while((ch = getchar()) != '\n' && ch != EOF);
                }

                while((ch = getchar()) != '\n' && ch != EOF);

                switch(choice){
                    case 1:
                        printf("Enter the New Name: ");
                        if(fgets(member.memberName, sizeof(member.memberName), stdin) == NULL){
                            fprintf(stderr, "Error reading the new name, please try again.\n");
                        }
                        else{member.memberName[strcspn(member.memberName, "\n")] = '\0';
                        }
                        break;
                    case 2:
                        printf("Enter the New Age: ");
                        while(scanf("%d", &member.age) != 1){
                            printf("Invalid input! Please enter a valid age.\n");
                            while((ch = getchar()) != '\n' && ch != EOF);
                        }
                        break;
                    case 3:
                        while(1){
                            printf("Enter the New Sex (M for Male and F for Female): ");
                            scanf("%1s", &member.sex);
                            member.sex[0] = toupper(member.sex[0]);

                            if(member.sex[0] == 'M' || member.sex[0] == 'F'){
                                break;
                            }
                            else{
                                printf("Invalid input. Please enter a new valid sex.\n");
                            }
                            while((ch = getchar()) != '\n' && ch != EOF);
                        }
                            
                        break;
                    case 4:
                        printf("Enter a New address: ");
                        if(fgets(member.memberAddress, sizeof(member.memberAddress), stdin) == NULL){
                            fprintf(stderr, "Error reading the new address of the member.\n");
                            }
                        else{
                            member.memberAddress[strcspn(member.memberAddress, "\n")] = '\0';
                            }
                            break;
                    case 5:
                        printf("Enter the New Mobile Phone of the member: ");
                        while(scanf("%d", member.phoneNumber) != 1){
                            printf("Invalid Input! Please enter the valid new phone number.\n");
                            while((ch = getchar()) != '\n' && ch != EOF);
                        }
                        break;
                    case 6:
                        fclose(memberRec);
                        fclose(tempMemberRec);
                        remove(TEMP_MEMBERS_FILE);
                        return;
                    default:
                        printf("Invlaid choice! Returning to the main menu.\n");
                        fclose(memberRec);
                        fclose(tempMemberRec);
                        remove(TEMP_MEMBERS_FILE);
                        return;
                }
            }
        }

        fwrite(&currentRoom, sizeof(currentRoom), 1, tempMemberRec);
        fwrite(&member, sizeof(Member), 1, tempMemberRec);
    }

    fclose(memberRec);
    fclose(tempMemberRec);

    if(found){
        if(remove(MEMBERS_FILE) != 0){
            fprintf(stderr, "Error deleting the original member data.\n");
        }
        else if(rename(TEMP_MEMBERS_FILE, MEMBERS_FILE) != 0){
            fprintf(stderr, "Error renaming the temporary file.\n");
        }
        else{
            printf("The details of the member was successfully updated.\n");
        }
    }
    else{
        remove(TEMP_MEMBERS_FILE);
        printf("The member was not found.\n");
    }
}
void viewMembers(const char *roomName){
    Member member;
    FILE *memberRec;
    char fileRoomName[MAX_ROOM_NAME];

    memberRec = fopen(MEMBERS_FILE, "rb");
    if(memberRec == NULL){
        fprintf(stderr, "Error opening the members.dat\n");
        return;
    }

    printf("List of Members in %s Room\n", roomName);
    while(fread(fileRoomName, sizeof(char), MAX_ROOM_NAME, memberRec) == MAX_ROOM_NAME){
        if(strcmp(fileRoomName, roomName) != 0){
            fseek(memberRec, sizeof(Member), SEEK_CUR);
            continue;
        }
            
        if(fread(&member, sizeof(Member), 1, memberRec) != 1){
            fprintf(stderr, "Error reading member data from the file.\n");
            break;;
        }

        printf("ID: %d, Name: %s, Age: %d, Sex: %s, Address: %s, Phone: %d\n", member.id, member.memberName, member.age, member.sex, member.memberAddress, member.phoneNumber);
    }

    fclose(memberRec);
}