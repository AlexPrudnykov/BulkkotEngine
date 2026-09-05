#include "window.hpp"

namespace BulkkotEngine {
   GLFWwindow* Window::window_ = nullptr;

   Window::Window(int width, int height, std::string name) : width{ width }, height{ height }, windowName_{name} {
      initWindow();
   }

   Window::~Window() {
      glfwDestroyWindow(window_);
      glfwTerminate();
   }

   void Window::initWindow() {
      glfwInit();
      glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
      glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

      window_ = glfwCreateWindow(width, height, windowName_.c_str(), nullptr, nullptr);
   }

    GLFWwindow* Window::getWindow() {
      return window_;
   }
}