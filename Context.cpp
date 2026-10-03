#include "Context.hpp"
#include "Surface.hpp"


namespace BulkkotEngine {
   Context::Context(Window& window,
                    std::vector<std::string> requestedLayers,
                    std::vector<std::string> requestedDeviceExtensions,
                    std::vector<std::string> requestedInstanceExtensions) : window_{ window }
   {
      createUtility();

      createInstance(requestedLayers, requestedInstanceExtensions);
      addDebugMessenger();
      createSurface();
   }

   Context::~Context() {

   }

   void Context::createInstance(std::vector<std::string> requestedLayers, std::vector<std::string> requestedInstanceExtensions)
   {

      // App Information 
      VkApplicationInfo appInfo = {
         .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
         .pNext = nullptr,
         .pApplicationName = "Vulkan",
         .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
         .pEngineName = "BulkkotEngine",
         .engineVersion = VK_MAKE_VERSION(1, 0, 0),
         .apiVersion = VK_API_VERSION_1_4,
      };

      enabledLayers_ = utility_->filterLayers(utility_->getAvailableLayers(), requestedLayers);
      enabledInstanceExtensions_ = utility_->filterExtensions(utility_->getAvailableInstanceExtensions("VK_LAYER_KHRONOS_validation"), requestedInstanceExtensions);

      std::vector<std::string> enabledInstanceLayers(
         enabledLayers_.begin(),
         enabledLayers_.end()
      );

      std::vector<std::string> enabledInstanceExtensions(
         enabledInstanceExtensions_.begin(),
         enabledInstanceExtensions_.end()
      );

      // Layers
      std::vector<const char*> layers;
      layers.reserve(enabledInstanceLayers.size());
      for (const std::string& s : enabledInstanceLayers)
      {
         layers.push_back(s.c_str());
      }

      // Extensions
      std::vector<const char*> extensions;
      extensions.reserve(enabledInstanceExtensions.size());
      for (const std::string& s : enabledInstanceExtensions)
      {
         extensions.push_back(s.c_str());
      }

      auto features = utility_->getValidationConfig(false);
      features.validationFeatures.pEnabledValidationFeatures = features.enabledFeatures.data();

      // Create vulkan instance
      VkInstanceCreateInfo createInfo = {
         .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
         .pNext = &features.validationFeatures,
         .pApplicationInfo = &appInfo,
         .enabledLayerCount = static_cast<uint32_t>(layers.size()),
         .ppEnabledLayerNames = layers.data(),
         .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
         .ppEnabledExtensionNames = extensions.data()
      };

      auto test = features.layerSettings[0].pLayerName;

      VK_CHECK(vkCreateInstance(&createInfo, nullptr, &instance_));

   }

   void Context::addDebugMessenger() {
      const VkDebugUtilsMessengerCreateInfoEXT messengerInfo = utility_->getMessengerConfig(enabledInstanceExtensions_);
      auto pfnCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
         vkGetInstanceProcAddr(instance_, "vkCreateDebugUtilsMessengerEXT")
         );

      if (pfnCreateDebugUtilsMessengerEXT != nullptr) {
         VK_CHECK(pfnCreateDebugUtilsMessengerEXT(instance_, &messengerInfo, nullptr, &messenger_));
      } else {
         LOGE("Failed to load function pointer for vkCreateDebugUtilsMessengerEXT");
      }
   }

   void Context::createSurface() {
      surface_ = std::make_unique<Surface>(instance_, window_.getWindow(), enabledInstanceExtensions_);
   }

   void Context::createUtility() {
      utility_ = std::make_unique<Utility>();
   }
}
