#include "header.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void infoRoom() {
  char roomChoice[3];
  int roomCapacity = 0;
  char ch;

  printf("\nChoose what room do you want:\n");
  printf("a. Small Room (%d persons)\n", SMALL_ROOM_CAPACITY);
  printf("b. Medium Room (%d persons)\n", MEDIUM_ROOM_CAPACITY);
  printf("c. Large Room (%d persons)\n", LARGE_ROOM_CAPACITY);

  while (roomCapacity == 0) {
    printf("------------------\n");
    printf("Your choice: ");

    if (fgets(roomChoice, sizeof(roomChoice), stdin) == NULL) {
      fprintf(stderr, "Error reading the input. Please try again.\n");
      continue;
    }

    roomChoice[strcspn(roomChoice, "\n")] = '\0';

    if (strlen(roomChoice) != 1) {
      printf("Invalid Input! Please enter a single charater.\n");

      while ((ch = getchar()) != '\n' && ch != EOF)
        ;
      continue;
    }

    roomChoice[0] = toupper((unsigned char)roomChoice[0]);
    printf("------------------\n");

    switch (roomChoice[0]) {
    case 'A':
      printf("You choose the small room.\n");
      roomCapacity = SMALL_ROOM_CAPACITY;
      break;
    case 'B':
      printf("You choose the medium room.\n");
      roomCapacity = MEDIUM_ROOM_CAPACITY;
      break;
    case 'C':
      printf("You choose the largest room.\n");
      roomCapacity = LARGE_ROOM_CAPACITY;
      break;
    default:
      printf("You Room Choice was invalid! Please enter a valid choice.\n");
      break;
    }
  }

  printf("Room Capacity will be %d persons\n", roomCapacity);

  addRoom(roomCapacity);
}

int addRoom(int roomCapacity) {
  Room room;
  room.capacity = roomCapacity;
  FILE *roomRec;

  printf("Enter the Room Name: ");
  if (fgets(room.roomName, sizeof(room.roomName), stdin) == NULL) {
    fprintf(stderr, "Error reading filename.\n");
    return 1;
  }

  room.roomName[strcspn(room.roomName, "\n")] = '\0';

  roomRec = fopen(ROOMS_FILE, "ab");
  if (roomRec == NULL) {
    fprintf(stderr, "\nError to open rooms.data for writing.\n");
    return 1;
  }

  if (fwrite(&room, sizeof(Room), 1, roomRec) != 1) {
    fprintf(stderr, "Error writing room data to file.\n");
    fclose(roomRec);
    return 1;
  }

  printf("The room was successfully created\n");

  fclose(roomRec);

  return 0;
}

void deleteRoom() {
  Room room;
  FILE *roomRec;
  FILE *tempFile;
  int found = 0;
  char roomName[MAX_ROOM_NAME];

  printf("Enter the name of the room you want to delete: ");
  if (fgets(roomName, sizeof(roomName), stdin) == NULL) {
    fprintf(stderr, "Error reading room name.\n");
    return;
  }

  roomName[strcspn(roomName, "\n")] = '\0';

  roomRec = fopen(ROOMS_FILE, "rb");
  if (roomRec == NULL) {
    fprintf(stderr, "Error opening rooms.dat.\n");
    return;
  }

  tempFile = fopen(TEMP_FILE, "wb");
  if (tempFile == NULL) {
    fprintf(stderr, "Error to opening the temp.dat.\n");
    fclose(tempFile);
    return;
  }

  while (fread(&room, sizeof(Room), 1, roomRec)) {
    if (strcmp(room.roomName, roomName) == 0) {
      found = 1;
      printf("The %s room was succesfully deleted\n", room.roomName);
    } else {
      fwrite(&room, sizeof(Room), 1, tempFile);
    }
  }

  fclose(roomRec);
  fclose(tempFile);

  if (!found) {
    remove(TEMP_FILE);
    printf("The room %s was not found.\n", roomName);
    return;
  }

  if (remove(ROOMS_FILE) != 0) {
    fprintf(stderr, "Error deleting the original room data file.\n");
  } else if (rename(TEMP_FILE, ROOMS_FILE) != 0) {
    fprintf(stderr, "Error renaming the temporary file.\n");
  }
}

