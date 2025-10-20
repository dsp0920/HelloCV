# 一、cmake安装
## 1.建立cmake文件夹，将安装包移动至该文件下
解压安装包

```bash
tar -zxvf cmake-3.31.9.tar.gz
```

结果如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760885621573-fb0ebfae-fd57-4fc4-b202-0b630221ad13.png)

## 2.安装环境依赖
输入以下指令：

```bash
sudo apt-get install g++
sudo apt-get install openssl
sudo apt-get install libssl-dev
sudo apt-get install build-essential
```

运行结果如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760885642639-e83ff1dd-5d59-40cb-a200-2d95cfca9098.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760885975397-1d33af3e-d5fa-46d7-8714-11447c3262ab.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760885746499-de66f457-1928-4962-8203-eab856240b9d.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760885798809-f27bff50-948d-41aa-9a52-d1019fccfbcc.png)

### 3.进入cmake包文件，执行引导脚本
```bash
#进入cmake包文件
cd cmake-3.31.9
#查看文件内容
ls
#执行引导脚本
./bootstrap
```

结果如图所示：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760923001591-75bf8470-4773-4cb7-856b-51f33552c7de.png)

## 4.执行编译构建
```bash
make -j8
#-j8 指用8个线程进行编译
```

运行结果如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760923225032-a9da405b-0e78-42a3-a18f-6b8d4127f660.png)

## 5.检验安装
终端输入以下命令：

```bash
cmake -version
#查看cmake版本信息
```

结果如图

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760934803844-a371fa51-7365-4172-b1cc-1f1f8dafa6c0.png)

至此，CMake安装配置完毕。

# 二、cmake学习
## 1.CMake的作用及工作机制
## 1）CMake的作用
<font style="color:rgb(78, 161, 219) !important;">CMak</font><font style="background-color:#FAFAFA;">e </font><font style="background-color:#FFFFFF;">是一个跨平台的构建系统工具，广泛应用于 C/C++ 项目的构建和管理。CMake 的主要目的是通过抽象化构建流程，让开发者可以编写一次构建脚本，然后在不同平台上生成相应的构建文件（如 Makefile、Visual Studio 工程等），从而实现跨平台的构建支持。</font>

## 2）CMake工作机制
当我们在用编辑器编写简单程序代码时，直接生成的文件就是源文件（如main.c），接着用编译器（如gcc）将源代码翻译成二进制指令文件，即目标文件（如main.o），最后用链接器将目标文件连接到一块，生成可执行文件（如 .exe）。

但是随着项目工程的不断扩大，如果对于每个源文件都用gcc命令去编译，很容易混乱且工作量大，所以出现了make工具。make工具可以看成一个只能的批处理工具，本身不具有编译和连接功能。而它的批处理功能，是通过调用makefile文件中用户指定的命令来进行编译和连接的。简单来说，make工具就像指挥家，makefile文件就像乐谱，指挥家根据乐谱指挥整个乐团如何演唱，而make工具根据makefile文件中的指令来进行编译和链接。而makefile文件中就包含了调用gcc（或者其他编译器）去编译某个源文件的命令。所以，一些简单的工程，只需要编写makefile中的指令就能完成系统构建。但是，如果当工程非常大非常复杂的时候，手写makefile非常麻烦，而且换个平台后就要修改，于是就出现了CMake。

CMake可以更加简单地生成makefile文件给make用。CMake还可以跨平台生成对应平台能用的makefile，这样就不需要我们再去自己修改makefile文件了。

但是CMAake根据什么来生成makefile呢？它要根据一个叫CMakeLists.txt文件（组态档）去自动生成makefile。所以现在程序员构建系统只需要编写CMakeLists.txt文件就行了。

## 2.CMakeLists.txt 文件
CMakeLists.txt文件是CMake文件的核心配置文件，作用是告诉CMake“如何生成编译所需要的Makefile文件”，是连接源码和编译器的桥梁，一般放在项目的根目录。

CMakeList.txt不直接编译代码，而是通过清晰的指令，让CMake自动适应不同的系统、不同的编译器，生成对应的构建文件，最终再用这些构建文件完成编译。

