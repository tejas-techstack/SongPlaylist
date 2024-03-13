#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>



struct SongNode{	
	char SongName[100];
	struct SongNode *NextSong;
};

struct SongNode * playlist;
int n;

struct SongNode createplaylist();
int menu();
int queue(struct SongNode *);
int addsong(struct SongNode *);
int removesong(struct SongNode *);
int playsongs(struct SongNode *);
int songplayer(char *);
//int nextsong(int, struct SongNode *);
//int prevsong(int, struct SongNode *);



int main() {
	//song playlist using linked lists
	int n = 0;

	printf("-------------------------------------\n");
	printf("Hello, Welcome to playlist creation\n");
	printf("-------------------------------------\n\n");
	
	printf("Press any key to continue....");
	getchar();

	createplaylist();

	//printf("%s", playlist[0].NextSong->SongName);

	menu(playlist);

	return 0;
}

struct SongNode createplaylist(){
	


	printf("Enter number of songs to add to the playlist:");
	scanf("%d",&n);
	if (n > 50) {
		printf("Please create smaller playlist\n");
		exit(0);
	}
	getchar();
	n++;
	
	playlist = (struct SongNode *) malloc(n*sizeof(struct SongNode));
	
	

	if (playlist == NULL){
		printf("Memory insufficient");
		exit(1);
	}


	for (int i = 0 ; i <= n-1; i++){
		if (i < n-1){
			playlist[i].NextSong = &playlist[i+1];
		}else {
			playlist[i].NextSong = &playlist[0];
		}
	}

	strcpy(playlist[0].SongName,"\0");

	for (int i = 1; i < n; i++){
		printf("Enter song %d:", i);
		scanf("%[^\n]%*c", playlist[i].SongName);
	}
	


	return * playlist;
}





int menu(struct SongNode * playlist) {

	char ch;

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
	int SongNumber = 1;


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

int addsong(struct SongNode * playlist){
	//printf("In addsong");

	playlist = (struct SongNode *) realloc(playlist, n*sizeof(struct SongNode)+sizeof(struct SongNode));
	n++;

	playlist[n-1].NextSong = &playlist[0];
	playlist[n-2].NextSong = &playlist[n-1];

	printf("Enter the song you want to add to the queue:");
	scanf("%[^\n]", playlist[n-2].NextSong->SongName);

	menu(playlist);
 	return 1;
}	

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

int playsongs(struct SongNode * playlist){

	for (int i = 0; i < n; i++){
		printf("helo");
		songplayer(playlist[i].NextSong->SongName);
	}

	return 0;
}


int songplayer(char * SongName){


	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	Mix_Music * music = Mix_LoadMUS(SongName);
	Mix_PlayMusic(music, 1);

	while (Mix_PlayingMusic()){
		SDL_Delay(100);
	}

	Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}



