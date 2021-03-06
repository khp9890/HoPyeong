#include "JSFile.h"
     
char* JSFile::readline() {
 char buffer[BUFSIZ];
 char* line;
 if (fgets(buffer, BUFSIZ, rfile) == NULL) {
  return NULL;
 }
     
 if (buffer[strlen(buffer) - 1] == '\n') {
  buffer[strlen(buffer) - 1] = '\0'; //delete new line;
 }
 line = new char[strlen(buffer)+1];
 strcpy(line, buffer);
 return line;
}
     
void JSFile::printEndStatement() {
 /*int a = rand() % 5;
 if (a == 0 || a == 1) { // 40%
  fprintf(wfile, "; ");
 }
 else {
  
 }*/
 fprintf(wfile, "\n");
}
vector< vector<char>* >* JSFile::getStringList(int len, char* line) {
 vector< vector<char>* >* string_list = new vector< vector<char>* >;
     
 vector<char> *string_content;
 char st_mode = 0;
 int jsonMode=0;
     
 for (int i = 0; i < len; i++) {
     
  if (line[i] == '{') {
   i++;
   while (1) {
    while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' && i < len)
     i++;
    if (i >= len) break;
    if (i == len || line[i] == '}') {
     jsonMode = 0; break;
    }
     
    while (line[i] != ':'  && i < len)//key
     i++;
    i++;
    if (i >= len) break;
    while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'  && i < len)
     i++;
     
    if (i >= len) break;
    if (line[i] == '\"' || line[i] == '\'') {//value
     char t = line[i++];
     string_content = new vector<char>;
     
     while (line[i] != t  && i < len) {
      string_content->push_back(line[i]);
      i++;
     }
     string_list->push_back(string_content);
     if (i >= len) break;
     
    }
    if (i >= len) break;
    while (line[i] != ',' && line[i] != '}'  && i < len)
     i++;
    if (i >= len) break;
    if (line[i] == '}') {
     i++;
     jsonMode = 0;
     break;
    }
     
    i++;
    if (i >= len) break;
   }
  }
  if (i >= len) break;
  if (st_mode == 0 && line[i] == '\"') {
   string_content = new vector<char>;
   st_mode = '\"';
  }
  else if (st_mode == 0 && line[i] == '\'') {
   string_content = new vector<char>;
   st_mode = '\'';
  }
  else if (st_mode == '\"' && line[i] == '\"') {
   string_list->push_back(string_content);
   st_mode = 0;
   string_content = NULL;
  }
  else if (st_mode == '\'' && line[i] == '\'') {
   string_list->push_back(string_content);
   st_mode = 0;
   string_content = NULL;
  }
  else if (st_mode != 0) {
   if (string_content == NULL) {
    fputs("Error in obfuscation", stderr);
   }
   string_content->push_back(line[i]);
  }
 }
 return string_list;
}
     
