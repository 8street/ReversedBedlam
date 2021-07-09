#include <cstdlib>

#include "dsound_func.h"
#include "file.h"
#include "window.h"

LPDIRECTSOUND ppDS;

int DSOUND_ERRORCODE;
int DSOUND_INNITED;

LPDIRECTSOUNDBUFFER PRIMARY_DSOUND_BUFFER;

LPDIRECTSOUNDBUFFER *DSOUND_BUFFERS_ARR;

int DSOUND_BUFFERS_USAGE;

int NUM_DSOUND_BUFFERS = 512;
int NUM_PLAYING_BUFFERS = 4;

//0044C068
int init_dsound()
{
    int ret_val = 0;
    DSBUFFERDESC lpcDSBufferDesc;
    WAVEFORMATEX waveformat;

    DSOUND_BUFFERS_USAGE = 0;

    PRIMARY_DSOUND_BUFFER = NULL;
    DSOUND_BUFFERS_ARR = (LPDIRECTSOUNDBUFFER *)malloc(sizeof(LPDIRECTSOUNDBUFFER) * NUM_DSOUND_BUFFERS * NUM_PLAYING_BUFFERS);
    if (DSOUND_BUFFERS_ARR) {
        memset(DSOUND_BUFFERS_ARR, NULL, sizeof(LPDIRECTSOUNDBUFFER) * NUM_DSOUND_BUFFERS * NUM_PLAYING_BUFFERS);
        
        DSOUND_ERRORCODE = 0;
        DSOUND_INNITED = 1;
    }
    else {
        DSOUND_ERRORCODE = -1;
        DSOUND_INNITED = 0;
    }

    if ((uint32_t)DirectSoundCreate(NULL, &ppDS, NULL)) {
        ret_val = 1;
        DSOUND_ERRORCODE = -1;
        DSOUND_INNITED = 0;
    }
    else if ((uint32_t)ppDS->SetCooperativeLevel(WINDOW_HWND, DSSCL_PRIORITY)) {
        ret_val = 2;
        DSOUND_ERRORCODE = -1;
        DSOUND_INNITED = 0;
    }
    else {
        memset(&waveformat, 0, sizeof(waveformat));
        waveformat.wFormatTag = WAVE_FORMAT_PCM;
        waveformat.wBitsPerSample = 16;
        waveformat.nChannels = 2;
        waveformat.nSamplesPerSec = 44100;
        waveformat.nBlockAlign = (waveformat.wBitsPerSample / 8) * waveformat.nChannels;
        waveformat.nAvgBytesPerSec = waveformat.nSamplesPerSec * waveformat.nBlockAlign;


        memset(&lpcDSBufferDesc, 0, sizeof(lpcDSBufferDesc));
        lpcDSBufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
        lpcDSBufferDesc.lpwfxFormat = NULL;
        lpcDSBufferDesc.dwSize = sizeof(lpcDSBufferDesc);
        if ((uint32_t)ppDS->CreateSoundBuffer(&lpcDSBufferDesc, &PRIMARY_DSOUND_BUFFER, NULL))
        {
            ret_val = 3;
            DSOUND_ERRORCODE = -1;
            DSOUND_INNITED = 0;
        }
        else if ((uint32_t)PRIMARY_DSOUND_BUFFER->SetFormat(&waveformat))
        {
            ret_val = 4;
            DSOUND_ERRORCODE = -1;
            DSOUND_INNITED = 0;
        }
        else
        {
            PRIMARY_DSOUND_BUFFER->Play(NULL, NULL, DSBPLAY_LOOPING);
            ret_val = 0;
        }
    }
    return ret_val;
}

//0044C64C
int load_raw_to_dsound_buffer(uint8_t *raw_ptr, int filesize, int discretization, int bit, int channels)
{
    int ret_val; // eax
    int cur_buf = DSOUND_BUFFERS_USAGE; // ebx
    DSBUFFERDESC lpcDSBufferDesc; // [esp+8h] [ebp-4Ch] OVERLAPPED BYREF
    WAVEFORMATEX waveformat; // [esp+1Ch] [ebp-38h] BYREF
    LPVOID dest_1 = NULL; // [esp+30h] [ebp-24h] BYREF
    LPVOID dest_2 = NULL; // [esp+34h] [ebp-20h] BYREF
    DWORD count_1 = 0;
    DWORD count_2 = 0;

    if (DSOUND_ERRORCODE == -1 || filesize <= 0) {
        return -1;
    }

    memset(&waveformat, 0, sizeof(waveformat));
    waveformat.wFormatTag = WAVE_FORMAT_PCM;
    waveformat.nChannels = channels;
    waveformat.wBitsPerSample = bit;
    waveformat.nSamplesPerSec = discretization;
    waveformat.nBlockAlign = (waveformat.wBitsPerSample / 8) * waveformat.nChannels;
    waveformat.nAvgBytesPerSec = waveformat.nSamplesPerSec * waveformat.nBlockAlign;

    memset(&lpcDSBufferDesc, 0, sizeof(lpcDSBufferDesc));
    lpcDSBufferDesc.dwSize = sizeof(lpcDSBufferDesc);
    lpcDSBufferDesc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME; // 0xE2
    lpcDSBufferDesc.lpwfxFormat = &waveformat;
    lpcDSBufferDesc.dwBufferBytes = filesize;

    if ((uint32_t)ppDS->CreateSoundBuffer(&lpcDSBufferDesc, &DSOUND_BUFFERS_ARR[cur_buf], NULL)) {
        return -2;
    }

    if ((uint32_t)DSOUND_BUFFERS_ARR[cur_buf]->Lock(0, filesize, &dest_1, &count_1, &dest_2, &count_2, 0))
    {
        DSOUND_BUFFERS_ARR[cur_buf]->Release();
        DSOUND_BUFFERS_ARR[cur_buf] = NULL;
        return -2;
    }
    memcpy(dest_1, raw_ptr, count_1);
    if (dest_2) {
        memcpy(dest_2, &raw_ptr[count_1], count_2);
    }

    if ((uint32_t)DSOUND_BUFFERS_ARR[cur_buf]->Unlock(dest_1, count_1, dest_2, count_2))
    {
        DSOUND_BUFFERS_ARR[cur_buf]->Release();
        DSOUND_BUFFERS_ARR[cur_buf] = NULL;
        ret_val = -2;
    }
    else
    {
        ret_val = cur_buf;
        DSOUND_BUFFERS_USAGE++;
    }
    return ret_val;
}

