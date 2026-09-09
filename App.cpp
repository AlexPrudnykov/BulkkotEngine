#include "App.hpp"

namespace BulkkotEngine {
   App::App(int width, int height, const std::string& title) : window(width, height, title), context(window) {

   }

   void App::run() {
      while (!window.shouldClouse()) {
         glfwPollEvents();
      }
   }
}