string JSFile::triMethod(vector<char>* string_content, int th, char* line) {
 //srand(time(NULL));
 if (string_content->size() == 0)
  return "";
 int pieceCnt = rand() % string_content->size() + 1;
 int string_content_i = 0;
     
 string switchChar = "";
 for (int i = 0; i < pieceCnt; i++) {
  
  int numberOfChar = rand() % 
   ((string_content->size() - string_content_i) - (pieceCnt - i) + 1) + 1;
  if (i == pieceCnt - 1) {
   numberOfChar = (string_content->size() - string_content_i);
  }
  int randomGen = rand() % 20 + 5;
     
  int ranV1 = rand() % 987654321 + 5;
  int ranV2 = rand() % 987654321 + 4;
     
  if (i != 0) {
   switchChar += "+";
  }
  switchChar += "(";
  if (ranV1 > ranV2) { // real string go to true area
   switchChar += (std::to_string(ranV1) + ">" + std::to_string(ranV2));
   switchChar += " ? ";
   switchChar += "\"";
   char before = 0;
   for (int j = 0; j < numberOfChar; j++) {
     
    if ((j == numberOfChar - 1 && (string_content->at(string_content_i) == '\\')
     || ((string_content->at(string_content_i) == '\\') && string_content->at(string_content_i + 1) != '\"' && string_content->at(string_content_i + 1) != '\''))) {
     switchChar += '\\';
    }
    if (string_content->at(string_content_i) == '\"' && before != '\\')// && th == -1 )
     switchChar += "\\";
     
    switchChar += string_content->at(string_content_i++);
    before = string_content->at(string_content_i - 1);
   }
   switchChar += "\"";
   switchChar += " : ";
   switchChar += "\"";
   int l = rand() % randomGen;
   for (int j = 0; j < randomGen; j++) {
    if (l == j) {
     switchChar += ';';
     continue;
    }
    int k = rand() % 2;
    if (k)
     switchChar += (rand() % 26 + 1 + 'A');
    else
     switchChar += (rand() % 26 + 1 + 'a');
   }
   switchChar += "\"";
  }
  else { // real string go to false area
   switchChar += (std::to_string(ranV1) + ">" + std::to_string(ranV2));
   switchChar += " ? ";
   switchChar += "\"";
   int l = rand() % randomGen;
   for (int j = 0; j < randomGen; j++) {
    if (l == j) {
     switchChar += ';';
     continue;
    }
    int k = rand() % 2;
    if (k)
     switchChar += (rand() % 26 + 1 + 'A');
    else
     switchChar += (rand() % 26 + 1 + 'a');
   }
   switchChar += "\"";
   switchChar += " : ";
   switchChar += "\"";
   char before = 0;
   for (int j = 0; j < numberOfChar; j++) {
    if ((j == numberOfChar - 1 && (string_content->at(string_content_i) == '\\')
     || ((string_content->at(string_content_i) == '\\') && string_content->at(string_content_i + 1) != '\"' && string_content->at(string_content_i + 1) != '\''))) {
     switchChar += '\\';
    }
    if (string_content->at(string_content_i) == '\"' && before != '\\')// && th == -1 )
     switchChar += "\\";
     
    switchChar += string_content->at(string_content_i++);
    before = string_content->at(string_content_i - 1);
   }
   switchChar += "\"";
  }
  switchChar += ")";
 }//TODO removed
 //switchChar += '\n';
 return switchChar;
}
string JSFile::parenMethod(vector<char>* string_content, int th, char* line)
{
 if (string_content->size() == 0)
  return "";
 //srand(time(NULL));
 //int pesudoChar = rand() % parenSize;
 int pieceCnt = rand() % string_content->size() + 1;
 int string_content_i = 0;
     
 string switchChar = "";
 for (int i = 0; i < pieceCnt; i++) {
  int numberOfChar = rand() %
   ((string_content->size() - string_content_i) - (pieceCnt - i) + 1) + 1;
  if (i == pieceCnt - 1) {
   numberOfChar = (string_content->size() - string_content_i);
  }
  int randomGen = rand() % 4 + 2;
     
  if (i != 0) {
   switchChar += "+";
  }
  switchChar += "(";
  for (int j = 0; j < randomGen; j++) {
   if (j != 0) {
    switchChar += ",";
   } 
   switchChar += "\"";
   for (int k = 0; k < numberOfChar; k++) {
    int s;
    do {
     s = rand() % 90 + 35;
    } while (s == 92 || s == 34 || s == 39 || s == 96);
    switchChar += s;
   }
   
   switchChar += "\"";
  }
  
  switchChar += ",";
  switchChar += "\"";
     
  char before = 0;
  for (int j = 0; j < numberOfChar; j++) {
   if ((j == numberOfChar-1 && (string_content->at(string_content_i) == '\\')
    || ((string_content->at(string_content_i) == '\\') && string_content->at(string_content_i+1) != '\"' && string_content->at(string_content_i + 1) != '\''))) {
    switchChar += '\\';
   }
   if ( string_content->at(string_content_i) == '\"' && before != '\\' )// && th == -1 )
    switchChar += "\\";
   
   switchChar += string_content->at(string_content_i++);
   before = string_content->at(string_content_i - 1);
  }
  switchChar += "\"";
  switchChar += ")";
 }//TODO removed
 //switchChar += '\n';
     
 return switchChar;
}
     
