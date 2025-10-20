#include "Crypto.h"
using namespace std;
//��������ʵ�֣������ı�text����Կkey�����ؼ��ܺ���ı�
string Crypto::caesarEncrypt(const string& text, int key) {
    string result = text;
    //����ԭ�ı�ÿ���ַ�
    for (char& c : result) {
        //�ж��ַ��Ƿ�Ϊ��ĸ
        if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
            //ȷ����ĸ��׼ʱ'A'����'a'
            char base = isupper(c) ? 'A' : 'a';
            //����keyλ��������ѭ��
            c = static_cast<char>((c - base + key) % 26 + base);
        }
    }
    return result;       //���ؼ��ܺ���ı�
}


//��������ʵ�֣������ı�text����Կkey�����ؽ��ܺ���ı�
string Crypto::caesarDecrypt(const string& text, int key)
{
    string result = text;
    //���������ı�ÿ���ַ�
    for (char& c : result) {
        //�ж��ַ��Ƿ�Ϊ��ĸ
        if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
            //ȷ����ĸ��׼ʱ'A'����'a'
            char base = isupper(c) ? 'A' : 'a';
            //����keyλ�����仰˵��������26-keyλ��������ѭ��
            c = static_cast<char>((c - base + 26 - key % 26) % 26 + base);
        }
    }
    return result;       //���ؽ��ܺ���ı�
}