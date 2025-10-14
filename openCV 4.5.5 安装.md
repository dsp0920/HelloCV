安装方法参考b站的一篇专栏： [第六篇—Ubuntu22.04安装；C++开发环境配置；VScode安装；Opencv4安装; - 哔哩哔哩](https://www.bilibili.com/opus/677207151761948675?from=search&spm_id_from=333.337.0.0)

<h1 id="suMKX">安装步骤</h1>
<h2 id="aXe2c">1.配置c++开发环境</h2>
<h3 id="m7wYT"><font style="color:rgb(47, 50, 56);">（1）</font><font style="color:rgb(47, 50, 56);">编译器和调试器安装</font></h3>
```bash
sudo apt update
#更新软件源

sudo apt install build-essential gdb
#下载安装g++、gcc和cdb
```

<font style="color:#DF2A3F;">所遇问题：</font>

在执行`sudo apt update`时报错：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760419595014-2e30bf29-b9e6-42b4-8489-a56b2d9120c6.png)

若出现该问题，可导入对应的GPG公钥：

```bash
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 40976EAF437D05B5
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 3B4FE6ACC0B21F32
```

再执行`sudo apt update`就不会出错了。

检查版本号，看看是否安装成功

```bash
gcc --version
g++ --version
gdb --version
```

执行效果

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760420035302-f8550204-efce-4efe-afa1-0cf7cd8f077f.png)

<h3 id="gq43a"><font style="color:rgb(47, 50, 56);">（2）</font><font style="color:rgb(47, 50, 56);">cmake安装</font></h3>
```bash
sudo apt install cmak
#安装cmake和build-essential

cmake --version
#检查安装
```

检查安装结果：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760429231457-d346eba8-e71c-499f-8414-862ff9d9f5bf.png)



<h2 id="QgUCn">2.安装依赖</h2>
```bash
sudo apt-get install build-essential libgtk2.0-dev libavcodec-dev libavformat-dev libjpeg-dev libtiff5-dev libswscale-dev libjasper-dev
```

执行结果：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760430535324-11c4a3ee-2628-4dd8-b920-a6164863c2f3.png)



<h2 id="u8hiA">3.下载安装opencv 4</h2>
<h3 id="mOVxm">（1）下载Sources文件</h3>
[官方源文件下载链接](https://opencv.org/releases/)

找到目标版本opencv 4.5.5：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760429948485-cf3220ce-5103-4504-8e81-3bb09807990c.png)

下载Sources文件。



<h3 id="U7dG3">（2）解压zip文件</h3>
进入到Sources所在文件，在当前文件打开终端，输入：  


```bash
unzip opencv-4.5.5.zip
#解压opencv的zip文件
```



解压结果：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760430806490-19550cdd-e8f1-42b4-8ada-0c6753168442.png)



<h3 id="MOrO6">（3）编译安装</h3>
<h4 id="EiDsC">1）建立build文件</h4>
进入解压完的opencv-4.5.5文件，新建一个build文件。

如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760431349177-95462559-b10f-4dc1-b0d8-8d1316045d3b.png)

<h4 id="Nbj5r">2）在build文件下执行cmake</h4>
进入build文件，在该文件终端中输入：

```bash
sudo cmake -DCMAKE_BUILD_TYPE=Release -DOPENCV_GENERATE_PKGCONFIG=ON -DCMAKE_INSTALL_PREFIX=/usr/local ..
```

执行效果如下：

（由于过程较长，仅展示开始和结束部分）

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760431883913-26fbc791-26b4-4bbf-8eff-dac77e969684.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760431897407-4c537b93-5d36-4184-a212-1cae1fb69575.png)



<h4 id="yRVQ2">3）继续在build文件下执行make</h4>
在build的终端输入：

```bash
sudo make -j2
#-j2表示根据CPU核数提高编译速度
```

#查看<font style="color:rgb(47, 50, 56);">CPU核数的命令：</font>

```python
 cat /proc/cpuinfo | grep "cpu cores" | uniq
```

执行效果：

			   ![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760432216343-c5c2c6fb-e784-4be0-8b0c-b49cd72bd2ed.png)



<font style="color:rgb(47, 50, 56);">执行make后的结果如下（部分）：</font>

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760432464579-3a8caadc-2c02-499a-ad77-6d968a0ac157.png)

<h4 id="y81Db">4）在build文件下执行安装指令</h4>
终端输入：

```bash
sudo make install
```

		执行效果（部分）：  
		![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760432582504-38ee9bd6-2c91-43fd-9c35-f077b530da4a.png)			



<h3 id="fEx8w">（4）环境配置</h3>
<h4 id="uRZ0c">1）一、</h4>
终端打开opencv4.conf：

```bash
sudo vim /etc/ld.so.conf.d/opencv4.conf
```

在打开的文件中第一行添加`/usr/local/lib`，然后按`Esc`键，输入`：wq`保存并退出。

如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760433319297-9509ae0b-6a23-4245-afe1-a57861fcac84.png)

输入指令：

```python
sudo ldconfig
```

使得配置生效。



<h4 id="RZTzK">2）二、</h4>
打开<font style="color:rgb(47, 50, 56);">bash.bashrc文件</font>

```python
sudo vim /etc/bash.bashrc
```

打开文件后，按`shift`+`g`快速跳到文件末尾，按`i`键进入插入模式，<font style="color:rgb(47, 50, 56);">在文件的末尾加入以下	      内容：</font>

```python
PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig
export PKG_CONFIG_PATH
```

如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760433565245-5c84714e-d285-43ef-a01e-a658f93a0aa5.png)

按`Esc`键，输入`：wq`保存并退出。

执行指令：

```python
source /etc/bash.bashrc
```

使得配置生效。

<h4 id="NVfkv">3）三、</h4>
执行下列指令更新数据库：

```python
sudo updatedb
```

<font style="color:#DF2A3F;">所遇问题</font>

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760433886782-e637d451-1b1c-43bc-afd3-0d0f2e5095b7.png)

<font style="color:rgb(47, 50, 56);">先安装mlocate，再执行updatedb</font>

```python
sudo apt-get install mlocate
sudo updatedb
```

效果如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760434000605-3a028ce0-9606-4755-9e25-7510ccfc9f41.png)



<h3 id="NUfIW">（5）验证安装</h3>
<font style="color:rgb(47, 50, 56);">我们创建一个文件夹project1，里面再创建一个c1.cpp的源文件，并准备一张RGB图像img.png，如图：</font>

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760434141204-2b4638e7-ecee-4298-b1b0-b87530dcc3da.png)

在c1.cpp中输入以下代码：

```bash
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat img=imread("img.png");
    imshow("img",img);
    waitKey(0);
    destroyAllWindows();
    return 0;
    
}
```

<font style="color:rgb(47, 50, 56);">利用g++编译c1.cpp，生成可执行文件c1</font>

```python
sudo g++ c1.cpp -o c1 `pkg-config --cflags --libs opencv4`
```

效果如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760434338377-724d2f72-adf4-4987-ad1a-b53179fe1caa.png)

运行可执行文件c1，得到的图片与img.png相同		  
![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760434440286-dd53814d-e9f6-46f5-80dd-5e99e4580cc2.png)

说明opencv 4.5.5安装成功。

