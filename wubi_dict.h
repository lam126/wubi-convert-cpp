#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>


using namespace std;

vector<string> split(const string &s, const char &delim) {
  vector<string> result;
  string token = "";
  for (char ch : s) {
    if (ch == delim) {
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
  return result;
}

// wubi_dict is a map of wubi code to its corresponding Chinese characters.
unordered_map<string, string> wubi_dict;

// load_wubi_dict loads the wubi dictionary from a file.
void load_wubi_dict(const string &filename) {
  cout << "Loading wubi dictionary from " << filename << endl;
  ifstream infile(filename);
  if (!infile) {
    cerr << "Error: cannot open file " << filename << endl;
    return;
  }
  string line;
  while (getline(infile, line)) {
    vector<string> tokens = split(line, '\t');
    string unicode = tokens[0];
    string code = tokens[2];
    wubi_dict[unicode] = code;
  }
  infile.close();
}