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

   void Context::createInstance(std::vector<std::string> requestedLayers, std::vector<std::string> requestedInstanceExtensions) {

      // App Information 
      VkApplicationInfo appInfo = {
         .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
         .pApplicationName = "Vulkan",
         .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
         .pEngineName = "BulkkotEngine",
         .engineVersion = VK_MAKE_VERSION(1, 0, 0),
         .apiVersion = VK_API_VERSION_1_4
      };

      enabledLayers_ = utility_->filterLayers(utility_->getAvailableLayers(), requestedLayers);
      enabledInstanceExtensions_ = utility_->filterExtensions(utility_->getAvailableInstanceExtensions(), requestedInstanceExtensions);

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
      for (const std::string& s : enabledInstanceLayers) {
         layers.push_back(s.c_str());
      }

      // Extensions
      std::vector<const char*> extensions;
      extensions.reserve(enabledInstanceExtensions.size());
      for (const std::string& s : enabledInstanceExtensions) {
         extensions.push_back(s.c_str());
      }

      auto features = utility_->getValidationConfig(false).validationFeatures;

      // Create vulkan instance
      VkInstanceCreateInfo createInfo = {
         .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
         .pNext = &features,
         .pApplicationInfo = &appInfo,
         .enabledLayerCount = static_cast<uint32_t>(layers.size()),
         .ppEnabledLayerNames = layers.data(),
         .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
         .ppEnabledExtensionNames = extensions.data()
      };

      VK_CHECK(vkCreateInstance(&createInfo, nullptr, &instance_));
   }


   void Context::addDebugMessenger() {
      const VkDebugUtilsMessengerCreateInfoEXT messengerInfo = utility_->getMessengerConfig(enabledInstanceExtensions_);
      VK_CHECK(vkCreateDebugUtilsMessengerEXT(instance_, &messengerInfo, nullptr, &messenger_));
   }

   void Context::createSurface() {
      surface_ = std::make_unique<Surface>(instance_, window_.getWindow(), enabledInstanceExtensions_);
   }

   void Context::createUtility() {
      utility_ = std::make_unique<Utility>();
   }
}
