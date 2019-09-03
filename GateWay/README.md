/*
	GateWay Logic simulator and EEPROM PLC writer
		Written by B.J. Cownley
		Version 1.0
		31/8/2019
*/

Layout

1	-	Intro	
2	-	Use
3	-	options
4a	-	Language and .drcb files
4b	-	Possiblilities for complex circuits
5	-	Troubleshooting
6	-	Code Design (for software authors and for improvement ideas)




1)	Intro

GateWay is a logic simulator and EEPROM logic writer written in just 10 days.
Its a simple CLI(Command line interface) program that processes a file
describing the logic system in a simple script format.

This enables users to check that their logic circuits function correctly. It's
secondary feature is to assist users in using parallel EEPROM as a logic circuit

The results of which are stored in a text file relating to the script file. 

2)	Use

To compile the software, there is a script BuildGate.sh that will do it,
assuming g++ is already installed.

To use the software, simply run it from the command line as shown

   $ ./GateWay [File] [optional flag(s)]
     	       	       -e == EEPROM generate 
		       -p == Print enable

The File should be a .drcb file which is just a simple text file with .drcb .
The file is the script for which the program will read and test.
    (Refer to 4a for further info)

The results should appear on the screen.

$ ./GateWay Test1.drcb

=================GATEWAY==================
File selected: Test1			  //Shows the File selected to run
print_enabled:0				  //Has -p been entered?
eeprom_gen:0				  //Has -e been entered?
Beginning setup...			  //Setup
 ... 
In:4					  // 4 Inputs detected
 ... 
Out:3					  // 3 outputs detected
 ...
 ... 
Gates allocated: 3			  // 3 Gates detected in file
Initialising simulator			  // setting up simulator
Beginning Simulation			  // beginning testing
Simulation complete			  
exiting ...

The results are stored in a text file labelled in relation to the selected file.

In the above case, the results would be stored in Test1_results.txt

$ cat Test1_results.txt

===========			 // Shows the Inputs and the Outputs
Ins D,A,C,B,|Outs Z,Y,X,	 // Shows the layout of the signals
===========
0000|000			 // DACB|ZYX
0001|010			 // only B is high, only Y is high
0010|010
0011|010
0100|100
0101|111
0110|110
0111|111
1000|100
1001|110
1010|110
1011|110
1100|000
1101|011
1110|010
1111|011


If an error occurs then refer to 5

3)   	Options

	-p	print flag

	description: print the simulation results as they occur, enabling the
		     user to see the simulation in action, so that the user
		     doesn't need to read the file to see the results.
		     results file will still be wrote.


	-e	EEPROM flag

	description: make a separate file that stores the hex values that
		     will be written to the EEPROM. This is on the premise
		     of the address pins being used as inputs and the data
		     pins being used as outputs.
		     (Programmable logic using ROM)
		     The file is labelled *_results.hex 
		     In the file will be packets arranged as
		     
		     5 LB[0xf,0x7,0,0]HB

		     LB meaning Lowest Byte, and HB (Highest Byte) respectively
		     LB[(bits 7-0),(bits 15-8),(bits 23-16),(bits 31-24)]HB
		     The user is currently required to select which bits to use.
		     This enables a wide range of EEPROM to be used
		     	  (8bit,16bit,32bit,etc)
		     Each packet relates to an address in EEPROM.
		     In the above case, the 5 represents address location 5.


4a)	Language and .drcb files

The language is simple and primitive, with only a few rules.
+ There are only 6 keywords (which are case-sensitive)
  In - indicates this is going to be an input
  Out - indicates this will be an output
  Wire - indicates this is a wire and is just for connection, not simulating
  assign - indicates this is a gate (syntax rule is below)
  ; - indicates end of line
  // - indicates comment space between // and ;

Declaring Ins and Outs

Ins and Outs are declared by the use of the In and Out keywords respectivly.
The // and ; keywords tell the program to look for the next keys. for example.

   In Select;
   In B// Pins of a multiplexer
   In A;
   Out Q;
   
declares 3 Ins and 1 Outs with a comment for the B In

It is possible to declare multiple Ins or Outs on one line as such

   In Select A B// Input pins
   Out Q;

Gates are declared by using the assign keyword. There are 7 gates available:
{AND,OR,NOT,NAND,NOR,XOR,XNOR}. The syntax for most of them is as follows

   assign [OUTPUT] [GATE] [INPUT1] [INPUT2] [LAYER]

The only exception is the NOT gate which is

   assign [OUTPUT] NOT [INPUT1] [LAYER]

