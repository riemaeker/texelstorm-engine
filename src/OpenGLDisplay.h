#ifndef __OpenGLDisplay_h__
#define __OpenGLDisplay_h__

#include <SDL2/SDL.h>

#include "IDisplay.h"

/**
 * \brief OpenGL display manager.
 */
class OpenGLDisplay : public IDisplay
{
public:
  OpenGLDisplay(int window_width, int window_height);
  ~OpenGLDisplay();

  void Present();

  SDL_Window *GetWindow();
  SDL_Texture *GetFrameBuffer();

private:
  SDL_Window *sdlWindow = nullptr;
  SDL_Renderer *sdlRenderer = nullptr;
  SDL_Texture *sdlFramebuffer = nullptr;
};

#endif /* define __OpenGLDisplay_h__ */