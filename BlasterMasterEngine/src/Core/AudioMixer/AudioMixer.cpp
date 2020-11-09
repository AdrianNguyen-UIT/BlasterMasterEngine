#include "d3dpch.h"
#include "AudioMixer.h"

LPDIRECTSOUND8 AudioMixer::m_DirectSound = NULL;
LPDIRECTSOUNDBUFFER AudioMixer::m_PrimaryBuffer = NULL;
std::vector<std::shared_ptr<AudioMixer::Audio>> AudioMixer::audios;

AudioMixer::AudioMixer()
{
}

AudioMixer::~AudioMixer()
{
	ShutdownAudios();
	ShutdownDirectSound();
}

HRESULT AudioMixer::CreateAudioMixerResources(HWND hwnd)
{
	HRESULT hr = S_OK;

	// Initialize the direct sound interface pointer for the default sound device.
	hr = DirectSoundCreate8(NULL, &m_DirectSound, NULL);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to create Direct Sound resources!")
		return hr;
	}

	hr = m_DirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to set cooperative level!");
		return hr;
	}

	hr = CreatePrimaryBuffer();
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to create sound buffer!");
		return hr;
	}

	hr = CreateAudios();
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to create audios!");
		return hr;
	}
	return hr;
}

void AudioMixer::ShutdownDirectSound()
{
	if (m_PrimaryBuffer)
	{
		m_PrimaryBuffer->Release();
	}

	if (m_DirectSound)
	{
		m_DirectSound->Release();
	}
}