OUTPUT is the name of the wire or out that is connected to the gates output.
INPUT is the name of the wire or in that is the input of the gate
there are either 1 or 2.
LAYER is the logic layer of the gate. It determines which gate is tested first.
Its priority is 1 - 255, 1 being first to be tested and 255 last to be tested.
The layers must be consecutive, no gaps. ie 1 2 3 are layers allowed but layers
1 2 4 will only cause layers 1 and 2 to be tested.

The example below further explains this

   Wire x y z;
   assign x NOT Select 1;
   assign y AND x A 2;
   assign z AND Select B 2;
   assign Q OR y z 3;

Note that the y and z are both on the 2nd layer, this is because they can be
tested in parallel. You need to think about which gates need to be tested
first so that the later gates perform correctly. x needs to checked before y
and z are tested and Q needs y and z to be checked before being tested.

Wires are bidirectional connections that can be either read or wrote. They
are for connecting gates together. They allow for a clear way of connecting it
and reducing the parts needed to be read for the readout.

Ins,Outs,and Wires can be declared anywhere in the file but its recommended that
the layout be sensible and logical. It is not possible to declare wires of the
same name as it will confuse the program. DONT redeclare them.

The example below shows a script for a 2:1 multiplexer

   In Select A B// Input pins
   Out Q;
   Wire x y z;
   assign x NOT Select 1// Select and nSelect
   assign y AND x A 2// y is for when Select is low 
   assign z AND Select B 2// z is for when Select is high
   assign Q OR y z 3;

.drcb files are text files that are for the user to use to interact with the
software. Just a simple text file with .drcb at the end. Use to store the
programs you want to test/simulate.

4b)     Possibilities for complex circuits

The system is designed so that there's a max amount of 64 Ins and 64 Outs but
no known limit for wires and gates. Please note the larger the system, the
more computation and the more time waiting for the results.

More importantly; Why are you simulating something that large with homebrew?

There does lie the potential of creating a sequential circuit by feeding a wire
from a gates output to an input of the respective gate, however its not fully
supported and may crash the program but it still remains possible just DONT
feedback to a In. This will upset the simulator and cause problems.

5)	Troubleshooting

The program will present error messages in the event of a user error.
See list below.

ERROR FOUND: FILE NOT FOUND
- The file you entered either wasn't there or wasn't a .drcb file.
- File.txt would cause this but File.drcb won't

NO 'assign' FOUND
- There's no assigns in the file so there's no gates to declare: no simulations!

[WIRE/IN/OUT] NOT FOUND
- A gate can't find the wire/in/out required. Probably a spelling error or
  failure to declare it.

Incorrect gate entered
- Probably a spelling error for a gate, make sure all the Gates declared
  are in caps and that they are on the list

Not enough arguments, ./GateWay [Filename] -flags(opt)
- You need to include the filename with the command, Refer to 2 for example

IF THE NUMBER OF WIRES OR GATES FOUND IS NOT EQUAL TO THAT OF THE FILE
- The spacing between the words is important, if not done right, it will tell
  the program that everyword is an In or Out or Wire. Make sure there is a
  space between every word but no spaces between a word and // or ;

SIMULATION SHOWS NOTHING HAPPENING OR PARTIALLY NOTHING HAPPENING
- Check the file, It should be noted that if the layering has gaps, this will
  occur as the simulator will assume that theres no more layers.
  i.e if you have gates with layers 1 and 4. layer 1 will be tested but since
  there isn't a 2, the simulator will stop. You must always have consecutive
  layers

6)	Code design

/Gates
	This is where the code for the gates and Wires are.
	The Gate is a poly-obj so any additions to the gates must inherit
	or the software won't accept it.
	Any additions must also be added to the makeGate factory

/Simul
	This is responsible for testing the inputs, logging the results and
	testing each gate. It needs to be initiated and then it can be
	updated, go to next test state, etc

/FileP
	This is what reads the file the user enters and processes and generates
	the gates and wires needed. It can currently only search for words,
	check for Ins,Outs,Wires and allocate Gates.

/GateWay
	This connects everything. It has a FileP and Simul Obj, and vectors to
	store the Ins,Outs,Wires and Gates.
	It makes it work and when done it will clean up and close up.

6-)	Possibilities for Improvement
# Replace Pin.get and Pin.set with Pin[] and Pin =
# More streamlined functions (Simul and FileP can be friends)
# Further flag extension to set what EEPROM is used
# A more sophisticated file processor
  - Spaces not necessary -Wire redundancy
# Sequential Logic support
# Verilog and VHDL support