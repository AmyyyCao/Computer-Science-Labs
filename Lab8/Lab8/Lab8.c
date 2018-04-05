// APS105 Lab 8 Lab8.c
//
// This is a program written to maintain a personal music library,
// using a linked list to hold the songs in the library.
//
// Author: Songeun You

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct song {
    char *songName;
    char *artist;
    char *genre;
    struct song *next;
} Song;

//THIS IS THE HEAD OF THE LINKED LIST...
Song *p;



// Declarations of linked list functions

void inputStringFromUser( char prompt[], char s[], int arraySize ) ;
void songNameDuplicate( char songName[] ) ;
bool compareSongName( Song *p, char *name[] );
void songNameFound( char songName[] ) ;
void songNameNotFound( char songName[] ) ;
void songNameDeleted( char songName[] ) ;
void artistFound( char artist[] ) ;
void artistNotFound( char artist[] ) ;
void printMusicLibraryEmpty( void ) ;
void printMusicLibraryTitle( void ) ;
void printMusicLibrary( Song *p );
void songFound( Song *p, char *promptName );
void insertSong( Song *p, char *name, char *artist, char *genre );
void deleteSong( Song *p, char *name );
void deleteLibrary ( Song *p );

const int MAX_LENGTH = 1024;

int main( void ) {
    
    // Announce the start of the program
    printf( "Personal Music Library.\n\n" ) ;
    printf( "%s", "Commands are I (insert), D (delete), S (search by song name),\n"
           "P (print), Q (quit).\n" ) ;
    
    char response ;
    char input[ MAX_LENGTH + 1 ] ;
    do {
        inputStringFromUser("\nCommand", input, MAX_LENGTH) ;
        
        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper( input[0] ) ;
        
        if( response == 'I' ) {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            
            char *promptName = "Song name" ;
            char *promptArtist =  "Artist" ;
            char *promptGenre = "Genre" ;
            
            char *name[100];
            char *artist[100];
            char *genre[100];
            
            inputStringFromUser(promptName, input, MAX_LENGTH) ;
            strcpy(*name, input);
            inputStringFromUser(promptArtist, input, MAX_LENGTH) ;
            strcpy(*artist, input);
            inputStringFromUser(promptGenre, input, MAX_LENGTH) ;
            strcpy(*genre, input);
        
            if (!compareSongName(p, name)) {
                insertSong(p, *name, *artist, *genre);
            }
            else {
                songNameDuplicate(input);
            }
        }
        
        
        else if( response == 'D' ) {
            // Delete a song from the list.
            
            char *prompt = "\nEnter the name of the song to be deleted" ;
            inputStringFromUser(prompt, input, MAX_LENGTH);
            deleteSong(p, input);
            songNameDeleted(input);
        }
        
        
        else if( response == 'S' ) {
            // Search for a song by its name.
            char *name[20];
            
            char *prompt = "\nEnter the name of the song to search for" ;
            inputStringFromUser(prompt, input, MAX_LENGTH);
            strcpy(*name, input);
            
            if (compareSongName(p, name)) {
                songNameFound(input);
                
                //PRINT INFORMATION IN NODE
                printf("%s", p->songName);
                printf("%s", p->artist);
                printf("%s", p->genre);
            }
            
            else {
                songNameNotFound(input);
            }
        }
        
        
        else if( response == 'P' ) {
            // Print the music library.
            
            if (p->next != NULL) {
                printMusicLibraryTitle();
                printMusicLibrary(p); //can you declare this elsewhere?
            }
            else
                printMusicLibraryEmpty();

        }
        
        
        else if( response == 'Q' ) {
            ; // do nothing, we'll catch this below
        }
        
        
        else {
            // do this if no command matched
            printf( "\nInvalid command.\n" ) ;
        }
    } while( response != 'Q' ) ;
    
    
    // Delete the entire linked list and print to confirm deletion.
    deleteLibrary (p);
    
    return 0 ;
}
























// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser( char prompt[], char s[], int maxStrLength ) {
    int i = 0;
    char c;
    
    printf( "%s --> ", prompt ) ;
    while( i < maxStrLength && (c = getchar()) != '\n' )
        s[i++] = c ;
    s[i] = '\0' ;
}

// Function to call when the user is trying to insert a song name
// that is already in the personal music library.
void songNameDuplicate( char songName[] ) {
    printf( "\nA song with the name '%s' is already in the music library.\n"
           "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound( char songName[] ) {
    printf( "\nThe song name '%s' was found in the music library.\n",
           songName ) ;
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound( char songName[] ) {
    printf( "\nThe song name '%s' was not found in the music library.\n",
           songName);
}


void deleteSong(Song *p, char *name) {
    
    
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted( char songName[] ) {
    printf( "\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf( "\nThe music library is empty.\n" ) ;
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
    printf( "\nMy Personal Music Library: \n" ) ;
}

//Print songs in music library
void printMusicLibrary(Song *p) {
    if (p->next == NULL) {
        return;
    }
    //strcpy
    printf("%s\n", p->songName);
    printf("%s\n", p->artist);
    printf("%s\n", p->genre);
    printMusicLibrary( p->next );
}









// Add your functions below this line.

//YEAH?
bool compareSongName( Song *p, char *name[] ) {
    
    if (strcmp(p->songName, *name)) {
        return true;
    }
    
    else if (p->next != NULL) {
        if(compareSongName( p->next, name )) {
            return true;
        }
        return false;
    }
    
    else {
        return false;
    }
}

//ALMOST OK
void insertSong ( Song *p, char *name, char *artist, char *genre ) {
    
    Song *newSong;
    
    newSong->songName = name;
    newSong->artist = artist;
    newSong->genre = genre;
    
    Song *newSong = (Song *)malloc(sizeof(newSong)); //HOW TO MALLOC?
    
    newSong->next = p->next;
    p->next = newSong;
    
}


void deleteLibrary ( Song *p ) {
    if (p==NULL) {
        printf("\nThe music library is empty");
    }
    
    else {
        printf("\nDeleting a song with name '%s' from the music library.\n", p->songName);
        Song *f = p->next;
        free(p);
        deleteLibrary(f);
    }
}