string JSFile::escapeMethod(vector<char>* string_content, int th, char* line) {
 
 if (string_content->size() == 0)
  return "";
 string switchChar = "";
 switchChar = "unescape(\"";
 for (int i = 0; i < string_content->size(); i++) {
  char w = string_content->at(i);
  if ( (w >= '0' && w <= '9') || 
   (w >= 'a' && w <= 'z' ) ||
   (w >= 'A' && w <= 'Z') ||
   (w == '*' || w == '@' || w == '-' || w == '_' || w == '+' || w == '.' || w == '/' ))
   switchChar += w;
  else {
   wchar_t s[20];
   char a[20];
   char32_t w32 = w;
   unsigned long b = w32;
   //printf("%c:", w);
   //wprintf(L"0x%04x\n", b);
   wsprintf(s, L"%%%02x", b);
   wcstombs(a, s, 7);
   //printf("%s", a);
   switchChar += a;
  }
 }
     
 switchChar += "\")";
 //TODO removed
 //switchChar += '\n';
 return switchChar;
}
     
string JSFile::evalMethod(string* result, vector<char>* string_content, int th, char* line) {
     
 if (string_content->size() == 0)
  return "";
 string switchChar = "";
     
 char* variableName = createRandomVariable();
 *(result) += variableName;
 *(result) += " = \"";
 for (int i = 0; i < string_content->size(); i++) {
  if (i != 0) {
   (*result) += ",";
  }
  //wchar_t s[20];
  char a[20];
  //char32_t w32 = line[i];
  //unsigned long b = w32;
  //printf("%c:", w);
  //wprintf(L"0x%04x\n", b);
  sprintf(a, "%d", string_content->at(i));
  //wcstombs(a, s, 7);
  //printf("%s", a);
  (*result) += a;
 }
 *(result) += "\";\n";
 *(result) += variableName;
 *(result) += "= eval(\"String.fromCharCode(\"+";
 *(result) += variableName;
 *(result) += "+\")\");";
     
 switchChar += variableName;
 //TODO removed
 delete variableName;
 return switchChar;
}
     
