<h1 id="B5CCH">一、Ubuntu的vs code 中配置open CV</h1>
<h2 id="qk7bv">1.确认OpenCV的安装</h2>
终端执行指令`pkg-config --modversion opencv4`，确认opencv安装。结果如下图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1761315889610-1fffe459-042d-4255-a631-d38ca759bec1.png)

输出版本号，说明安装正常。

<h2 id="zIMsd">2.创建项目结构</h2>
在vscode中打开一个空文件，这里命名为`Trafficlight`，创建如下结构：

```cmake
Trafficlight/
├── CMakeLists.txt  # CMake 配置文件（核心）
├── src/            # 源代码目录
│   └── main.cpp    # 测试代码
└── build/          # 编译输出目录（自动生成或手动创建）
```

<h2 id="mZs5J">3.编写CMakeLists.txt</h2>
在项目根目录创建`CMakeLists.txt`，内容如下：

```cmake
# 要求的 CMake 最低版本
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(Trafficlight)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 OpenCV 库（自动定位安装路径）
find_package(OpenCV 4 REQUIRED)

# 打印 OpenCV 信息（可选，用于验证）
message(STATUS "OpenCV 版本: ${OpenCV_VERSION}")
message(STATUS "OpenCV 头文件路径: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV 库路径: ${OpenCV_LIBS}")

# 添加源代码（将 src/main.cpp 加入编译）
add_executable(${PROJECT_NAME} src/main.cpp)

# 链接 OpenCV 库到可执行文件
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
```

<h2 id="f6lef">4.编写测试代码</h2>
在`main.cpp`中编写测试代码：

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat img = imread("test.jpg");  // 图像放在项目根目录或指定绝对路径
    if (img.empty()) {             // 这里将图片放在了build目录下  
        cerr << "无法读取图像！" << endl;
        return -1;
    }

    imshow("Test", img);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
```

<h2 id="xCUNT">5.vs code 中使用CMake编译运行</h2>
<h3 id="cwVUs">（1）配置CMake</h3>
按`ctrl+shift+P`打开命令面板，输入`CMake:Configure`。首次配置会提示选择编译器，选择`GCC XXX.XX`。配置成功后，vs code会自动在`build`目录生成`Makefile`等编译文件。

<h3 id="gmzlk">（2）编译项目</h3>
终端中进入`build`目录，手动`make`编译。

<h3 id="ox5G9">（3）运行程序</h3>
命令面板输入`CMake:Run Without Debugging`直接运行。

或者在`build`目录下终端运行`./Trafficlight`

最终运行结果为：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1761416422948-ddc7e8e6-07d9-418b-80ff-3a78647f157c.png)

至此，在vs code中已经配置好了opencv。

<h1 id="SGNdf">二、openCV的初步学习</h1>
参考学习来源：[4小时学会OPENCV(C++)_包含三个演示案例_Win/Mac_2021](https://www.bilibili.com/video/BV1UU4y1x7oR/?from=search&seid=6885553110271687384&spm_id_from=333.337.0.0&vd_source=2645f0a74795536f33bdfc4f415062e2)

<h2 id="HtlkB">1.几个头文件</h2>
<h3 id="jDVOA">（1）`#include <opencv2/imgcodecs.hpp>`</h3>
引入OpenCV中用于图像编码/解码的模块，比如读取不同格式的图像文件（如JPG、PNG等）

<h3 id="SZMg2">（2）`#include <opencv2/highgui.hpp>`</h3>
引入OpenCV中用于高级图形用户界面的模块，比如创建显示图像的窗口、处理鼠标键盘事件等）

<h3 id="BqvZv">（3）`#include <opencv2/imgproc.hpp>`</h3>
引入OpenCV中用于图像处理的模块，包含各种图像滤波、几何变换、形状分析等功能。



<h2 id="T5LUt">2.图像读取与显示</h2>
<h3 id="LA2md">（1）`Mat`对象</h3>
`Mat`是Matrix（矩阵）的缩写。主要作用是<font style="color:rgb(0, 0, 0);">存储图像像素数据（包括灰度图、彩色图、带 Alpha 通道的图像等）、表示数学矩阵（如用于线性代数运算的矩阵）。</font>

`<font style="color:rgba(0, 0, 0, 0.85) !important;">Mat</font>`<font style="color:rgb(0, 0, 0);"> 包含两部分数据：</font>

**<font style="color:rgb(0, 0, 0) !important;">头部（Header）</font>**<font style="color:rgb(0, 0, 0);">：存储矩阵的尺寸、通道数、数据类型、引用计数等元信息。</font>

**<font style="color:rgb(0, 0, 0) !important;">数据块（Data）</font>**<font style="color:rgb(0, 0, 0);">：存储实际的像素值或矩阵元素，可通过内存共享（引用计数）实现高效复制。</font>

