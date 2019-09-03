#include "Gates.h++"
#include <vector>
#include <fstream>
class Simul
{
private:
  bool print = false;
  bool eeprom = false;
  u64 limit = 0;
  u64 inState = 0;
  string name;
  fstream results;
  fstream hexf;
  vector<Pin*> Ins;
  vector<Pin*> Outs;
  vector<Gate*> gates;
public:
  void Init(bool print,bool eeprom,const vector<Pin*>& Ins,const vector<Pin*>& Outs,const vector<Gate*>& gates,string File);
  u8 nextState();
  void update();
  void writeResults();
  void finish();
};
