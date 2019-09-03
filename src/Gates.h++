#include <string>
#define u8 unsigned char
#define u64 unsigned long int

using namespace std;
class Pin
{
protected:
  u8 Value;
public:
  string name;
  u8 Layer;
  Pin();
  Pin(string name);
  ~Pin();
  void set(u8 value);
  bool get();
};

class Gate
{
public:
  u8 layer;
  Gate();
  virtual ~Gate();
  virtual void perform();
};

class AND:public Gate
{
private:
  Pin* In1 = nullptr;
  Pin* In2 = nullptr;
  Pin* Out1 = nullptr;
public:
  AND(Pin* I1,Pin* I2,Pin* O1,u8 layer);
  ~AND();
  void perform();
};

class OR:public Gate
{
private:
  Pin* In1 = nullptr;
  Pin* In2 = nullptr;
  Pin* Out1 = nullptr;
public:
  OR(Pin* I1,Pin* I2,Pin* O1,u8 layer);
  ~OR();
  void perform();
};

class NOT:public Gate
{
private:
  Pin* In1 = nullptr;
  Pin* Out1 = nullptr;
public:
  NOT(Pin* I1,Pin* O1,u8 layer);
  ~NOT();
  void perform();
};

class XOR:public Gate
{
private:
  Pin* In1 = nullptr;
  Pin* In2 = nullptr;
  Pin* Out1 = nullptr;
public:
  XOR(Pin* I1,Pin* I2,Pin* O1,u8 layer);
  ~XOR();
  void perform();
};

class NAND:public Gate
{
private:
  Pin* In1 = nullptr;
  Pin* In2 = nullptr;
  Pin* Out1 = nullptr;
public:
  NAND(Pin* I1,Pin* I2,Pin* O1,u8 layer);
  ~NAND();
  void perform();
};

class NOR:public Gate
{
private:
  Pin* In1 = nullptr;
  Pin* In2 = nullptr;
  Pin* Out1 = nullptr;
public:
  NOR(Pin* I1,Pin* I2,Pin* O1,u8 layer);
  ~NOR();
  void perform();
};

class XNOR:public Gate
{
private:
  Pin* In1 = nullptr;
  Pin* In2 = nullptr;
  Pin* Out1 = nullptr;
public:
  XNOR(Pin* I1,Pin* I2,Pin* O1,u8 layer);
  ~XNOR();
  void perform();
};


Gate* makeGate(string gate,Pin* In1,Pin* In2,Pin* Out,u8 layer);
