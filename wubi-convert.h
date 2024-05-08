#include "wubi_dict.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class WubiConvert {
private:
  vector<string> utf8_split(const string &str);
  // 按utf8编码分词
  uint16_t utf8_to_unicode(const std::string &utf8_str);
  // 转换utf8编码为unicode

  vector<string> char_in_dict(string input);
  // 将字符串中在五笔字典中的汉字提取出来
public:
  // WubiConvert();
  vector<string> single_to_wubi(string han);
  // 查字典,将单个汉字转成五笔编码
  vector<vector<string>> convert_multi(string input);
  // 输入字符串转换成五笔编码,多种转换方式
  string convert(string input);
  // 输入字符串转换成五笔编码
  vector<string> phrase_segment(string input);
  // 输入字符串分词
};

uint16_t WubiConvert::utf8_to_unicode(const std::string &utf8_str) {
  if (utf8_str.empty()) {
    return 0;
  }
  uint16_t unicode = 0;
  int len = utf8_str.length();
  if (len == 1) {
    unicode = static_cast<uint16_t>(utf8_str[0]);
  } else if (len == 2) {
    unicode = (static_cast<uint16_t>(utf8_str[0]) & 0x1F) << 6;
    unicode |= (static_cast<uint16_t>(utf8_str[1]) & 0x3F);
  } else if (len == 3) {
    unicode = (static_cast<uint16_t>(utf8_str[0]) & 0x0F) << 12;
    unicode |= (static_cast<uint16_t>(utf8_str[1]) & 0x3F) << 6;
    unicode |= (static_cast<uint16_t>(utf8_str[2]) & 0x3F);
  } else if (len == 4) { // 四字节UTF-8字符
    unicode = (static_cast<uint16_t>(utf8_str[0]) & 0x07) << 18;
    unicode |= (static_cast<uint16_t>(utf8_str[1]) & 0x3F) << 12;
    unicode |= (static_cast<uint16_t>(utf8_str[2]) & 0x3F) << 6;
    unicode |= (static_cast<uint16_t>(utf8_str[3]) & 0x3F);
  }
  return unicode;
}

vector<string> WubiConvert::utf8_split(const string &str) {
  vector<string> result;
  size_t pos = 0;
  // 获取第一个字符的字节长度
  size_t charLen;

  while (pos < str.length()) {
    unsigned char firstByte = str[pos];

    if (firstByte < 0x80) {
      charLen = 1; // ASCII 字符
    } else if (firstByte < 0xE0) {
      charLen = 2; // 两字节 UTF-8 字符
    } else if (firstByte < 0xF0) {
      charLen = 3; // 三字节 UTF-8 字符
    } else {
      charLen = 4; // 四字节 UTF-8 字符
    }

    // 创建一个变量来存储一个字符
    std::string firstChar(str.substr(pos, charLen)); // 获取前 charLen 个字节
    result.push_back(firstChar);                     // 加入结果集
    pos += charLen; // 指针移动到下一个字符的位置
  }
  return result;
}

vector<string> WubiConvert::single_to_wubi(string han) {
  vector<string> result;
  uint16_t han_unicode = utf8_to_unicode(han);
  std::stringstream ss;
  ss << "0x" << std::hex // 设置流为 16 进制
     << han_unicode;

  if (wubi_dict.find(ss.str()) != wubi_dict.end()) {
    auto it = wubi_dict.find(ss.str());
    string wubi_code = (*it).second;
    //分割字符串中的,符号
    string token = "";
    for (char ch : wubi_code) {
      if (ch == ',') {
        if (!token.empty()) {
          result.push_back(token); // 添加非空子串
          token.clear();           // 清除临时变量
        }
      } else {
        token += ch; // 继续添加字符
      }
    }
    if (!token.empty()) {
      result.push_back(token); // 添加最后一个子串
    }
  } else {
    result.push_back(han); // 未找到对应五笔编码，返回原字符}
  }
  return result;
}

vector<string> WubiConvert::char_in_dict(string input) {
  vector<string> result;
  vector<string> words = utf8_split(input);

  for (string han : words) {
    uint16_t han_unicode = utf8_to_unicode(han);
    std::stringstream ss;
    ss << "0x" << std::hex << han_unicode;
    if (wubi_dict.find(ss.str()) != wubi_dict.end()) {
      result.push_back(han);
    }
  }
  return result;
}

vector<vector<string>> WubiConvert::convert_multi(string input) {
  vector<string> words = utf8_split(input);
  vector<vector<string>> result;
  for (string word : words) {
    vector<string> wubi_code = single_to_wubi(word);
    result.push_back(wubi_code);
  }
  return result;
}

string WubiConvert::convert(string input) {
  string result = "";
  vector<string> words = char_in_dict(input);
  int len_words = words.size();

  if (len_words == 1)
    return single_to_wubi(words[0])[0];
  else if (len_words == 2) {
    result = single_to_wubi(words[0])[0].substr(0, 2);
    result += single_to_wubi(words[1])[0].substr(0, 2);
  } else if (len_words == 3) {
    result += single_to_wubi(words[0])[0][0];
    result += single_to_wubi(words[1])[0][0];
    result += single_to_wubi(words[2])[0].substr(0, 2);
  } else if (len_words >= 4) {
    result = single_to_wubi(words[0])[0][0];
    result += single_to_wubi(words[1])[0][0];
    result += single_to_wubi(words[2])[0][0];
    result += single_to_wubi(words[len_words - 1])[0][0];
  }
  return result;
}

vector<string> WubiConvert::phrase_segment(string input) {
  vector<string> words = utf8_split(input);
  return words;
}