| **<font style="color:rgb(0, 0, 0) !important;">参数</font>** | **<font style="color:rgb(0, 0, 0) !important;">说明</font>** | **<font style="color:rgb(0, 0, 0) !important;">示例 / 获取方式</font>** |
| :--- | :--- | :--- |
| **<font style="color:rgb(0, 0, 0) !important;">尺寸（Size）</font>** | <font style="color:rgba(0, 0, 0, 0.85) !important;">包含矩阵的行数（</font>`<font style="color:rgb(0, 0, 0);">rows</font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;">）和列数（</font>`<font style="color:rgb(0, 0, 0);">cols</font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;">），即图像的高和宽。</font> | `<font style="color:rgb(0, 0, 0);">cv::Size size = mat.size();</font>`<br/>`<font style="color:rgb(0, 0, 0);">int rows = mat.rows;</font>`<br/>`<font style="color:rgb(0, 0, 0);">int cols = mat.cols;</font>` |
| **<font style="color:rgb(0, 0, 0) !important;">数据类型</font>** | <font style="color:rgba(0, 0, 0, 0.85) !important;">用</font><font style="color:rgba(0, 0, 0, 0.85) !important;"> </font>`<font style="color:rgb(0, 0, 0);">CV_<位数><符号><通道数></font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;"> </font><font style="color:rgba(0, 0, 0, 0.85) !important;">表示，如</font><font style="color:rgba(0, 0, 0, 0.85) !important;"> </font>`<font style="color:rgb(0, 0, 0);">CV_8UC3</font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;">（8 位无符号整数、3 通道）。</font> | `<font style="color:rgb(0, 0, 0);">int type = mat.type();</font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;">可通过</font><font style="color:rgba(0, 0, 0, 0.85) !important;"> </font>`<font style="color:rgb(0, 0, 0);">CV_MAT_CN(type)</font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;"> </font><font style="color:rgba(0, 0, 0, 0.85) !important;">取通道数，</font>`<font style="color:rgb(0, 0, 0);">CV_MAT_DEPTH(type)</font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;"> </font><font style="color:rgba(0, 0, 0, 0.85) !important;">取深度</font> |
| **<font style="color:rgb(0, 0, 0) !important;">通道数（Channels）</font>** | <font style="color:rgba(0, 0, 0, 0.85) !important;">单通道（灰度图）为 1，三通道（彩色图）为 3，四通道（带 Alpha 通道）为 4 等。</font> | `<font style="color:rgb(0, 0, 0);">int channels = mat.channels();</font>` |
| **<font style="color:rgb(0, 0, 0) !important;">深度（Depth）</font>** | <font style="color:rgba(0, 0, 0, 0.85) !important;">像素值的存储位数，如</font><font style="color:rgba(0, 0, 0, 0.85) !important;"> </font>`<font style="color:rgb(0, 0, 0);">CV_8U</font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;">（8 位无符号）、</font>`<font style="color:rgb(0, 0, 0);">CV_32F</font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;">（32 位浮点）等。</font> | `<font style="color:rgb(0, 0, 0);">int depth = mat.depth();</font>` |


+ **<font style="color:rgb(0, 0, 0) !important;">尺寸和通道数</font>**<font style="color:rgb(0, 0, 0);">：决定了图像的分辨率和色彩模式（如 640×480 三通道彩色图）。</font>
+ **<font style="color:rgb(0, 0, 0) !important;">数据类型和深度</font>**<font style="color:rgb(0, 0, 0);">：影响像素值的范围和精度（如</font><font style="color:rgb(0, 0, 0);"> </font>`<font style="color:rgb(0, 0, 0);">CV_8UC1</font>`<font style="color:rgb(0, 0, 0);"> </font><font style="color:rgb(0, 0, 0);">灰度图的像素值范围是 0~255，</font>`<font style="color:rgb(0, 0, 0);">CV_32FC3</font>`<font style="color:rgb(0, 0, 0);"> </font><font style="color:rgb(0, 0, 0);">彩色图可存储浮点型颜色值）。</font>
+ **<font style="color:rgb(0, 0, 0) !important;">内存参数</font>**<font style="color:rgb(0, 0, 0);">：</font>`<font style="color:rgb(0, 0, 0);">Mat</font>`<font style="color:rgb(0, 0, 0);"> 的高效内存管理（引用计数、数据共享）依赖这些底层参数，避免了不必要的内存拷贝，提升了性能。</font>

```cpp
cv::Mat mat(rows, cols, type);  // 如 cv::Mat(480, 640, CV_8UC3);
cv::Mat mat(rows, cols, type, cv::Scalar(0, 255, 0));  // 三通道时表示 BGR 值
```

<h3 id="SsQZe">（2）`imread()`函数</h3>
```cpp
cv::Mat imread(const std::string& filename, int flags = cv::IMREAD_COLOR);
```

`filename`图像文件的路径，<font style="color:rgba(0, 0, 0, 0.85);">支持绝对路径、相对路径（相对于可执行文件运行目录）。</font><font style="color:rgb(0, 0, 0);">函数通过文件内容（而非扩展名）识别图像格式。</font>

`<font style="color:rgb(0, 0, 0);">flags</font>`<font style="color:rgb(0, 0, 0);">读取模式，可选。</font>

