#include "Gates.h++"
//function bodies go in cpp, rest goes in header
Pin::Pin(string name)  {this->name = name;}
Pin::Pin() {}
Pin::~Pin() {/*Not used*/}
void Pin::set(u8 value)            {  this->Value = value;}
bool Pin::get()             {  return ((this->Value) > 0);}

Gate::Gate(){/*Virtual object */}
Gate::~Gate(){/*Virtual object */}
void Gate::perform(){/*Virtual  function */}


AND::AND(Pin* I1,Pin* I2,Pin* O1,u8 layer)
  {
    this->In1 = I1;
    this->In2 = I2;
    this->Out1 = O1;
    this->layer = layer;
  }
AND::~AND(){/*Not needed */}
void AND::perform()
  {
    if(In1->get() && In2->get())
      {
	Out1->set((u8)1);
      }
    else
      {
	Out1->set((u8)0);
      }
  }

OR::OR(Pin* I1, Pin* I2, Pin* O1,u8 layer)
  {
    this->In1 = I1;
    this->In2 = I2;
    this->Out1 = O1;
    this->layer = layer;
  }
OR::~OR(){/*Not needed */}
void OR::perform()
  {
    if(In1->get() || In2->get())
      {
	Out1->set(1);
      }
    else
      {
	Out1->set(0);
      }
  }

NOT::NOT(Pin* I1,Pin* O1,u8 layer)
  {
    this->In1 = I1;
    this->Out1 = O1;
    this->layer = layer;
  }
NOT::~NOT(){/*Not Needed */}
void NOT::perform()
  {
    if(In1->get())
      {
	Out1->set(0);
      }
    else
      {
	Out1->set(1);
      }
  }

XOR::XOR(Pin* I1,Pin* I2,Pin* O1,u8 layer)
  {
    this->In1 = I1;
    this->In2 = I2;
    this->Out1 = O1;
    this->layer = layer;
  }
XOR::~XOR(){/*Not needed */}
void XOR::perform()
  {
    if(In1->get() == In2->get())
      {
	Out1->set(0);
      }
    else
      {
	Out1->set(1);
      }
  }

NAND::NAND(Pin* I1,Pin* I2,Pin* O1,u8 layer)
  {
    this->In1 = I1;
    this->In2 = I2;
    this->Out1 = O1;
    this->layer = layer;
  }
NAND::~NAND() {/*Not needed */}
void NAND::perform()
  {
    if(In1->get() & In2->get())
      {
	Out1->set(0);
      }
    else
      {
	Out1->set(1);
      }
  }

NOR::NOR(Pin* I1,Pin* I2,Pin* O1,u8 layer)
  {
    this->In1 = I1;
    this->In2 = I2;
    this->Out1 = O1;
    this->layer = layer;
  }
NOR::~NOR(){/*Not needed */}
void NOR::perform()
  {
    if(In1->get() | In2->get())
      {
	Out1->set(0);
      }
    else
      {
	Out1->set(1);
      }
  }

XNOR::XNOR(Pin* I1,Pin* I2,Pin* O1,u8 layer)
  {
    this->In1 = I1;
    this->In2 = I2;
    this->Out1 = O1;
    this->layer = layer;
  }
XNOR::~XNOR() {/*Not needed */}
void XNOR::perform()
  {
    if(In1->get() == In2->get())
      {
	Out1->set(1);
      }
    else
      {
	Out1->set(0);
      }
  }

Gate* makeGate(string gate,Pin* In1,Pin* In2,Pin* Out,u8 layer)
{
  if(gate == "AND")        {return new AND(In1,In2,Out,layer);}
  else if(gate == "OR")     {return new OR(In1,In2,Out,layer);}
  else if(gate == "NOT")       {return new NOT(In1,Out,layer);}
  else if(gate == "NAND") {return new NAND(In1,In2,Out,layer);}
  else if(gate == "NOR")   {return new NOR(In1,In2,Out,layer);}
  else if(gate == "XOR")   {return new XOR(In1,In2,Out,layer);}
  else if(gate == "XNOR") {return new XNOR(In1,In2,Out,layer);}
  else                                           {return NULL;}
}
