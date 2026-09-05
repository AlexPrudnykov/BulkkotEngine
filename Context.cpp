#define VMA_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION


#include "Context.hpp"
#include "Window.hpp"


namespace BulkkotEngine {
   Context::Context() {
      utility_ = Utility();

      createInstance();
      createSurface();
   }

   Context::~Context() {

   }

   void Context::createInstance() {
      // App Information 
      VkApplicationInfo appInfo = {
         .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
         .pApplicationName = "Vulkan",
         .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
         .pEngineName = "BulkkotEngine",
         .engineVersion = VK_MAKE_VERSION(1, 0, 0),
         .apiVersion = VK_API_VERSION_1_4
      };


      // Layers
      std::vector<const char*> layers;
      std::vector<std::string> instanceLayers = getLayers();
      layers.reserve(instanceLayers.size());
      for (const std::string& s : instanceLayers) {
         layers.push_back(s.c_str());
      }

      // Extensions
      std::vector<const char*> extensions;
      std::vector<std::string> instanceExtensions = getExtensions();
      extensions.reserve(instanceExtensions.size());
      for (const std::string& s : instanceExtensions) {
         extensions.push_back(s.c_str());
      }

      // Create vulkan instance
      VkInstanceCreateInfo createInfo = {
         .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
         .pApplicationInfo = &appInfo,
         .enabledLayerCount = static_cast<uint32_t>(layers.size()),
         .ppEnabledLayerNames = layers.data(),
         .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
         .ppEnabledExtensionNames = extensions.data()
      };

      VK_CHECK(vkCreateInstance(&createInfo, nullptr, &instance_));
   }


   void Context::createSurface() {
      const auto windowGlfw = glfwGetWin32Window(Window::getWindow());

      #if defined(VK_USE_PLATFORM_WIN32_KHR) && defined(VK_KHR_win32_surface)
         if (utility_.getInstanceExtensionsSet().contains(VK_KHR_WIN32_SURFACE_EXTENSION_NAME)) {
            if (windowGlfw != nullptr) {
               const VkWin32SurfaceCreateInfoKHR ci = {
                  .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
                  .hinstance = GetModuleHandle(NULL),
                  .hwnd = (HWND)windowGlfw
               };
               VK_CHECK(vkCreateWin32SurfaceKHR(instance_, &ci, nullptr, &surface_));
            }
         }
      #endif
   }

   std::vector<std::string> Context::getLayers() {
      return utility_.requestedLayers();
   }

   std::vector<std::string> Context::getExtensions() {
      return utility_.requestedExtensions();
;   }
}
