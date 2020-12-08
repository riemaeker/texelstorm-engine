#ifndef __IRenderer_h__
#define __IRenderer_h__

#include <SDL2/SDL.h>

/**
 * \brief Abstract infterface for renderer implementations. 
 */
class IRenderer
{
public:
  virtual ~IRenderer() {}

  /**
   * \brief Initializes the renderer.
   * \param width Window width (pixels).
   * \param height Window height (pixels).
   */
  virtual void Setup(int width, int height) = 0;

  /**
   * \brief Renders the current frame to the frame buffer.
   * \param frameBuffer Frame buffer texture. 
   */
  virtual void Refresh(SDL_Texture *frameBuffer) = 0;

  /**
   * \brief Releases renderer resources.
   */
  virtual void Quit() = 0;
};

#endif /* define __IRenderer_h__ */