| `<font style="color:rgb(0, 0, 0);">IMREAD_UNCHANGED</font>` | `<font style="color:rgb(0, 0, 0);">-1</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">按原图格式读取（包含 Alpha 通道，若存在）</font> |
| :--- | :--- | :--- |
| `<font style="color:rgb(0, 0, 0);">IMREAD_GRAYSCALE</font>` | `<font style="color:rgb(0, 0, 0);">0</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">强制转换为单通道灰度图</font> |
| `<font style="color:rgb(0, 0, 0);">IMREAD_COLOR</font>` | `<font style="color:rgb(0, 0, 0);">1</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">强制转换为三通道 BGR 彩色图（默认值）</font> |
| `<font style="color:rgb(0, 0, 0);">IMREAD_ANYDEPTH</font>` | `<font style="color:rgb(0, 0, 0);">2</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">保留图像深度（如 16 位 / 32 位图像，否则转为 8 位）</font> |
| `<font style="color:rgb(0, 0, 0);">IMREAD_ANYCOLOR</font>` | `<font style="color:rgb(0, 0, 0);">4</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">按图像实际通道数读取（不超过 3 通道）</font> |
| `<font style="color:rgb(0, 0, 0);">IMREAD_REDUCED_GRAYSCALE_2</font>` | `<font style="color:rgb(0, 0, 0);">16</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">灰度图且尺寸缩小 1/2</font> |
| `<font style="color:rgb(0, 0, 0);">IMREAD_REDUCED_COLOR_2</font>` | `<font style="color:rgb(0, 0, 0);">17</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">彩色图且尺寸缩小 1/2</font> |


<h3 id="mRCOK">（3）`imshow()`函数</h3>
```cpp
void imshow(const std::string& winname, const cv::Mat& mat);
```

参数说明：

| `**<font style="color:rgb(0, 0, 0);">winname</font>**` | `<font style="color:rgb(0, 0, 0);">const std::string&</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">窗口名称，需唯一。后续对该窗口的操作（如关闭、调整大小）需使用相同名称。</font> |
| :--- | :--- | :--- |
| `**<font style="color:rgb(0, 0, 0);">mat</font>**` | `<font style="color:rgb(0, 0, 0);">const cv::Mat&</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">待显示的</font><font style="color:rgba(0, 0, 0, 0.85) !important;"> </font>`<font style="color:rgb(0, 0, 0);">Mat</font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;"> </font><font style="color:rgba(0, 0, 0, 0.85) !important;">图像对象，支持单通道（灰度图）、三通道（BGR 彩色图）、四通道（带 Alpha 通道）。</font> |


+ <font style="color:rgb(0, 0, 0);">单通道</font><font style="color:rgb(0, 0, 0);"> </font>`<font style="color:rgb(0, 0, 0);">Mat</font>`<font style="color:rgb(0, 0, 0);">（灰度图）：显示为灰度图像。</font>
+ <font style="color:rgb(0, 0, 0);">三通道</font><font style="color:rgb(0, 0, 0);"> </font>`<font style="color:rgb(0, 0, 0);">Mat</font>`<font style="color:rgb(0, 0, 0);">：仅支持</font><font style="color:rgb(0, 0, 0);"> </font>**<font style="color:rgb(0, 0, 0) !important;">BGR 格式</font>**<font style="color:rgb(0, 0, 0);">（OpenCV 默认彩色格式），若输入 RGB 格式图像，需先通过</font><font style="color:rgb(0, 0, 0);"> </font>`<font style="color:rgb(0, 0, 0);">cvtColor</font>`<font style="color:rgb(0, 0, 0);"> </font><font style="color:rgb(0, 0, 0);">转换为 BGR 再显示。</font>
+ <font style="color:rgb(0, 0, 0);">四通道 </font>`<font style="color:rgb(0, 0, 0);">Mat</font>`<font style="color:rgb(0, 0, 0);">（如带 Alpha 通道的 PNG）：仅在窗口支持 Alpha 透明时生效（需特殊配置，默认通常忽略 Alpha 通道）。</font>

<font style="color:rgba(0, 0, 0, 0.85);">若需创建可调整大小的窗口，需在 </font>`<font style="color:rgba(0, 0, 0, 0.85) !important;">imshow</font>`<font style="color:rgba(0, 0, 0, 0.85);"> 前手动调用 </font>`<font style="color:rgba(0, 0, 0, 0.85) !important;">namedWindow</font>`<font style="color:rgba(0, 0, 0, 0.85);"> 设置窗口属性：</font>

```cpp
namedWindow("Resizable Window", WINDOW_NORMAL);  // 创建可调整大小的窗口
imshow("Resizable Window", img);
waitKey(0);
```

<font style="color:rgba(0, 0, 0, 0.5);"></font>

**<font style="color:rgb(0, 0, 0) !important;">必须配合 </font>**`**<font style="color:rgb(0, 0, 0);">waitKey</font>**`**<font style="color:rgb(0, 0, 0) !important;"> 函数</font>**`<font style="color:rgba(0, 0, 0, 0.85);">imshow</font>`<font style="color:rgba(0, 0, 0, 0.85);"> 显示窗口后会立即返回，若不调用 </font>`<font style="color:rgba(0, 0, 0, 0.85);">waitKey</font>`<font style="color:rgba(0, 0, 0, 0.85);">，窗口会瞬间闪退。</font>

<font style="color:rgba(0, 0, 0, 0.85);">可通过不同的 </font>`<font style="color:rgba(0, 0, 0, 0.85);">winname</font>`<font style="color:rgba(0, 0, 0, 0.85);"> 创建多个窗口，分别显示不同图像，关闭时需调用 </font>`<font style="color:rgba(0, 0, 0, 0.85);">destroyAllWindows()</font>`<font style="color:rgba(0, 0, 0, 0.85);"> 或 </font>`<font style="color:rgba(0, 0, 0, 0.85);">destroyWindow(winname)</font>`<font style="color:rgba(0, 0, 0, 0.85);">：</font>

```cpp
imshow("Window1", img1);
imshow("Window2", img2);
waitKey(0);
destroyAllWindows();  // 关闭所有窗口
```

<h3 id="qLtcZ"><font style="color:rgba(0, 0, 0, 0.85);">（4）</font>`<font style="color:rgba(0, 0, 0, 0.85);">waitKey</font>`函数</h3>
```cpp
int waitKey(int delay = 0);
```

