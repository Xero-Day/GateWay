#include <fstream>

using namespace std;
void writeHex(fstream& dest,unsigned char byte)
{
  
  dest << hex << showbase  << (int)byte << dec << ","; 
}

void endHex(fstream& dest,unsigned char byte)
{
  dest << (int)byte;
  dest.close();
}
