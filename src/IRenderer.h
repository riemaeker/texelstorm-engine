#ifndef __IRenderer_h__
#define __IRenderer_h__

#include <SDL2/SDL.h>
#include "IDisplay.h"

/**
 * \brief Abstract infterface for renderer implementations. 
 */
class IRenderer
{
public:
  virtual ~IRenderer() {}

  /**
   * \brief Renders the current frame to the frame buffer.
   */
  virtual void Refresh() = 0;
};

#endif /* define __IRenderer_h__ */