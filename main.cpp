#include <cstdio>
#include <Windows.h>
#include "JSFile.h"
#include "HtmlFile.h"
int main() {
 srand(time(NULL));
 
 while (1) {
  int InputNum;
  fprintf(stdout, "*------------------------------------------------------*\n");
  fprintf(stdout, "|                     M  E  N  U                       |\n");
  fprintf(stdout, "*------------------------------------------------------*\n");
  fprintf(stdout, "| 1. JavaScript Obfuscation                            |\n");
  fprintf(stdout, "| 2. HTML Obfuscation                                  |\n");
  fprintf(stdout, "| 3. Download From Web                                 |\n");
  fprintf(stdout, "| 4. EXIT                                              |\n");
  fprintf(stdout, "*------------------------------------------------------*\n");
     
  for (;;) {
   printf("Input Menu Number : ");
   scanf("%d", &InputNum);
     
   if (InputNum == 1 || InputNum == 2 || InputNum == 3 || InputNum == 4)
    break;
   else
    printf("Input Error!!!\nTry Again!!!\n");
  }
  system("cls");
     
  while (getchar() != '\n');
     
  char buffer[BUFSIZ];
     
  if (InputNum == 1) {
   fputs("Input filename: ", stdout);
   fgets(buffer, BUFSIZ, stdin);
   if (buffer[strlen(buffer) - 1] == '\n') {
    buffer[strlen(buffer) - 1] = '\0';
   }
   JSFile jsfile(buffer);
   jsfile.openFile();
   jsfile.writeFile(jsfile.obfuscation(0));
     
   fputs("Done. Press Any key to continue.",stdout);
   getchar();
  }
  else if (InputNum == 2) {
   fputs("Input filename: ", stdout);
   fgets(buffer, BUFSIZ, stdin);
   if (buffer[strlen(buffer) - 1] == '\n') {
    buffer[strlen(buffer) - 1] = '\0';
   }
   HtmlFile htmlFile(buffer);
   htmlFile.openFile();
   htmlFile.obfuscation();
   fputs("Done. Press Any key to continue.", stdout);
   getchar();
  }
  else if (InputNum == 3) {
   int InputNum;
   char buffer[BUFSIZ];
   string oriFileName = "../downloaded.html";
   fprintf(stdout, "Input site address: ");
   scanf("%s", buffer);
     
   string command = "python getSite.py " + string(buffer) + " > ../downloaded.html";
   int status = system(command.c_str());
   if (status < 0) {
    fputs("Error in python", stderr);
    exit(1);
   }
   else {
    Sleep(1000);
    fputs("Success to download html file\n", stdout);
   }
     
   HtmlFile htmlFile(oriFileName.c_str());
   htmlFile.openFile();
   htmlFile.obfuscation();
   fputs("Done. Press Any key to continue.", stdout);
   getchar();
  }
  else if (InputNum == 4) {
   break;
  }
  system("cls");
 }
 return 0;
}
