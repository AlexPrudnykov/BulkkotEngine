#include "Utility.hpp";

namespace BulkkotEngine {
   Utility::Utility() {
   }

   std::vector<std::string> requestedLayers() { 
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

   std::vector<std::string> getAvailableLayers() {

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

   std::unordered_set<std::string> filterLayers(std::vector<std::string> availableLayers, std::vector<std::string> requestedLayers) {
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


   std::unordered_set<std::string> filterExtensions(std::vector<std::string> availableExtensions, std::vector<std::string> requestedExtensions) {
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
}