void updateRoom() {
  Room room;
  FILE *roomRec;
  FILE *tempFile;
  char oldRoomName[MAX_ROOM_NAME];
  char newRoomName[MAX_ROOM_NAME];
  int found = 0;

  printf("Enter the Room Name you want update: ");
  if (fgets(oldRoomName, sizeof(oldRoomName), stdin) == NULL) {
    fprintf(stderr, "Error reading the file name.\n");
    return;
  }

  oldRoomName[strcspn(oldRoomName, "\n")] = '\0';

  roomRec = fopen(ROOMS_FILE, "rb");
  if (roomRec == NULL) {
    fprintf(stderr, "Error opening the rooms.dat\n");
    return;
  }

  tempFile = fopen(TEMP_FILE, "wb");
  if (tempFile == NULL) {
    fprintf(stderr, "Error opening the temp.dat\n");
    fclose(roomRec);
    return;
  }

  while (fread(&room, sizeof(Room), 1, roomRec)) {
    if (strcmp(room.roomName, oldRoomName) == 0) {
      found = 1;
      printf("Updating th room: %s\n", room.roomName);

      printf("Enter the new room name: ");
      if (fgets(newRoomName, sizeof(newRoomName), stdin) == NULL) {
        fprintf(stderr, "Error reading the new name\n");
        fclose(roomRec);
        fclose(tempFile);
        return;
      }

      newRoomName[strcspn(newRoomName, "\n")] = '\0';
      strncpy(room.roomName, newRoomName, MAX_ROOM_NAME - 1);
      room.roomName[MAX_ROOM_NAME - 1] = '\0';
    }

    fwrite(&room, sizeof(Room), 1, tempFile);
  }

  fclose(roomRec);
  fclose(tempFile);

  if (found) {
    if (remove(ROOMS_FILE) != 0) {
      fprintf(stderr, "Error deleting the original room data file.\n");
    } else if (rename(TEMP_FILE, ROOMS_FILE) != 0) {
      fprintf(stderr, "Error renaming the temporary file.\n");
    } else {
      printf("The room name was successfully updated.\n");
    }
  }

  else {
    remove(TEMP_FILE);
    printf("Room not found.\n");
  }
}

void viewRooms() {
  Room room;
  FILE *roomRec;

  roomRec = fopen(ROOMS_FILE, "rb");
  if (roomRec == NULL) {
    fprintf(stderr, "Error opening the rooms data file.\n");
    return;
  }

  printf("Rooms:\n");
  printf("---------------------------------------------------------\n");
  printf("| %-20s | %-10s |\n", "Room Name", "Capacity");
  printf("---------------------------------------------------------\n");

  while (fread(&room, sizeof(Room), 1, roomRec)) {
    printf("| %-20s | %-10d |\n", room.roomName, room.capacity);
  }

  printf("---------------------------------------------------------\n");

  fclose(roomRec);
}

void modMember() {
  Room room;
  FILE *roomRec;
  int found = 0;
  char roomName[MAX_ROOM_NAME];
  int choice;

  printf("Enter the Room Name: ");

  if (fgets(roomName, sizeof(roomName), stdin) == NULL) {
    fprintf(stderr, "Error reading the room name.\n");
    return;
  }

  roomName[strcspn(roomName, "\n")] = '\0';

  roomRec = fopen(ROOMS_FILE, "rb");
  if (roomRec == NULL) {
    fprintf(stderr, "Error opening the rooms.dat.\n");
    return;
  }

  while (fread(&room, sizeof(Room), 1, roomRec)) {
    if (strcmp(room.roomName, roomName) == 0) {
      found = 1;

      while (1) {
        printf("------------------------------\n");
        printf("Welcom to %s Room\n", roomName);
        printf("1. Add a Member.\n");
        printf("2. Delete a Member.\n");
        printf("3. Update a Member\n");
        printf("4. View Members of the room\n");
        printf("5. Return to the main menu\n");
        printf("------------------------------\n");

        printf("Enter you choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
          addMember(roomName);
          break;
        case 2:
          removeMember();
          break;
        case 3:
          updateMember(roomName);
          break;
        case 4:
          viewMembers(roomName);
          break;
        case 5:
          fclose(roomRec);
          printf("Return to the main menu....\n");
          return;
        default:
          printf("Your choice was invalid, please try again.\n");
          break;
        }
      }
    }
  }

  if (!found) {
    printf("The room name that you entered was not found.\n");
  }

  fclose(roomRec);
}
