#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "RemoteFriendsList.h"

/*Create a friends list text file for a certain username*/
void CreateFriendListFile(char *username){
    char* extension = "friendlist.txt";
    char fileSpec[strlen(username)+strlen(extension)+1];
    
    snprintf( fileSpec, sizeof(fileSpec), "%s%s", username, extension );
    
    FILE *userfriendlist = fopen(fileSpec , "a");
    fprintf(userfriendlist, "%s's Friend List: \n", username);
}

void CreateRequestListFile(char *username){
    
    char* extension = "requestlist.txt";
    char fileSpec[strlen(username)+strlen(extension)+1];
    
    snprintf( fileSpec, sizeof(fileSpec), "%s%s", username, extension );
    
    FILE *userrequestlist = fopen(fileSpec, "a");
    fprintf(userrequestlist, "%s's Request List: \n", username);
}

/*Will print the friend list or request list to the client's window*/
void ViewList(char *username, char *list){
    /*if (fptr == NULL)
     {
     printf("Cannot open file \n");
     exit(0);
     } */
    
    /*Read contents from file*/
    FILE *l = fopen(list, "r");
    char c = fgetc(l);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(l);
    }
    
}
char *GetFriendListName(char *username){
    char *filename = malloc(sizeof(char) *10000);
    char *extension = "friendlist.txt";
    strcpy(filename, username);
    strcat(filename, extension);
    return filename;
}
char *GetRequestListName(char *username){
    
    char *filename = NULL;
    char *extension = "requestlist.txt";
    strcpy(filename, username);
    strcat(filename, extension);
    return filename;
}

int AddToRequestList(char *requestusername, char *acceptusername, char *requestlist){
    FILE *request = fopen(requestlist, "a");
    char *requestinguser = requestusername;
    
    fprintf(request, "%s\n", requestinguser);
    
    return 0;
}

int RemoveFromRequestList(char *removeusername, char *username, char *requestlist){
    FILE *request = fopen(requestlist, "r");
    char *friends[100];
    char *string = NULL;
    int counter = 0;
    while(fgets(string, sizeof(string), request) != NULL) // copy stuff to array
    {
        strtok(string, "\n");
        friends[counter] = string;
        counter++;
    }
    char *filename = GetRequestListName(username);
    remove(filename);
    for(int i = 0; i < sizeof(friends); i++)
    {
        if(strcmp(friends[i], removeusername) == 0)
        {
            friends[i] = "#DELFRIEND#";
            break;
        }
        if(i == sizeof(friends)-1 && strcmp(friends[i], removeusername) != 0)
        {
            return 1;
        }
    }
    FILE *newfile = fopen(filename, "a");
    for(int i = 0; i < sizeof(friends); i++)
    {
        if(strcmp(friends[i], "#DELFRIEND#") != 0)
        {
            fprintf(newfile, "%s\n", friends[i]);
        }
    }
    return 0;
}
/*Add a friend to a user's friendlist text file*/
int AddFriend(char *friendusername, char *yourusername, FILE *friendsfile, FILE *yourfile)
{
    /*append the requestusername (the user who is requesting to be their friend if they choose to accept*/ //friend
    if(strcmp(friendusername, yourusername) == 0)
    {
        return 1;
    }
    char string[10000];
    while(fgets(string, sizeof(string), yourfile) != NULL)
    {
        strtok(string, "\n");
        if(strcmp(string, friendusername) == 0)
        {
            return 1;
        }
    }
    fprintf(friendsfile, "%s\n", yourusername);
    fprintf(yourfile, "%s\n", friendusername);
    fclose(yourfile);
    fclose(friendsfile);
    return 0;
}

/*Remove a friend from a user's friendlist text file*/
int RemoveFriend(char *removeusername, char *username, FILE *friendlist){
    char *friends[100];
    char string[10000];
    int numfriends = 0;
    for(numfriends = 0; fgets(string, sizeof(string), friendlist) != NULL; numfriends++)
    {
        strtok(string, "\n");
        friends[numfriends] = (char*)malloc(sizeof(string));
        strcpy(friends[numfriends], string);
    }
    for(int i = 0; i < numfriends; i++)
    {
        if(strcmp(friends[i], removeusername) == 0)
        {
            friends[i] = "#DELFRIEND#";
            break;
        }
        if(i == numfriends-1 && strcmp(friends[i], removeusername) != 0)
        {
            printf("Error removing friend. Please try again. \n");
            return 1;
        }
    }
    char *filename = GetFriendListName(username);
    remove(filename);
    FILE *newfile = fopen(filename, "a");
    for(int i = 0; i < numfriends; i++)
    {
        if(strcmp(friends[i], "#DELFRIEND#") != 0)
        {
            fprintf(newfile, "%s\n", friends[i]);
        }
    }
    fclose(newfile);
    return 0;
}
