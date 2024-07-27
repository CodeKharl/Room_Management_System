#ifndef ROOM_H
#define ROOM_H

#define MAX_ROOM_NAME 50
#define SMALL_ROOM_CAPACITY 15
#define MEDIUM_ROOM_CAPACITY 25
#define LARGE_ROOM_CAPACITY 40
#define MAX_MEMBER_NAME 100

#define MAX_MEMBER_ADDRESS 150
#define MAX_SEX_LENGTH 2

#define ROOMS_FILE "rooms.dat"
#define TEMP_FILE "temp.dat"
#define MEMBERS_FILE "members.dat"
#define TEMP_MEMBERS_FILE "tempMemberRec.dat"
#define ABOUT_FILE "about.txt"

typedef struct{
    char roomName[MAX_ROOM_NAME];
    int capacity;
} Room;

typedef struct{
    int id;
    char memberName[MAX_MEMBER_NAME];
    int age;
    char sex[MAX_SEX_LENGTH];
    char memberAddress[MAX_MEMBER_ADDRESS];
    int phoneNumber;
} Member;

void infoRoom();
int addRoom(int roomCapacity);
void deleteRoom();
void updateRoom();
void viewRooms();
void aboutSystem();
void modMember();

void addMember(const char *roomName);
void removeMember();
void updateMember(const char *roomName);
void viewMembers(const char *roomName);

#endif