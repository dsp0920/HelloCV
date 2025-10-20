#include "Crypto.h"
using namespace std;
//凯撒加密实现，传入文本text和密钥key，返回加密后的文本
string Crypto::caesarEncrypt(const string& text, int key) {
    string result = text;
    //遍历原文本每个字符
    for (char& c : result) {
        //判断字符是否为字母
        if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
            //确认字母基准时'A'还是'a'
            char base = isupper(c) ? 'A' : 'a';
            //右移key位，并处理循环
            c = static_cast<char>((c - base + key) % 26 + base);
        }
    }
    return result;       //返回加密后的文本
}


//凯撒解密实现，传入文本text和密钥key，返回解密后的文本
string Crypto::caesarDecrypt(const string& text, int key)
{
    string result = text;
    //遍历加密文本每个字符
    for (char& c : result) {
        //判断字符是否为字母
        if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
            //确认字母基准时'A'还是'a'
            char base = isupper(c) ? 'A' : 'a';
            //左移key位，换句话说就是右移26-key位，并处理循环
            c = static_cast<char>((c - base + 26 - key % 26) % 26 + base);
        }
    }
    return result;       //返回解密后的文本
}