#ifndef __IDisplay_h__
#define __IDisplay_h__

#include <SDL2/SDL.h>

/**
 * \brief Abstract infterface for display manager implementations. 
 */
class IDisplay
{
public:
  virtual ~IDisplay() {}

  /**
   * \brief Refreshes the display with the current contents of the frame buffer.
   */
  virtual void Present() = 0;

  /**
   * \brief Gets the SDL window.
   */
  virtual SDL_Window *GetWindow() = 0;

  /**
   * \brief Gets the framebuffer texture.
   */
  virtual SDL_Texture *GetFrameBuffer() = 0;
};

#endif /* define __IDisplay_h__ */