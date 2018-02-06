//Librerias

#include <DueTimer.h>

//Variables
#define stp1 3
#define stp2 6
#define dir1 4
#define dir2 7
#define ena1 5
#define ena2 8
#define x_axis A0
#define y_axis A1

int x_value=0;
int y_value=0;

boolean state=0;

long  cont1;
long tmp=31500;

string lect="";
string inString="";

void setup(){
Serial.begin(9600);
pinMode(stp1,OUTPUT);  	//defino salidas del motor 1 y 2
pinMode(stp2,OUTPUT);	//*****  
pinMode(dir1,OUTPUT);	//*****
pinMode(dir2,OUTPUT);	//*****
pinMode(ena1,OUTPUT);	//*****
pinMode(ena2,OUTPUT);	//*****
Timer3.attachInterrupt(ra).start(tmp);  //Llamo a RA cada tmp [ms]
}

void loop ()
{
	
lectura();
manual();


}

void lectura(){
lect=Serial.readStringUntil(\n);
	if(lect=="RA+"||lect=="ra+"||lect=="Ra+"||lect=="rA+")
			{
			lect="";							
			Timer3.stop();
			Timer3.detachInterrupt();			
			tmp+=150;
			Serial.println("Mi nuevo RA: ");	
			Serial.println(tmp);
			Timer3.attachInterrupt(ra).start(tmp);
			}
	if(lect=="RA-"||lect=="ra-"||lect=="Ra-"||lect=="rA-")
			{
			lect="";
			Timer3.stop();
			Timer3.detachInterrupt();
			tmp-=150;
			Serial.println("Mi nuevo RA: ");
			Serial.println(tmp);
			Timer3.attachInterrupt(ra).start(tmp);
			}
	if(lect=="STOPRA"||lect=="stopra")
			{
			lect="";
			Timer3.stop();
			Timer3.detachInterrupt();
			Serial.println("RA Apagado");
			}
	
	if(lect=="RESUMERA"||lect=="resumera")
			{
			lect="";
			Timer3.attachInterrupt(ra).start(tmp);
			Serial.println("RA encendido");
			}
	if(lect=="borrarstring"||lect=="BORRARSTRING"){
		inString="";
		Serial.println("String borrado")
	}
	
	
	 if (isDigit(lect)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (str)buffer;
	  Serial.println(buffer)
    }
	lect="";
	
}

void manual()
{
	x_value=analog.Read(x_axis);
	y_value=analog.Read(y_axis);
	
if(x_value>750||x_value<450||y_value>750||y_value<450)
   {
	while(x_value>750)
	{
		digitalWrite(dir1,1);
		digitalWrite(stp1,1);
		delayMicroseconds(200);
		digitalWrite(stp1,0);
		delayMicroseconds(200);
	}
	while(x_value<450)
	{
		digitalWrite(dir1,0);
		digitalWrite(stp1,1);
		delayMicroseconds(200);
		digitalWrite(stp1,0);
		delayMicroseconds(200);
	}
	while(y_value>750)
	{
		digitalWrite(dir2,1);
		digitalWrite(stp2,1);
		delayMicroseconds(200);
		digitalWrite(stp2,0);
		delayMicroseconds(200);
	}
	while(y_value<450)
	{
		digitalWrite(dir2,0);
		digitalWrite(stp2,1);
		delayMicroseconds(200);
		digitalWrite(stp2,0);
		delayMicroseconds(200);
	}
  }	
}

 
void ra()
{	
state=!state;
digitalWrite(dir1,1);
digitalWrite(stp1,state);
cont1++;
}
