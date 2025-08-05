#include "Music.h"

Music audio[10];
int currentMusicIndex = -1;

void LoadAllMusic()
{
    audio[0] = LoadMusicStream("scary-horror-music.mp3");
    audio[1] = LoadMusicStream("high-tension-and-suspense-background.mp3");
    audio[2] = LoadMusicStream("whisper-fluisteren.mp3");
    audio[3] = LoadMusicStream("monsters-cave.mp3");
    audio[4] = LoadMusicStream("music-box-scary.mp3");
    audio[5] = LoadMusicStream("scary-game-effect.mp3");
    audio[6] = LoadMusicStream("scary-piano-music.mp3");
    audio[7] = LoadMusicStream("code-of-silence.mp3");
    audio[8] = LoadMusicStream("this-is-suspense-end-of-the-line.mp3");
    audio[9] = LoadMusicStream("horror-suspense.mp3");
}

void UnloadAllMusic()
{
    for (int i = 0; i < 10; i++)
    {
        UnloadMusicStream(audio[i]);
    }
}

void PlayMapMusic(int newMusicIndex)
{
    if (currentMusicIndex != newMusicIndex)
    {
        for (int i = 0; i < 10; i++)
        {
            if (IsMusicStreamPlaying(audio[i]))
            {
                StopMusicStream(audio[i]);
            }
        }
        PlayMusicStream(audio[newMusicIndex]);
        currentMusicIndex = newMusicIndex;
    }
    UpdateMusicStream(audio[newMusicIndex]);
}