### 核心作用与基础指令
#### （1）指定CMake最低版本：
确保使用的CMake支持后续指令，避免兼容性问题。

`cmake_minimun_required(VERSION <版本号>)`

```cmake
cmake_minimun_required(VERSION 3.10)   #要求CMake版本不低于3.10
```

#### （2）定义项目名称：
标识当前文件，可指定支持的编程语言

`project(<项目名> [LANGUAGES <语言列表>])`

```cmake
project(MyFirstPrject LANGUAGES C CXX)
#"MyFirstProject"是项目名称
#"LANGUAGES C CXX"支持c语言和c++
```

#### （3）添加可执行文件/库
告诉CMake要编译哪些源代码文件，生成可执行程序或动态/静态库

生成可执行文件：

`add_executable(<可执行文件名> <源码文件列表>)`

```cmake
add_executable(my_app main.c utils.c)
#执行后，生成可执行文件名 my_app ,依赖源代码文件 main.c utils.c
```

	生成静态库：

`add_library(math STATIC math.c)`

```cmake
add_library(<库名> <库类型> <源码文件列表>)
#库名 math ，库类型 STATIC （静态库），依赖源码 math.c
```

STATIC处为库类型名，库类型可选`STATIC`（静态库，后缀常为`.a`（Linux）、`.lib`（windows）），`SHARED`（动态库，后缀常为`.so`（Linux）、`.dll`（Windows））

默认生成静态库。

#### (4)链接依赖库：
若项目依赖其他库，需指定连接关系：

`target_link_libraries(<目标名> <依赖库列表>)`

```cmake
target_link_libraries(my_app PRIVATE math pthread)
#让 my_app 链接 math 库和 pthread 库
```

#### (5)指定头文件的搜索目录
当源码中使用`#include "xxx.h"`时，CMake会在这些指定的目录中查找对应的头文件。

`include_directories(<头文件目录列表>)`

例如，当头文件都放在`include`目录下时，让编译器能够找到这些文件：

```bash
include_directories(include)
```

#### （6）将指定的子目录纳入CMake的构建流程。
CMake会进入该子目录，查找其中的`CMakeLists.txt`并执行里面的指令，通过用于多模块、多目录的大型项目管理。

`add_subdirectory(<子目录名>)`

如，项目有一个`src`子目录，里面有自己的`CMakeLists.txt`，要让CMake处理这个子目录：

```cmake
add_subdirectory(src)
```

#### (7)为特定目标（可执行文件或库）指定头文件搜索目录，且通过<作用范围>控制这些头文件目录的可见性。
相比`include_directories`，它的作用范围更精准。

`target_include_directories(<目标名> <作用范围> <头文件目录列表>)`

如，让`mylib`库自身能在`include`目录找到头文件，且依赖`mylib`的其他目标也能使用这些头文件：

```cmake
target_include_directories(mylib PUBLIC include)
```

`<控制范围>`控制这些头文件目录的可见性（`PUBLIC`：目标自身及依赖该目标的其他目标都能使用；`PRIVATE`：仅目标自身能使用；`INTERFACE`：仅依赖该目标的其他目标能使用。）

#### （8）查找系统中是否安装了第三方库/包
`find_package(<包名> [指定所需的包版本] [REQUIRED] [COMPONENTS 包的特定组件名列表])`

如果指定`REQUIRED`，表示该库是必须的，若找不到则CMake会报错并终止构建。找到后，通常会生成对应的变量（`OpenCV_INCLUDE_DIRS`、`OpenCV_LIBRARIES`)，用于后续头文件和库的连接。

如，查找OpenCV库，且该库为必须依赖：

```cmake
find_package(OpenCV REQUIRED)
# 之后可通过${OpenCV_INCLUDE_DIRS} 和${OpenCV_LIBRARIES} 来使用 OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(myapp${OpenCV_LIBRARIES})

```

## 3.源码外构建
<font style="color:rgb(77, 77, 77);">CMake内部构建，就是在当前工程目录中进行编译，但缺点是会产生很多的临时编译文件，容易污染工程，不方便清理。而外部构建就是编译生成的文件统一放在一个目录中，不会对</font><font style="color:rgb(78, 161, 219) !important;">源代码</font><font style="color:rgb(77, 77, 77);">工程有任何影响，清理也只需要删除这个编译目录。所以强烈推荐使用外部构建，外部构建的一般步骤如下：</font>

