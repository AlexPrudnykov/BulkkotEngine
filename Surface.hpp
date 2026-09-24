#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define VMA_IMPLEMENTATION
#define TINYOBJLOADER_DISABLE_FAST_FLOAT
#define TINYOBJLOADER_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp> 


#include "Utility.hpp"

namespace BulkkotEngine {
   class Surface {
   public:
      Surface(VkInstance instance, GLFWwindow* window, std::unordered_set<std::string> enabledInstanceExtensions);
      ~Surface();

      VkSurfaceKHR getVkSurface();

   private:
      VkSurfaceKHR surface_;

      void createSurface(VkInstance instance, GLFWwindow* window, std::unordered_set<std::string> enabledInstanceExtensions);
   };
}