#ifndef __VulkanDisplay_h__
#define __VulkanDisplay_h__

#include <tuple>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include "IDisplay.h"

/**
 * \brief Vulkan display manager.
 */
class VulkanDisplay : public IDisplay
{
public:
  VulkanDisplay(int window_width, int window_height);
  ~VulkanDisplay();

  void Present();

  SDL_Window *GetWindow();
  SDL_Texture *GetFrameBuffer();

private:
  void CheckVulkanResult();
  std::tuple<const char**, uint32_t> GetVulkanExtensions(SDL_Window *window);
  void CreateVulkanInstance(const char** extensions, uint32_t extensionCount, VkInstance& outInstance);
  void GetPhysicalDevice(VkInstance instance, VkPhysicalDevice& outDevice);
  void GetLogicalDevice(VkPhysicalDevice physicalDevice, VkDevice& outDevice, uint32_t& outQueueFamily);

  SDL_Window *sdlWindow = nullptr;

  VkResult vulkanResult;

  VkAllocationCallbacks* vulkanAllocator = nullptr;
  VkInstance vulkanInstance = VK_NULL_HANDLE;
  VkPhysicalDevice vulkanPhysicalDevice = VK_NULL_HANDLE;
  VkDevice vulkanDevice = VK_NULL_HANDLE;
  uint32_t vulkanQueueFamily = (uint32_t)-1;
  VkQueue vulkanQueue = VK_NULL_HANDLE;
  VkDebugReportCallbackEXT vulkanDebugReport = VK_NULL_HANDLE;
  VkPipelineCache vulkanPipelineCache = VK_NULL_HANDLE;
  VkDescriptorPool vulkanDescriptorPool = VK_NULL_HANDLE;
};

#endif /* define __VulkanDisplay_h__ */