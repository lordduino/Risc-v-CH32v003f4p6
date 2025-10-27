/* 
  Brasil - sp - sp
     Autor: lordduino 
     Data:  outubro de 2025
     Placa: RISC-V ch32v003f4p6 TENSTAR ROBOT
     rotina de reset por software utilizando IDE Arduino
     Direitos: livre
     https://github.com/lordduino     
*/

#include "debug.h"
// rotina de reset residente
extern "C" {void handle_reset(void);} 
#define Bt PC0  // pino ligado ao botão ligado ao + 3,2v
#define press_short 100  // tempo limite pressão rapida botão 
#define press_long 1000   // tempo minimo botão seguro pressionado
long press=0;   // retenção de tempo para calculo

void setup()	{ 
 SystemCoreClockUpdate();   // ajustamento de clock
 pinMode (PC6, OUTPUT);  // pino ligado ao botão ligado ao + 3,2v
 pinMode (PC5, OUTPUT);  // pino ligado ao botão ligado ao + 3,2v
 pinMode (PC7, OUTPUT);  // pino ligado ao botão ligado ao + 3,2v
 pinMode(Bt, INPUT);   // pino botão como entrada
 Serial.begin(115200);   // habilita serial
 Serial.printf("Ola Este é Risk-V CH32v003F4P6 \n\r");    // inicia impressão serial
 Serial.printf("Pressione Botão para ver SystemClk & ChipID \n\r");
 Serial.printf("Pressione e segure Botão para reiniciar placa (*reset) \n\r");
 Serial.printf("SystemClk: %d\r\n",SystemCoreClock);
 Serial.printf( "ChipID:    %08x\r\n", DBGMCU_GetDEVID() );
 delay(500);    // tempo para evitar repet reset continuo
}

void loop()	{  
if(digitalRead(Bt) == HIGH)	{	// Pressionado Botao
    press = millis();		// Conta tempo Pressionado
   while((millis() - press < press_long) && (digitalRead(Bt) == HIGH)) // Compara tempos
 if(millis() - press >= press_long)	  {	   // Tempo => press_long, reset
    handle_reset(); // realiza reset
   while(digitalRead(Bt) == HIGH);		}    // botão solto, compara
 else if (millis() - press < press_short) {	   // tempo < press_short, imprime dados
  Serial.printf("\r\n");   // inicia impressão serial
  Serial.printf("SystemClk:  %d\r\n",SystemCoreClock);
  delay(100);
  Serial.printf("ChipID:     %08x\r\n",DBGMCU_GetDEVID());
  Serial.printf("TempoPress: %d\r\n",press);
 //                                         }
 //                           }  
  digitalWrite(PC5, HIGH);  // Azul
  delay(50);
  digitalWrite(PC7, LOW);
  delay(100);
    digitalWrite(PC6, HIGH);  // Verde
    delay(50);
  digitalWrite(PC5, LOW);
  delay(100);
 digitalWrite(PC7, HIGH); //Vermelho
 delay(50);
 digitalWrite(PC6, LOW);
  delay(100);
   digitalWrite(PC7, LOW);
   delay(100);
    }
  }
}