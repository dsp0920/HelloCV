#include "FileHandler.h"
#include <fstream>
#include <stdexcept>

string FileHandler::readFile(const string& filePath) {
	ifstream file(filePath);              //创建ifstream对象file，并打开文件

	//判断文件是否成功打开
	if (!file.is_open()) {
		throw runtime_error("打开文件失败");
	}
	string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());  //读取文件内容到字符串text
	file.close();     //关闭文件
	return text;      //返回读取的内容
}


//用布尔值表示写入是否成功
bool FileHandler::writeFile(const string& text, const string& filePath) {
	ofstream file(filePath);      //创建ofstream对象file，并打开文件
	if (!file.is_open()) {         //判断文件是否成功打开
		return false;            //打开失败说明写入失败，返回false
	}
	file << text;             //将text内容写入文件
	file.close();            //关闭文件
	return true;		    //文件关闭说明写入成功，返回true
}