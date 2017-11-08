#include <string>
#include <cstring>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <map>
#include <locale>
#include <codecvt>
#include <iostream>
#include <Windows.h>
#include <fstream>
using namespace std;
class JSFile {
private:
 const int parenSize = 5;
 string filename;
 string dest_filename;
 FILE *rfile, *wfile;
 ofstream wStream;
     
 char* readline();
 vector< vector<char>* >* getStringList(int len, char* line);
 string splitMethod(string* result, vector<char>* string_content, int th, char* line, int depth);
 string parenMethod(vector<char>* string_conetnt, int th, char* line);
 string triMethod(vector<char>* string_content, int th, char* line);
 string escapeMethod(vector<char>* string_content, int th, char* line);
 string evalMethod(string* result, vector<char>* string_content, int th, char* line);
 string evalMethod(char* line);
 char* createRandomVariable();
 void printEndStatement();
 
public:
 JSFile(string fn) {
  filename = fn;
 }
 ~JSFile() {
  //free all variable
 }
 bool openFile();
 void writeFile(string s);
 bool setFile(FILE* readFile, FILE* writeFile);
 string obfuscation(int depth);
 string obfuscation(char* data,int* pos,int depth);
};
