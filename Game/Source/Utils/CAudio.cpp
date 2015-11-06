#include "CAudio.h"

CAudio CAudio::Player;

CAudio::CAudio() {
}

bool CAudio::Init()
{
  return !(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0);  
}
void CAudio::LoadWAV(const std::string  &key, const std::string &file)
{
  Mix_Chunk* sfx_file = NULL;

  if ((sfx_file = Mix_LoadWAV(file.c_str())) == NULL) {
    SDL_Log(" Couldn't load sfx %s ", file.c_str());
    return;
  }
  m_soundList[key] = sfx_file;
}

void CAudio::Cleanup() 
{
  for (auto it = m_soundList.begin(); it != m_soundList.end(); it++)
    Mix_FreeChunk(it->second);
  m_soundList.clear();
  
}

void CAudio::Play(const std::string &sfx_file) 
{
  if (m_soundList.find(sfx_file) != m_soundList.end())
    Mix_PlayChannel(-1, m_soundList[sfx_file], 0);
  else
    SDL_Log(" %s not found in sound library", sfx_file.c_str());
}