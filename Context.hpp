#pragma once
#define VMA_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define TINYOBJLOADER_DISABLE_FAST_FLOAT

#include <vulkan/vulkan.hpp> 
#include <memory>

#include "Utility.hpp"
#include "Surface.hpp"
#include "Window.hpp"

namespace BulkkotEngine {
   class Context {
   public:
      Context(Window& window);
      ~Context();

      VkQueue getQueue();
      VkDevice getDevice();

   private:
      std::unique_ptr<Utility> utility_ = nullptr;
      std::unique_ptr<Surface> surface_ = nullptr;

      VkQueue queue_;
      VkDevice device_;
      Window& window_;
      VkInstance instance_;
      VkPhysicalDevice physicalDevice_;

      void createQueue();
      void createDevice();
      void createSurface();
      void createInstance();
      void createPhysicalDevice();

      std::vector<std::string> getLayers();
      std::vector<std::string> getExtensions();

      void createUtility();
   };
}