bool AudioMixer::LoadWaveFile(const char* filename, LPDIRECTSOUNDBUFFER8* secondaryBuffer)
{
	errno_t error;
	FILE* filePtr = NULL;
	size_t count = 0;
	WaveHeaderType waveFileHeader;
	HRESULT hr = S_OK;
	BYTE* waveData = NULL;
	LPVOID bufferPtr = NULL;
	DWORD bufferSize = 0;

	// Open the wave file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if (error)
	{
		__ASSERT(false, "Unable to open file!");
		return false;
	}

	if (!filePtr)
	{
		__ASSERT(false, "File is corrupted!");
		return false;
	}

	// Read in the wave file header.
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if (count != 1)
	{
		__ASSERT(false, "Unable to read in the wave file header!");
		return false;
	}

	// Check that the chunk ID is the RIFF format.
	if ((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') ||
		(waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
	{
		__ASSERT(false, "Chunk ID is not RIFF format!");
		return false;
	}

	// Check that the file format is the WAVE format.
	if ((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
		(waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
	{
		__ASSERT(false, "File format is not WAVE!");
		return false;
	}

	// Check that the sub chunk ID is the fmt format.
	if ((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
		(waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
	{
		__ASSERT(false, "Sub chunk ID is not fmt format!");
		return false;
	}

	// Check that the audio format is WAVE_FORMAT_PCM.
	if (waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		__ASSERT(false, "Audio format is not WAVE_FORMAT_PCM!");
		return false;
	}

	// Check that the wave file was recorded in stereo format.
	if (waveFileHeader.numChannels != 2)
	{
		__ASSERT(false, "Wave file was not recorded in stereo format!");
		return false;
	}

	// Check that the wave file was recorded at a sample rate of 44.1 KHz.
	if (waveFileHeader.sampleRate != 44100)
	{
		__ASSERT(false, "Wave file was not recorded at a sample rate of 44.1 KHz!");
		return false;
	}

	// Ensure that the wave file was recorded in 16 bit format.
	if (waveFileHeader.bitsPerSample != 16)
	{
		__ASSERT(false, "Wave file was not recorded at in 16 bit format!");
		return false;
	}

	// Check for the data chunk header.
	if ((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
		(waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
	{
		__ASSERT(false, "Data chunk header is not compatible!");
		return false;
	}

	//Create seconday buffer
	hr = CreateSecondaryBuffer(secondaryBuffer, waveFileHeader.dataSize);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to create secondary buffer!");
		return false;
	}

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	// Create a temporary buffer to hold the wave file data.
	waveData = new BYTE[waveFileHeader.dataSize];
	if (!waveData)
	{
		__ASSERT(false, "WaveData (temporary buffer to hold the wave file data) is NULL!");
		return false;
	}

	// Read in the wave file data into the newly created buffer.
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if (count != waveFileHeader.dataSize)
	{
		__ASSERT(false, "Unable to read in the wave file data into WaveData!");
		return false;
	}

	// Close the file once done reading.
	error = fclose(filePtr);
	if (error != 0)
	{
		__ASSERT(false, "Unable to close file!");
		return false;
	}

	// Lock the secondary buffer to write wave data into it.
	hr = (*secondaryBuffer)->Lock(0, waveFileHeader.dataSize, &bufferPtr, &bufferSize, NULL, NULL, 0);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to lock the secondary buffer!");
		return false;
	}

	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, bufferSize);

	// Unlock the secondary buffer after the data has been written to it.
	hr = (*secondaryBuffer)->Unlock(bufferPtr, bufferSize, NULL, 0);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to unlock the secondary buffer!");
		return false;
	}

	// Release the wave data since it was copied into the secondary buffer.
	delete[] waveData;
	waveData = NULL;

	return true;
}

HRESULT AudioMixer::CreatePrimaryBuffer()
{
	HRESULT hr = S_OK;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;

	// Setup the primary buffer description.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Get control of the primary sound buffer on the default sound device.
	hr = m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_PrimaryBuffer, NULL);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to create primary sound buffer!");
		return hr;
	}

	// Setup the format of the primary sound bufffer.
	// In this case it is a .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format).
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the primary buffer to be the wave format specified.
	hr = m_PrimaryBuffer->SetFormat(&waveFormat);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to set the primary buffer to be the wave format specified!");
		return hr;
	}
	return hr;
}

HRESULT AudioMixer::CreateSecondaryBuffer(LPDIRECTSOUNDBUFFER8* buffer, DWORD bufferSize)
{
	HRESULT hr = S_OK;
	LPDIRECTSOUNDBUFFER tempBuffer;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;

	// Setup the format of the primary sound bufffer.
	//High quaility - .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format)
	memset(&waveFormat, 0, sizeof(WAVEFORMATEX));
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Setup buffer description
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_LOCSOFTWARE | DSBCAPS_GETCURRENTPOSITION2;
	bufferDesc.dwBufferBytes = bufferSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create a temporary sound buffer with the specific buffer settings.
	hr = m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to create sound buffer!");
		return hr;
	}

	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	hr = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)buffer);
	if (FAILED(hr))
	{
		__ASSERT(false, "Fail to test the buffer format against the direct sound 8 interface!");
		return hr;
	}
	tempBuffer->Release();

	return hr;
}

void AudioMixer::ShutdownAudios()
{
	for (size_t index = 0; index < audios.size(); ++index)
	{
		audios[index]->buffer->Release();
		audios[index]->buffer = NULL;
	}
	audios.clear();
}

bool AudioMixer::PlayWaveFile(std::string name, bool looping)
{
	HRESULT hr = S_OK;
	for (size_t index = 0; index < audios.size(); ++index)
	{
		if (audios[index]->name == name)
		{	
			// Set position at the beginning of the sound buffer.
			hr = audios[index]->buffer->SetCurrentPosition(0);
			if (FAILED(hr))
			{
				__ASSERT(false, "Unable to set position at the beginning of the sound buffer!");
				return false;
			}

			// Play the contents of the secondary sound buffer.
			hr = audios[index]->buffer->Play(0, 0, looping ? DSBPLAY_LOOPING : 0);
			if (FAILED(hr))
			{
				__ASSERT(false, "Unable to set play the contents of the secondary sound buffer!");
				return false;
			}
		}
	}

	return true;
}

void AudioMixer::SetVolume(std::string name, LONG volume)
{
	HRESULT hr = S_OK;
	for (size_t index = 0; index < audios.size(); ++index)
	{
		if (audios[index]->name == name)
		{
			hr = audios[index]->buffer->SetVolume(volume);
			if (FAILED(hr))
			{
				__ASSERT(false, "Unable to set volume!");
			}
			return;
		}
	}
	return;
}

HRESULT AudioMixer::CreateAudios()
{
	HRESULT hr = S_OK;
	
	audios.reserve(2);
	std::shared_ptr<Audio> bgm = std::make_shared<Audio>();
	bgm->name = "BGM";
	LoadWaveFile(BGM_AUDIO, &bgm->buffer);
	audios.emplace_back(bgm);

	std::shared_ptr<Audio> bip = std::make_shared<Audio>();
	bip->name = "BIP";
	LoadWaveFile(BIP_SOUND, &bip->buffer);
	audios.emplace_back(bip);
	return hr;
}