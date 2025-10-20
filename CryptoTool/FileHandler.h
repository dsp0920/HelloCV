#include <string>
using namespace std;

class FileHandler {
public:
	static string readFile(const string& filePath);           //读取文件内容
	static bool writeFile(const string& content, const string& filePath);    //写入内容到文件
};
