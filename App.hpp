#pragma one

#include "window.hpp"
#include "Pipeline.hpp"

namespace BulkkotEngine {
   class App {

   public:
      static constexpr int WIDTH = 600;
      static constexpr int HEIGHT = 600;

      void run();

   private:

      // Create window
      Window window = { WIDTH, HEIGHT, "안녕, 엔진!"};
   };
}