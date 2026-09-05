#pragma once
#include <vulkan/vulkan.h>
#include <vulkan/vk_enum_string_helper.h>
#include <cassert>
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#define VK_NO_PROTOTYPES


   #ifdef _WIN32
   #if !defined(VK_USE_PLATFORM_WIN32_KHR)
   #define NOMINMAX
   #define VK_USE_PLATFORM_WIN32_KHR
   #endif
   #endif

   #ifdef _WIN32
   #define VK_CHECK(func)                                                                 \
   {                                                                                      \
      const VkResult result = func;                                                       \
      if (result != VK_SUCCESS) {                                                         \
         std::cerr << "Error calling functin " << #func << " at " << __FILE__ << ":"      \
                   << __LINE__ << ". Result is " << string_VkResult(result) << std::endl; \
         assert(false);                                                                   \
       }                                                                                  \
   }
   #endif