| `**<font style="color:rgb(0, 0, 0);">delay</font>**` | `<font style="color:rgb(0, 0, 0);">int</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">等待时间（单位：毫秒），决定函数的阻塞行为：</font><br/><font style="color:rgba(0, 0, 0, 0.85) !important;">- </font>`<font style="color:rgb(0, 0, 0);">delay ≤ 0</font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;">：无限阻塞，直到用户按下任意键后返回。</font><br/><font style="color:rgba(0, 0, 0, 0.85) !important;">- </font>`<font style="color:rgb(0, 0, 0);">delay > 0</font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;">：阻塞</font><font style="color:rgba(0, 0, 0, 0.85) !important;"> </font>`<font style="color:rgb(0, 0, 0);">delay</font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;"> </font><font style="color:rgba(0, 0, 0, 0.85) !important;">毫秒后自动返回，期间若有按键按下则立即返回。</font> |
| :--- | :--- | :--- |


<font style="color:rgb(0, 0, 0);">若在等待期间</font>**<font style="color:rgb(0, 0, 0) !important;">有按键按下</font>**<font style="color:rgb(0, 0, 0);">：返回被按下按键的 </font>**<font style="color:rgb(0, 0, 0) !important;">ASCII 码</font>**<font style="color:rgb(0, 0, 0);">（如按下 </font>`<font style="color:rgb(0, 0, 0);">ESC</font>`<font style="color:rgb(0, 0, 0);"> 键返回 </font>`<font style="color:rgb(0, 0, 0);">27</font>`<font style="color:rgb(0, 0, 0);">，按下 </font>`<font style="color:rgb(0, 0, 0);">A</font>`<font style="color:rgb(0, 0, 0);"> 键返回 </font>`<font style="color:rgb(0, 0, 0);">65</font>`<font style="color:rgb(0, 0, 0);">）。若</font>**<font style="color:rgb(0, 0, 0) !important;">无按键按下且等待超时</font>**<font style="color:rgb(0, 0, 0);">（仅 </font>`<font style="color:rgb(0, 0, 0);">delay > 0</font>`<font style="color:rgb(0, 0, 0);"> 时）：返回 </font>`<font style="color:rgb(0, 0, 0);">-1</font>`<font style="color:rgb(0, 0, 0);">。</font>

<font style="color:rgba(0, 0, 0, 0.85);">若先调用 </font>`<font style="color:rgba(0, 0, 0, 0.85);">waitKey</font>`<font style="color:rgba(0, 0, 0, 0.85);"> 再调用 </font>`<font style="color:rgba(0, 0, 0, 0.85);">imshow</font>`<font style="color:rgba(0, 0, 0, 0.85);">，窗口仍会闪退，因为 </font>`<font style="color:rgba(0, 0, 0, 0.85);">waitKey</font>`<font style="color:rgba(0, 0, 0, 0.85);"> 需关联已创建的窗口事件。</font>

<font style="color:rgba(0, 0, 0, 0.85);">无论创建多少个窗口，一个 </font>`<font style="color:rgba(0, 0, 0, 0.85);">waitKey</font>`<font style="color:rgba(0, 0, 0, 0.85);"> 即可处理所有窗口的按键事件，无需为每个窗口单独调用。</font>

<h3 id="WaPcP"><font style="color:rgba(0, 0, 0, 0.85);">（5）代码运行</font></h3>
![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1761428998120-251b0d06-f1e7-4769-a103-66925e8567cc.png)

<h4 id="yo23d">遇见问题：</h4>
初次运行时，发生了如下错误：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1761429041069-b929272b-6369-4cae-9524-2d005d2445d5.png)

无法识别头文件。

<font style="color:rgba(0, 0, 0, 0.85);">起初以为是没有编译正确，于是进入</font>`<font style="color:rgba(0, 0, 0, 0.85);">build</font>`<font style="color:rgba(0, 0, 0, 0.85);">文件进行编译，结果如图</font>![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1761429161968-391cc313-f592-4e3b-8944-60e90623a9ab.png)

仍然无法运行。

结果显示问题出在图像文件路径，导致`imread`函数无法正确读取图像，进而引发异常。

原因是我将保存有图片`pyy.png`的文件夹`images`直接放在了项目根目录下，而`path`写的是`"images/pyy.png"`。

经过多次实验，似乎只有当`images`文件夹处于`Trafficlight/src`路径下时才能成功运行。

修改后的文件结构以及代码:

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1761429723823-bc060130-16de-44c2-95bb-c38ec4564d76.png)

`src`目录下`./main`运行程序后：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1761429951388-2dc06d76-1e2c-4bcf-a19b-3ea9bfabf956.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1761430236252-2215a29b-4baf-4702-8236-4564a89d3e13.png)

<h2 id="FhiOc">3.视频读取与播放</h2>
<h3 id="VHFJE">（1）视频读取：`cv::VideoCapture`类</h3>
用于从视频文件、摄像头、网络流等源读取视频帧，是视频处理的入口。

<h4 id="EeekW">1）构造函数（初始化）</h4>
```cpp
//从本地视频文件读取（参数为本地文件路径）
cv::VideoCapture cap("input.mp4");

//从摄像头读取（参数为摄像头索引，0表示默认摄像头）
cv::VideoCapture cap(0);

