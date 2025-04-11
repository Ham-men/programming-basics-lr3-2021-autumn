#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>
#pragma warning(disable : 4996)
#define YES 1
#define NO 0
#define MAXLEN 1000 // максимальная длина строки
#define NLINES 1000 // максимальное число строк
//скопировать содержимое текстового файла, удаляя строки, если они уже встречались ранее
int word_counter0(char lines[][MAXLEN], int n);
int word_counter1(char** lines, int n);
int main(void)
{
	//setlocale(LC_ALL, "RU");
	FILE* fp; // входной файл
	FILE* fw;
	int nlines0, nlines1; // число строк в файле
	static char lines[NLINES][MAXLEN]; // статический
	// массив для
	// хранения
	// строк
	char** lines_ptr = NULL; // указатель на
	// динамический
	// массив
	int npointers; // число указателей в
	// динамическом массиве
	int i, i2;
	int nwords0, nwords1; // число слов в массиве строк
	// открыть файл для чтения
	fp = fopen("test.txt", "rt");
	fw = fopen("write.txt", "w");
	if (fp == NULL)
		return 0; // ошибка при открытии файла
	// заказать и обнулить динамический массив
	// указателей (два варианта)
#if 1
	lines_ptr = (char**)malloc(NLINES * sizeof(char*));
	// обнулить массив указателей
	memset(lines_ptr, 0, NLINES * sizeof(char*));
#else
	lines_ptr = (char**)calloc(NLINES, sizeof(char*));
#endif
	npointers = NLINES;
	nlines0 = 0;
	nlines1 = 0;
	while (!feof(fp)) // цикл до конца файла
	{
		char line[MAXLEN];
		// чтение строки
		char* ptr = fgets(line, MAXLEN, fp);
		int len;
		if (ptr == NULL)
			break; // файл исчерпан
		if (nlines0 < NLINES)
		{
			// статический массив ещё не исчерпан
			// сохранить строку в статическом массиве
			strcpy(&lines[nlines0][0], line);
			nlines0++;
		}
		// определить длину строки
		len = (int)strlen(line);
		if (nlines1 == npointers)
		{
			// динамический массив исчерпан
			npointers += NLINES;// увеличить число
			//указателей в массиве
			// перезаказать память для массива
			// указателей
			lines_ptr = (char**)realloc(lines_ptr, npointers * sizeof(char*));
			// обнулить новую часть массива указателе
			memset(&lines_ptr[nlines1], 0, NLINES * sizeof(char*));
		}
		// заказать в памяти место для строки
		// плюс один байт
		lines_ptr[nlines1] = (char*)malloc(len + 1);
		// сохранить строку в динамическом массиве
		i2 = 0;
		for (i = 0; i < nlines1; i++) //ЗДЕСЬ ИДЕТ			ПРОВЕРКА НА ДУБЛИКАТ ТЕКСТА
		{
		if (strcmp(line, lines_ptr[i]) == 0)
		{
		printf("\n odinakovo");
		i2 = 1;
		break;
		}
		}
			if (i2 == 0)
			{
				strcpy(lines_ptr[nlines1], line);
				//printf("\nlineptr [%d]= %s",nlines1,lines_ptr[nlines1]);
				nlines1++;
			}
	}
	//printf("\n red_stroki = %s",lines_ptr); lines_ptr-записать в файл
	for (i = 0; i < nlines1; i++)
	{
		fputs(lines_ptr[i], fw);
		printf("\nlineptr [%d]= %s", i, lines_ptr[i]);
	}
	nwords0 = word_counter0(lines, nlines0);
	nwords1 = word_counter1(lines_ptr, nlines1);
	printf("\n number of words: %d\n", nwords0);
	printf("\n number of words prvilnoe: %d\n", nwords1);
	// отказаться от памяти для строк
	for (i = 0; i < nlines1; i++)
	{
		if (lines_ptr[i] != NULL)
			free(lines_ptr[i]);
	}
	// отказаться от динамического массива указателей
	if (lines_ptr != NULL)
		free(lines_ptr);
	fclose(fp); // закрыть входной файл
	fclose(fw);
	return 0;
	}
	int word_counter0(char lines[][MAXLEN], int n)
	{
		int i, j;
		int counter; // счётчик слов
		int flag; // признак слова
		counter = 0;
		flag = NO;
		for (i = 0; i < n; i++)
		{
			// цикл по строкам
			char* ptr = &lines[i][0]; // указатель на
			// текущую строку
			for (j = 0; ptr[j] != '\0'; j++)
			{
				if (ptr[j] == ' ' || ptr[j] == ',' ||
					ptr[j] == '.' || ptr[j] == '\n')
				{
					// текущий символ - разделитель
					flag = NO;
				}
				else
				{
					// текущий символ - буква
					if (flag == NO)
					{
						// первая буква в слове
						counter++;
					}
					flag = YES;
				}
			}
			if (flag == YES)
			{
				// строка закончилась буквой
				counter++;
			}
		}
		return counter;
	}
	int word_counter1(char** lines, int n)
	{
		int i, j;
		int counter; // счётчик слов
		int flag; // признак слова
		counter = 0;
		flag = NO;
		for (i = 0; i < n; i++)
		{
			// цикл по строкам
			// получить адрес текущей строки
			// ( два варианта )
#if 1
			char* ptr = *(lines + i); // указатель на
			// текущую строку
#else
			char* ptr = lines[i]; // указатель на текущую
			// строку
#endif
			for (j = 0; ptr[j] != '\0'; j++)
			{
				if (ptr[j] == ' ' || ptr[j] == ',' ||
					ptr[j] == '.' || ptr[j] == '\n')
				{
					// текущий символ - разделитель
					flag = NO;
				}
				else
				{
					// текущий символ - буква
					if (flag == NO)
					{
						// первая буква в слове
						counter++;
					}
					flag = YES;
				}
				if (flag == YES)
				{
					// строка закончилась буквой
					//counter++;
				}
			}
			return counter;
		}
	}