string JSFile::evalMethod(char* line) {
     
 string result = "eval(";
 bool flag = false;
 char character = 0;
     
 for (int i = 0; i < strlen(line); i++) {
     
  if (flag == true && (line[i] == character)) {
   character = 0;
   flag = false;
   result += line[i];
   continue;
  }
     
  if (line[i] == '\n') continue;
  if (i == strlen(line) - 1 && line[i] == ';') break;
  if( !flag ) 
   result += line[i];
  else {
   if ((line[i] >= 'A' && line[i] <= 'Z') ||
    (line[i] >= 'a' && line[i] <= 'z') ) {
    wchar_t s[20];
    char a[20];
    char32_t w32 = line[i];
    unsigned long b = w32;
    //printf("%c:", w);
    //wprintf(L"0x%04x\n", b);
    wsprintf(s, L"%%%02x", b);
    wcstombs(a, s, 7);
    //printf("%s", a);
    result += a;
   }
  }
  
  if (flag == false && (line[i] == '\'' || line[i] == '\"')) {
   character = line[i];
   flag = true;
  }
  
 }
     
 result += ");";
 result += "\n";
 return result;
}
string JSFile::splitMethod(string* result, vector<char>* string_content, int th, char* line, int depth) {
 
 if (string_content->size() == 0)
  return "";
 int index = 0;
 int string_content_i = 0;
 char* variableName;
 int pieceCnt = 1;
 if (string_content->size() > 1) {
  pieceCnt = rand() % (string_content->size() - 1) + 2;
 }
 string switchChar = "";
 for (int i = 0; i < pieceCnt - 1; i++) {
  int numberOfChar = rand() % 
   ((string_content->size()-string_content_i) - (pieceCnt-i) + 1) + 1;
     
  if (i == pieceCnt - 1) {
   numberOfChar = (string_content->size() - string_content_i);
  }
  variableName = createRandomVariable();
  (*result) += variableName;
  //(*result) += std::to_string(++index);
  (*result) += "=";
  //fprintf(wfile, "%s", variableName);
  //fprintf(wfile, "%d", ++index);
  //fprintf(wfile, "=");
  if (i != 0) 
   switchChar += "+";
  switchChar += string(variableName);
  //switchChar += (string(variableName) + std::to_string(index));
  //(*result) += "\"";
  //fprintf(wfile, "\"");
  vector<char>* string_content_this = new vector<char>;
  char before = 0;
  for (int j = 0; j < numberOfChar; j++) {
   if ((j == numberOfChar - 1 && (string_content->at(string_content_i) == '\\')
    || ((string_content->at(string_content_i) == '\\') && string_content->at(string_content_i + 1) != '\"' && string_content->at(string_content_i + 1) != '\'') )) {
    string_content_this->push_back('\\');
   }
   if (string_content->at(string_content_i) == '\"' && before != '\\')// && th == -1 )
    string_content_this->push_back('\\');
   string_content_this->push_back( string_content->at(string_content_i++) );
   before = string_content->at(string_content_i - 1);
   /*if (string_content->at(string_content_i) == '\"')// && th == -1 )
    (*result) += "\\";
   (*result) += string_content->at(string_content_i++);*/
   //fprintf(wfile, "%c", string_content->at(string_content_i++));
  }
  if (depth != 0) {
   (*result) += "\"";
   for (int i = 0; i < string_content_this->size(); i++) {
    (*result) += string_content_this->at(i);
   }
   (*result) += "\"";
  }
  else {
   int method = rand() % 2;
   if (method == 0)
    (*result) += parenMethod(string_content_this, 0, NULL);
   else
    (*result) += triMethod(string_content_this, 0, NULL);
  }
  //(*result) += "\"";
  //fprintf(wfile, "\"");
  
  
  (*result) += ";";
  
  //TODO removed
  //(*result) += '\n';
  
  //printEndStatement();
  delete string_content_this;
  delete variableName;
 }
 //print all remain string
 int remainChar = string_content->size() - string_content_i;
 variableName = createRandomVariable();
 (*result) += variableName;
 //(*result) += std::to_string(++index);
 //fprintf(wfile, "%s", variableName);
 //fprintf(wfile, "%d", ++index);
 if (pieceCnt != 0)
  switchChar += "+";
 switchChar += (string(variableName));
 (*result) += "=";
 //(*result) += "\"";
 //fprintf(wfile, "=");
 //fprintf(wfile, "\"");
 vector<char>* string_content_this = new vector<char>;
 char before = 0;
 for (int j = 0; j < remainChar; j++) {
  if ((j == remainChar-1 && (string_content->at(string_content_i) == '\\')
   || ((string_content->at(string_content_i) == '\\') && string_content->at(string_content_i + 1) != '\"' && string_content->at(string_content_i + 1) != '\''))) {
   string_content_this->push_back('\\');
  }
  if (string_content->at(string_content_i) == '\"' && before != '\\')// && th == -1 )
   string_content_this->push_back('\\');
  string_content_this->push_back(string_content->at(string_content_i++));
  //fprintf(wfile, "%c", string_content->at(string_content_i++));
  before = string_content->at(string_content_i - 1);
 }
 if (depth != 0) {
  (*result) += "\"";
  for (int i = 0; i < string_content_this->size(); i++) {
   (*result) += string_content_this->at(i);
  }
  (*result) += "\"";
 }
 else {
  int method = rand() % 2;
  if (method == 0)
   (*result) += parenMethod(string_content_this, 0, NULL);
  else
   (*result) += triMethod(string_content_this, 0, NULL);
 }
 delete string_content_this;
 //(*result) += "\"";
 //fprintf(wfile, "\"");
 (*result) += ";";
 //printEndStatement();
     
 //change process of line
 int len = strlen(line);
 
 for (int i = 0; i < len; i++) {
  if (line[i] == '\'' || line[i] == '\"' && th == 0) {
   index = i; break;
  }
  else if (line[i] == '\'' || line[i] == '\"') {
   th -= 1;
  }
 }
 delete variableName;
 return switchChar;
}
     
