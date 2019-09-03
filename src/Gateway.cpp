#include "FileP.h++"
#include <vector>
#include <string>
template <class T> 
void memClear(vector<T> list)
{
  for (T element : list)
    {
      delete element;
      element = NULL;
    }
}

void cleanUp(vector<Pin*> Ins,vector<Pin*> Outs,vector<Pin*> Wires,vector<Gate*> Gates)
{
  memClear(Ins);
  memClear(Outs);
  memClear(Wires);
  memClear(Gates);
  cout << "exiting ..." << endl;
}

using namespace std;
int main(int argc, char **argv)
{
  FileP processor;
  Simul simer;
  vector<Pin*> Ins;
  vector<Pin*> Outs;
  vector<Pin*> Wires;
  vector<Gate*> Gates;
  string name;
  //command line arg
  bool pflag = false;
  bool eflag = false;
  cout << "=================GATEWAY==================\n";
  if(argc == 1)
    {
      cout << "Not enough arguments, ./GateWay [Filename] -flags(opt)\n";
      return 0;
    }
  name = argv[1];
  unsigned int i;
  i = name.find('.');
  name.erase(i);
  cout << "File selected: " << name << endl;
  if(argc > 2)//flag handling
    {
      for(int i = 2;i<argc;i++)
	{
	  if(argv[i][0] == '-')
	    {
	      if(argv[i][1] == 'p'){pflag=true;}
	      if(argv[i][1] == 'e'){eflag=true;}
	    }
	}
    }
  cout << "print_enabled:" << (int)pflag << endl;
  cout << "eeprom_gen:" << (int)eflag << endl;
  //setup
  cout << "Beginning setup..." << endl;
  if(processor.setup(name))
    {
      cleanUp(Ins,Outs,Wires,Gates);
      return 0;
    }
  cout << " ... " << endl;
  string target = "In";
  if(processor.checkFor(Ins,target))
    {
      cout << "No Ins found\n";
      cleanUp(Ins,Outs,Wires,Gates);
      return 0;
    }
  cout << " ... " << endl;
  target = "Out";
  if(processor.checkFor(Outs,target))
    {
      cout << "No Outs found\n";
      cleanUp(Ins,Outs,Wires,Gates);
      return 0;
    }
  cout << " ... " << endl;
  target = "Wire";
  if(processor.checkFor(Wires,target))
    {
      //if error occurs for wires
    }
  cout << " ... " << endl;
  if(processor.allocateGates(Gates,Ins,Outs,Wires))
    {
      cleanUp(Ins,Outs,Wires,Gates);
      return 0;
    }
  cout << "Initialising simulator" << endl;
  simer.Init(pflag,eflag,Ins,Outs,Gates,name);
  //do until done
  u8 Done = 0;
  cout << "Beginning Simulation" << endl;
  while(true)
    {
      simer.update();
      simer.writeResults();
      Done = simer.nextState();
      if(Done) {break;}
    }
  simer.finish();
  cout << "Simulation complete" << endl;
  cleanUp(Ins,Outs,Wires,Gates);
  return 0;
}


