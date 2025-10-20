#include "Menu.h"
#include "Crypto.h"
#include "FileHandler.h"
#include <iostream>
#include <string>
using namespace std;
void Menu::showMenu() {
    int choice = 0;
    //展示菜单并处理用户输入
    while (true) {
        cout << "\n----CryptoTool-----------\n";
        cout << "1. 加密文本\n" << endl;
        cout << "2. 解密文本\n" << endl;
        cout << "3. 加密文件\n" << endl;
        cout << "4. 解密文件\n" << endl;
        cout << "0. 退出\n" << endl;
        cout << "请输入您的选项：" << endl;
        cin >> choice;


        if (choice == 0) {
            break;
        }
        int key = 0;
        string text, filePath, outputPath;
        // 根据输入执行相应操作
        switch (choice) {
            //文本加密
        case 1:
            cout << "输入需要加密的文本: " << endl;
            cin.ignore();
            getline(cin, text);
            cout << "请输入密钥: " << endl;
            cin >> key;
            cout << "加密结果: " << Crypto::caesarEncrypt(text, key) << endl;
            break;
            //文本解密
        case 2:
            cout << "请输入需要解密的文本: " << endl;
            cin.ignore();
            getline(cin, text);
            cout << "请输入密钥: " << endl;
            cin >> key;
            cout << "解密结果: " << Crypto::caesarDecrypt(text, key) << endl;
            break;
            //文件加密
        case 3:
            cout << "请输入需要加密的文本路径: " << endl;
            cin.ignore();
            getline(cin, filePath);
            cout << "请输入密钥: " << endl;
            cin >> key;
            try {
                text = FileHandler::readFile(filePath);
                text = Crypto::caesarEncrypt(text, key);
                outputPath = "encrypted_" + filePath;
                if (FileHandler::writeFile(text, filePath)) {
                    cout << "加密结果已保存到: " << outputPath << endl;
                }
                else {
                    cout << "保存失败" << endl;
                }
            }
            //捕获文件读取的异常
            catch (const exception& e) {
                cout << "错误" << e.what() << endl;
            }
            break;
            //文件解密
        case 4:
            cout << "输入需要解密的文本路径: " << endl;
            cin.ignore();
            getline(cin, filePath);
            cout << "请输入密钥: " << endl;
            cin >> key;
            try {
                text = FileHandler::readFile(filePath);
                text = Crypto::caesarDecrypt(text, key);
                outputPath = "decrypted_" + filePath;
                if (FileHandler::writeFile(text, filePath)) {
                    cout << "解密结果已保存到: " << outputPath << endl;
                }
                else {
                    cout << "保存失败" << endl;
                }
            }
            catch (const exception& e) {
                cout << "错误" << e.what() << endl;
            }
            break;
        default:
            cout << "无效输入，请重试" << endl;
        }
    }
}