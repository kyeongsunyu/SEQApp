#include "..\pch.h"
#include "CLASS_MediaPlayer.h"

//////////////////////////////////////////////////////////////////////////
CMediaPlayer::CMediaPlayer()
{
	NowPlaying = 0;
	Loop = false;
	Shuffle = true;
	Paused = false;
}
//////////////////////////////////////////////////////////////////////////
void CMediaPlayer::Close(void)
{
	wcscpy_s(Pcommand, L"close mp3");
	mciSendString(Pcommand, NULL, 0, NULL);
}
//////////////////////////////////////////////////////////////////////////
bool CMediaPlayer::Open(TCHAR* sFileName)
{
	TCHAR Buffer[128];

	Close();
	// Try to open as mpegvideo 
	swprintf(Pcommand, 127, L"open \"%s\" type mpegvideo alias mp3", sFileName);
	
	error = mciSendString(Pcommand, NULL, 0, NULL);
	mciGetErrorString(error, Buffer, 128);
	wprintf(L"MCI Msg : %s", Buffer);
	if (error != 0) {
		// Let MCI deside which file type the song is
		swprintf(Pcommand, 128, L"open \"%s\" alias mp3", sFileName);
		
		error = mciSendString(Pcommand, NULL, 0, NULL);
		if (error == 0)
			return true;
		else
			return false;
	}
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////
bool CMediaPlayer::Play(void)
{
	wcscpy_s(Pcommand, L"play mp3 repeat");
	error = mciSendString(Pcommand, NULL, 0, NULL);
	if (error == 0) {
		return true;
	}
	else {
		Close();
		return false;
	}
}
//////////////////////////////////////////////////////////////////////////
void CMediaPlayer::Pause(void)
{
	if (Paused) {
		Resume();
		Paused = false;
	}
	else if (IsPlaying()) {
		wcscpy_s(Pcommand, L"pause mp3");
		error = mciSendString(Pcommand, NULL, 0, NULL);
		Paused = true;
	}
}
//////////////////////////////////////////////////////////////////////////
void CMediaPlayer::Stop(void)
{
	wcscpy_s(Pcommand, L"stop mp3");
	error = mciSendString(Pcommand, NULL, 0, NULL);
	Paused = false;
	Close();
}
//////////////////////////////////////////////////////////////////////////
void CMediaPlayer::Resume(void)
{
	wcscpy_s(Pcommand, L"resume mp3");
	error = mciSendString(Pcommand, NULL, 0, NULL);
}
//////////////////////////////////////////////////////////////////////////
TCHAR* CMediaPlayer::Status(void)
{
	wcscpy_s(Pcommand, L"status mp3 mode");
	error = mciSendString(Pcommand, returnData, 128, NULL);

	return returnData;
}
//////////////////////////////////////////////////////////////////////////
bool CMediaPlayer::IsPlaying(void)
{
	wcscpy_s(Pcommand, L"status mp3 mode");
	error = mciSendString(Pcommand, returnData, 128, NULL);
	if (wcscmp(returnData, L"playing") == 0)
		return true;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////
bool CMediaPlayer::IsOpen(void)
{
	wcscpy_s(Pcommand, L"status mp3 mode");
	error = mciSendString(Pcommand, returnData, 128, NULL);
	if (wcscmp(returnData, L"open") == 0)
		return true;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////
bool CMediaPlayer::IsPaused(void)
{
	wcscpy_s(Pcommand, L"status mp3 mode");
	error = mciSendString(Pcommand, returnData, 128, NULL);
	if (wcscmp(returnData, L"paused") == 0)
		return true;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////
bool CMediaPlayer::IsStopped(void)
{
	wcscpy_s(Pcommand, L"status mp3 mode");
	error = mciSendString(Pcommand, returnData, 128, NULL);
	if (wcscmp(returnData, L"stopped") == 0)
		return true;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////
int CMediaPlayer::GetCurentMilisecond(void)
{
	wcscpy_s(Pcommand, L"status mp3 position");
	error = mciSendString(Pcommand, returnData, 128, NULL);
	return _wtoi(returnData);
}
//////////////////////////////////////////////////////////////////////////
void CMediaPlayer::SetPosition(int miliseconds)
{
	if (IsPlaying()) {
		swprintf(Pcommand, 128, L"play mp3 from %d", miliseconds);
		error = mciSendString(Pcommand, NULL, 0, NULL);
	}
	else {
		swprintf(Pcommand, 128, L"seek mp3 to %d", miliseconds);
		error = mciSendString(Pcommand, NULL, 0, NULL);
	}
}
//////////////////////////////////////////////////////////////////////////
int CMediaPlayer::GetSongLenght(void)
{
	if (IsPlaying()) {
		wcscpy_s(Pcommand, L"status mp3 length");
		error = mciSendString(Pcommand, returnData, 128, NULL);
		return _wtoi(returnData);
	}
	else
		return 0;
}
//////////////////////////////////////////////////////////////////////////
bool CMediaPlayer::SetVolume(int volume)
{
	if (volume >= 0 && volume <= 1000) {
		swprintf(Pcommand, 128, L"setaudio mp3 volume to %d", volume);
		error = mciSendString(Pcommand, NULL, 0, NULL);
		return true;
	}
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////
bool CMediaPlayer::SetBalance(int balance)
{
	if (balance >= 0 && balance <= 1000) {
		swprintf(Pcommand, 128, L"setaudio mp3 left volume to %d", (1000 - balance));
		error = mciSendString(Pcommand, NULL, 0, NULL);
		swprintf(Pcommand, 128, L"setaudio mp3 right volume to %d", balance);
		error = mciSendString(Pcommand, NULL, 0, NULL);
		return true;
	}
	else
		return false;
}