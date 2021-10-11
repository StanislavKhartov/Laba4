#include <iostream>
#include <fstream>

#define MAX 100

using namespace std;

bool isSymbolInString(const char needle, const char* haystack)
{
	for (int i = 0; ((haystack[i] != '\n') && (haystack[i] != '\0')); i++)
	{
		if (needle == haystack[i])
		{
			return true;
		}
	}
	return false;
}

int realizeStrspn(const char* string, const char* strCharSet)
{
	int rule = 0;
	int counter = 0;
	for (int i = 0; string[i] != '\n'; i++)
	{
		bool permission = isSymbolInString(string[i], strCharSet);
		if ((!permission) && (rule == 0))
		{
		}
		else if ((permission) && (rule == 0 || rule == 1))
		{
			rule = 1;
			counter++;
		}
		else if ((!permission) && (rule == 1))
		{
		return counter;
		}
	}
	return counter;
}

void partA(const char* fileName)
{
	ifstream file;
	file.open(fileName);
	if (!file)
	{
		cout << "File in part A not found\n";
		return;
	}
	char* str = new char[MAX + 1];
	char* strCharSet = new char[MAX + 1];
	file.getline(str, MAX, ' ');
	file.getline(strCharSet, MAX, '\n');
	cout << realizeStrspn(str, strCharSet);
}

bool isDigit(const char symb)
{
	if ((symb <= '9') && (symb >= '0'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int searchNulls(const char* str)
{
	int counter = 0;
	for (int i = 0; ((str[i] != '\n') && (str[i] != '\0') && (str[i])!='H'); i++)
	{ 
		if (!isDigit(str[i]))
		{
			return -1;
		}
		else if (str[i] == '0')
		{
			counter++;
		}
	}
	if (str[0] == '\n' || str[0] == '\0' || str[0] == ' ')
	{
		return -1;
	}
	return counter;
}

void printString(const char* str)
{
	for (int i = 0; ((str[i] != '\n') && (str[i] != '\0') && (str[i] != 'Н')); i++)
	{
		cout << str[i];
	}
	cout << "\n";
}

char* getSubstring(const char* str, int start, int end)
{
	char* substr = new char[MAX + 1];
	for (int i = 0; i <= end - start; i++)
	{
		substr[i] = str[start + i];
	}
	substr[end - start + 1] = '\0';
	return substr;
}

void partB(const char* fileName)
{
	ifstream file;
	file.open(fileName);
	if (!file)
	{
		cout << "File in part B not found\n";
		return;
	}
	char* haystack = new char[MAX + 1];
	char* lastWord = new char[MAX + 1];
	char* penultWord = new char[MAX + 1];
	char* buffer = new char[MAX + 1];
	int nulls = 0;
	file.getline(haystack, MAX);
	int state = 0;
	int firstPointer;
	int secondPointer;
	for (int i = 0; ((haystack[i] != '\n') && (haystack[i] != '\0')); i++)
	{
		if ((haystack[i] != ' ') && (state == 0))
		{
			state = 1;
			firstPointer = i;
		}
		else if ((haystack[i] != ' ') && (state != 0))
		{
		}
		else if ((haystack[i] == ' ') && (state != 0))
		{
			secondPointer = i - 1;
			state = 0;
			buffer = getSubstring(haystack, firstPointer, secondPointer);
			if (searchNulls(buffer) == nulls)
			{
				penultWord = lastWord;
				lastWord = buffer;
			}
			if (searchNulls(buffer) > nulls)
			{
				lastWord = buffer;
				penultWord = lastWord;
				nulls = searchNulls(buffer);
			}
		}
		else if ((haystack[i] == ' ') && (state == 0))
		{
		}
	}
	printString(penultWord);
}

int main()
{
	partA("pointA.txt");
	cout << "\n";
	partB("pointB.txt");
	return 0;
}

