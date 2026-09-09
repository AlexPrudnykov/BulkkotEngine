#pragma one

#include "window.hpp"
#include "Context.hpp"

namespace BulkkotEngine {
   class App {

   public:
      App(int width = 600, int height = 600, const std::string& title = "안녕, 엔진!");

      void run();

   private:
      Window window;
      Context context;
   };
}