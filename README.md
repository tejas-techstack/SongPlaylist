# SongPlaylist

Author : Tejas Ramakrishnan
Dated  : 2/3/2024

## What is SongPlaylist?

This short project is a c99 based program to play songs stored locally.
The project is meant to demonstrate an application of linked lists(circular linked lists) in real time.

To play the songs [SDL]("https://www.libsdl.org/") (Simple DirectMedia Layer) is uesd. It is a library in C that allows low level access to WAV formatted files.

SDL-mixer is also being used to play songs of different formats like MP3, OGG, MIDI, etc. This is a sub-library of SDL2 and it also supports WAV format.


## Features:

On code run, the user can add songs to the playlist and then these songs are played in order.

Current:
1. Creating a playlist, from existing local songs.
2. Adding a new song to the end of the queue.(Not in use in the current version)
3. Removing any song based on the song number.(Not in use in the current version)
4. Play Songs using SDL2, SDL\_mixer.

Upcoming:
1. The ability to Pause/Play/Next/Previous.
2. Adding a song anywhere in the queue.
3. Removing song based on song name.


