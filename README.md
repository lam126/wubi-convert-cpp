汉字五笔转换工具（C++ 版）
=============================

   
将汉字转为五笔码。现只支持 86 版编码。
如需其它编码，请自行替换字典文件`wubi_dict.h`。


## 介绍

1. 将词组转成五笔编码。比如词语：`离离原上草，一岁一枯荣`。换成五笔码为：`yyda`；
2. 中文分词。比如：“你好，世界！”分词结果为：“你 好 ， 世 界 ！”；
3. 将一段输入，转成五笔码。如:`离离原上草，一岁一枯荣`：输出为：`ybmc ybm yb  , ybmc ybm yb  , drii dri dr  , hhgg hhg h  , ajj  , ，  , ggll ggl g  , mqu  , ggll ggl g  , sdg sd  , apsu aps`,以逗号分隔每一项，每一项代表一个汉字的五笔码，多个五笔码按长度降序排列。

## 使用 

1. 下载源码：`git clone https://github.com/lam126/wubi-convert-cpp.git`
2. 在你的项目中包含 `wubi-convert.h` 文件。

## 编译
     g++ -g -o main.exe .\main.cpp

## 函数说明
     vector<string> single_to_wubi(string han);
     // 查字典,将单个汉字转成五笔编码,返回其所有编码
     vector<vector<string>> convert_multi(string input);
     // 输入字符串转换成五笔编码,多种转换方式
     string convert(string input);
     // 输入字符串转换成五笔编码
     vector<string> phrase_segment(string input);
     // 输入字符串分词

## 使用示例
      #include "wubi-convert.h"
      #include <iostream>
      #include <string>

      using namespace std;

      int main() {
        //system("chcp 65001");
        //windows下中文显示乱码解决方案

        WubiConvert wubi; // 实例化 WubiConvert 对象
        string inputText = "你好，世界！";
        cout << "输入的文本：" << inputText << endl;

        // 调用 convert_multi 函数
        cout << "调用 convert_multi 函数:" << endl;
        vector<vector<string>> multi_text = wubi.convert_multi(inputText);
        for (auto &text : multi_text) {
          for (auto &wubi_text : text) {
            cout << wubi_text << " ";
          }
          cout << " | ";
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

### 输出结果
      输入的文本：你好，世界！
      调用 convert_multi 函数:
      wqiy wqi wq  | vbg vb  | ，  | anv an  | lwjj lwj  | ！  |
      调用 convert 函数转换文本:
      wval
      调用 phrase_segment 函数分词:
      你 好 ， 世 界 ！
    


## 关于

* GitHub: [https://github.com/lam126/wubi-convert-cpp](https://github.com/lam126/wubi-convert-cpp)
