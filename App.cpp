#include "App.hpp"

namespace BulkkotEngine {
   App::App(int width, int height, const std::string& title) : window(width, height, title), context(window, requestedLayers(), requestedDeviceExtensions(), requestedInstanceExtensions()) {

   }

   void App::run() {
      while (!window.shouldClouse()) {
         glfwPollEvents();
      }
   }

   std::vector<std::string> App::requestedLayers() { 
      const std::vector<std::string> requestedInstanceLayers = {
         "VK_LAYER_KHRONOS_validation"
      };

      return requestedInstanceLayers;
   }

   std::vector<std::string> App::requestedDeviceExtensions()
   {
      std::vector<std::string> devicedExtensions = {
      #if defined(VK_EXT_calibrated_timestamps) 
         VK_EXT_CALIBRATED_TIMESTAMPS_EXTENSION_NAME
      #endif
         VK_KHR_SWAPCHAIN_EXTENSION_NAME,
         VK_EXT_MEMORY_BUDGET_EXTENSION_NAME
      };

      return devicedExtensions;
   }

   std::vector<std::string> App::requestedInstanceExtensions() {
      std::vector<std::string> requestedInstanceExtensions;

      requestedInstanceExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);

      #ifdef _WIN32
         requestedInstanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
      #endif

      #ifdef VK_EXT_debug_utils
         requestedInstanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
      #endif

      #ifdef VK_KHR_surface
         requestedInstanceExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
      #endif

      return requestedInstanceExtensions;
   }
}