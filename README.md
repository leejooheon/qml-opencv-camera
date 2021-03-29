qml-opencv-camera
============

qml-opencv-camera is an example of camera access using C++'s OpenCV and QML.

Both IP camera and general camera can be used.

  - Ubuntu `18.04`
  - Qt `5.15.2`, `5.14.2`
  - OpenCV `3.4.10`


## Usage
Modify the 17th line (normal_url) of camera.cpp to suit your camera.
```
const std::string normal_url = "rtsp://admin:qwe1010@192.168.1.6:554/live2.sdp"; // origin code
```


## apt-packages for QtCreator
```
$ sudo apt install build-essential git cmake software-properties-common
```

## video codec
```
$ sudo apt install ubuntu-restricted-extras
```

# opencv
### Create a working directory named opencv
1. Download opencv source
```
$ cd ANY_WHERE
$ mkdir opencv
$ cd opencv

# Download sources
$ wget -O opencv-3.4.10.zip https://github.com/opencv/opencv/archive/3.4.10.zip
$ wget -O opencv_contrib-3.4.10.zip https://github.com/opencv/opencv_contrib/archive/3.4.10.zip

# Unpack
$ unzip opencv-3.4.10.zip
$ unzip opencv_contrib-3.4.10.zip
```

2. Build using cmake
```
# Create a build directory
$ mkdir build && cd build

# Run CMake
$ cmake \
-D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D BUILD_opencv_python2=OFF \
-D BUILD_opencv_python3=ON \
-D BUILD_WITH_DEBUG_INFO=OFF \
-D BUILD_DOCS=OFF \
-D INSTALL_C_EXAMPLES=OFF \
-D BUILD_EXAMPLES=OFF \
-D BUILD_TESTS=OFF \
-D BUILD_PERF_TESTS=OFF \
-D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib-3.4.10/modules \
-D WITH_FFMPEG=ON \
-D WITH_V4L=OFF \
-D WITH_XINE=OFF \
-D WITH_GSTREAMER=OFF \
-D BUILD_NEW_PYTHON_SUPPORT=ON \
../opencv-3.4.10/ 2>&1 | tee cmake_messages.txt
```

3. Compile and install
```
# find out the number of CPU cores in your machine
$ nproc

# substitute 2 after -j by the output of nproc
$ make -j2 2>&1 | tee build_messages.txt
$ sudo make install
$ sudo ldconfig

# If the output of next command is '3.4.10' then it's ok!
$ pkg-config --modversion opencv
```
