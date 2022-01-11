#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <TM1637Display.h>
#include <TM1637Display.h>

#define CLK 2 // reloj para display
#define DIO 3 //datos para display

const uint8_t SEG_READ[] = {
  SEG_E | SEG_G ,                                  
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,           
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_G | SEG_F,                          
  SEG_D | SEG_E | SEG_B | SEG_G | SEG_C          
  };

 const uint8_t SEG_HI[] = {
  SEG_G,
  SEG_F |  SEG_E | SEG_G | SEG_B | SEG_C,                                  
  SEG_E ,
  SEG_G                                           
  };

 const uint8_t SEG_LO[] = {
  SEG_G,
  SEG_F | SEG_E |SEG_D, 
  SEG_E |  SEG_D | SEG_G | SEG_C,                                  
  SEG_G                                           
  };
  
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); 
int rele1=4;
int rele2=5;
const int Trigger = 6;   //Pin digital 2 para el Trigger del sensor
const int Echo = 7;   //Pin digital 3 para el Echo del sensor
int buzz = A0;
int feed=8; 

float temp,temp1,temp2,temp3,temp4,temp5; 

TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  pinMode(buzz, OUTPUT); 
    
  pinMode(rele1,OUTPUT);
  pinMode(rele2,OUTPUT);
  
  pinMode(feed,OUTPUT);
  digitalWrite(feed,HIGH);
  display.clear();
  mlx.begin();
}

void loop()
{
  display.setBrightness(1);
  display.setSegments(SEG_READ);
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  /*Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();*/
  delay(1000);          //Hacemos una pausa de 100ms 

  if(d <= 10)
  {
    //Serial.print("Ambiente = ");
    //Serial.print(mlx.readAmbientTempC()); 
    //Serial.print("ºC\tObjeto = "); 

display.setBrightness(5);

temp1= 0;
 delay(30);
 temp2= mlx.readObjectTempC();
 delay(30);
 temp3= mlx.readObjectTempC();
 delay(30);
 temp4= mlx.readObjectTempC();
 delay(30);
 temp= mlx.readObjectTempC();


if(temp >= 27.4 && temp <=  28.3){
      temp1= 8.3+temp;
      
    }
      if(temp >= 28.4 && temp <=  29.1){
      temp1= 7.2 +temp;
      
    }
  if(temp >= 29.2 && temp <=  29.9){
      temp1= 6.4+temp;
      
    }
      if(temp >= 30 && temp <=  30.7){
      temp1= 5.6+temp;
      
    }
     if(temp >= 30.8 && temp <=  31.4){
      temp1= 4.9+temp;
      
    }
      if(temp >= 31.5 && temp <=  32.2){
      temp1= 4.2+temp;
      
    }
    if(temp >= 32.3 && temp <=  33){
      temp1= 3.4+temp;
      
    }
    if(temp >= 33.1 && temp <= 33.8){
      temp1 = 2.6 + temp;
      
    }
    if(temp >= 33.9 && temp <= 34.6){
      temp1 = 1.9 + temp;
     
    }
    if(temp >= 34.7 && temp <= 35.4){
      temp1 = 1.2 + temp;
      
    }
     if(temp >= 35.4 && temp <= 35.7){
      temp1 = .3 + temp;
      
    }

  if(temp >= 35.8){
  temp1= temp;
    
}

 
    if(temp1 < 34.7)
    {
      display.setSegments(SEG_LO);
      digitalWrite(rele2,HIGH);
      digitalWrite(buzz,HIGH);
      delay(500);
      digitalWrite(buzz,LOW);
      delay(500);
      digitalWrite(buzz,HIGH);
      delay(500);
      digitalWrite(buzz,LOW);
      delay(500);
      delay(2800);
      digitalWrite(rele2,LOW);
      }
      if(temp1 < 37 && temp1 > 34.8)
      {
        //Serial.print(mlx.readObjectTempC()); 
        //Serial.println("ºC");
        temp1= temp1*100;
        display.showNumberDecEx(temp1,0b11100000);
        digitalWrite(rele1,HIGH); 
        digitalWrite(buzz,HIGH);
        delay(100);
        digitalWrite(buzz,LOW);
        delay(100);
        digitalWrite(buzz,HIGH);
        delay(100);
        digitalWrite(buzz,LOW);
        delay(100);
        delay(2800);
        digitalWrite(rele1,LOW);
        }
        if(temp1 >= 37 && temp1 < 40)
        {
          //Serial.print(mlx.readObjectTempC()); 
          //Serial.println("ºC");
          temp1= temp1*100;
          display.showNumberDecEx(temp1,0b11100000);
          digitalWrite(rele2,HIGH);
          digitalWrite(buzz,HIGH);
          delay(500);
          digitalWrite(buzz,LOW);
          delay(500);
          digitalWrite(buzz,HIGH);
          delay(500);
          digitalWrite(buzz,LOW);
          delay(500);
          delay(2800);
          digitalWrite(rele2,LOW);
          } 
          if(temp1 > 39)
          {
            //Serial.println("Hi");
            display.setSegments(SEG_HI);
            digitalWrite(rele2,HIGH);
            digitalWrite(buzz,HIGH);
            delay(900);
            digitalWrite(buzz,LOW);
            delay(900);
            delay(2800);
            digitalWrite(rele2,LOW);
            }
    }

}
