# CMAKE #

## web ##

https://cmake.org/cmake/help/v3.4/manual/cmake-buildsystem.7.html#cmake-buildsystem-7

## BASE ##
https://www.cnblogs.com/rickyk/p/3875334.html
https://www.cnblogs.com/lidabo/p/3976947.html


**CMakeLists.txt**

> 这是CMake脚本代码和配置参数的载体

**CMake基本宏**

|宏的名字|解释|type value|
|::|::|::|
|CMAKE_BUILD_TYPE|编译类型|Debug、Release、RelWithDebInfo和MinSizeRel|
|CMAKE_MODULE_PATH|设置搜索CMakeModules模块（.cmake）的额外路径|..|
|CMAKE_INCLUDE_PATH|设置自动查找依赖工程头文件的额外路径|默认为脚本中指定的搜索路径|
|CMAKE_LIBRARY_PATH|设置自动查找依赖工程库文件的额外路径|默认为脚本中指定的搜索路径|
|CMAKE_INSTALL_PREFIX|设置安装时的路径。这是一个重要的配置参数|默认的安装目录为/usr/local/或者C:/Program Files/|
|EXECUTABLE_OUTPUT_PATH|输出exe|当前目录|
|LIBRARY_OUTPUT_PATH|输出lib|当前目录|
**CMake缓存信息**

	cmake . -DCMAKE_BUILD_TYPE=Release
    cmake –C CMakeCache.txt
	

**CMake交叉编译配置**
> 1. CMAKE_SYSTEM_NAME
> 2. CMAKE_C_COMPILER
> 3. CMAKE_CXX_COMPILER
> 4. CMAKE_FIND_ROOT_PATH
> 5. CMAKE_FIND_ROOT_PATH_MODE_PROGRAM
> 6. CMAKE_FIND_ROOT_PATH_MODE_LIBRARY
> 7. CMAKE_FIND_ROOT_PATH_MODE_INCLUDE
> 8. BOOST_ROOT
> 9. QT_QMAKE_EXECUTABLE


**demo**

	# this is required
	SET(CMAKE_SYSTEM_NAME Linux)
	
	# specify the cross compiler
	SET(CMAKE_C_COMPILER   /opt/arm/usr/bin/ppc_74xx-gcc)
	SET(CMAKE_CXX_COMPILER /opt/arm/usr/bin/ppc_74xx-g++)
	
	# where is the target environment 
	SET(CMAKE_FIND_ROOT_PATH  /opt/arm/ppc_74xx /home/rickk/arm_inst)
	
	# search for programs in the build host directories (not necessary)
	SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
	# for libraries and headers in the target directories
	SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
	SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
	
	# configure Boost and Qt
	SET(QT_QMAKE_EXECUTABLE /opt/qt-embedded/qmake)
	SET(BOOST_ROOT /opt/boost_arm)

