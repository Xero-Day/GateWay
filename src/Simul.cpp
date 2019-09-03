#include "Simul.h++"
#include "Table.h++"
#include "Hexf.h++"
using namespace std;
/*
  Sets up the Simulator so it can write/read the ins,outs and operate gates
  Calculates the upper limit that finishes the simulation
  Takes in the print flag, references to the Ins,Outs,Gates and the filename
  Writes the head of the results, using Table graphics functions
  Returns nothing
 */
void Simul::Init(bool print,bool eeprom,const vector<Pin*>& Ins,const vector<Pin*>& Outs,const vector<Gate*>& gates,string File)
{
  this->print = print;
  this->eeprom = eeprom;
  this->Ins = Ins;
  for(Pin* element : this->Ins)
    {
      element->set(0);
    }
  this->Outs = Outs;
  for(Pin* element : this->Outs)
    {
      element->set(0);
    }
  this->gates = gates; 
  this->name = File;
  results.open((name + "_results.txt"),ios_base::out);
  if(eeprom) {hexf.open((name+"_results.hex"),ios_base::out);}
  limit = Ins.size();
  limit = 1 << limit;
  //File Head set up
  lineOf('=',Ins.size() + Outs.size() + 4,results);
  results << "Ins ";
  for(int i = (Ins.size() - 1);i>=0;i--)
    {
      results << Ins[i]->name << ",";
    }
  results << "|";
  results << "Outs ";
  for(int i = (Outs.size() - 1);i>=0;i--)
    {
      results << Outs[i]->name << ",";
    }
  results << "\n";
  lineOf('=',Ins.size() + Outs.size() + 4,results);
  //Optional screen print
  if(print)
    {
      lineOf('=',Ins.size() + Outs.size() + 4);
      cout << "Ins ";
      for(int i = (Ins.size() - 1);i>=0;i--)
	{
	  cout << Ins[i]->name << ",";
	}
      cout << "|";
      cout << "Outs ";
      for(int i = (Outs.size() - 1);i>=0;i--)
	{
	  cout << Outs[i]->name << ",";
	}
      cout << endl;
      lineOf('=',Ins.size() + Outs.size() + 4);
    }
}
/*
  Goes to the next Testcase or state
  Returns 0 if successful,-1 if Sim is done
 */
u8 Simul::nextState()
{
  inState++;
  if(inState == limit)
    {
      results.close();
      return -1;
    }
  u64 j = 1;
  for(int i = 0;j < limit;i++)
    {
      Ins[i]->set((inState & j) >> i);//This should do bit-setting
      j = j << 1;
    }
  return 0;
}

/*
  Updates the gates,  to be done after the next state is set
  Goes through the first layers to the last ones
  if it can't find any gates of the target layer,
    then its assumed that all the gates are done.
 */
void Simul::update()
{
  bool Done;
  for(u8 target = 1;target<255;target++)
    {
      Done = true;
      for(Gate* element : gates)
	{
	  if(element->layer == target)
	    {
	      element->perform();
	      Done = false;
	    }
	}
      if (Done) {break;}
    }
}
/* 
   Writes the current results of the logic sim based on the Ins and Outs
 */
void Simul::writeResults()
{
  int address = 0;
  int value = 0;
  for(int i = (Ins.size() - 1);i>=0;i--)
    {
      results << (int)Ins[i]->get();
      if(print){cout << (int)Ins[i]->get();}
      if(eeprom)
	{
	  address = address << 1;
	  address = address + Outs[i]->get();
	}
    }
  results << "|";
  if(print){cout << "|";}
  for(int i = (Outs.size() - 1);i>=0;i--)
    {
      results << (int)Outs[i]->get();
      if(print){cout << (int)Outs[i]->get();}
      if(eeprom)
	{
	  value = value << 1;
	  value = value + Outs[i]->get();
	}
	
    }
  if(print){cout << endl;}
  if(eeprom)
    {
      hexf << address << " ";
      hexf << "LB[";
      for(int i = 0;i<4;i++)
	{
	  u8 *byte = (u8*)&value;
	  writeHex(hexf,*(byte+i));
	}
       hexf << "]HB\n";
    } 
 
  results << endl; 
}

// File clean up
void Simul::finish()
{
  results.close();
  endHex(hexf,0x00);
}