char* JSFile::createRandomVariable() {
 char* variableName = new char[20];
 for (int i = 0; i < 19; i++) {
  variableName[i] = rand() % 26 + 'a';
 }
 variableName[19] = '\0';
 return variableName;
}
     
bool JSFile::openFile() {
 string dest_filename = "../result.js";
 rfile = fopen(filename.c_str(), "rt");
 if (rfile == NULL) {
  fprintf(stdout, "Fail to read %s", filename);
  return false;
 }
 //wfile = fopen(dest_filename.c_str(), "wt");
 wStream.open(dest_filename.c_str(), ios::out);
 /*if (wfile == NULL) {
  fprintf(stdout, "Fail to write %s", dest_filename);
  return false;
 }*/
 return true;
}
void JSFile::writeFile(string s) {
 wStream << s << endl;
}
     
bool JSFile::setFile(FILE* readFile, FILE* writeFile) {
 if (readFile == NULL || writeFile == NULL) {
  fputs("Error occur", stderr);
  exit(1);
 }
 rfile = readFile;
 wfile = writeFile;
}
string JSFile::obfuscation(int depth) {
 bool base = false;
 char* line;
 string statement;
 char t,temp;
 int state = 0;
 string result = "";
 char before = 0;
 while (1) {
  statement = "";
  while (fscanf(rfile,"%c", &t) == 1) {
   if (t == '\t')
    continue;
   if (state != 0 && t == '\n')
    continue;
   else if (state == 0 && t == '\n' &&
    strlen(statement.c_str()) != 0)
    break;
   /*else if (t == '\n')
    continue;*/
   
   statement += t;
    if (statement.find("function") != -1) {
    state = 1;
    while (fscanf(rfile, "%c", &t) == 1) {
     statement += t;
     if (t == '{')
      break;
    }
    statement += obfuscation(depth+1);
    state = -3;
    break;
   }
   else if (statement.find("//") != -1) {
    while (fscanf(rfile, "%c", &t) && t != '\n');
    state = -1;
    break;
   }
   else if (statement.find("/*") != -1) {
    while (fscanf(rfile, "%c", &t)) {
     statement += t;
     if (statement.find("*/") != -1)
      break;
    }
    state = -2;
    break;
   }
   else if (t == '(' || t=='{' ) {
    state += 1;
   }
   else if (t == ')' || t== '}') {
    state -= 1;
   }
   else if (t == '}') {
    return statement;
   }
     
   else if (state == 0 && (t == ';' || t == ',')) {
    break;
   }
     
   if (statement.c_str()[0] == '\n')
    break;
  }
     
  //result += statement;
  //fprintf(wfile, "%s", statement.c_str());
  if (state < 0) {
   result += statement;
   before = 0;
   state = 0; continue;
  }
     
     
  if (strcmp(statement.c_str(), "\n") == 0) {
   state = 0;
   continue;
  }
     
  //obfuscation
  line = new char[strlen(statement.c_str()) + 1];
  strcpy(line, statement.c_str());
  int len = strlen(line);
  int switchCount = 0;
     
  vector< vector<char>* > *string_list = getStringList(len, line);
  vector<string> switchStringList;
  int size = string_list->size();
     
  int eval = rand() % 2;
  eval = 1;
  /*if (eval == 0 && t != ',' && before != ',' && 
   statement.find("return") == -1 &&
   statement.find("var") == -1 &&
   statement.find("if") == -1 && 
   statement.find("else") == -1 ) {
   result += evalMethod(line);
   //fprintf(wfile, "%s", result.c_str());
  }*/
  //else {
   for (int i = 0; i < size; i++) {
    int method = rand() % 5;
    switch (method) {
    case 0:
     switchStringList.push_back(splitMethod(&result, string_list->at(i), i, line, depth));
     break;
    case 1:
     switchStringList.push_back(parenMethod(string_list->at(i), i, line));
     break;
    case 2:
     switchStringList.push_back(triMethod(string_list->at(i), i, line));
     break;
    case 3:
     switchStringList.push_back(escapeMethod(string_list->at(i), i, line));
     break;
    case 4:
     switchStringList.push_back(evalMethod(&result, string_list->at(i), i, line));
     break;
    }
   }
   int jsonMode = 0;
   if (switchStringList.size() == 23) {
    jsonMode = 0;
   }
   for (int i = 0; i < len; i++) {
     
    if (line[i] == '{') {
     result += line[i];
     i++;
     jsonMode = 1;
     while (1) {
     
      while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' && i < len)
       i++;
      if (i >= len) break;
      if (line[i] == '}') {
       result += line[i];
       jsonMode = 0;  break;
      }
     
      while (line[i] != ':' && i < len ) {//key
       result += line[i];
       i++;
      }
      if (i >= len) break;
      result += line[i];
      i++;
      if (i >= len) break;
      while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' && i < len)
       i++;
      if (i >= len) break;
      if (line[i] == '\"' || line[i] == '\'') {//value
       char t = line[i++];
       result += switchStringList.at(switchCount++);
       while (line[i] != t) {
        i++;
       }
       i++;
      }
      if (i >= len) break;
      while (line[i] != ',' && line[i] != '}' && i < len) {
       result += line[i];
       i++;
      }
      if (i >= len) break;
      if (line[i] == '}' ) {
       result += line[i];
       i++;
       jsonMode = 0;
       break;
      }
      result += line[i];
      i++;
      if (i >= len) break;
     }
    }
    if (i >= len) break;
     
    if (line[i] == '\'' || line[i] == '\"') {
     result += switchStringList.at(switchCount++);
     //fprintf(wfile, "%s", switchStringList.at(switchCount++).c_str());
     if (line[i] == '\'')
      while (line[++i] != '\'');
     else
      while (line[++i] != '\"');
    }
    else
     result += line[i];
     //fprintf(wfile, "%c", line[i]);
   }
  //}
   /*if (t == ',')
    result += ',';
   else if (result.c_str()[0] == '{' || result.c_str()[0] == '}');
   else
    result += ";";*/
  if (t == '\n')
     result += ';';
    //result += ';';
  for (vector< vector<char>* >::iterator it = string_list->begin();
   it != string_list->end(); ++it) {
     
   vector<char>* element = *it;
   element->clear();
   delete element;
  }
     
  
  delete string_list;
  delete[] line;
     
  if (feof(rfile)) {
   return result;
  }
  before = t;
 }
 return result;
}
     
