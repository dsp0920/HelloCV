<h1 id="GP5pa">一、版本以及安装方式选择</h1>
考虑到稳定性与兼容性，以及为适配 Ubuntu 22.04，ROS 2选择了 Humble 版本。

了解到 ROS 2 在Ubuntu 系统中有多种安装方法，如从源代码构建安装、使用一键安装脚本以及通过系统包管理器安装。

从源代码构建安装，该方法操作复杂度较高，需手动安装繁杂的构建工具和编译依赖，对新手不友好；使用一键安装脚本，由于该方法为从第三方获取脚本链接，缺少官方背书，可能出现“依赖冗余”或者“依赖缺失”的问题，导致后续功能异常。故经过综合考量后，选择通过系统包管理器安装的方法。

<h1 id="tp85M">二、安装步骤</h1>
<h2 id="T00FZ">1.设置语言环境</h2>
<font style="color:rgba(0, 0, 0, 0.85);">ROS 2 的核心代码和工具默认依赖 </font>**<font style="color:rgb(0, 0, 0) !important;">UTF-8 编码。</font>**<font style="color:rgba(0, 0, 0, 0.85);">ROS 2 在运行时会输出大量日志信息（如节点状态、话题数据），如果系统编码不是 UTF-8，这些信息可能会显示为乱码（比如 “???” 或特殊符号），导致你无法排查问题。ROS 2 的部分依赖库（如用于字符串处理的库）默认只支持 UTF-8 编码。如果系统使用其他编码（如 GBK），可能会导致库文件加载异常，进而让节点启动失败。</font><font style="color:rgb(0, 0, 0);">无论是官方文档、社区教程还是第三方包，都默认基于 UTF-8 环境编写。统一编码能避免因环境差异导致的 “别人能运行，自己却报错” 的问题。</font>

<font style="color:rgb(0, 0, 0);">因此，在安装ROS 2 前，需要先设置语言环境。</font>

设置语言环境可在终端中执行以下命令：

```bash
sudo apt install locales
#安装locales包，该包包含语言环境配置工具

sudo locale-gen en_US en_US.UTF-8
# 生成指定的语言环境（en_US和en_US.UTF-8）

sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
# 配置系统默认的本地化环境变量，设置全局默认编码为UTF-8，确保所有程序默认使用该编码

export LANG=en_US.UTF-8
# 在当前终端会话中临时设置LANG环境变量，立即生效，避免需要重新启动终端才能应用配置
```

<font style="color:rgba(0, 0, 0, 0.85);">  
</font><font style="color:rgba(0, 0, 0, 0.85);"> 各行指令在终端中输出如下：</font>

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760238397920-b57a8b7f-fbc3-44a9-9710-be93ed31222c.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760238441378-c31c6aad-edf3-40e7-8eed-a5f8ad58abe0.png)![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760238466098-9ed2bc91-f8a0-4771-966f-6e65076fbc0b.png)

`export LANG=en_US.UTF-8`指令没有输出内容。

<h2 id="gGfDg">2.添加软件源</h2>
在终端中执行以下命令：

```bash
sudo apt install software-properties-common
#安装软件资源管理工具

sudo add-apt-repository universe
#添加 universe 软件源（ROS 2 部分依赖包位于此处）

sudo apt install curl
#安装curl

sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
# 下载 ROS 2 官方 GPG 密钥并保存到系统密钥环 ，用于验证后续下载的 ROS 2 软件包完整性

echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
# 添加 ROS 2 软件源到系统源列表，根据当前系统版本自动适配（通过 . /etc/os-release 获取 Ubuntu 版本代号）
```

执行效果如下：  
![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760274260672-e93e3677-74a8-4c60-b378-3fa7026c7040.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760274276177-1a396d15-1d19-404f-a8fc-ac0ac63f8b6a.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760274289723-557057b2-df21-4c56-bcd1-e2400bc006f5.png)

最后两句指令在终端中无内容输出。

<h2 id="XF5Kt">3.安装ROS 2 </h2>
在终端中输入以下指令：

```bash
sudo apt update
#首先更新软件包索引

sudo apt install ros-humble-desktop-full
#安装ROS 2 Humble桌面完整版
```

运行效果如下：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760274906851-04bfecf1-7165-4898-aabd-eb2b12cb552c.png)

由于内容过多，`sudo apt install ros-humble-desktop-full`这一指令的执行结果仅展示了部分：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760357726711-193ce63f-e7ae-40df-8d51-6a00d8bc4ca6.png)



<h2 id="vl8ML">4.配置环境变量</h2>
```bash
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
# 将 ROS 2 环境变量配置添加到 .bashrc ，使每次打开终端时自动加载 ROS 2 环境

source ~/.bashrc
# 立即加载环境变量
```

该两句命令终端无输出。

<h2 id="T3Rjh">5.安装额外工具</h2>
<font style="color:rgba(0, 0, 0, 0.85);">安装编译和依赖管理工具，方便后续开发：</font>

```bash
sudo apt install python3-colcon-common-extensions
sudo apt install python3-rosdep
sudo rosdep init
rosdep update
```

<h2 id="Wgq0k">6.验证安装</h2>
在终端1中执行以下指令：

```bash
ros2 run demo_nodes_cpp talker
```

效果如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760281858740-f794f0bc-58a6-4122-aedd-b80751886a62.png)

同时，在终端2中执行以下指令：

```bash
ros2 run demo_nodes_py listener
```

效果如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760281883693-c4bc2784-e034-42d3-a542-daeca936e64b.png)

终端1中发出的内容恰好是终端2中接受的内容，说明安装成功。