//从网络流读取（参数为RTSP/HTTP 地址）
cv::VideoCapture cap("https://www.bilibili.com/video");
```

<h4 id="xljHD">2）核心方法</h4>
| `<font style="color:rgb(0, 0, 0);">open(const String& filename)</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">打开视频源（与构造函数功能相同，可用于后期重新打开）。</font> |
| :--- | :--- |
| `<font style="color:rgb(0, 0, 0);">isOpened()</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">判断视频源是否成功打开（返回 </font>`<font style="color:rgb(0, 0, 0);">true</font>`<font style="color:rgba(0, 0, 0, 0.85) !important;">表示成功）。</font> |
| `<font style="color:rgb(0, 0, 0);">read(Mat& frame)</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">读取一帧视频到 </font>`<font style="color:rgb(0, 0, 0);">frame</font>`<font style="color:rgba(0, 0, 0, 0.85) !important;">中（返回 </font>`<font style="color:rgb(0, 0, 0);">true</font>`<font style="color:rgba(0, 0, 0, 0.85) !important;"> 表示读取成功）。</font> |
| `<font style="color:rgb(0, 0, 0);">release()</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">释放视频源资源（关闭文件 / 摄像头）。</font> |
| `<font style="color:rgb(0, 0, 0);">get(int propId)</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">获取视频属性（如帧率、宽高），</font>`<font style="color:rgb(0, 0, 0);">propId</font>`<font style="color:rgba(0, 0, 0, 0.85) !important;">为属性常量（见下表）。</font> |
| `<font style="color:rgb(0, 0, 0);">set(int propId, double value)</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">设置视频属性（如摄像头分辨率，部分属性可能不支持，取决于设备）。</font> |


<h4 id="V7eUR">3）常用属性常量（propId）</h4>
| **<font style="color:rgb(0, 0, 0) !important;"></font>** | **<font style="color:rgb(0, 0, 0) !important;">含义</font>** | **<font style="color:rgb(0, 0, 0) !important;">示例（获取方式）</font>** |
| :--- | :--- | :--- |
| `<font style="color:rgb(0, 0, 0);">CAP_PROP_FRAME_WIDTH</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">帧宽度</font> | `<font style="color:rgb(0, 0, 0);">int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);</font>` |
| `<font style="color:rgb(0, 0, 0);">CAP_PROP_FRAME_HEIGHT</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">帧高度</font> | `<font style="color:rgb(0, 0, 0);">int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);</font>` |
| `<font style="color:rgb(0, 0, 0);">CAP_PROP_FPS</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">帧率（帧 / 秒）</font> | `<font style="color:rgb(0, 0, 0);">double fps = cap.get(cv::CAP_PROP_FPS);</font>` |
| `<font style="color:rgb(0, 0, 0);">CAP_PROP_FRAME_COUNT</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">总帧数（仅文件有效）</font> | `<font style="color:rgb(0, 0, 0);">int totalFrames = cap.get(cv::CAP_PROP_FRAME_COUNT);</font>` |
| `<font style="color:rgb(0, 0, 0);">CAP_PROP_POS_FRAMES</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">当前帧索引</font> | `<font style="color:rgb(0, 0, 0);">cap.set(cv::CAP_PROP_POS_FRAMES, 100);</font>`<br/><font style="color:rgba(0, 0, 0, 0.85) !important;"> </font><font style="color:rgba(0, 0, 0, 0.85) !important;">// 跳转到第 100 帧</font> |


<h3 id="mH44y">2.视频写入：`cv::VideoWriter`类</h3>
用于将处理后的帧写入视频文件，需指定输出格式、帧率、尺寸等参数。

<h4 id="bcVm6">1）构造函数（初始化）</h4>
```cpp
cv::VideoWriter out(
    "output.mp4",   // 输出文件路径
    cv::VideoWriter::fourcc('M','P','4','V'),  // 编码器（MP4 格式）
    30.0,          // 帧率（需与输入视频一致或自定义）
    cv::Size(width, height)   // 帧尺寸（需与输入帧尺寸一致）
);
```

<h4 id="jHUn7">2）核心方法</h4>
| **<font style="color:rgb(0, 0, 0) !important;">方法</font>** | **<font style="color:rgb(0, 0, 0) !important;">说明</font>** |
| :--- | :--- |
| `<font style="color:rgb(0, 0, 0);">open(...)</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">打开输出文件（参数与构造函数相同，用于后期重新初始化）。</font> |
| `<font style="color:rgb(0, 0, 0);">isOpened()</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">判断输出文件是否成功打开。</font> |
| `<font style="color:rgb(0, 0, 0);">write(const Mat& frame)</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">写入一帧图像（</font>`<font style="color:rgb(0, 0, 0);">frame</font>`<font style="color:rgba(0, 0, 0, 0.85) !important;">尺寸需与初始化时的 </font>`<font style="color:rgb(0, 0, 0);">Size</font>`<font style="color:rgba(0, 0, 0, 0.85) !important;">一致）。</font> |
| `<font style="color:rgb(0, 0, 0);">release()</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">释放资源（必须调用，否则视频文件可能损坏）。</font> |


<h3 id="qkToU">3.编码器<font style="color:rgb(0, 0, 0);">（</font>`<font style="color:rgb(0, 0, 0);">fourcc</font>`<font style="color:rgb(0, 0, 0);">）</font></h3>
`<font style="color:rgba(0, 0, 0, 0.85) !important;">fourcc</font>`<font style="color:rgb(0, 0, 0);"> </font><font style="color:rgb(0, 0, 0);">是四字符代码，用于指定视频编码格式，常见值：</font>

`<font style="color:rgb(0, 0, 0);">'M','P','4','V'</font>`<font style="color:rgb(0, 0, 0);">：MP4 格式（推荐，兼容性好）。</font>

`<font style="color:rgb(0, 0, 0);">'X','V','I','D'</font>`<font style="color:rgb(0, 0, 0);">：AVI 格式（压缩率较低）。</font>

`<font style="color:rgb(0, 0, 0);">'H','2','6','4'</font>`<font style="color:rgb(0, 0, 0);">：H.264 编码（需系统支持）。用法：</font>`<font style="color:rgb(0, 0, 0);">cv::VideoWriter::fourcc('M','P','4','V')</font>`<font style="color:rgb(0, 0, 0);"> 或直接简写为 </font>`<font style="color:rgb(0, 0, 0);">CV_FOURCC('M','P','4','V')</font>`<font style="color:rgb(0, 0, 0);">。</font>

