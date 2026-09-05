#pragma once
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan.hpp> 


namespace BulkkotEngine {
   class Context {
   public:
      Context() { };
      ~Context() { };

      VkQueue getQueue() { }
      VkDevice getDevice() { }

   private:
      VkQueue queue_;
      VkDevice device_;
      VkInstance instance_;
      VkSurfaceKHR surface_;
      VkPhysicalDevice physicalDevice_;

      void createQueue() { }
      void createDevice() { }
      void createSurface() { }
      void createInstance() { }
      void createPhysicalDevice() { }
   };
}