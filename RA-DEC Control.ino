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

long HHRA,MMRA,SSRA;


int x_value=0;
int y_value=0;

boolean state=0;
boolean state2=0;

long  cont1;
long  cont2;

long tmp=31500;

long tmp2=100000;

uint32_t newra;
uint32_t curra;
int32_t newdec;
int32_t curdec;


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
Timer4.attachInterrupt(dec).start(tmp2);

HHRA=0;
MMRA=0;
SSRA=0;

}

void loop ()
{
lectura();
getObj();
mode();	
manual();
comparacion();

}

void lectura(){
	
lect=Serial.readStringUntil('#'||'\n');
	if(lect==":GR#"){
		
	}
	if(lect==":Gr#"){
		
	}
	if(lect==":GD#"){
	
	}
	if(lect==":Gd#"){
		
	}

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
			
	if(lect=="DEC+"||lect=="dec+")
			{
			lect="";							
			Timer4.stop();
			Timer4.detachInterrupt();			
			tmp2+=5000;
			Serial.println("Mi nuevo DEC: ");	
			Serial.println(tmp2);
			Timer3.attachInterrupt(dec).start(tmp2);
			}
	if(lect=="DEC-"||lect=="dec-")
			{
			lect="";
			Timer4.stop();
			Timer4.detachInterrupt();
			tmp-=5000;
			Serial.println("Mi nuevo DEC: ");
			Serial.println(tmp2);
			Timer3.attachInterrupt(dec).start(tmp2);
			}
	if(lect=="STOPRA"||lect=="stopra")
			{
			lect="";
			Timer3.stop();
			Timer3.detachInterrupt();
			Serial.println("RA Apagado");
			}
			
	if(lect=="STOPDEC"||lect=="stopdec")
			{
			lect="";
			Timer4.stop();
			Timer4.detachInterrupt();
			Serial.println("DEC Apagado");
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
	x_value=analogRead(x_axis);
	y_value=analogRead(y_axis);
	
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
	while(y_value>950)
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

void dec(){
	state2=!state2;
	digitalWrite(dir2,1);
	digitalWrite(stp2,state2);
	cont2++;
}

void mode(){

}

void comparacion(){
	
}

void getObj(){
Serial.print(":Gr#");
String get_Obj=Serial.readStringUntil('#');
String get_ObjHH= get_Obj.substring(0,3);
String get_ObjMM= get_Obj.substring(3,6);
String get_ObjSS= get_Obj.substring(6);

}
