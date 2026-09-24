#include "Utility.hpp"

namespace BulkkotEngine {
   Utility::Utility() {

   }

   Utility::~Utility() {
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

   std::vector<std::string> Utility::getAvailableInstanceExtensions() {
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

   Utility::ValidationConfig Utility::getValidationConfig(bool enableShaderPrintf) const {
      ValidationConfig config = { };

      #if defined(VK_EXT_layer_setting)
         config.layerSetting = {
            VkLayerSettingEXT = {
               .pLayerName = config.layerName.c_str(),
               .pSettingName = "debug_action",
               .type = VK_LAYER_SETTING_TYPE_STRING_EXT,
               .valueCount = static_cast<uint32_t>(config.debugAction.size()),
               .pValues = config.debugAction.data()
            },

            VkLayerSettingEXT = {
               .pLayerName = config.layerName.c_str(),
               .pSettingName = "validate_gpu_based",
               .type = VK_LAYER_SETTING_TYPE_STRING_EXT,
               .valueCount = static_cast<uint32_t>(config.gpuBaseedAction.size()),
               .pValues = config.gpuBasedAction.data()
            },

            VkLayerSettingEXT = {
               .pLayerName = config.layerName.c_str(),
               .pSettingName = "printf_to_stdout",
               .type = VK_LAYER_SETTING_TYPE_BOOL32_EXT,
               .valueCount = 1,
               .pValues = &config.printfToStdout
            },

            VkLayerSettingEXT = {
               .pLayerName = config.layerName.c_str(),
               .pSettingName = "printf_verbose",
               .type = VK_LAYER_SETTING_TYPE_BOOL32_EXT,
               .valueCount = 1,
               .pValues = &config.printfVerbose
            }

         };

         config.layerSettingsCreateInfo.sType = VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT;
         config.layerSettingsCreateInfo.pNext = nullptr;
         config.layerSettingsCreateInfo.settingCount = static_cast<uint32_t>(config.layerSettings.size());
         config.layerSettingsCreateInfo.pSettings = config.layerSettings.data();

         #elif defined(VK_EXT_layer_settings)
            if (enableShaderPrintf) {
               config.enabledFeatures.push_back(VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT);
            } else {
               config.enabledFeatures.push_back(VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT);
            }

            config.validationFeatures.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
            config.validationFeatures.pNext = nullptr;
            config.validationFeatures.enabledValidationFeatureCount = static_cast<uint32_t>(config.enabledFeatures.size());
            config.validationFeatures.pEnabledValidationFeatures = config.enabledFeatures.data();
         #endif

         return config;
   }

   VkDebugUtilsMessengerCreateInfoEXT Utility::getMessengerConfig(std::unordered_set<std::string> enabledInstanceExtensions) {
      const VkDebugUtilsMessengerCreateInfoEXT messengerInfo = {
         .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
         .flags = 0,
         .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
         .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT

         #if defined(VK_EXT_device_address_binding_report)
                        | VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT
         #endif

         ,
         .pfnUserCallback = nullptr,
         .pUserData = nullptr
      };

      return messengerInfo;
   }

}