//0044C828
int duplicate_sound_buffer(int index)
{
    int ret_val; // eax

    if (DSOUND_ERRORCODE || index < 0 || !DSOUND_BUFFERS_ARR[index])
    {
        return -1;
    }
    if (DSOUND_BUFFERS_USAGE >= NUM_DSOUND_BUFFERS)
    {
        return 1;
    }

    ppDS->DuplicateSoundBuffer(DSOUND_BUFFERS_ARR[index], &DSOUND_BUFFERS_ARR[DSOUND_BUFFERS_USAGE]);
    ret_val = DSOUND_BUFFERS_USAGE;
    DSOUND_BUFFERS_USAGE++;
    return ret_val;
}

//0043A39C
int load_raw(const char* filename)
{
    int num_copy = 0; // edx
    int raw_index; // ebx

    File raw_file(filename);

    raw_index = load_raw_to_dsound_buffer(raw_file.get_ptr(), static_cast<int>(raw_file.get_size()), 11025, 8, 1);
    while(num_copy < NUM_PLAYING_BUFFERS)
    {
        duplicate_sound_buffer(raw_index);
        num_copy++;
    }
    return raw_index;
}

//0044C5AC
bool dsound_buf_is_not_playing(int buffer_index)
{
    bool is_not_playing = true;
    DWORD status = NULL;

    if (DSOUND_ERRORCODE && buffer_index >= 0 && buffer_index < NUM_DSOUND_BUFFERS)
    {
        return true;
    }

    if (DSOUND_BUFFERS_ARR[buffer_index])
    {
        DSOUND_BUFFERS_ARR[buffer_index]->GetStatus(&status);
        if (status == DSBSTATUS_PLAYING) {
            is_not_playing = false;
        }
    }
    return is_not_playing;
}


//0043A48E
int play_sound(int raw_index, int x, int y, int a5)
{
    int balance; // [esp+0h] [ebp-18h]
    int volume; // [esp+4h] [ebp-14h]

    if (x == -1 && y == -1)
    {
        volume = 32768;
        balance = 32768;
    }
    else
    {
        //volume = get_volume(x, y);
        //balance = get_balance(x, y);
        volume = 32768;
        balance = 32768;
    }

    int not_busy_index = 0; // ebp
    int i = 0;
    for (int raw2 = raw_index; raw2 < raw_index + NUM_PLAYING_BUFFERS; raw2++)
    {
        if (dsound_buf_is_not_playing(raw2))
        {
            not_busy_index = i;
            break;
        }
        i++;
    }

    int play_index = raw_index + not_busy_index;

    if (!not_busy_index) {
        dsound_stop(play_index);
    }
    return dsound_play1(play_index, 0, 11025, volume, balance);
}

//0044C8C4
int dsound_play1(int buffer_index, int pos, int samplerate, int volume, int balance)
{
    if (DSOUND_ERRORCODE) {
        return -1;
    }
    dsound_play(buffer_index, pos, samplerate, volume, balance);
    return buffer_index;
}

//0044C4A8
void dsound_play(int buffer_index, int pos, int samplerate, int volume, int balance)
{
    if (!DSOUND_ERRORCODE)
    {
        if (buffer_index >= 0 && buffer_index < NUM_DSOUND_BUFFERS)
        {
            if (DSOUND_BUFFERS_ARR[buffer_index])
            {
                if (volume)
                {
                    if (dsound_buf_is_not_playing(buffer_index))
                    {
                        long vol = (volume - 32768) * 10000 / 32768;
                        long bal = (balance - 32768) * 10000 / 32768;
                        DSOUND_BUFFERS_ARR[buffer_index]->SetCurrentPosition(pos);
                        DSOUND_BUFFERS_ARR[buffer_index]->SetFrequency(samplerate);
                        DSOUND_BUFFERS_ARR[buffer_index]->SetVolume(vol);
                        DSOUND_BUFFERS_ARR[buffer_index]->SetPan(bal);
                        DSOUND_BUFFERS_ARR[buffer_index]->Play(0, 0, 0);// play no looping
                    }
                }
            }
        }
    }
}

//0044C904
void dsound_stop(int buffer_index)
{
    if (!DSOUND_ERRORCODE && buffer_index >= 0 && buffer_index < NUM_DSOUND_BUFFERS)
    {
        if (DSOUND_BUFFERS_ARR[buffer_index]) {
            DSOUND_BUFFERS_ARR[buffer_index]->Stop();
        }
    }
}
