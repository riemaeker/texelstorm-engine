#include "SoftwareRenderer.h"

SoftwareRenderer::SoftwareRenderer(IDisplay *display)
{
  // Allocate color buffer.
  SDL_QueryTexture(display->GetFrameBuffer(), NULL, NULL, &window_width, &window_height);
  colorBuffer = (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);

  this->display = display;
}

SoftwareRenderer::~SoftwareRenderer()
{
  free(colorBuffer);
}

/**
 * \brief Renders the current frame to the frame buffer.
 */
void SoftwareRenderer::Refresh()
{
  ClearColorBuffer();
  DrawGrid(16);

  // Copy color buffer to frame buffer.
  SDL_UpdateTexture(
    display->GetFrameBuffer(),
    NULL,
    colorBuffer,
    (int)(window_width * sizeof(uint32_t)));
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