<font style="color:rgb(0, 0, 0);"></font>

<h3 id="qYVal"><font style="color:rgb(0, 0, 0);">4.帧处理函数</font></h3>
<h4 id="B7cHx">1）灰度化 <font style="color:rgb(0, 0, 0);background-color:rgba(0, 0, 0, 0.06);">cvtColor(frame, gray, COLOR_BGR2GRAY)</font></h4>
<h5 id="QPnOj">函数原型</h5>
```cpp
void cvtColor(
    InputArray src,   // 输入图像（Mat 类型）
    OutputArray dst,  // 输出图像（转换后的结果）
    int code,         // 色彩空间转换码（如 COLOR_BGR2GRAY）
    int dstCn = 0     // 输出图像的通道数（默认 0 表示自动匹配）
);
```

<h5 id="TKhqj">核心参数：色彩空间转码</h5>
| **<font style="color:rgb(0, 0, 0) !important;">转换码</font>** | **<font style="color:rgb(0, 0, 0) !important;">含义</font>** | **<font style="color:rgb(0, 0, 0) !important;">适用场景</font>** |
| :--- | :--- | :--- |
| `<font style="color:rgb(0, 0, 0);">COLOR_BGR2GRAY</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">BGR 转灰度图</font> | <font style="color:rgba(0, 0, 0, 0.85) !important;">灰度化处理、边缘检测</font> |
| `<font style="color:rgb(0, 0, 0);">COLOR_GRAY2BGR</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">灰度图转 BGR（3 通道）</font> | <font style="color:rgba(0, 0, 0, 0.85) !important;">灰度图需转为彩色格式输出</font> |
| `<font style="color:rgb(0, 0, 0);">COLOR_BGR2HSV</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">BGR 转 HSV 空间</font> | <font style="color:rgba(0, 0, 0, 0.85) !important;">颜色识别（HSV 对颜色区分更直观）</font> |
| `<font style="color:rgb(0, 0, 0);">COLOR_HSV2BGR</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">HSV 转 BGR 空间</font> | <font style="color:rgba(0, 0, 0, 0.85) !important;">HSV 处理后转回 BGR 显示</font> |
| `<font style="color:rgb(0, 0, 0);">COLOR_BGR2RGB</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">BGR 转 RGB 空间</font> | <font style="color:rgba(0, 0, 0, 0.85) !important;">与其他库（如 PIL）颜色格式兼容</font> |
| `<font style="color:rgb(0, 0, 0);">COLOR_BGR2YUV</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">BGR 转 YUV 空间</font> | <font style="color:rgba(0, 0, 0, 0.85) !important;">视频压缩、色彩分析</font> |
| `<font style="color:rgb(0, 0, 0);">COLOR_YUV2BGR</font>` | <font style="color:rgba(0, 0, 0, 0.85) !important;">YUV 转 BGR 空间</font> | <font style="color:rgba(0, 0, 0, 0.85) !important;">同上</font> |




<h4 id="UWvRn">2）滤波函数</h4>
<h5 id="D8Zou">2.1）均值滤波`blur`</h5>
<font style="color:rgba(0, 0, 0, 0.85);">均值滤波是最简单的线性滤波，核心思想是</font>**<font style="color:rgb(0, 0, 0) !important;">用卷积核内所有像素的平均值替换中心像素的值。</font>**<font style="color:rgb(0, 0, 0);">卷积核（如 3×3）覆盖的区域内，计算所有像素的灰度值之和，再除以像素总数（如 9），得到的平均值作为中心像素的新值。</font>

<font style="color:rgb(0, 0, 0);">效果：平滑图像、降低噪声，但会模糊边缘细节（对所有像素 “一视同仁”，边缘像素也会被平均）</font>

```cpp
void blur(
    InputArray src,       // 输入图像（单通道或多通道，如 Mat）
    OutputArray dst,      // 输出图像（与输入尺寸、类型相同）
    Size ksize,           // 卷积核大小（如 Size(3,3) 表示 3×3 核）
    Point anchor = Point(-1,-1),  // 锚点（核的中心，默认 (-1,-1) 即中心）
    int borderType = BORDER_DEFAULT  // 边界填充方式（默认自动填充边缘）
);
```

<h5 id="ezb2y">关键参数</h5>
`**<font style="color:rgb(0, 0, 0);">ksize</font>**`<font style="color:rgb(0, 0, 0);">：卷积核尺寸，必须是正整数（如 </font>`<font style="color:rgb(0, 0, 0);">Size(3,3)</font>`<font style="color:rgb(0, 0, 0);">、</font>`<font style="color:rgb(0, 0, 0);">Size(5,5)</font>`<font style="color:rgb(0, 0, 0);">）。核越大，平滑效果越强，但图像越模糊。</font>

`**<font style="color:rgb(0, 0, 0);">borderType</font>**`<font style="color:rgb(0, 0, 0);">：处理图像边缘的方式（边缘像素没有足够的邻域像素），默认 </font>`<font style="color:rgb(0, 0, 0);">BORDER_DEFAULT</font>`<font style="color:rgb(0, 0, 0);"> 会自动用边缘像素填充，避免边缘失真。</font>

