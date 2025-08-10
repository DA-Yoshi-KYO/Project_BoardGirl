#pragma once

#include <xaudio2.h>

class CAudio : public CComponent
{
public:
	static void InitMaster();
	static void UninitMaster();

	using CComponent::CComponent;

	void Uninit();

	void Load(const char *FileName);
	void Play(bool Loop = false);
	void Stop();
    void SetVolume(float inVolume);
    bool IsPlay();

private:
	static IXAudio2*				_XAudio;
	static IXAudio2MasteringVoice*	_masteringVoice;

	IXAudio2SourceVoice*	_sourceVoice{};
	BYTE*					_soundData{};

	int	_length{};
	int	_playLength{};

};
