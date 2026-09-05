#pragma once
#include <vulkan/vulkan.hpp> 
#include "Common.hpp";

// std lib headers
#include <string>
#include <algorithm>
#include <unordered_set>
#include <vector>


namespace BulkkotEngine {
   class Utility {

      public:
         Utility() { }
         ~Utility() { }

         std::vector<std::string> requestedLayers() { }
         std::vector<std::string> getAvailableLayers() { }
         std::vector<std::string> requestedExtensions() { }
         std::vector<std::string> getAvailableExtensions() { }
         std::unordered_set<std::string> filterLayers(std::vector<std::string> availableLayers, std::vector<std::string> requstedLayers) { }
         std::unordered_set<std::string> filterExtensions(std::vector<std::string> availableExtensions, std::vector<std::string> requestedExtensions) { }
   };
}