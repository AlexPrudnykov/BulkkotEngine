#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define TINYOBJLOADER_DISABLE_FAST_FLOAT
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan.hpp> 

#include "Utility.hpp"

namespace BulkkotEngine {
   class Context {
   public:
      Context();
      ~Context();

      VkQueue getQueue();
      VkDevice getDevice();

   private:
      Utility utility_;

      VkQueue queue_;
      VkDevice device_;
      VkInstance instance_;
      VkSurfaceKHR surface_;
      VkPhysicalDevice physicalDevice_;

      void createQueue();
      void createDevice();
      void createSurface();
      void createInstance();
      void createPhysicalDevice();

      std::vector<std::string> getLayers();
      std::vector<std::string> getExtensions();
   };
}