find /Applications/Xcode_* -maxdepth 0 -type d ! -name 'Xcode_${{ env.XC_VERSION }}.app' -exec rm -rf {} \;
brew install autoconf autoconf-archive automake libtool cmake make bzip2