# Ports

CEF is currently built as a port for MacOS and Linux

## TODO

The wxWebView chromium module should be built as a port. This can be 
done one of two ways:

1. Implement wxWebView CEF backend and set wxWidgets as a dependency
2. Build wxWidgets as a port with both Edge and CEF.

The first option is simpler and cleaner, but this could change in the 
future.