string JSFile::obfuscation(char* data, int* pos, int depth) {
 
 bool base = false;
 string statement;
 char t, temp;
 int state = 0;
 int lenLine = strlen(data);
 char before;
 string result = "";
 while (1) {
  statement = "";
  while ((*pos) < lenLine) {
   t = data[(*pos)++];
   if (t == '\t')
    continue;
   if (state != 0 && t == '\n')
    continue;
   else if (state == 0 && t == '\n' &&
    strlen(statement.c_str()) != 0)
    break;
   /*else if (t == '\n')
   continue;*/
   /*if (state != 0 && t == '\n')
   continue;*/
     
   statement += t;
   if (state == 0 && t == '\n')
    break;
   if (statement.find("function") != -1) {
    state = 1;
    while((*pos) < lenLine) {
     t = data[(*pos)++];
     statement += t;
     if (t == '{')
      break;
    }
    statement += obfuscation(data, pos, depth+1);
    state = -3;
    break;
   }
   else if (statement.find("//") != -1) {
    while ((*pos) < lenLine) {
     t = data[(*pos)++];
     if (t == '\n') break;
    }
    state = -1;
    break;
   }
   else if (statement.find("/*") != -1) {
    while ((*pos) < lenLine) {
     t = data[(*pos)++];
     statement += t;
     if (statement.find("*/") != -1)
      break;
    }
    state = -2;
    break;
   }
   else if (t == '(' || t == '{') {
    state += 1;
   }
   else if (t == ')' || t == '}') {
    state -= 1;
   }
   else if (t == '}') {
    return statement;
   }
     
   else if (state == 0 && (t == ',' || t == ';')) {
    break;
   }
  }
     
  //result += statement;
  //fprintf(wfile, "%s", statement.c_str());
  if (state < 0) {
   result += statement;
   before = 0;
   state = 0; continue;
  }
     
     
  if (strcmp(statement.c_str(), "\n") == 0) {
   state = 0;
   continue;
  }
     
     
  //obfuscation
  char* line = new char[strlen(statement.c_str()) + 1];
  strcpy(line, statement.c_str());
  int len = strlen(line);
  int switchCount = 0;
     
  vector< vector<char>* > *string_list = getStringList(len, line);
  vector<string> switchStringList;
  int size = string_list->size();
     
     
     
  for (int i = 0; i < size; i++) {
   int method = rand() % 5;
   //method = 0;
   switch (method) {
   case 0:
    switchStringList.push_back(splitMethod(&result, string_list->at(i), i, line, depth));
    break;
   case 1:
    switchStringList.push_back(parenMethod(string_list->at(i), i, line));
    break;
   case 2:
    switchStringList.push_back(triMethod(string_list->at(i), i, line));
    break;
   case 3:
    switchStringList.push_back(escapeMethod(string_list->at(i), i, line));
    break;
   case 4:
    switchStringList.push_back(evalMethod(&result, string_list->at(i), i, line));
    break;
   }
  }
  int jsonMode = 0;
  for (int i = 0; i < len; i++) {
   if (line[i] == '{') {
    result += line[i];
    i++;
    jsonMode = 1;
    while (1) {
     while (i < len && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
      i++;
     if (i >= len) break;
     if (i == len || line[i] == '}') {
      result += line[i];
      jsonMode = 0;  break;
     }
     
     while (i < len && line[i] != ':') {//key
      result += line[i];
      i++;
     }
     if (i >= len) break;
     result += line[i];
     i++;
     if (i >= len) break;
     while (i < len && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
      i++;
     
     if (line[i] == '\"' || line[i] == '\'') {//value
      char t = line[i++];
      result += switchStringList.at(switchCount++);
      while (i < len && line[i] != t) {
       i++;
      }
      i++;
     }
     if (i >= len) break;
     while (i < len && line[i] != ',' && line[i] != '}') {
      result += line[i];
      i++;
     }
     if (i >= len) break;
     if (line[i] == '}') {
      result += line[i];
      i++;
      jsonMode = 0;
      break;
     }
     result += line[i];
     i++;
     if (i >= len) break;
    }
   }
   if (line[i] == '\'' || line[i] == '\"') {
    result += switchStringList.at(switchCount++);
    //fprintf(wfile, "%s", switchStringList.at(switchCount++).c_str());
    if (line[i] == '\'')
     while (line[++i] != '\'');
    else
     while (line[++i] != '\"');
   }
   else
    result += line[i];
   //fprintf(wfile, "%c", line[i]);
  }
  /*if (t == ',');
  else if (t == ';');
  else if (result.c_str()[0] == '{' || result.c_str()[0] == '}');*/
  if (t == '\n')
   result += ';';
  //printEndStatement();
  for (vector< vector<char>* >::iterator it = string_list->begin();
   it != string_list->end(); ++it) {
     
   vector<char>* element = *it;
   element->clear();
   delete element;
  }
     
     
  delete string_list;
  delete[] line;
  if ((*pos) == lenLine) {
   return result;
  }
  before = 0;
 }
 return result;
}
