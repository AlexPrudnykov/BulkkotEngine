#pragma once


#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// std lib headers
#include <string>

namespace BulkkotEngine {
   class Window {
   public:
      Window(int width, int height, std::string name);
      ~Window();

      GLFWwindow* getWindow();

      bool shouldClouse() {
         return glfwWindowShouldClose(window_);
      }

   private:
      void initWindow();

      const int width;
      const int height;

      std::string windowName_;
      GLFWwindow* window_;
   };
}