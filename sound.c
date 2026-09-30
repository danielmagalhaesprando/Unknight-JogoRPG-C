#include <math.h>
#include "sound.h"


void initAudio(gameData * game)
{
    putenv("SDL_AUDIODRIVER=winmm"); // winmm or directsound

    if(SDL_Init(SDL_INIT_AUDIO) != 0)
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());

    SDL_AudioSpec want;
    want.freq = game->SAMPLE_RATE; // number of samples per second
    want.format = AUDIO_S16SYS; // sample type (here: signed short i.e. 16 bit)
    want.channels = 1; // only one channel
    want.samples = 2048; // buffer-size
    want.callback = audio_callback; // function SDL calls periodically to refill the buffer
    want.userdata = game; // counter, keeping track of current sample number and other stuff

    SDL_AudioSpec have;
    if(SDL_OpenAudio(&want, &have) != 0)
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to open audio: %s", SDL_GetError());

    if(want.format != have.format)
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to get the desired AudioSpec");

    SDL_PauseAudio(0); // start playing sound
}

void audio_callback(void *user_data, Uint8 *raw_buffer, int bytes)
{
    Sint16 *buffer = (Sint16*)raw_buffer;
    int length = bytes / 2; // 2 bytes per sample for AUDIO_S16SYS

    gameData *game = (gameData*)user_data;

    for(int i = 0; i < length; i++, game->audioSampleNumber++)
    {
        double time = (double)game->audioSampleNumber / (double)game->SAMPLE_RATE;
        buffer[i] = (Sint16)(330000.0 * sin(2.0f * M_PI * game->audioTone * time)); // render sine wave of audioTone frequency (Hz)
    }
}
