#ifndef _MEDIA_PLAYER_H_
#define _MEDIA_PLAYER_H_

#pragma once
#include <windows.h> 
#include <mmsystem.h>  // mciSendString() 
#include <conio.h> 
#include <stdio.h>
#include <string.h>
#include <tchar.h>

#pragma comment (lib, "winmm.lib") //MCI 

class CMediaPlayer
{
	TCHAR returnData[128];  // MCI return data
	int error;
	TCHAR Pcommand[128];  // String that holds the MCI command

	int NowPlaying;
	bool Paused;
	bool Loop;
	bool Shuffle;

public:
	CMediaPlayer(void);
	void Close(void);
	bool Open(TCHAR* sFileName);
	bool Play(void);
	void Pause(void);
	void Stop(void);
	void Resume(void);
	TCHAR* Status(void);
	bool IsPlaying(void);
	bool IsOpen(void);
	bool IsPaused(void);
	bool IsStopped(void);
	int GetCurentMilisecond(void);
	void SetPosition(int miliseconds);
	int GetSongLenght(void);
	bool SetVolume(int volume);
	bool SetBalance(int balance);
};

#endif