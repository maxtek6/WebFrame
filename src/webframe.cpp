#include "webframe/webframe.h"
#include <iostream>

namespace webframe {

Runtime::Runtime() : initialized_(false) {}

Runtime::~Runtime() = default;

void Runtime::initialize() {
  if (initialized_) {
    return;
  }
  
  std::cout << "WebFrame runtime initializing..." << std::endl;
  initialized_ = true;
}

void Runtime::run(const std::string& appPath) {
  if (!initialized_) {
    initialize();
  }
  
  std::cout << "Running application from: " << appPath << std::endl;
  // TODO: Implement actual web application runtime
}

std::string Runtime::version() const {
  return "0.1.0";
}

} // namespace webframe
