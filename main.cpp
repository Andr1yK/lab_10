#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <class T, class R>
void log(T str, R name) {
  cout << name << ": " << str << endl;
} 

void CreateTXT(char* fname) {
  ofstream fout(fname);
  char ch;
  string s;

  do {
    cin.get();
    cin.sync();
    cout << "enter line: "; getline(cin, s);
    fout << s << endl;
    cout << "continue? (y/n): "; cin >> ch;
  } while (ch == 'y' || ch == 'Y');

  cout << endl;
}

void PrintTXT(char* fname)
{
  ifstream fin(fname); 
  string s;

  for (; getline(fin, s); cout << s << endl);
  
  cout << endl;
}

bool isInclude(char letter) {
  const string LETTERS = "BASIC";
  const size_t len = LETTERS.length();

  for (size_t i = 0; i < len; i++)
    if (LETTERS[i] == letter)
      return true;
  
  return false;
}

int CountLetters(char* fname)
{
  ifstream fin(fname);
  string s;
  int k = 0;

  while ( getline(fin, s) ) {
    for (unsigned i = 0; i < s.length(); k += isInclude(s[i]), i++);
  };

  return k;
}

string findWord(char* fname , char letter) {
  ifstream fin(fname);
  string str;

  string word = "";
  int line_index = 1;

  while ( getline(fin, str) ) {
    const int firstSpace = str.find(' ', 1);
    
    if (str[0] == letter && firstSpace == -1) {
      word = str;
      continue;
    }

    if (firstSpace == -1) {
      continue;
    }

    word.assign(str, 0, str.find(' ', 0));

    size_t pos = -1;
    do
      if (str[pos + 1] == letter)
         word.assign(str, pos + 1, str.find(' ', pos + 1) - pos - 1);
    while (pos++, (pos = str.find(' ', pos)) != -1);

    line_index++;
  }

  return word;
}

int main()
{
  char fname[100];
  cout << "enter file name 1: "; cin >> fname;

  CreateTXT(fname);
  PrintTXT(fname);

  cout << "k(BASIC) = " << CountLetters(fname) << endl;
  cout << "Last word(start with 'a') = " << findWord(fname, 'a') << endl;

  return 0;
}