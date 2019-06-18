# cmake demo #
------
------
## cpp code ##
	/* Hello */
	class HELLOWORLD_EXPORT Hello
	{
	public:
	    void sayHello();
	};

	/* Hello.cpp */
	#include <iostream>
	#include "Hello"
	void Hello::sayHello()
	{
	    std::cout << "Hello CMake!" << std::endl;
	}

	/* test.cpp */
	#include <Hello>
	int main( int argc, char** argv )
	{
	    Hello obj;
	    obj.sayHello();
	    return 0;
	}


## cmake code ##

**根目录下的CMakeLists.txt**

	PROJECT( HelloWorld )
	CMAKE_MINIMUM_REQUIRED( VERSION 2.4.7 )
	ADD_SUBDIRECTORY( HelloLib )
	ADD_SUBDIRECTORY( Test )

**库工程就建立**

	ADD_DEFINITIONS( -DHELLOWORLD_LIBRARY ) #宏定义
	ADD_LIBRARY( HelloLib SHARED
	    Hello.cpp
	)

注意：
> ( 库名称 库类型 源文件 )
> 类型为SHARED，即动态链接库（.dll或.so），而STATIC自然就表示生成静态链接库了（.lib或.a）


**可执行工程**

	INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/HelloLib )
	ADD_EXECUTABLE( Test
	    test.cpp
	)
	TARGET_LINK_LIBRARIES( Test HelloLib )






