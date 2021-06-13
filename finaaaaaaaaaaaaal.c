#include "tm4c123.h"
#include "Stdio.h"
#include "Stdint.h"
#include "string.h"
#include "math.h"
#include "time.h"
#include "Stdlib.h"

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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//Assume a 16 MHz bus clock , creates 9600 baud rate
void UART_Init(void) {
  SYSCTL_RCGCUART_R |= 0x0020; // activate UART5
  SYSCTL_RCGCGPIO_R |= 0x0010; // activate Port E
  UART5_CTL_R &= ~0x0001; // disable UART
  UART5_IBRD_R = 104;
// IBRD = int(16000000/(16*9600)) = int(104.0.1666) = 104
  UART5_FBRD_R = 11;
// FBRD = round(0.1666 * 64 + 0.5) = 11.1624 = 11
  UART5_LCRH_R = 0x0070; // 8-bit word length, enable FIFO 001110000 
  UART5_CTL_R = 0x0301; // enable RXE, TXE and UART 001100000001
  GPIO_PORTE_AFSEL_R |= 0x30; // enable alt function on PE4 ,PE5
  GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFF00FFFF)+0x00110000;
  GPIO_PORTE_DEN_R |= 0x30; // enable digital I/O on PE4, PE5 
  GPIO_PORTE_AMSEL_R &= ~0x30; // disable analog function on PE4, PE5
//E4 RX
//E5 TX


	
}
	
	
	
	
	
	
	
	unsigned char UART5_In_Char(void){
	while((UART5_FR_R&0x10) != 0){}
	return UART5_DR_R&0xFF;
}

void UART5_In_String(char *str){
	char c = UART5_In_Char();
	while(c && c != ','){
		*str = c;
		str++;
		c = UART5_In_Char();
	}
	*str = 0x00;
}

//$GPRMC,time,A,latitude,N,longitude,E,speed,angle,Date,Magnetic Variation,checksum data
//$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A
void gps_read(double * logitude,double * latitude){ 
	char holder[50];
	char c;
	c = UART5_In_Char();
	if(c == '$'){
		c = UART5_In_Char();
		if(c == 'G'){
			c = UART5_In_Char();
			if(c == 'P'){
				c = UART5_In_Char();
				if(c == 'R'){
					c = UART5_In_Char();
					if(c == 'M'){
						c = UART5_In_Char();
						if(c == 'C'){
							c = UART5_In_Char();
							if(c == ','){
								c = UART5_In_Char();
								if(c != ','){ //if there is good data
									while(c != ','){c = UART5_In_Char();} //revise the following code carefully
									c = UART5_In_Char();
									if((c == 'A') || (c == 'V')){
										c = UART5_In_Char();
										if(c == ','){
											UART5_In_String(holder); //Get latitude in holder
											
											*latitude = atof(holder);
											
											c = UART5_In_Char();//Read N
											c = UART5_In_Char();//Read ,
											
											UART5_In_String(holder);
											*logitude = atof(holder);
											return;
	}}}}}}}}}}
	*latitude = 0;
	*logitude = 0;
	
}
	

	
	
	
	
	
	
	



	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void PortA_B_Init(void)
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
	int c=0;
	int s;
	double x1=0,y1=0,x2=0,y2=0;
	PortF_Init();
	PortA_B_Init();
  UART_Init();
	
	while (x1==0&&y1==0){ 
	 gps_read(&x1,&y1);
	}
		GPIO_PORTF_DATA_R |= 0x08; 
	
	
	while(1) {
	
	if ((GPIO_PORTF_DATA_R&0x10)==0x00){
	     if(c>100)
{
GPIO_PORTF_DATA_R &=~ 0x04;
	GPIO_PORTF_DATA_R |= 0x02;//red
}
  gps_read(&x1,&y1);
			GPIO_PORTF_DATA_R &=~ 0x08;
	GPIO_PORTF_DATA_R |= 0x04; //blue
  delay(1000);
	
		while(1){

	if ((GPIO_PORTF_DATA_R&0x01)==0x01){
		gps_read(&x2,&y2);
	c=c+distance(x1,y1,x2,y2); 
  x1=x2;
  y1=y2;
  delay(1000);
		
	GPIO_PORTF_DATA_R|=0x02;
	}
	
	
	
	
 	else if ((GPIO_PORTF_DATA_R&0x01)==0x00){

  	
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
		
 
}
	
}
}
		
}
	
	
	/*
gps_read(&x1,&y1);
	PortF_Init();
	c=c+distance(31.244223,30.045307,31.802575,30.051153); // this will give 745
	s=c;
	if(c>=100){
	GPIO_PORTF_DATA_R = 0x02;
	}
	

	
	
	
	
	PortA_B_Init();
	
	
	
	

	
	
	
	
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
	
	*/
	
	
	

	
return 0;
}
