#include "App.hpp"

namespace BulkkotEngine {
   void App::run() {
      while (!window.shouldClouse()) {
         glfwPollEvents();
      }
   }
}