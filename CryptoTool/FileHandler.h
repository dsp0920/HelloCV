#include <string>
using namespace std;

class FileHandler {
public:
	static string readFile(const string& filePath);           //��ȡ�ļ�����
	static bool writeFile(const string& content, const string& filePath);    //д�����ݵ��ļ�
};
