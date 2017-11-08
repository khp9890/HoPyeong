#pragma once
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
#include "JSFile.h"
using namespace std;
class HtmlFile {
private:
 JSFile* jsFile;
 string filename;
 string dest_filename;
 FILE *rfile;
 ofstream wStream;
 
 char* readline();
     
public:
 class HtmlFile (string fn) {
  filename = fn;
  jsFile = new JSFile(filename);
  
 }
 ~HtmlFile() {
  //free all variable
 }
 bool openFile();
 //bool setFile(FILE* readFile, FILE* writeFile);
 void obfuscation();
};
