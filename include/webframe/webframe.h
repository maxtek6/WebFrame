#pragma once

#include <string>

namespace webframe {

class Runtime {
public:
  Runtime();
  ~Runtime();

  /// Initialize the runtime with configuration
  void initialize();

  /// Run the web application
  void run(const std::string& appPath);

  /// Get runtime version
  std::string version() const;

private:
  bool initialized_;
};

} // namespace webframe