<h5 id="xXCx7"><font style="color:rgb(0, 0, 0);">2.2）高斯滤波</font>`<font style="color:rgb(0, 0, 0);">GaussianBlur</font>`</h5>
<font style="color:rgb(0, 0, 0);">高斯滤波是一种</font>**<font style="color:rgb(0, 0, 0) !important;">加权平均滤波</font>**<font style="color:rgb(0, 0, 0);">，核心思想是</font>**<font style="color:rgb(0, 0, 0) !important;">用高斯分布（正态分布）的权重矩阵作为卷积核</font>**<font style="color:rgb(0, 0, 0);">，对邻域像素加权求和。</font>

<font style="color:rgb(0, 0, 0);">高斯核的特点：中心像素权重最大，离中心越远权重越小（符合 “近邻影响大，远邻影响小” 的规律）。</font>

<font style="color:rgb(0, 0, 0);">效果：在平滑噪声的同时，比均值滤波</font>**<font style="color:rgb(0, 0, 0) !important;">保留更多边缘细节</font>**<font style="color:rgb(0, 0, 0);">（边缘处的像素值差异较大，中心权重高，边缘模糊程度低）。</font>

<font style="color:rgb(0, 0, 0);">函数原型：</font>

```cpp
void GaussianBlur(
    InputArray src,
    OutputArray dst,
    Size ksize,           // 卷积核大小（宽高必须是正奇数，如 3×3、5×5）
    double sigmaX,        // X 方向高斯标准差（控制权重分布的“宽窄”）
    double sigmaY = 0,    // Y 方向标准差（默认 0 表示与 sigmaX 相同）
    int borderType = BORDER_DEFAULT
);
```

关键参数：

`**<font style="color:rgb(0, 0, 0);">ksize</font>**`<font style="color:rgb(0, 0, 0);">：必须是正奇数（如 3×3、5×5），确保核有唯一中心。核越大，平滑效果越强。</font>

`**<font style="color:rgb(0, 0, 0);">sigmaX</font>**`<font style="color:rgb(0, 0, 0);">：X 方向的高斯标准差（σ）：</font>

<font style="color:rgb(0, 0, 0);">σ 越大，权重分布越 “平缓”（远处像素影响越大），平滑效果越强；</font>

<font style="color:rgb(0, 0, 0);">σ 越小，权重集中在中心，平滑效果弱但边缘保留更好；</font>

<font style="color:rgb(0, 0, 0);">若 σ=0，OpenCV 会根据核大小自动计算（</font>`<font style="color:rgb(0, 0, 0);">sigma = 0.3×((ksize-1)×0.5 - 1) + 0.8</font>`<font style="color:rgb(0, 0, 0);">）。</font>

<font style="color:rgb(0, 0, 0);"></font>

<h2 id="fBeQ2"><font style="color:rgb(0, 0, 0);">4.形态学操作</font></h2>
<font style="color:rgba(0, 0, 0, 0.85);">形态学操作是基于图像形状的非线性处理方法，通过</font>**<font style="color:rgb(0, 0, 0) !important;">结构元素（卷积核）</font>**<font style="color:rgba(0, 0, 0, 0.85);"> 与图像进行交互，实现对目标区域的形状调整（如扩大、缩小、填充、分割），核心用于噪声去除、边缘提取、形状分析等场景。</font>

<h3 id="pzjzD"><font style="color:rgba(0, 0, 0, 0.85);">1.核心概念：</font>**<font style="color:rgb(0, 0, 0) !important;">结构元素（Kernel）</font>**</h3>
<font style="color:rgba(0, 0, 0, 0.85);">用于与图像进行形态学交互的 “模板”，通常为矩形、椭圆或十字形，需通过</font>`<font style="color:rgba(0, 0, 0, 0.85);">getStructuringElement</font>`<font style="color:rgba(0, 0, 0, 0.85);"> 函数创建。</font>

`<font style="color:rgba(0, 0, 0, 0.85);">getStructuringElement</font>`<font style="color:rgba(0, 0, 0, 0.85);">函数原型：</font>

```cpp
Mat getStructuringElement(
    int shape,        // 形状：MORPH_RECT（矩形）、MORPH_ELLIPSE（椭圆）、MORPH_CROSS（十字）
    Size ksize,       // 尺寸（如 Size(3,3)）
    Point anchor = Point(-1,-1)  // 锚点（默认中心）
);
```

<h3 id="wjEfJ">2<font style="color:rgb(0, 0, 0);">.基础形态学操作（膨胀与腐蚀）</font></h3>
<h4 id="s9Vw6">（1）<font style="color:rgb(0, 0, 0);">膨胀（</font>`<font style="color:rgb(0, 0, 0);">dilate</font>`<font style="color:rgb(0, 0, 0);">）</font></h4>
**<font style="color:rgb(0, 0, 0) !important;">功能</font>**<font style="color:rgb(0, 0, 0);">：扩大图像中的</font>**<font style="color:rgb(0, 0, 0) !important;">亮区域</font>**<font style="color:rgb(0, 0, 0);">，填充目标内部的小空洞，连接相邻的亮区域。</font>

**<font style="color:rgb(0, 0, 0) !important;">原理</font>**<font style="color:rgb(0, 0, 0);">：结构元素滑动时，若其覆盖区域内存在亮像素（白色），则将中心像素设为亮像素（相当于 “扩张” 亮区域）。</font>

<font style="color:rgb(0, 0, 0);">函数原型：</font>

```cpp
void dilate(
    InputArray src,          // 输入图像（单/多通道，推荐二值图）
    OutputArray dst,         // 输出图像（与输入尺寸、类型一致）
    InputArray kernel,       // 结构元素
    Point anchor = Point(-1,-1),  // 锚点（默认中心）
    int iterations = 1,      // 迭代次数（次数越多，膨胀越明显）
    int borderType = BORDER_CONSTANT,  // 边界填充方式
    const Scalar& borderValue = morphologyDefaultBorderValue()  // 边界填充值
);
```

