------------------------------------------------------------
  HWComposer GUNIT/Gmock/googletest

  To simplify the environment setup and build process,
  CMakeLists.txt in this repository has been refactored
  based upon the CMakeLists.txt found under: 
  https://github.com/cpp-testing/gunit/

  This repository contains the Googletest and GMock cmake
  directives needed for automating the cloning of 
  Googletest and GMock repositories  It also omits 
  Gherkin which is not required for HWComposer development.
 
------------------------------------------------------------
#
# Install dependencies (one time)
sudo apt-get install jq
sudo apt-get install cmake

#
# Include library
export PATH=$PATH:/usr/lib/x86_64-linux-gnu/

#
# Clone HWC GUnit
git clone https://github.com/MicheleL-Intel/GUnit-hwc.git

#
# Clean build
./clean.sh

#
#Compile and execute tests
cd ~/GUnit-hwc
cmake -H. -Bout
cmake --build out

#
# Run all tests
./runAllTests.sh
