# Run ORB-SLAM3

```bash
./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt Examples/Monocular/EuRoC.yaml ./MH_01_easy Examples/Monocular/EuRoC_TimeStamps/MH01.txt
```
# Cross compiled ORB Slam 3

## steps to Cross-Compile OpenCV for ARM

```bash
sudo apt-get update
sudo apt-get install build-essential cmake git unzip pkg-config \
libjpeg-dev libpng-dev libtiff-dev \
libavcodec-dev libavformat-dev libswscale-dev \
libv4l-dev libxvidcore-dev libx264-dev \
libgtk-3-dev libatlas-base-dev gfortran \
python3-dev

git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git

cd opencv
mkdir build
cd build

```
```bash
cd ..

nano toolchain-aarch64.cmake

```
### add followrinf to toolchain file

```bash

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)

# Specify the cross compiler
SET(CMAKE_C_COMPILER   /usr/bin/aarch64-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)

# Where is the target environment
SET(CMAKE_FIND_ROOT_PATH  /usr/aarch64-linux-gnu)

# Search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# Search for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

```
### run follwing commad
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain-aarch64.cmake \
      -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/path/to/install/opencv/aarch64 ..
```
