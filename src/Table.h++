#include <iostream>
#include <fstream>
using namespace std;

void lineOf(const char key,const int digits)
{
  for (int i = 0;i < digits;i++)
    {
      cout << key;
    }
  cout << endl;
}

void lineOf(const char key,const int digits,fstream& To)
{
  for (int i = 0;i < digits;i++)
    {
      To << key;
    }
  To << endl;
}

void linePart(const char key,const int digits)
{
  for (int i = 0;i < digits;i++)
    {
      cout << key;
    }
}

void linePart(const char key,const int digits,fstream& To)
{
  for (int i = 0;i < digits;i++)
    {
      To << key;
    }
}
