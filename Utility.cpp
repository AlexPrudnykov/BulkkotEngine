#include "Utility.hpp"

namespace BulkkotEngine {
   Utility::Utility() {

   }

   Utility::~Utility() {
   }

   std::vector<std::string> Utility::requestedLayers() { 
      const std::vector<std::string> requestedInstanceLayers = {
         "VK_LAYER_KHRONOS_validation"
      };

      auto enabldedInstanceLayersSet = filterLayers(getAvailableLayers(), requestedInstanceLayers);

      std::vector<std::string> enabledInstanceLayers(
         enabldedInstanceLayersSet.begin(),
         enabldedInstanceLayersSet.end()
      );

      return enabledInstanceLayers;
   }

   std::vector<std::string> Utility::requestedExtensions() {
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

         enabledInstanceExtensionsSet_ = filterExtensions(getAvailableExtensions(), requestedInstanceExtensions);

         std::vector<std::string> enabledInstanceExtensions(
            enabledInstanceExtensionsSet_.begin(),
            enabledInstanceExtensionsSet_.end()
         );

         return enabledInstanceExtensions;
   }

   std::vector<std::string> Utility::getAvailableLayers() {

      uint32_t instanceLayerCount = { 0 };
      VK_CHECK(vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr));

      std::vector<VkLayerProperties> layers(instanceLayerCount);
      VK_CHECK(vkEnumerateInstanceLayerProperties(&instanceLayerCount, layers.data()));

      std::vector<std::string> availableLayesr;
      std::transform(
         layers.begin(),
         layers.end(),
         std::back_inserter(availableLayesr),
         [](const VkLayerProperties& properties) {
            return properties.layerName;
         }
      );

      return availableLayesr;
   }

   std::vector<std::string> Utility::getAvailableExtensions() {
      uint32_t extensionsCount = { 0 };
      vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
      std::vector<VkExtensionProperties> extensioProperties(extensionsCount);
      vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensioProperties.data());

      std::vector<std::string> availableExtensions;
      std::transform(
         extensioProperties.begin(),
         extensioProperties.end(),
         std::back_inserter(availableExtensions),
         [](const VkExtensionProperties& properties) {
         return properties.extensionName;
         }
      );

      return availableExtensions;
   }

   std::unordered_set<std::string> Utility::filterLayers(std::vector<std::string> availableLayers, std::vector<std::string> requestedLayers) {
      std::sort(availableLayers.begin(), availableLayers.end());
      std::sort(requestedLayers.begin(), requestedLayers.end());

      std::vector<std::string> result;
      std::set_intersection(availableLayers.begin(),
                            availableLayers.end(),
                            requestedLayers.begin(),
                            requestedLayers.end(),
                            std::back_inserter(result));

      return std::unordered_set<std::string>(result.begin(), result.end());
   }


   std::unordered_set<std::string> Utility::filterExtensions(std::vector<std::string> availableExtensions, std::vector<std::string> requestedExtensions) {
      std::sort(availableExtensions.begin(), availableExtensions.end());
      std::sort(requestedExtensions.begin(), requestedExtensions.end());

      std::vector<std::string> result;
      std::set_intersection(availableExtensions.begin(),
                            availableExtensions.end(),
                            requestedExtensions.begin(),
                            requestedExtensions.end(),
                            std::back_inserter(result));

      return std::unordered_set<std::string>(result.begin(), result.end());
   }

   std::unordered_set<std::string> Utility::getInstanceExtensionsSet() {
      return enabledInstanceExtensionsSet_;
   }
}