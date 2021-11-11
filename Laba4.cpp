#include <iostream>
#include <fstream>

#define MAX 100

#define endString1 '\n'
#define endString2 '\0'
#define maxDigit '9'
#define minDigit '0'
#define space ' '

using namespace std;

bool isSymbolInString(const char needle, const char *haystack) {
  for (int i = 0; ((haystack[i] != endString1) && (haystack[i] != endString2)); i++) {
    if (needle == haystack[i]) {
      return true;
    }
  }
  return false;
}

int realizeStrspn(const char *string, const char *strCharSet) {
  int rule = 0;
  int counter = 0;
  for (int i = 0; string[i] != endString1; i++) {
    bool permission = isSymbolInString(string[i], strCharSet);
    if ((!permission) && (rule == 0)) {
    } else if (!(permission) || !(rule == 0 || rule == 1)) {
      if ((!permission) && (rule == 1)) {
        return counter;
      }
    } else {
      rule = 1;
      counter++;
    }
  }
  return counter;
}

void realizeFunction(const char *fileName) {
  ifstream file;
  file.open(fileName);
  if (!file) {
    cout << "File in part A not found\n";
    return;
  }
  char *str = new char[MAX + 1];
  char *strCharSet = new char[MAX + 1];
  file.getline(str, MAX, space);
  file.getline(strCharSet, MAX, endString1);
  cout << realizeStrspn(str, strCharSet);
}

bool isDigit(const char symb) {
  return ((symb <= maxDigit) && (symb >= minDigit));
}

int searchNulls(const char *str) {
  int counter = 0;
  for (int i = 0; ((str[i] != endString1) && (str[i] != endString2)); i++) {
    if (!isDigit(str[i])) {
      return -1;
    } else if (str[i] == '0') {
      counter++;
    }
  }
  if (str[0] == endString1 || str[0] == endString2 || str[0] == space) {
    return -1;
  }
  return counter;
}

void printString(const char *str) {
  for (int i = 0; ((str[i] != endString1) && (str[i] != endString2)); i++) {
    cout << str[i];
  }
  cout << "\n";
}

char *getSubstring(const char *str, int start, int end) {
  char *substr = new char[MAX + 1];
  for (int i = 0; i <= end - start; i++) {
    substr[i] = str[start + i];
  }
  substr[end - start + 1] = endString2;
  return substr;
}

void SearchMaxNULLS(const char *fileName) {
  ifstream file;
  file.open(fileName);
  if (!file) {
    cout << "File in part B not found\n";
    return;
  }
  char *haystack = new char[MAX + 1];
  char *lastWord = new char[MAX + 1];
  char *penultWord = new char[MAX + 1];
  char *buffer = new char[MAX + 1];
  int nulls = 0;
  file.getline(haystack, MAX);
  int state = 0;
  int firstPointer;
  int secondPointer;
  for (int i = 0; ((haystack[i] != endString1) && (haystack[i] != endString2)); i++) {
    if ((haystack[i] != space) && (state == 0)) {
      state = 1;
      firstPointer = i;
    } else if ((haystack[i] == space) && (state != 0)) {
      secondPointer = i - 1;
      state = 0;
      buffer = getSubstring(haystack, firstPointer, secondPointer);
      if (searchNulls(buffer) == nulls) {
        penultWord = lastWord;
        lastWord = buffer;
      }
      if (searchNulls(buffer) > nulls) {
        lastWord = buffer;
        penultWord = lastWord;
        nulls = searchNulls(buffer);
      }
    }
  }
  printString(penultWord);
}

int main() {
  realizeFunction("pointA.txt");
  cout << "\n";
  SearchMaxNULLS("pointB.txt");
  return 0;
}