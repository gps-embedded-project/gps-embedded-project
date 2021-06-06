#include "tm4c123.h"
#include "Stdio.h"
#include "Stdint.h"
#include "string.h"
#include "math.h"
#include "time.h"
#define PI 3.141592653589793238462643383279502884L
//#include "UART.h"



void SystemInit()
{
	
}
void PortF_Init(void)
{
	SYSCTL_RCGCGPIO_R|=0x00000020;
	while((SYSCTL_PRGPIO_R&0x00000020)==0){};
		GPIO_PORTF_CR_R = 0x1F;
		GPIO_PORTF_DIR_R = 0x0E;
		GPIO_PORTF_PUR_R = 0x11;
		GPIO_PORTF_DEN_R = 0x1F;
	}
	void PortF_Output(uint32_t data){
		GPIO_PORTF_DATA_R = data;
	}
	
	
	
double distance(double x1,double y1,double x2,double y2){
	
	double r;
	double a;
	double c;
	double radius=6371;

  x1=x1*PI/180;
  y1=y1*PI/180;
  x2=x2*PI/180;
  y2=y2*PI/180;

	
	a= pow(sin((y2-y1)/2),2) +  pow(sin((x2-x1)/2),2)*cos(y1)*cos(y2);
	c=asin(sqrt(a));	
	r=2*radius*c*1000;
	
	return r;	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	void PortB_D_Init(void)
{
	SYSCTL_RCGCGPIO_R|=0x00000003;
	while((SYSCTL_PRGPIO_R&0x00000003)==0){};
		GPIO_PORTB_CR_R = 0xFF;
		GPIO_PORTB_DIR_R = 0xFF;
		GPIO_PORTB_PUR_R = 0x00;
		GPIO_PORTB_DEN_R = 0xFF;
		GPIO_PORTB_AMSEL_R = 0x00;
		GPIO_PORTB_AFSEL_R = 0x00;

		GPIO_PORTA_CR_R |= 0xFF;
		GPIO_PORTA_DIR_R |= 0xFF;
		GPIO_PORTA_PUR_R = 0x00;
		GPIO_PORTA_DEN_R = 0xFF;
		GPIO_PORTA_AMSEL_R = 0x00;
		GPIO_PORTA_AFSEL_R = 0x00;	
		
	}
	
	
	
	
	
	
	
	void delay(int x){
	int i;
	int j;
		for(i=0;i<x;i++){
			for(j=0;j<x;j++){}
			}
	}
	
	
	
	
	
	
	
	
	
	
	
	int digit(int* d)
{
int r=*d%10;
*d=*d/10;
switch(r)
{ case 0:
   return 252; //0xFC
  case 1:
   return 96; //0x60
  case 2:
   return 218; //0xDA
  case 3:
   return 242;  //0xF2
  case 4:
   return 102; //0x66
  case 5:
   return 182;  //0xB6
  case 6:
   return 190;  //0xBE
  case 7:
   return 224;  //0xE0
  case 8:
   return 254;  //0xFE
  case 9:
   return 230;  //0xE6
}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
int main(){
	int c=699;
	int s;

	PortF_Init();
	//c=c+distance(31.244223,30.045307,31.802575,30.051153); // this will give 745
	s=c;
	if(c>=100){
	GPIO_PORTF_DATA_R = 0x02;
	}
	

	
	
	
	
	PortB_D_Init();
	
	
	
	

	
	
	
	
	while(1){     //we will replace 1 be push button condition
	GPIO_PORTA_DATA_R &=0xDF;
		GPIO_PORTA_DATA_R |=0xC0 ;


	
			GPIO_PORTB_DATA_R=digit(&c);
		
delay(200);
				

	
	
		
  	GPIO_PORTA_DATA_R &=0xBF;
	  GPIO_PORTA_DATA_R |=0xA0 ;
	   GPIO_PORTB_DATA_R=digit(&c);		
	
delay(200);
		
		GPIO_PORTA_DATA_R &=0x7F;
		GPIO_PORTA_DATA_R |=0x60;
	   GPIO_PORTB_DATA_R=digit(&c);		
		
delay(200);

c=s;



}
	


			
	
	
	
	
	
	
	
	
	
	
	
return 0;
}
