

<h1 id="oV8pD">1.更新系统</h1>
打开终端并运行以下apt指令：

```bash
sudo apt update
sudo apt upgrade -y
```

运行结果如下：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760439713066-b65924dc-8b13-418a-95e0-196b7979b933.png)



<h1 id="idNff">2.安装Git</h1>
终端输入以下指令：

```bash
sudo apt install git
```

结果如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760439841284-159b3cd0-d09d-420b-8d99-27063b641855.png)

检验安装：

```bash
git --version
```

结果：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760439916864-5b0bdf5a-2746-47fe-a351-a679b0bc4063.png)

说明安装成功。

<h1 id="SGGYA">3.配置Git</h1>
终端输入以下指令，双引号内填写对应的github "name" 和 "email"

```bash
git config --global user.name "dsp0920"
git config --global user.email "3272038914@qq.com"
```

如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760441550276-0c0df868-1e35-472a-8f2c-018387a02eae.png)

用git来验证配置：

```bash
 git config --list
```

验证如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760441566456-1186ab95-7235-4eba-ba3d-b8c42baf446b.png)

说明配置成功。



<h1 id="SWO7T">4.创建文件夹并初始化git存储库</h1>
<font style="color:rgb(77, 77, 77);">为项目创建一个新文件夹并初始化一个 Git存储库。</font>

```bash
mkdir project_code
cd project_code
git init
```

结果如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760442020346-4fea139c-3033-4a00-aa09-319f86a1ca67.png)

<h1 id="u0GYX">5.更改并提交</h1>
在`projectc_code`文件中新建一个文件`project_1`，并且添加初始代码。

输入指令：

```bash
touch project_1
git add .
git commit -m "First Commit"
```

效果如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760455205323-4050c96f-d488-4d8c-840c-354825e40c69.png)

<h1 id="zaWom">6.创建一个github新仓库</h1>
在GitHub上创建一个新仓库project_1。

<h1 id="AYPbD">7.<font style="color:rgb(77, 77, 77);">生成ssh密钥并上传到GitHub账户</font></h1>
终端运行以下指令：

```bash
ssh-keygen
#生成ssh密钥

cat ~/.ssh/id_rsa.pub
查看公钥内容
```

执行结果如图：  
![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760487069973-4e1fc30c-5ed9-498b-8a58-d90b5a5c4fa0.png)

将公钥内容上传至GitHub，结果如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760487188221-fadc8092-b27c-4650-9186-652c0ce45a6e.png)

<h1 id="yzPWI">8.将本地储存连接到远程GitHub存储库</h1>
进入project_code文件，打开终端，输入以下指令：  


```bash
git remote add origin http://github.com/dsp0920/project_1.git
#连接GitHub库

git branch -M main
#选择库的main分支

git remote -v
#查看
```

结果如下：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760487919462-3e22652c-90d1-4c3d-a7a1-85479b5a16ef.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760487946197-64a49bfc-81cb-4c6c-bef1-2a1dec433ed5.png)

<h1 id="jHNoP">9.将更改推送至GitHub</h1>
执行以下指令：

```bash
git push -u origin main
```

执行后，在对应处输入GitHub用户名和个人访问Tokens，如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760488404132-e0bb2f3c-935c-4799-89a7-d06a15b81308.png)

个人访问Tokens可以这样生成：

在GitHub设置界面往下划，找到"Developer setting"

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760488686213-90dfd51c-e53a-4a5a-a0b8-7b1d956f6c66.png)

进入后点击"Personal access tokens"中的"Tokens(classic)",再点击右上角的"Generate new token",

选择"Generate new token (classic)"

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760488864424-aaeb0df6-c7e7-4277-a577-55207318ce29.png)

输入用户密码后，勾选以下选项，并划到底部，点击生产Tokens

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760489024981-f078d5bc-cee0-4cf7-a8ab-efe5c6aad217.png)

如图，复制tokens到终端，运行指令

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760455664947-46901126-a0fa-4abb-9eb9-89b12ed6e640.png)

运行结果如图：  
![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760489135200-6a3f3805-4131-4b43-9059-18f492fc7fcc.png)

<h1 id="NFmNn">10.验证连接</h1>
打开GitHub仓库，若project_1仓库界面如图：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760489237534-742381cd-4707-4215-afed-1ae0d1045e4a.png)

则说明



