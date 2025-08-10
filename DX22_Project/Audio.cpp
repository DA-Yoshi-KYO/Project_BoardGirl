
#include "Main.h"
#include "Audio.h"

IXAudio2* CAudio::_XAudio = NULL;
IXAudio2MasteringVoice* CAudio::_masteringVoice = NULL;

void CAudio::InitMaster()
{
	// COM初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio生成
	XAudio2Create(&_XAudio, 0);

	// マスタリングボイス生成
	_XAudio->CreateMasteringVoice(&_masteringVoice);
}

void CAudio::UninitMaster()
{
	_masteringVoice->DestroyVoice();
	_XAudio->Release();
	CoUninitialize();
}

void CAudio::Load(const char *FileName)
{

	// サウンドデータ読込
	WAVEFORMATEX wfx = { 0 };

	{
		HMMIO hmmio = NULL;
		MMIOINFO mmioinfo = { 0 };
		MMCKINFO riffchunkinfo = { 0 };
		MMCKINFO datachunkinfo = { 0 };
		MMCKINFO mmckinfo = { 0 };
		UINT32 buflen;
		LONG readlen;


		hmmio = mmioOpen((LPSTR)FileName, &mmioinfo, MMIO_READ);
		assert(hmmio);

		riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

		mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(hmmio, (HPSTR)&wfx, sizeof(wfx));
		}
		else
		{
			PCMWAVEFORMAT pcmwf = { 0 };
			mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
			memset(&wfx, 0x00, sizeof(wfx));
			memcpy(&wfx, &pcmwf, sizeof(pcmwf));
			wfx.cbSize = 0;
		}
		mmioAscend(hmmio, &mmckinfo, 0);

		datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);



		buflen = datachunkinfo.cksize;
		_soundData = new unsigned char[buflen];
		readlen = mmioRead(hmmio, (HPSTR)_soundData, buflen);


		_length = readlen;
		_playLength = readlen / wfx.nBlockAlign;


		mmioClose(hmmio, 0);
	}


	// サウンドソース生成
	_XAudio->CreateSourceVoice(&_sourceVoice, &wfx);
	assert(_sourceVoice);
}

void CAudio::Uninit()
{
	_sourceVoice->Stop();
	_sourceVoice->DestroyVoice();

	delete[] _soundData;
}

void CAudio::Play(bool Loop)
{
	_sourceVoice->Stop();
	_sourceVoice->FlushSourceBuffers();


	// バッファ設定
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = _length;
	bufinfo.pAudioData = _soundData;
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = _playLength;

	// ループ設定
	if (Loop)
	{
		bufinfo.LoopBegin = 0;
		bufinfo.LoopLength = _playLength;
		bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	_sourceVoice->SubmitSourceBuffer(&bufinfo, NULL);

/*
	float outputMatrix[4] = { 0.0f , 0.0f, 1.0f , 0.0f };
	m_SourceVoice->SetOutputMatrix(m_MasteringVoice, 2, 2, outputMatrix);
	//m_SourceVoice->SetVolume(0.1f);
*/


	// 再生
	_sourceVoice->Start();

}

void CAudio::Stop()
{
    _sourceVoice->Stop();
}

void CAudio::SetVolume(float inVolume)
{
    inVolume = std::clamp(inVolume, 0.0f, 1.0f);
    _sourceVoice->SetVolume(inVolume);
}

bool CAudio::IsPlay()
{
    XAUDIO2_VOICE_STATE state;
    _sourceVoice->GetState(&state);
	return state.BuffersQueued > 0;
}

