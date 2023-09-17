#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
* 8. В файле записан текст стихотворения. Форматировать текст так,
* чтобы каждый куплет из 4 строк следовал с одной и той же позиции,
* начинался с прописной буквы и был сдвинут относительно предыдущего
* куплета на 5 позиций вправо или влево поочередно.
*/

void RemoveDuplicateSpace(char* str)
{
	int count = 0;
	for (int i = 0; str[i] == ' '; i++)
		count++;

	int len = strlen(str);

	for (int i = 0; i < len; i++)
		str[i] = str[i + count];

	int i = 1, j = 1;
	while (str[i])
	{
		if (str[i] != ' ' || str[i - 1] != ' ')
			str[j++] = str[i];

		i++;
	}
	str[j] = '\0';
}

void formatPoem(const char* inputFilename, const char* outputFilename)
{
	FILE* inputFile;
	fopen_s(&inputFile, inputFilename, "r");

	if (inputFile == NULL)
	{
		cout << "Не удалось открыть файл с исходными данными." << endl;
		return;
	}

	FILE* outputFile;
	fopen_s(&outputFile, outputFilename, "w");

	if (outputFile == NULL)
	{
		cout << "Не удалось открыть файл для записи результатов." << endl;
		fclose(inputFile);
		return;
	}

	int lineCount = 0;
	int shift = 5;
	int pos = 0;
	char line[1000];

	while (fgets(line, sizeof(line), inputFile) != NULL)
	{
		if (line[0] == '\n')
			continue;

		if (lineCount % 4 == 0)
			pos += shift;

		RemoveDuplicateSpace(line);
		line[0] = toupper(line[0]);

		fprintf_s(outputFile, "%*s%s", pos, "", line);

		if (lineCount % 4 == 3)
			shift *= -1;

		lineCount++;
	}

	fclose(inputFile);
	fclose(outputFile);
}

int main()
{
	system("chcp 1251 & cls");

	const char* inputFilename = "1.txt";
	const char* outputFilename = "2.txt";

	formatPoem(inputFilename, outputFilename);

	return 0;
}