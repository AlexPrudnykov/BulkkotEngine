#include "Context.hpp";


namespace BulkkotEngine {
   Context::Context() {

   }

   Context::~Context() {

   }

   void Context::createQueue() {
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
      //auto instanceLayers =
     
   }
}
