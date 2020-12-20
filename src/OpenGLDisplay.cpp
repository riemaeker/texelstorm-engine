#include <iostream>

#include "OpenGLDisplay.h"

OpenGLDisplay::OpenGLDisplay(int window_width, int window_height)
{
  sdlWindow = SDL_CreateWindow(
    "Texelstorm",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    window_width,
    window_height,
    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    // Create SDL renderer.
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);

    // Create SDL framebuffer texture.
    sdlFramebuffer = SDL_CreateTexture(
      sdlRenderer,
      SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STREAMING,
      window_width,
      window_height);
}

OpenGLDisplay::~OpenGLDisplay()
{
  if (sdlWindow != nullptr)
  {
    SDL_DestroyWindow(sdlWindow);
  }
}

void OpenGLDisplay::Present()
{
  SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
  SDL_RenderClear(sdlRenderer);

  SDL_RenderCopy(sdlRenderer, sdlFramebuffer, NULL, NULL);
  
  SDL_RenderPresent(sdlRenderer); 
}

SDL_Window *OpenGLDisplay::GetWindow()
{
  return sdlWindow;
}

SDL_Texture *OpenGLDisplay::GetFrameBuffer()
{
  return sdlFramebuffer;
}