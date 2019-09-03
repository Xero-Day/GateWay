#include "FileP.h++"

/* Searchs and opens the file with the name
   returns 0 if successful,-1 elsewise    */
u8 FileP::setup(string& name)
{
  this->name = name;
  this->Params.open((name + ".drcb"),ios_base::in);
  if(Params.is_open())
    {
      return 0;
    }
  else
    {
      cout << "ERROR FOUND: FILE NOT FOUND\n";
      return -1;
    }
  return 0;
}

/* Search for the first occurence of a target word
   Takes the target string and a bool meaning whether
   to rewind or to continue from the current position
   returns 0 if successful,127 if end of file #Tested:fine
 */ 
u8 FileP::searchForWord(string target,bool fromBeginning)
{
  if(fromBeginning)
    {
      Params.close();
      Params.open((name + ".drcb"),ios_base::in);
    }
  string word;
  while(true)
    {
      Params >> word;
      if (word == target){return 0;}
      if(Params.eof()) {return 127;}
    }
  
}

/* Test if // or ; is in the string
   Remove it if necessary 
 */
bool FileP::eol(string& target)
{
  if (target == ";" || target == "//")  {return true;}
  else if(target.find(";") != string::npos)
    {
      target.erase(target.find(";"));
      return true;
    }
  else if(target.find("//") != string::npos)
    {
      target.erase(target.find("//"));
      return true;
    }
  else                                   {return false;}
}

/* Read the Params file and fill the arg list needed
   key is for looking for the target words
   returns 0 if successful,-1 if no <key> found  */
u8 FileP::checkFor(vector<Pin*>& list, string& key)
{
  u8 errorvalue;
  string x;
  bool test = true;
  errorvalue = this->searchForWord(key,test);
  if (errorvalue == 127)
    {
      return -1;
    }
  test = false;
  //Now move on to the next word
  while(!Params.eof())
    {
      Params >> x;
      if(this->eol(x))
	{
	  list.push_back(new Pin(x));
	  this->searchForWord(key,test);
	}
      else
	{
	  list.push_back(new Pin(x));
	}
    }
  cout << key << ":" << list.size() << endl;
  return 0; 
}


/* Read the Params file and allocates and assembles the gates needed 
      returns 0 if successful,
      127 if Pin not found,
      63 if invalid gate,
      -1 if no assigns */
u8 FileP::allocateGates(vector<Gate*>& list,vector<Pin*>& I, vector<Pin*>& O,vector<Pin*> W)
{
  bool start = true;
  u8 errorvalue;
  string x;
  int layer;
  string gate;
  errorvalue = this->searchForWord("assign",start);
  if(errorvalue==127) {cout<<"NO 'assign' FOUND";return -1;}
  while(!Params.eof())
    {
      Pin* Out = NULL;
      Pin* In1 = NULL;
      Pin* In2 = NULL;
      errorvalue = this->searchForWord("assign",start);
      if(errorvalue==127) {break;}
      start = false;
      Params >> x;
      Out = this->searchByName(O,x);
      if(Out == NULL) {Out = this->searchByName(W,x);}
      if(Out == NULL) {cout << x << " NOT FOUND";return 127;}
      Params >> gate;
      Params >> x;
      In1 = this->searchByName(I,x);
      if(In1 == NULL) {In1 = this->searchByName(W,x);}
      if(In1 == NULL) {cout << x << " NOT FOUND";return 127;}
      if(gate != "NOT")//A Not only has one In
	{
	  Params >> x;
	  In2 = this->searchByName(I,x);
	  if(In2 == NULL) {In2 = this->searchByName(W,x);}
	  if(In2 == NULL) {cout << x << " NOT FOUND";return 127;}
	}
      Params >> x;
      this->eol(x);
      layer = stoi(x);
      list.push_back(makeGate(gate,In1,In2,Out,(u8)layer));
    }
  //Just to see if any null gates exist
  for(Gate* element : list)
    {
      if(element == NULL) {cout << "Incorrect gate entered"; return 63;}
    }
  cout << "Gates allocated: " << list.size() << endl;
  return 0;
}

/* Search a list for a Pin with the right name
  returns the reference for the Pin
 */

Pin* FileP::searchByName(vector<Pin*>& list,string& name)
{
  for(Pin* element : list)
    {
      if(element->name == name)
	{
	  return element;
	}
    }
  return NULL;
}