### <font style="color:rgb(77, 77, 77);">（1）创建并进入编译目录</font>
在项目根目录中新建一个`build`目录，CMake生成的中间文件都会存放在此目录中。

项目终端中输入

```bash
mkdir build  #新建build目录
cd build  #进入build目录
```

### （2）进行cmake编译
进入`build`目录后，终端输入：

```bash
cmake ..  #把编译的文件放在 /build 路径下
```

即根据源码目录中的`CMakeLists.txt`文件生成构建所需的文件（如Makefile）。`..`表示父目录

### （3）构建并生成可执行文件
继续在刚才的目录下执行：

```bash
make
```

`make`会读取`cmake`在`build`目录中生成的构建文件，然后按照其中的规则，编译源码生成最终的程序（存放在`build`目录下）。

## 4.安装与配置
<font style="color:rgba(0, 0, 0, 0.85);">在 CMake 中，</font>`<font style="color:rgba(0, 0, 0, 0.85);">install()</font>`<font style="color:rgba(0, 0, 0, 0.85);"> 指令是用于</font><font style="color:rgb(0, 0, 0) !important;">定义项目构建完成后，如何将编译生成的文件（可执行文件、库文件、头文件等）安装（复制）到指定的系统路径</font><font style="color:rgba(0, 0, 0, 0.85);">的关键指令。</font>

<font style="color:rgba(0, 0, 0, 0.85);">当我们通过 CMake 完成项目的编译构建后，通常需要将最终的产物（比如可执行程序、库、头文件等）部署到系统中便于使用的位置（比如系统的</font>`<font style="color:rgba(0, 0, 0, 0.85);">bin</font>`<font style="color:rgba(0, 0, 0, 0.85);">目录放可执行文件</font>`<font style="color:rgba(0, 0, 0, 0.85);">lib</font>`<font style="color:rgba(0, 0, 0, 0.85);"> 目录放库文件、</font>`<font style="color:rgba(0, 0, 0, 0.85);">include</font>`<font style="color:rgba(0, 0, 0, 0.85);"> 目录放头文件）。</font>`<font style="color:rgba(0, 0, 0, 0.85);">install()</font>`<font style="color:rgba(0, 0, 0, 0.85);"> 指令就是用来指定这些文件 “安装” 时的目标路径和规则的。</font>

#### <font style="color:rgba(0, 0, 0, 0.85);">（1）安装可执行文件</font>
`RUNTIME`对应Windows和Unix-like系统的可执行文件

```bash
# TARGETS 后接 CMake 中 add_executable() 定义的目标名
install(TARGETS 可执行程序目标名
        RUNTIME DESTINATION bin  # 安装到 ${CMAKE_INSTALL_PREFIX}/bin（默认 /usr/local/bin）
        COMPONENT Runtime  # 可选：分组安装（如区分“运行组件”“开发组件”）
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ  # 可选：设置文件权限
                    GROUP_EXECUTE GROUP_READ
                    WORLD_EXECUTE WORLD_READ)

```

#### （2）安装配套配置文件（如程序运行所需的 config.ini、json 配置等）
```cmake
install(FILES 源码目录下的配置文件路径（如 config/config.ini）
        DESTINATION etc/项目名  # 安装到 ${CMAKE_INSTALL_PREFIX}/etc/项目名（便于集中管理配置）
        COMPONENT Runtime)
```

#### （3）安装头文件（如项目核心头文件 my_project.h）
```cmake
install(FILES 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/my_project.h  # 源码中头文件的绝对路径（用变量确保跨平台）
        DESTINATION include/项目名  # 安装到 ${CMAKE_INSTALL_PREFIX}/include/项目名（加项目名避免与其他库头文件冲突）
        COMPONENT Development  # 归为“开发组件”，仅供其他项目编译时引用
        PERMISSIONS OWNER_READ OWNER_WRITE  # 可选：设置头文件权限（默认已有合理权限，可省略）
                    GROUP_READ
                    WORLD_READ)

```

