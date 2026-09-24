#include "Surface.hpp"

namespace BulkkotEngine {
   Surface::Surface(VkInstance instance, GLFWwindow* window, std::unordered_set<std::string> enabledInstanceExtensions) {
      createSurface(instance, window, enabledInstanceExtensions);
   }

   Surface::~Surface() {

   }

   void Surface::createSurface(VkInstance instance, GLFWwindow* window, std::unordered_set<std::string> enabledInstanceExtensions) {
      const auto windowGlfw = glfwGetWin32Window(window);

      #if defined(VK_USE_PLATFORM_WIN32_KHR) && defined(VK_KHR_win32_surface)
         if (enabledInstanceExtensions.contains(VK_KHR_WIN32_SURFACE_EXTENSION_NAME)) {
            if (windowGlfw != nullptr) {
               const VkWin32SurfaceCreateInfoKHR ci = {
                  .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
                  .hinstance = GetModuleHandle(NULL),
                  .hwnd = (HWND)windowGlfw
               };

               VK_CHECK(vkCreateWin32SurfaceKHR(instance, &ci, nullptr, &surface_));
            }
         }
      #endif
   }

   VkSurfaceKHR Surface::getVkSurface() {
      return surface_;
   }
}