#ifndef __Engine_h__
#define __Engine_h__

#include <SDL2/SDL.h>
#include "IRenderer.h"

 #define ENGINE_NAME "Texelstorm engine"
 #define ENGINE_VERSION "1.0.0"

/**
 * \brief Core system and subsystems.
 */
class Engine
{
public:
  /**
  * \brief Initializes the engine and its subsystems.
  */
  bool Setup();

  /**
   * \brief Runs the engine loop until a quit event or fatal error happens.
   * \return Return code to be output by the application when it terminates.
   */
  int Run();

  /**
   * \brief Quits the engine and its subsytems.
   */
  void Quit();

private:
  /**
   * \brief Processes events and updates engine subsytems.
   */
  void Update();

  SDL_Window *sdlWindow = nullptr;
  SDL_Renderer *sdlRenderer = nullptr;
  SDL_Texture *sdlFramebuffer = nullptr;

  IRenderer *renderer = nullptr;

  Uint32 lastFrameTime;
};

#endif /* define __Engine_h__ */
