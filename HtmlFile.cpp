#include "HtmlFile.h"
     
bool HtmlFile::openFile() {
 dest_filename = "../result.html";
 rfile = fopen(filename.c_str(), "rt");
 if (rfile == NULL) {
  fprintf(stdout, "Fail to read %s", filename);
  return false;
 }
 wStream.open(dest_filename.c_str(), ios::out);
 /*wfile = fopen(dest_filename.c_str(), "wt");
 if (wfile == NULL) {
  fprintf(stdout, "Fail to write %s", dest_filename);
  return false;
 }*/
 //jsFile->setFile(rfile, wfile);
 return true;
}
     
char* HtmlFile::readline() {
 char buffer[BUFSIZ];
 char* line;
 if (fgets(buffer, BUFSIZ, rfile) == NULL) {
  return NULL;
 }
     
 if (buffer[strlen(buffer) - 1] == '\n') {
  buffer[strlen(buffer) - 1] = '\0'; //delete new line;
 }
 line = new char[strlen(buffer) + 1];
 strcpy(line, buffer);
 return line;
}
     
void HtmlFile::obfuscation() {
 string s;
 bool javascriptMode = false;
 char t;
 char* buffer;
 while (1) {
  while (fscanf(rfile, "%c", &t) == 1) {
   s += t;
     
   if (!javascriptMode && s.find("<script") != -1) {
    while (fscanf(rfile, "%c", &t) == 1 && t != '>')
     s += t;
    s += t;
    javascriptMode = true;
    break;
   }
   if (javascriptMode && s.find("</script>") != -1) {
    
    int len = strlen(s.c_str());
    buffer = new char[len + 2];
    strcpy(buffer, s.c_str());
    buffer[len - 9] = '\0'; //delete </script>
    int pos = 0;
    if(strlen(buffer) != 0)
     s = jsFile->obfuscation(buffer, &pos, 0);
    s += "\n</script>";
    javascriptMode = false;
    break;
   }
  }
     
  wStream << s;
  s = "";
     
  if (feof(rfile)) {
   break;
  }
 }
}
