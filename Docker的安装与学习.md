# 一、docker的安装
## 1.卸载任何可能与docker冲突的软件包
Linux发行版可能会提供非官方的docker软件包，可能会与docker的官方软件包发生冲突，在安装docker引擎之前需要先卸载这些docker版本，以防安装失败。

指令窗输入以下指令来卸载非官方包：

```bash
for pkg in docker.io docker-doc docker-compose docker-compose-v2 podman-docker containerd runc; do sudo apt-get remove Spkg; done
```

执行结果如下：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760876274708-54081487-cc09-4c5b-8fda-95cca2c77e6d.png)

## 2.使用apt仓库
安装docker之前，需设置docker apt 仓库，这之后可以安装和更新来自仓库的docker。

指令窗依次输入以下指令：

```bash
# 添加docker官方GPG key:

sudo apt-get update
#检查系统包更新
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# 添加软件源的仓库:

echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "${UBUNTU_CODENAME:-$VERSION_CODENAME}") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
#添加完后再次更新系统包
```

运行结果如下：

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760876972303-846a853a-6f2b-4070-9ad2-b30944953f1a.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760877008399-c7a00b5f-6208-4a1d-a63e-65ab7041acad.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760877093034-4fed1548-a1b7-4dcf-855b-05d832f1223e.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760877132624-f280256c-50a4-4e69-965c-2f77dfa5f9aa.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760877161720-78a82171-1e01-4877-9689-23c09aaa183f.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760877269151-0cbcf91d-4cf4-4339-8c0e-366079593edd.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760877301563-5fc27fc2-57c4-4928-88bf-72acf3edccd0.png)



## 3.安装软件包
安装最新版本的docker软件包

```bash
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760877404222-2e4eb16a-b4a0-4abd-91bb-26c882d5c73f.png)



## 4.检查版本
```bash
sudo docker version
```

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760877477276-af8f55f3-1f86-4a3b-9cda-6e40e18bf440.png)



## 遭遇的问题
通过运行映像来验证安装是否成功时，出现了如下错误

```bash
sudo docker run hello-world
```

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760877635733-f5cdf241-0287-4702-8b0d-6635891e042e.png)

## 1.原因分析
官方的源网络不稳定，从仓库源获取映像时容易访问失败。

## 2.解决方法
#### 1.进入 `/etc/docker`文件，新建一个daemon.json文件
```bash
cd /etc/docker
sudo touch daemon.json
```

#### 2.进入daemon.json文件并输入新镜像源
进入文件

```bash
sudo nano /etc/docker/daemon.json
```

进入文件后输入以下代码

```bash
{
"registry-mirrors": [
"https://do.nark.eu.org",
"https://dc.j8.work",
"https://docker.m.daocloud.io",
"https://dockerproxy.com",
"https://docker.mirrors.ustc.edu.cn",
"https://docker.nju.edu.cn"
]
}
```

完成后退出。

#### 3.重新加载，并再次运行指令
```bash
sudo systemctl daemon-reload
#重新加载daemon

sudo docker run hello-world
#再次运行命令
```

结果如下

![](https://cdn.nlark.com/yuque/0/2025/png/61540382/1760882660303-826ea08c-fc4b-41dc-9c4a-016742f97703.png)

运行成功。

