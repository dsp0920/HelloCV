#include <string>
using namespace std;

class Crypto {
public:

	static string caesarEncrypt(const string& text, int key);  //��������
	static string caesarDecrypt(const string& text, int key);   //��������
};