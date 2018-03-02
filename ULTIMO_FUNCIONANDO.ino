//Librerias


#include <DueTimer.h>
#include <stdlib.h>


//Variables
#define stp1 3
#define stp2 6
#define dir1 4
#define dir2 7
#define ena1 5
#define ena2 8
#define x_axis A0
#define y_axis A1

char RA_telescopio[9];

char DEC_telescopio[10];

char datos[30];  

long HHRAtel,MMRAtel,SSRAtel,RAtel;

long DDDECtel,MMDECtel,SSDECtel,DECtel;



String get_ObjHHRA;
String get_ObjMMRA;
String get_ObjSSRA;
String get_ObjRA;

long get_telHHRA;
long get_telMMRA;
long get_telSSRA;
long get_telRA;


String get_ObjDDDEC;
String get_ObjMMDEC;
String get_ObjSSDEC;
String get_ObjDEC;



long get_telDDDEC;
long get_telMMDEC;
long get_telSSDEC;
long get_telDEC;




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


String lect="";
String inString="";

void setup(){
Serial.begin(9600);
pinMode(stp1,OUTPUT);    //defino salidas del motor 1 y 2
pinMode(stp2,OUTPUT); //*****  
pinMode(dir1,OUTPUT); //*****
pinMode(dir2,OUTPUT); //*****
pinMode(ena1,OUTPUT); //*****
pinMode(ena2,OUTPUT); //*****
//Timer3.attachInterrupt(ra).start(tmp);  //Llamo a RA cada tmp [ms]
//Timer4.attachInterrupt(dec).start(tmp2);


/*
RAtel=(long(42)*long(60))+long(42);   



DECtel=(long(41)*long(3600))+long(16)*long(60);
*/

RAtel=(long(01)*long(60))+long(01);   



DECtel=(long(-89)*long(3600))+long(59)*long(60);


}

void loop ()
{
lectura();
//getObj();
mode(); 
manual();
}

void lectura(){
  int i=0;
  datos[i++]=Serial.read();
  delay(5);
  while((datos[i++]=Serial.read())!='#'){       //Leo hasta el final del comando, que es un simbolo #
    delay(5);                                   //Espero 5ms por si aun no esta disponbile el siguiente dato
  }
  datos[i]='\0';        
  
 if(datos[1]==':' && datos[2]=='G' && datos[3]=='R' && datos[4]=='#'){
    
get_telHHRA=RAtel/long(3600);
get_telMMRA=(RAtel-(HHRAtel*long(3600)))/long(60);
get_telSSRA=RAtel-(HHRAtel*long(3600))-(MMRAtel*long(60));
    
    sprintf(RA_telescopio, "%02d:%02d:%02d", int(get_telHHRA), int(get_telMMRA), int(get_telSSRA));
    Serial.print(RA_telescopio);
    Serial.print("#");    
  }
  if(datos[1]==':' && datos[2]=='G' && datos[3]=='D' && datos[4]=='#'){
  
get_telDDDEC=DECtel/long(3600);
get_telMMDEC=(DECtel-(DDDECtel*long(3600)))/long(60);
get_telSSDEC=DECtel-(DDDECtel*long(3600))-(MMDECtel*long(60));
    
    sprintf(DEC_telescopio, "%+03d:%02d:%02d", int(get_telDDDEC), int(get_telMMDEC), int(get_telSSDEC));
    Serial.print(DEC_telescopio);
    Serial.print("#");    

 
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
    Serial.println("String borrado");
  }
  
  /*
   if (isDigit(lect)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (str)buffer;
    Serial.println(buffer);
    }
  */
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

//Comparo el valor obtenido de Stellarium (RA/DEC) con la
//posicion de mi telescopio.



  
}

void getObj(){

//Obtengo RA del objetivo
Serial.print(":Gr#");
delayMicroseconds(1000);
 get_ObjRA=Serial.readStringUntil('#');
 get_ObjHHRA= get_ObjRA.substring(0,3);
 get_ObjMMRA= get_ObjRA.substring(3,6);
 get_ObjSSRA= get_ObjRA.substring(6);

HHRAtel=get_ObjHHRA.toInt();

MMRAtel=get_ObjMMRA.toInt();

SSRAtel=get_ObjSSRA.toInt();

 RAtel=(HHRAtel*long(3600))+(MMRAtel*long(60))+(SSRAtel*long(1));

//Obtengo DEC del objetivo
Serial.print(":Gd#");
delayMicroseconds(1000);
 get_ObjDEC=Serial.readStringUntil('#');;
 get_ObjDDDEC=get_ObjDEC.substring(1,4);
 get_ObjMMDEC=get_ObjDEC.substring(4,7);
 get_ObjSSDEC=get_ObjDEC.substring(7);

DDDECtel=get_ObjDDDEC.toInt();

MMDECtel=get_ObjMMDEC.toInt();

SSDECtel=get_ObjSSDEC.toInt();

DECtel=(DDDECtel*long(3600))+(MMDECtel*long(60))+(SSDECtel*long(1));


comparacion();

}
