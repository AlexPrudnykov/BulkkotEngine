#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h> 
#include <vulkan/vulkan.hpp> 
#include "Common.hpp"

// std lib headers
#include <string>
#include <algorithm>
#include <unordered_set>
#include <vector>

namespace BulkkotEngine {
   #define LOGE(format, ...)                 \
     do {                                    \
       fprintf(stderr, format, __VA_ARGS__); \
       fprintf(stderr, "\n");                \
     } while (0)                             \

   #define LOGW(format, ...) LOGE(format, __VA_ARGS__)
   #define LOGI(format, ...) LOGE(format, __VA_ARGS__)
   #define LOGD(format, ...) LOGE(format, __VA_ARGS__)


   class Utility {

      public:
         struct ValidationConfig
         {
            std::string layerName = { "VK_LAYER_KHRONOS_validation" };
            std::vector<const char*> debugAction = { "VK_DBG_LAYER_ACTION_BREAK" };
            std::vector<const char*> gpuBasedAction = { "GPU_BASED_DEBUG_PRINTF" };
            VkBool32 printfToStdout = { VK_TRUE };
            VkBool32 printfVerbose = { VK_TRUE };
            std::vector<VkLayerSettingEXT> layerSettings;
            VkLayerSettingsCreateInfoEXT layerSettingsCreateInfo = {
               .sType = VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT,
               .pNext = nullptr
            };
            std::vector<VkValidationFeatureEnableEXT> enabledFeatures;
            VkValidationFeaturesEXT validationFeatures = {
               .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
               .pNext = nullptr
            };
         };

         Utility();
         ~Utility();

         std::vector<std::string> getAvailableLayers();
         PFN_vkDebugUtilsMessengerCallbackEXT setupDebugMessenger();
         ValidationConfig getValidationConfig(bool enableShaderPrintf = true) const;
         std::vector<std::string> getAvailableInstanceExtensions(std::optional<std::string> extraExtensions = std::nullopt);
         VkDebugUtilsMessengerCreateInfoEXT getMessengerConfig(std::unordered_set<std::string> enabledInstanceExtensions);
         std::unordered_set<std::string> filterLayers(std::vector<std::string> availableLayers, std::vector<std::string> requestedLayers);
         std::unordered_set<std::string> filterExtensions(std::vector<std::string> availableExtensions, std::vector<std::string> requestedExtensions);
   };
}