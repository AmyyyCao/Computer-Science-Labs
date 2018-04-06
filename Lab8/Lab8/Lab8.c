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



// Declarations of linked list functions

void inputStringFromUser( char prompt[], char s[], int arraySize ) ;
void songNameDuplicate( char songName[] ) ;
bool compareSongName( Song *p, char *name );
void songNameFound( char songName[] ) ;
void songNameNotFound( char songName[] ) ;
void songNameDeleted( char songName[] ) ;
void artistFound( char artist[] ) ;
void artistNotFound( char artist[] ) ;
void printMusicLibraryEmpty( void ) ;
void printMusicLibraryTitle( void ) ;
void printMusicLibrary( Song *p );
void songFound( Song *p, char *promptName );
Song *insertSong( Song *p, char *name, char *artist, char *genre );
void deleteSong( Song *p, char *name );
void deleteLibrary ( Song *p );

const int MAX_LENGTH = 1024;



int main( void ) {
    //THIS IS THE HEAD OF THE LINKED LIST...
    Song *p = NULL;
    
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
            
            char name[100];
            char artist[100];
            char genre[100];
            
            inputStringFromUser(promptName, input, MAX_LENGTH) ;
            strcpy(name, input);
            inputStringFromUser(promptArtist, input, MAX_LENGTH) ;
            strcpy(artist, input);
            inputStringFromUser(promptGenre, input, MAX_LENGTH) ;
            strcpy(genre, input);
            
            
            if (compareSongName(p, name)) {
                songNameDuplicate(input);
            }

            else {
                p = insertSong(p, name, artist, genre);
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
            
            char *prompt = "\nEnter the name of the song to search for" ;
            inputStringFromUser(prompt, input, MAX_LENGTH);

            if (compareSongName(p, input)) {
                ;
            }
            
            else {
                songNameNotFound(input);
            }
        }
        
        
        else if( response == 'P' ) {
            // Print the music library.
            
            if ( p == NULL ) {
                printMusicLibraryEmpty();
            } else {
                printMusicLibraryTitle();
                printMusicLibrary(p);
            }

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


//OK
void deleteSong(Song *p, char *name) {
    Song *temp = p, *prev = p;
    
    while ( (temp != NULL) && (*temp->songName != *name) ) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) return;
    
    prev->next = temp->next;
    
    free(temp);
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
    //strcpy
    printf("\n%s\n%s\n%s\n",
           p->songName,
           p->artist,
           p->genre);

    if (p->next == NULL)
        return;
    else
        printMusicLibrary( p->next );
}









// Add your functions below this line.

//YEAH?
bool compareSongName( Song *p, char *name ) {
    // will return true if the song name is the same
    // otherwise, will search the next node
    
    if (p == NULL) {
        return false;
    }
    
    else if (strcmp(p->songName, name) == 0) {
        return true;
    }
    
    else if (p->next != NULL) {
        if(compareSongName( p->next, name )) {
            songNameFound(name);
            //PRINT INFORMATION IN NODE
            printf("\n%s\n%s\n%s\n",
                   p->next->songName,
                   p->next->artist,
                   p->next->genre);
            
            return true;
        }
        return false;
    }
    
    else
        return false;
}




//ALMOST OK
//When you're at the node right before the one you want to add it to...
Song *insertSong ( Song *p, char *name, char *artist, char *genre ) {
    
    Song *temp = p, *prev = p;
    
    Song *newSong = (Song *)malloc(sizeof(Song));
    
    newSong->songName = (char *)malloc(sizeof(char)*strlen(name));
    newSong->artist = (char *)malloc(sizeof(char)*strlen(artist));
    newSong->genre = (char *)malloc(sizeof(char)*strlen(genre));
    
    
    //TO SORT: FIGURE OUT THE < SIGN IN THE FOLLOWING:
    while ( (temp != NULL) && (strcmp(temp->songName, name) == -1) ) {
        prev = temp;
        temp = temp->next;
    }
    
    strcpy(newSong->songName, name);
    strcpy(newSong->artist, artist);
    strcpy(newSong->genre, genre);
    
    if (temp == NULL) {
        
        p = newSong; //EXC_BAD_ACCESS when trying to insert song
        newSong->next = NULL;
        
    } else {
        
        newSong->next = prev->next;
        prev->next = newSong;
        
    }
    return p;
}



//Yeah
void deleteLibrary ( Song *p ) {
    if (p==NULL) {
        printf("\nThe music library is empty");
    }
    
    else {
        Song *freeItem = p->next;
        printf("\nDeleting a song with name '%s' from the music library.\n", p->songName);
        p = p->next;
        free(freeItem);
        deleteLibrary(p);
    }
}

