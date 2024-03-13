/*
	
	project name: SongPlaylist
	Author: Tejas R
	dated : 13/03/2024
	current version: 2

*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>


//create a linked list
struct SongNode{	
	char SongName[100];
	struct SongNode *NextSong;
};

struct SongNode * playlist;
int n;

int createplaylist();
int menu();
int queue(struct SongNode *);
int addsong(struct SongNode *);
int removesong(struct SongNode *);
int playsongs(struct SongNode *);
int songplayer(char *);
//int nextsong(int, struct SongNode *);
//int prevsong(int, struct SongNode *);



int main() {
	// song playlist using linked lists

	printf("-------------------------------------\n");
	printf("Hello, Welcome to playlist creation\n");
	printf("-------------------------------------\n\n");
	
	printf("Press any key to continue....");
	getchar();

	createplaylist(); // begin creation of playlist

	menu(playlist); // once playlist has been created go to menu.

	return 0;
}


//function to create the playlist.
int createplaylist(){
	
	printf("Enter number of songs to add to the playlist:");
	scanf("%d",&n);
	if (n > 50) {
		printf("Please create smaller playlist\n");
		exit(0);
	}
	getchar();
	n++;
	

	// n*(size of SongNode) represents n spaces with each space representing 1 Song
	// allocate memory and return that pointer address to playlist.
	playlist = (struct SongNode *) malloc(n*sizeof(struct SongNode));
	
	

	if (playlist == NULL){
		printf("Memory insufficient");
		exit(1);
	}

	//link the Nodes To each other and then link the last node to the first node
	//this creates a circular linked list
	for (int i = 0 ; i <= n-1; i++){
		if (i < n-1){
			playlist[i].NextSong = &playlist[i+1];
		}else {
			playlist[i].NextSong = &playlist[0];
		}
	}

	//initiate the head node with null value
	strcpy(playlist[0].SongName,"\0");

	//assign values to each node
	for (int i = 1; i < n; i++){
		printf("Enter song %d:", i);
		scanf("%[^\n]%*c", playlist[i].SongName);
	}
	


	return 0;
}


// function to access the menu and edit the queue
int menu(struct SongNode * playlist) {

	char ch;

	printf("------\n");
	printf(" MENU\n");
	printf("------\n");

	printf("\n   1. Show Queue(q)\n   2. Add Song(a)\n   3. Remove Song(r)\n   4. Play Song(p)\n   5. Exit(e)\n");

	printf("\n");
	printf("Enter Choice:");	
	scanf(" %c", &ch);
	getchar();

	switch(ch){

	case 'q' : queue(playlist);break;
	case 'a' : addsong(playlist); break;
	case 'r' : removesong(playlist); break;
	case 'p' : {	
			   printf("Playing Songs\n");
			   playsongs(playlist); 
			   break;
		   }
	case 'e' : printf("Exiting SongPlayer\n"); break;
	default: menu(playlist);
	}

	return 0;
}



int queue(struct SongNode * playlist){
	printf("\n---Current Queue---\n");


	int i = 0;
	int SongNumber = 1; //temporary variable to track number of songs


	while (i < n-1) {

		if (playlist[i].NextSong->SongName == NULL) {
			i++;
			continue;
		}
		printf("song %d: %s\n",SongNumber, playlist[i].NextSong->SongName);
		SongNumber++;
		i++;
	}
	
	menu(playlist);


	//END OF QUEUE
	return 1;
}


// function to add song
int addsong(struct SongNode * playlist){
	//printf("In addsong");

	//re-allocate memory with storage for one extra node
	playlist = (struct SongNode *) realloc(playlist, n*sizeof(struct SongNode)+sizeof(struct SongNode));
	n++;

	playlist[n-1].NextSong = &playlist[0];
	playlist[n-2].NextSong = &playlist[n-1];

	printf("Enter the song you want to add to the queue:");
	scanf("%[^\n]", playlist[n-2].NextSong->SongName);

	menu(playlist);
 	return 1;
}	

// function to remove song
int removesong(struct SongNode * playlist){
	int x = 0;

	printf("\nWhich song do you want to remove:");
	scanf(" %d", &x);
	if (x > n-1) return 0;
	if (x == 0) {
		playlist[0].NextSong = NULL;
		playlist[n-1].NextSong = &playlist[1];
	}else if (x < n-1) {
		playlist[x].NextSong = NULL;
		playlist[x-1].NextSong = &playlist[x+1];
	}else if (x == n-1) {
		playlist[x].NextSong = NULL;
		playlist[x-1].NextSong = NULL;
	}else return 0;
 	
	menu(playlist);
	
	return 1;
}

// play song using for loop
int playsongs(struct SongNode * playlist){

	for (int i = 0; i < n; i++){
		songplayer(playlist[i].NextSong->SongName);
	}

	return 0;
}

// function to play song using sdl
int songplayer(char * SongName){


	SDL_Init(SDL_INIT_AUDIO);                           // initiate sdl
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);  // initiate mixer

	Mix_Music * music = Mix_LoadMUS(SongName);          // create a music entity

	Mix_PlayMusic(music, 1);			    // play the music file

	while (Mix_PlayingMusic()){
		SDL_Delay(100);
	}

	Mix_FreeMusic(music);                               // free memory
	Mix_CloseAudio();                                   // close audio playback
	SDL_Quit();					    // quit sdl

	return 0;
}



