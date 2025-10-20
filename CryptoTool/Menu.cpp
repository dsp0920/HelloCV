#include "Menu.h"
#include "Crypto.h"
#include "FileHandler.h"
#include <iostream>
#include <string>
using namespace std;
void Menu::showMenu() {
    int choice = 0;
    //չʾ�˵��������û�����
    while (true) {
        cout << "\n----CryptoTool-----------\n";
        cout << "1. �����ı�\n" << endl;
        cout << "2. �����ı�\n" << endl;
        cout << "3. �����ļ�\n" << endl;
        cout << "4. �����ļ�\n" << endl;
        cout << "0. �˳�\n" << endl;
        cout << "����������ѡ�" << endl;
        cin >> choice;


        if (choice == 0) {
            break;
        }
        int key = 0;
        string text, filePath, outputPath;
        // ��������ִ����Ӧ����
        switch (choice) {
            //�ı�����
        case 1:
            cout << "������Ҫ���ܵ��ı�: " << endl;
            cin.ignore();
            getline(cin, text);
            cout << "��������Կ: " << endl;
            cin >> key;
            cout << "���ܽ��: " << Crypto::caesarEncrypt(text, key) << endl;
            break;
            //�ı�����
        case 2:
            cout << "��������Ҫ���ܵ��ı�: " << endl;
            cin.ignore();
            getline(cin, text);
            cout << "��������Կ: " << endl;
            cin >> key;
            cout << "���ܽ��: " << Crypto::caesarDecrypt(text, key) << endl;
            break;
            //�ļ�����
        case 3:
            cout << "��������Ҫ���ܵ��ı�·��: " << endl;
            cin.ignore();
            getline(cin, filePath);
            cout << "��������Կ: " << endl;
            cin >> key;
            try {
                text = FileHandler::readFile(filePath);
                text = Crypto::caesarEncrypt(text, key);
                outputPath = "encrypted_" + filePath;
                if (FileHandler::writeFile(text, filePath)) {
                    cout << "���ܽ���ѱ��浽: " << outputPath << endl;
                }
                else {
                    cout << "����ʧ��" << endl;
                }
            }
            //�����ļ���ȡ���쳣
            catch (const exception& e) {
                cout << "����" << e.what() << endl;
            }
            break;
            //�ļ�����
        case 4:
            cout << "������Ҫ���ܵ��ı�·��: " << endl;
            cin.ignore();
            getline(cin, filePath);
            cout << "��������Կ: " << endl;
            cin >> key;
            try {
                text = FileHandler::readFile(filePath);
                text = Crypto::caesarDecrypt(text, key);
                outputPath = "decrypted_" + filePath;
                if (FileHandler::writeFile(text, filePath)) {
                    cout << "���ܽ���ѱ��浽: " << outputPath << endl;
                }
                else {
                    cout << "����ʧ��" << endl;
                }
            }
            catch (const exception& e) {
                cout << "����" << e.what() << endl;
            }
            break;
        default:
            cout << "��Ч���룬������" << endl;
        }
    }
}