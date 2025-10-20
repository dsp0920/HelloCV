#include "FileHandler.h"
#include <fstream>
#include <stdexcept>

string FileHandler::readFile(const string& filePath) {
	ifstream file(filePath);              //����ifstream����file�������ļ�

	//�ж��ļ��Ƿ�ɹ���
	if (!file.is_open()) {
		throw runtime_error("���ļ�ʧ��");
	}
	string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());  //��ȡ�ļ����ݵ��ַ���text
	file.close();     //�ر��ļ�
	return text;      //���ض�ȡ������
}


//�ò���ֵ��ʾд���Ƿ�ɹ�
bool FileHandler::writeFile(const string& text, const string& filePath) {
	ofstream file(filePath);      //����ofstream����file�������ļ�
	if (!file.is_open()) {         //�ж��ļ��Ƿ�ɹ���
		return false;            //��ʧ��˵��д��ʧ�ܣ�����false
	}
	file << text;             //��text����д���ļ�
	file.close();            //�ر��ļ�
	return true;		    //�ļ��ر�˵��д��ɹ�������true
}