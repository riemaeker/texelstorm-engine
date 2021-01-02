#include <iostream>
#include <vector>

#include "VulkanDisplay.h"

using namespace std;

VulkanDisplay::VulkanDisplay(int window_width, int window_height)
{
  sdlWindow = SDL_CreateWindow(
    "Texelstorm",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    window_width,
    window_height,
    SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

  auto [extensions, extensionCount] = GetVulkanExtensions(sdlWindow);
  CreateVulkanInstance(extensions, extensionCount, vulkanInstance);
  GetPhysicalDevice(vulkanInstance, vulkanPhysicalDevice);
  GetLogicalDevice(vulkanPhysicalDevice, vulkanDevice, vulkanQueueFamily);
}

VulkanDisplay::~VulkanDisplay()
{
  if (vulkanInstance != nullptr)
  {
    vkDestroyInstance(vulkanInstance, vulkanAllocator);
  }

  if (sdlWindow != nullptr)
  {
    SDL_DestroyWindow(sdlWindow);
  }
}

void VulkanDisplay::Present()
{
}

SDL_Window *VulkanDisplay::GetWindow()
{
  return sdlWindow;
}

SDL_Texture *VulkanDisplay::GetFrameBuffer()
{
  return nullptr;
}

void VulkanDisplay::CheckVulkanResult()
{
  if (vulkanResult == 0) return;
  cerr << "[VulkanDisplay] Error " << vulkanResult << endl;
  if (vulkanResult < 0) abort();
}

tuple<const char**, uint32_t> VulkanDisplay::GetVulkanExtensions(SDL_Window *window)
{
  uint32_t extensions_count = 0;
  SDL_Vulkan_GetInstanceExtensions(window, &extensions_count, NULL);
  const char** extensions = new const char*[extensions_count];
  SDL_Vulkan_GetInstanceExtensions(window, &extensions_count, extensions);

  cout << "[VulkanDisplay] Extensions:";
  for (int i = 0; i < extensions_count; ++i) {
    cout << " " << extensions[i];
  }
  cout << endl;

  return make_tuple(extensions, extensions_count);
}

void VulkanDisplay::CreateVulkanInstance(const char** extensions, uint32_t extensionCount, VkInstance& outInstance)
{
  VkInstanceCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.enabledExtensionCount = extensionCount;
  createInfo.ppEnabledExtensionNames = extensions;

  VkInstance instance = VK_NULL_HANDLE;
  
  vulkanResult = vkCreateInstance(&createInfo, vulkanAllocator, &outInstance);
  CheckVulkanResult();

  cout << "[VulkanDisplay] Created Vulkan instance ✅" << endl;
}

void VulkanDisplay::GetPhysicalDevice(VkInstance instance, VkPhysicalDevice& outDevice)
{
  unsigned int deviceCount(0);
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
  
  if (deviceCount > 0)
  {
    vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (auto& device : devices)
    {
      VkPhysicalDeviceProperties properties;
      vkGetPhysicalDeviceProperties(device, &properties);

      if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
      {
        cout << "[VulkanDisplay] Using device: " << properties.deviceName << endl;
        outDevice = device;
        return;
      }
    }
  }

  cerr << "[VulkanDisplay] No suitable GPU found." << endl;
}


void VulkanDisplay::GetLogicalDevice(VkPhysicalDevice physicalDevice, VkDevice& outDevice, uint32_t& outQueueFamily)
{
  // Get a queue family that supports graphics.
  unsigned int familyCount(0);
  vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &familyCount, nullptr);
  if (familyCount == 0)
  {
    cerr << "[VulkanDisplay] No queue families found." << endl;
    return;
  }

  vector<VkQueueFamilyProperties> properties(familyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &familyCount, properties.data());

  unsigned int familyIndex = -1;
  for (unsigned int i = 0; i < familyCount; i++)
  {
    auto family = properties[i];
    if (family.queueCount > 0 && family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
    {
      familyIndex = i;
      break;
    }
  }

  if (familyIndex < 0)
  {
    cerr << "[VulkanDisplay] No queue family available that accepts graphics commands." << endl;
    return;
  }

  outQueueFamily = familyIndex;

  // 
}
