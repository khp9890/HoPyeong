#define _CRT_SECURE_NO_WARNINGS

#define ROW_VAL 1024		//배열의 행
#define COL_VAL 100			//배열의 열

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *fp;
FILE *ofp;

void InputFilePath(char arr[COL_VAL]);												//파일경로를 입력 받음
int InputCode(char Path[COL_VAL], char arr[ROW_VAL][COL_VAL]);						//소스코드입력
void PrintArray(char arr[ROW_VAL][COL_VAL]);										//입력받은 코드를 출력
void CodeAnalysis(char arr[ROW_VAL][COL_VAL], char arr2[COL_VAL][COL_VAL / 2]);		//코드 내의 변수를 인식하고 변수명을 입력
void PrintVariable(char arr[ROW_VAL][COL_VAL / 2]);									//입력받은 변수를 출력
void StraightCode(char arr[ROW_VAL][COL_VAL], char arr2[ROW_VAL * 20]);				//난독화된 코드를 1차원 배열에 한줄로 입력
void Output(char arr[ROW_VAL * 20]);												//최종 난독화된 코드를 O_test.html로 저장


int main() {
	int iter, iter2 = 0;
	int Existence, Existence2;

	char I_FilePath[COL_VAL] = { 0 };				//파일 경로를 입력 받을 1차배열
	char O_FilePath[COL_VAL] = { 0 };				//저장 할 파일 경로를 입력 받을 1차배열
	char I_Data[ROW_VAL][COL_VAL] = { 0 };			//입력받는 파일데이터를 담을 2차배열
	char I_Variable[COL_VAL][COL_VAL / 2] = { 0 };	//파일 데이터를 통해 얻은 소스의 변수명를 담을 2차배열
	char O_Data[ROW_VAL * 20] = { 0 };				//난독화된 소스를 한줄로 나열하여 저장할 1차 배열

	InputFilePath(I_FilePath);
	Existence = InputCode(I_FilePath, I_Data);

	if (Existence == 0) {
		printf("====================================================\n");
		printf("         Either unreadable or nonexistent!\n");
		printf("====================================================\n");

		return 0;
	}
	else {
		printf("====================================================\n");
		printf("                  Access success!\n");
		printf("====================================================\n");

		PrintArray(I_Data);
		CodeAnalysis(I_Data, I_Variable);
		PrintVariable(I_Variable);
		StraightCode(I_Data, O_Data);
		Output(O_Data);
	}

	return 0;
}

void InputFilePath(char arr[COL_VAL]) {
	int iter, iter2 = 0;
	int count = 0;
	char temp[COL_VAL] = { 0 };

	printf("Enter the file path : ");
	scanf("%s[^\n]", arr);

	for (iter = 0; iter < COL_VAL; iter++) {
		if (arr[iter] == '\\') {							//\가 나오면 모든 배열을 뒤로 한칸씩 밀고 그 사이에 \를 추가
			count = iter + 1;
			temp[iter2] = arr[count];
			arr[count] = arr[iter];
			for (count += 1; count < COL_VAL; count++) {
				temp[++iter2] = arr[count];
				arr[count] = temp[iter2 - 1];
			}
			iter += 1;
		}
		iter2 = 0;
	}
}

int InputCode(char Path[COL_VAL], char arr[ROW_VAL][COL_VAL]) {
	fopen_s(&fp, Path, "r");

	if (fp == NULL)
		return 0;
	else {
		while (fgets(arr++, COL_VAL, fp)) {}		//입력한 html파일을 데이터의 끝까지 입력받음
		return 1;
	}

	fclose(fp);
}

void PrintArray(char arr[ROW_VAL][COL_VAL]) {
	int iter = 0;

	printf("====================================================\n");
	printf("                     Code Print\n");
	printf("====================================================\n");

	for (iter = 0; iter < 100; iter++)			//코드를 입력받은 배열을 출력(코드출력)
		printf("%s", arr[iter]);
	printf("\n");
}

void CodeAnalysis(char arr[ROW_VAL][COL_VAL], char arr2[COL_VAL][COL_VAL / 2]) {
	int colval = 0;
	int count = 0;
	int iter, iter2, iter3 = 0;

	for (iter = 0; iter < 100; iter++) {
		if (strstr(arr[iter], "for(") != NULL)											//var형식이 입력될 수 있는 for문을 예외처리
			continue;

		if (strstr(arr[iter], "var ") == NULL)											//var를 찾아 없으면 다음 행을 탐색
			continue;

		for (iter2 = 0; iter2 < COL_VAL; iter2++) {
			if (arr[iter][iter2] == 'v') {												//var를 찾은 경우 처음으로 나오는 v를 탐색
				colval = iter2 + 4;														//v를 기준으로 4개의 열 뒤를 변수명의 첫 글자로 인식
				while (1) {
					if (arr[iter][colval] == ' ' || arr[iter][colval] == ';')			//v를 기준으로 4개의 열 뒤를 시작으로 띄어쓰기가 있는 공간을 인식
						break;
					arr2[count][iter3++] = arr[iter][colval++];							//띄어쓰기가 있는 데까지를 변수명으로 인식
				}
				iter3 = 0;
				count++;
				if (arr[iter][colval] == ' ' || arr[iter][colval] == ';')               //v를 기준으로 4개의 열 뒤를 시작으로 띄어쓰기가 있는 공간을 인식
					break;
			}
		}
	}
}

void PrintVariable(char arr[ROW_VAL][COL_VAL / 2]) {
	int iter, iter2;

	printf("====================================================\n");
	printf("                  Variable Print\n");
	printf("====================================================\n");

	for (iter = 0; iter < COL_VAL; iter++) {
		if (arr[iter][0] == 0)
			break;
		printf("%d행 : ", iter + 1);
		for (iter2 = 0; iter2 < (COL_VAL / 2); iter2++) {
			printf("%c", arr[iter][iter2]);						//입력받은 변수명을 출력
		}printf("\n");
	}printf("\n");
}

void StraightCode(char arr[ROW_VAL][COL_VAL], char arr2[ROW_VAL * 20]) {
	int iter, iter2, iter3 = 0;

	for (iter = 0; iter < ROW_VAL; iter++) {
		for (iter2 = 0; iter2 < COL_VAL; iter2++) {
			if (arr[iter][iter2] == 0x0a)						//0x0a(한줄아래)이면 다음행으로 넘어감
				break;
			arr2[iter3++] = arr[iter][iter2];
		}
	}
}

void Output(char arr[ROW_VAL * 20]) {
	int iter;
	char O_FilePath[COL_VAL] = { 0 };				//저장 할 파일 경로를 입력 받을 1차배열

	InputFilePath(O_FilePath);

	fopen_s(&ofp, O_FilePath, "a");

	fputs(arr, ofp);

	fclose(ofp);

	printf("====================================================\n");
	printf("                    Output Data\n");
	printf("====================================================\n");

	puts(arr);
}
