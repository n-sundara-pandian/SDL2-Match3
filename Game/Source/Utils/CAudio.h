#ifndef CAUDIO_h
#define CAUDIO_h

#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include <map>

class CAudio {
public:
  static CAudio  Player;
  CAudio();
  bool Init();
  void LoadWAV(const std::string  &key, const std::string &file);
  void Cleanup();
  void Play(const std::string &sfx);
private:
  std::vector<Mix_Chunk*>     SoundList;
  std::map<std::string, Mix_Chunk*> m_soundList;
};
#endif /*CAUDIO_h*/