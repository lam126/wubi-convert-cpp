#include "wubi-convert.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  //system("chcp 65001");

  WubiConvert wubi("D:\\MyFiles\\VScode\\C++\\wubiTool\\wubi-convert-cpp\\wubi86.dict.txt"); // 实例化 WubiConvert 对象
  string inputText = "你好，世界！";
  cout << "输入的文本：" << inputText << endl;

  // 调用 convert_multi 函数
  cout << "调用 convert_multi 函数:" << endl;
  vector<vector<string>> multi_text = wubi.convert_multi(inputText);
  for (auto &text : multi_text) {
    for (auto &wubi_text : text) {
      cout << wubi_text << " ";
    }
    cout << " , ";
  }
  cout << endl;

  // 调用 convert 函数转换文本
  cout << "调用 convert 函数转换文本:" << endl;
  string convert_text = wubi.convert(inputText);
  cout << convert_text << endl;

  // 调用 phrase_segment 函数分词
  cout << "调用 phrase_segment 函数分词:" << endl;
  vector<string> phrase_list = wubi.phrase_segment(inputText);
  for (auto &phrase : phrase_list) {
    cout << phrase << " ";
  }
  cout << endl;

  return 0;
}
