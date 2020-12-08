#include "SoftwareRenderer.h"

void SoftwareRenderer::Setup(int width, int height)
{
  window_width = width;
  window_height = height;

  // Allocate color buffer.
  colorBuffer = (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
}

void SoftwareRenderer::Refresh(SDL_Texture* frameBuffer)
{
  ClearColorBuffer();
  DrawGrid(16);

  // Copy color buffer to frame buffer.
  SDL_UpdateTexture(
    frameBuffer,
    NULL,
    colorBuffer,
    (int)(window_width * sizeof(uint32_t)));
}

void SoftwareRenderer::Quit()
{
  if (colorBuffer != nullptr)
  {
    free(colorBuffer);
  }
}

/**
 * \brief Clears the color buffer.
 */
void SoftwareRenderer::ClearColorBuffer()
{
  for (int y = 0; y < window_height; y++)
  {
    for (int x = 0; x < window_width; x++)
    {
      colorBuffer[(window_width * y) + x] = 0xFF000000;
    }
  }
}

/**
 * \brief Draws a grid to the color buffer.
 * \param gridSize Grid size (pixels).
 */
void SoftwareRenderer::DrawGrid(int gridSize)
{
  for (int y = 0; y < window_height; y += gridSize)
  {
    for (int x = 0; x < window_width; x += gridSize)
    {
      colorBuffer[(window_width * y) + x] = 0xFF444444;
    }
  }
}