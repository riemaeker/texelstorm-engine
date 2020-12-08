#ifndef __SoftwareRenderer_h__
#define __SoftwareRenderer_h__

#include <SDL2/SDL.h>
#include "IRenderer.h"

/**
 * \brief Software rasterization-based renderer implementation.
 */
class SoftwareRenderer : public IRenderer
{
public:
  void Setup(int width, int height);
  void Refresh(SDL_Texture *frameBuffer);
  void Quit();

private:
  void ClearColorBuffer();
  void DrawGrid(int gridSize);

  uint32_t *colorBuffer = nullptr;
  int window_width;
  int window_height;
};

#endif /* define __SoftwareRenderer_h__ */