**<font style="color:rgb(0, 0, 0) !important;">示例</font>**<font style="color:rgb(0, 0, 0);">：用 3×3 矩形核膨胀二值图，填充小空洞</font>**<font style="color:rgba(0, 0, 0, 0.85);"></font>**

```cpp
Mat src = imread("binary_with_holes.png", IMREAD_GRAYSCALE);
Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
Mat dst;
dilate(src, dst, kernel, Point(-1, -1), 1);  // 1 次膨胀
```

<h2 id="a4WtC"><font style="color:rgb(0, 0, 0);">练习：视频的读取和基于循环语句的逐帧输出</font></h2>


```cpp
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#incldue <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(){
    string path = "images/TrafficLight.mpa"; //视频存储在本地的路径
    VideoCapture cap(path);   //定义VideoCapture的对象cap，从指定的路径读取本地视频
    Mat img;  //定义Mat对象img，存储从视频中读取的每一帧图像
    while (true){
        cap.read(img);  //从视频中读取一帧视频到图像img
        imshow("Image",img); //在Image窗口中显示img图像
        waitKey(50);
    }
```

代码运行结果如图所示：

[此处为语雀卡片，点击链接查看](https://www.yuque.com/docs/241896578#cfmro)

若视频无法播放，可查看b站上传视频[opencv导入视频并采用循环逐帧播放](https://www.bilibili.com/video/BV1xaxwz8EcR/?vd_source=2645f0a74795536f33bdfc4f415062e2)





<h2 id="CZFF6">Trafficlight颜色识别</h2>
<h3 id="uyWrX">1.本地读取视频</h3>
通过相对路径访问本地视频，如果读取失败，反馈失败信息。

```cpp
string path = "images/TrafficLight.mp4";
VideoCapture cap(path);
if (!cap.isOpened()){
    cerr << "无法打开视频文件" << endl;
    return -1;
}
```

<h3 id="Zz8QK">2.获取原视频参数</h3>
```cpp
double fps = cap.get(CAP_PROP_FPS);
int width = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
int height =static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
```

获取原视频的帧数、宽、高，以便于输出时格式一致，不容易出错。

<h3 id="m8StN">3.创建输出视频</h3>
```cpp
 VideoWriter writer("/home/dsp/Videos/result.avi",VideoWriter::fourcc('M','J','P','G'),fps,Size(width,height));
    if(!writer.isOpened()){
        cerr << "无法创建输出视频文件！" << endl;
        cap.release();
        return -1;
    }
Mat frame,hsvFrame,redMask,greenMask;
```

规定格式为avi型，以符合要求,定义帧、hsv色彩帧、红色掩码和绿色砚玛。

<h3 id="ylXaX">4.逐帧处理视频</h3>
```cpp
//逐帧处理视频
    while(cap.read(frame)){
        if(frame.empty()) break;
        //转换到HSV颜色空间，HSV比BGR更容易分割颜色
        cvtColor(frame,hsvFrame,COLOR_BGR2HSV);

        //检测红灯信号
        Scalar lowerRed1 = Scalar(0,100,100);
        Scalar upperRed1 = Scalar(0,255,255);
        Scalar lowerRed2 = Scalar(170,100,100);
        Scalar upperRed2 = Scalar(180,255,255);
        inRange(hsvFrame,lowerRed1,upperRed1,redMask);
        Mat redMask2;
        inRange(hsvFrame, lowerRed2,upperRed2,redMask2);
        redMask = redMask | redMask2;  //合并两个红色区间掩码

        //检测绿灯信号
        Scalar lowerGreen = Scalar(35,100,100);
        Scalar upperGreen = Scalar(77,255,255);
        inRange(hsvFrame,lowerGreen,upperGreen,greenMask);

```

<h3 id="O0wTw">5.颜色轮廓检测并标记</h3>
```cpp
//轮廓检测与标注
        vector<vector<Point>> redContours, greenContours;
        vector<Vec4i> redHierarchy,greenHierarchy; 

        //检测红色区域的轮廓
        findContours(redMask,redContours,redHierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
        //检测绿色轮廓
        findContours(greenMask,greenContours,greenHierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE)；

        bool isRed = false, isGreen = false;
        Rect redRect,greenRect;


        //处理红色轮廓，筛选合理区域并标注
        for (size_t i =0;i < redContours.size();++i){
            double area = contourArea(redContours[i]);
            if (area > 100){
                redRect = boundingRect(redContours[i]);
                rectangle(frame,redRect,Scalar(0,0,255),2);
                isRed = true;
            }
        }
        //处理绿色轮廓，筛选合理区域并标注
        for (size_t i =0;i < greenContours.size();++i){
            double area = contourArea(greenContours[i]);
            if (area > 100){
                greenRect = boundingRect(greenContours[i]);
                rectangle(frame,greenRect,Scalar(0,255,0),2);
                isGreen = true;
            }
        }

```



<h3 id="Enacr">6.显示颜色文字</h3>
```cpp
//左上角显示颜色文字
        if(isRed){
            putText(frame,"red",Point(10,30),FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,255),2);
        }
        else if (isGreen){
            putText(frame,"green",Point(10,30),FONT_HERSHEY_SIMPLEX,1,Scalar(0,255,0),2);
        }

        writer.write(frame);
    
    }
```

<h3 id="YJCUo">7.释放资源</h3>
```cpp

    cap.release();
    writer.release();
    cout << "处理完成" << endl;
    return 0;
}
```



