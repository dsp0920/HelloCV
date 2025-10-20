#include <string>
using namespace std;

class Crypto {
public:

	static string caesarEncrypt(const string& text, int key);  //¿­Èö¼ÓÃÜ
	static string caesarDecrypt(const string& text, int key);   //¿­Èö½âÃÜ
};