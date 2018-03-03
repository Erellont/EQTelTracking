
//#include <AF//motor.h>
#include <stdlib.h>
#include <DueTimer.h>

/*
AF_Stepper //motor_AR(48, 1);
AF_Stepper //motor_DEC(48, 2);
*/
char datos[30];  //Datos leidos por el puerto serie

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
boolean state2=0;

long  cont1;
long  cont2;

long tmp=25000;

long tmp2=100000;


//Coordenadas del telescopio y del objetivo
char RA_telescopio[9];
char DEC_telescopio[10];
char RA_objetivo[9];
char DEC_objetivo[10];

int DEC_dd;
 unsigned int DEC_mm, DEC_ss;
int RA_hh;
 unsigned int RA_mm, RA_ss;



long RA_tel, DEC_tel, RA_obj, DEC_obj;

//Inicializamos los datos
void setup() {
  Serial.begin(9600);                                     // Puerto Serie a 9600 bps
  pinMode(stp1,OUTPUT);    //defino salidas del motor 1 y 2
  pinMode(stp2,OUTPUT); //*****  
  pinMode(dir1,OUTPUT); //*****
  pinMode(dir2,OUTPUT); //*****
  pinMode(ena1,OUTPUT); //*****
  pinMode(ena2,OUTPUT); //*****
  Timer3.attachInterrupt(ra).start(tmp);  //Llamo a RA cada tmp [ms]
//  Timer4.attachInterrupt(dec).start(tmp2);
  
  //Esto hay que modificarlo, las coordenadas iniciales tienen que venir dadas
  RA_obj=RA_tel=long(23)*long(3600)+long(59)*long(60)+long(59);             
  DEC_obj=DEC_tel=90*long(3600);
}

void loop() {
  if(Serial.available()>0){
    leer_datos_serie();
  }
  comparar_coordenadas();
  manual(); 
}

void comparar_coordenadas(){
    if(RA_tel<RA_obj){
      incrementar_ra();  
    }
    if(RA_tel>RA_obj){
    decrementar_ra();
    }
    if(DEC_tel<DEC_obj){
  incrementar_dec();
    }
    if(DEC_tel>DEC_obj){
 decrementar_dec();
    } 
}
void incrementar_ra(){
  RA_tel++;
}
void decrementar_ra(){
  RA_tel--;
}
void incrementar_dec(){
  DEC_tel++;
}
void decrementar_dec(){
  DEC_tel--;
}

//Recoge los datos que haya en el puerto serie
void leer_datos_serie(){
  int i=0;
  datos[i++]=Serial.read();
  delay(5);
  while((datos[i++]=Serial.read())!='#'){       //Leo hasta el final del comando, que es un simbolo #
    delay(5);                                   //Espero 5ms por si aun no esta disponbile el siguiente dato
  }
  datos[i]='\0';                                //Completo la cadena con el simbolo de fin de cadena, cosas del C
  parsear_datos();                              //Llamo a la funcion que interpreta los datos recibidos
}

//Interpreta los datos que se han recibido en el puerto serie
void parsear_datos(){

  // #:GR#  -> Obtener posicion RA del telecopio
  if(datos[1]==':' && datos[2]=='G' && datos[3]=='R' && datos[4]=='#'){
    RA_hh=RA_tel/long(3600);
    RA_mm=((RA_tel-(RA_hh*long(3600)))/long(60));
    RA_ss=(RA_tel-(RA_hh*long(3600))-(RA_mm*long(60)));
    sprintf(RA_telescopio, "%02d:%02d:%02d", int(RA_hh), int(RA_mm), int(RA_ss));
    //
    Serial.print(RA_telescopio);
    Serial.print("#");
  }

  // #:GD#  -> Obtener posicion DEC del telescopio
  if(datos[1]==':' && datos[2]=='G' && datos[3]=='D' && datos[4]=='#'){
    DEC_dd=DEC_tel/long(3600);   //148560 -> 41 16
    DEC_mm=((DEC_tel-(DEC_dd*long(3600)))/long(60));
    DEC_ss=(DEC_tel-(DEC_dd*long(3600))-(DEC_mm*long(60)));
    sprintf(DEC_telescopio, "%02d:%02d:%02d", int(DEC_dd), int(DEC_mm), int(DEC_ss));
    Serial.print('-');
    Serial.print(DEC_telescopio);
    Serial.print("#");  
  }

  // #:Q#   -> Detener el telescopio
  if(datos[1]==':' && datos[2]=='Q' && datos[3]=='#'){
  }                                                                        // <<<---- Esto hay que dejarlo bien

  // :Sr HH:MM:SS#  -> Direccion RA del objetivo
  if(datos[0]==':' && datos[1]=='S' && datos[2]=='r'){
    for(int i=0;i<8;i++)
      RA_objetivo[i]=datos[i+4];                                    
    Serial.print("1");
    RA_obj=long(atoi(datos+4))*long(3600)+long(atoi(datos+7))*long(60)+long(atoi(datos+10));
  }
  
  // :Sd sDD*MM:SS# ->Direccion DEC del objetivo
  if(datos[0]==':' && datos[1]=='S' && datos[2]=='d'){
    for(int i=0;i<9;i++)
      DEC_objetivo[i]=datos[i+5];                                        
    Serial.print("1");
    DEC_obj=long(atoi(datos+5))*long(3600)+long(atoi(datos+8))*long(60)+long(atoi(datos+11));
  }
  
  // :MS# -> Comenzar slew
  if(datos[0]==':' && datos[1]=='M' && datos[2]=='S' && datos[3]=='#'){
    Serial.print("0");                                                     // <<<---- Esto hay que dejarlo bien
  }
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
   x_value=analogRead(x_axis);
  y_value=analogRead(y_axis);
  
  }
  while(x_value<450)
  {
    digitalWrite(dir1,0);
    digitalWrite(stp1,1);
    delayMicroseconds(200);
    digitalWrite(stp1,0);
    delayMicroseconds(200);
 x_value=analogRead(x_axis);
  y_value=analogRead(y_axis);
  }
  while(y_value>950)
  {
    digitalWrite(dir2,1);
    digitalWrite(stp2,1);
    delayMicroseconds(200);
    digitalWrite(stp2,0);
    delayMicroseconds(200);
    x_value=analogRead(x_axis);
  y_value=analogRead(y_axis);
  }
  while(y_value<450)
  {
    digitalWrite(dir2,0);
    digitalWrite(stp2,1);
    delayMicroseconds(200);
    digitalWrite(stp2,0);
    delayMicroseconds(200);
  x_value=analogRead(x_axis);
  y_value=analogRead(y_axis);
  }
  } 


 
void ra()
{ 
state=!state;
digitalWrite(dir1,1);
digitalWrite(stp1,state);
cont1++;
if(cont1==40){
RA_tel--;
if(RA_tel==0){
  RA_tel=86400;
}
cont1=0;
}}

void dec(){
  state2=!state2;
  digitalWrite(dir2,1);
  digitalWrite(stp2,state2);
  DEC_tel--;
}
