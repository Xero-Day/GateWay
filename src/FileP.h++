#include <fstream>
#include <string>
#include <iostream>
#include "Simul.h++"
class FileP
{
private:
  fstream Params;
  string name;
  u8 searchForWord(string target,bool fromBeginning);
  bool eol(string& target);
public:
  u8 checkFor(vector<Pin*>& list, string& key);
  u8 allocateGates(vector<Gate*>& list,vector<Pin*>& I, vector<Pin*>& O,vector<Pin*> W);
  u8 setup(string& name);
  Pin* searchByName(vector<Pin*>& list, string& name);
};
