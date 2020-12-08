#include "Engine.h"
#include "SoftwareRenderer.h"

#include <iostream>
#include <sstream>
#include <cmath>

#include <SDL2/SDL.h>

bool Engine::Setup()
{
  SDL_version sdlVersion;
  SDL_GetVersion(&sdlVersion);

  std::cout << "Using SDL version "
    << static_cast<int>(sdlVersion.major) << "."
    << static_cast<int>(sdlVersion.minor) << "."
    << static_cast<int>(sdlVersion.patch) << std::endl << std::endl;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cerr << "Error initializing SDL.";
    return false;
  }

  // Create SDL window.
  int window_width = 800;
  int window_height = 600;

  sdlWindow = SDL_CreateWindow(
    "Texelstorm", 
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    window_width,
    window_height,
    SDL_WINDOW_SHOWN);

  if (sdlWindow == nullptr)
  {
    std::cerr << "Error creating SDL window.";
    return false;
  }

  // Create SDL renderer.
  sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
  if (sdlRenderer == nullptr)
  {
    std::cerr << "Error creating SDL renderer.";
    return false;
  }

  // Create SDL framebuffer texture.
  sdlFramebuffer = SDL_CreateTexture(
    sdlRenderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STREAMING,
    window_width,
    window_height);

  // Create engine renderer.
  renderer = new SoftwareRenderer();
  renderer->Setup(window_width, window_height);
 
  return true;
}

int Engine::Run()
{
  SDL_Event event;
  bool done = false;

  while (!done)
  {
    Uint32 startTime = SDL_GetTicks();

    SDL_PumpEvents();
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "SDL_QUIT");
        done = true;
        break;

      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
          done = true;
        }
        break;
      }
    }

    Update();

    lastFrameTime = SDL_GetTicks() - startTime;
  }

  return 0;
}

void Engine::Quit()
{
  if (renderer != nullptr)
  {
    renderer->Quit();
    free(renderer);
  }

  if (sdlRenderer != nullptr)
  {
    SDL_DestroyRenderer(sdlRenderer);
  }

  if (sdlWindow != nullptr)
  {
    SDL_DestroyWindow(sdlWindow);
  }

  SDL_Quit();
}

void Engine::Update()
{
  SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
  SDL_RenderClear(sdlRenderer);

  renderer->Refresh(sdlFramebuffer);

  SDL_RenderCopy(sdlRenderer, sdlFramebuffer, NULL, NULL);
  SDL_RenderPresent(sdlRenderer);
}