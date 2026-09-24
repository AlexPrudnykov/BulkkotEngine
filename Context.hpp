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
      Context(Window& window,
              std::vector<std::string> requestedLayers,
              std::vector<std::string> requestedDeviceExtensions,
              std::vector<std::string> requestedInstanceExtensions
              );
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

      #if defined(VK_EXT_debug_utils)
         VkDebugUtilsMessengerEXT messenger_ = VK_NULL_HANDLE;
      #endif

      std::unordered_set<std::string> enabledLayers_;
      std::unordered_set<std::string> enabledDeviceExtensions_;
      std::unordered_set<std::string> enabledInstanceExtensions_;

      void createQueue();
      void createDevice();
      void createSurface();
      void addDebugMessenger();
      void createPhysicalDevice();
      void createInstance(std::vector<std::string> requestedLayers, std::vector<std::string> requestedInstanceExtensions);

      void createUtility();
   };
}