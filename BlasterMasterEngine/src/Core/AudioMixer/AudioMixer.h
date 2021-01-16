#pragma once

class AudioMixer
{
private:
	struct WaveHeaderType
	{
		char chunkId[4];
		DWORD chunkSize;
		char format[4];
		char subChunkId[4];
		DWORD subChunkSize;
		WORD audioFormat;
		WORD numChannels;
		DWORD sampleRate;
		DWORD bytesPerSecond;
		WORD blockAlign;
		WORD bitsPerSample;
		char dataChunkId[4];
		DWORD dataSize;
	};

	struct Audio
	{
		LPDIRECTSOUNDBUFFER8 buffer;
		std::string name;

		Audio()
		{
			buffer = NULL;
			name = "Audio";
		}
	};
public:
	AudioMixer();
	~AudioMixer();

	HRESULT CreateAudioMixerResources(HWND hwnd);

	static bool PlayWaveFile(std::string name, bool looping = false);
	static void SetVolume(std::string, LONG volume = DSBVOLUME_MAX);
	static void Stop(std::string name);
private:
	void ShutdownDirectSound();
	bool LoadWaveFile(const char*, LPDIRECTSOUNDBUFFER8*);
	void ShutdownAudios();
	HRESULT CreatePrimaryBuffer();
	HRESULT CreateSecondaryBuffer(LPDIRECTSOUNDBUFFER8* buffer, DWORD bufferSize = 0);

	HRESULT CreateAudios();

private:
	static LPDIRECTSOUND8 m_DirectSound;
	static LPDIRECTSOUNDBUFFER m_PrimaryBuffer;

	static std::vector<std::shared_ptr<Audio>> audios;
};