#ifndef MUSIC_H
#define MUSIC_H

#include "raylib.h"

extern Music audio[14];
extern int currentMusicIndex;

void LoadAllMusic();
void UnloadAllMusic();
void PlayMapMusic(int newMusicIndex);

#endif
