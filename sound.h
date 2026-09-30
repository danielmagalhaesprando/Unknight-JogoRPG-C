#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include <SDL.h>
#include <SDL_audio.h>
#include "game.h"

void initAudio(gameData * game);
void audio_callback(void *user_data, Uint8 *raw_buffer, int bytes);

#endif // SOUND_H_INCLUDED
