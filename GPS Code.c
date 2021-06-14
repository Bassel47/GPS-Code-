#include"stdint.h"
#include"stdlib.h"
#include"stdio.h"
#include"math.h"
#include"string.h"
#include"C:\Keil\tm4c123gh6pm.h"
void SystemInit(){}

#define RS 0x20
#define RW 0x40
#define EN 0x80
#define pi 3.14159265358979323846

double deg2rad(double deg) {
return (deg * pi / 180);
}

double rad2deg(double rad) {
return (rad * 180 / pi);
}
double DST(double lat2, double lon2) {
    double lat1; double lon1;
double theta, dist;
if ((lat1 == lat2) && (lon1 == lon2)) {
return 0;
}
else {
    int n=1;
    if(n==1){
        lat1=lat2;
        lon1=lon2;
        n=n+1;
    }
       
theta = lon1 - lon2;
dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
dist = acos(dist);
dist = rad2deg(dist);
dist = dist * 60 * 2560.8651;
    lat1=lat2;
    lon1=lon2;
return (dist);
}
}
void delay(int x) {
int i,j;
for(i=0;i<x;i++)
{
for(j=0;j<3180;j++){}
}
}
void delayus(int y)
{
int i, j;
for(i = 0 ;i < y; i++)
for(j = 0; j < 3; j++)
{}
}
	
int UART3_Check(){
  return ((UART3_FR_R & UART_FR_RXFE ) == UART_FR_RXFE)? 0:1;
}
 

unsigned char UART3_read(void){
   while(UART3_Check()!=1){};
    return (unsigned char)(UART3_DR_R & 0xFF);	 
}	
	
	
void LCD_CMD(unsigned char cmd){
GPIO_PORTA_DATA_R = 0 ;
GPIO_PORTB_DATA_R = cmd ;
GPIO_PORTA_DATA_R |= EN ;
delay(2);
GPIO_PORTA_DATA_R &= ~EN ;
if(cmd<4) delay(2); else delayus(40);}
	
	
void GPS_Init(){
SYSCTL_RCGCUART_R |=SYSCTL_RCGCUART_R3 ;
    while((SYSCTL_PRUART_R & SYSCTL_RCGCUART_R3) == 0);
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2 ;   
    while((SYSCTL_PRGPIO_R & 0x04) == 0){};
GPIO_PORTC_LOCK_R = 0x4C4F434B;
GPIO_PORTC_CR_R |= 0x40 ;
GPIO_PORTC_DEN_R |= 0x40;
GPIO_PORTC_AFSEL_R |= 0x40;   
GPIO_PORTC_AMSEL_R &= ~0x40;
GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & ~0xFF000000) | (GPIO_PCTL_PC6_U3RX | GPIO_PCTL_PC7_U3TX );
UART3_CTL_R &= ~UART_CTL_UARTEN;
UART3_IBRD_R = 104;
UART3_FBRD_R = 11;
UART3_LCRH_R = (UART_LCRH_WLEN_8| UART_LCRH_FEN );
UART3_CTL_R = (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE);
}

	
void RGBLED_Init ()
{
SYSCTL_RCGCGPIO_R |= 0x20;
while ((SYSCTL_PRGPIO_R&0x20) == 0){};
GPIO_PORTF_LOCK_R = 0x4C4F434B;
GPIO_PORTF_CR_R |= 0x0E;
GPIO_PORTF_DIR_R |= 0X0E;
GPIO_PORTF_DEN_R |= 0x0E;
GPIO_PORTF_AMSEL_R &= ~0x0E;
GPIO_PORTF_AFSEL_R &= ~0x0E;
GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
} 


void LCD_Init(){
SYSCTL_RCGCGPIO_R |= 0x02;
while ((SYSCTL_PRGPIO_R & 0x02) == 0);	
GPIO_PORTB_DIR_R |= 0xFF;
GPIO_PORTB_DEN_R |= 0xFF;
GPIO_PORTB_AFSEL_R |= 0x00;    
GPIO_PORTB_AMSEL_R |= 0x00;
GPIO_PORTB_PCTL_R |= 0x00; 
	
SYSCTL_RCGCGPIO_R |= 0x01;
while ((SYSCTL_PRGPIO_R & 0x01) == 0);	
GPIO_PORTA_DIR_R |= 0xE0;
GPIO_PORTA_DEN_R |= 0xE0;
GPIO_PORTA_AFSEL_R |= 0x00;    
GPIO_PORTA_AMSEL_R |= 0x00;
GPIO_PORTA_PCTL_R |= 0x00; 
LCD_CMD(0x38);
LCD_CMD(0x0F);
LCD_CMD(0x06);
LCD_CMD(0x01);
}

void LCD_WR(unsigned char data){
GPIO_PORTA_DATA_R = RS ;
GPIO_PORTA_DATA_R &= ~RW ;
GPIO_PORTB_DATA_R = data ;
GPIO_PORTA_DATA_R |= EN ;
delay(2);
GPIO_PORTA_DATA_R &= ~EN  ;
}


int main (){
int i;
char text3[3];
char text2[2];
char text1[1];
int distance  ;
LCD_Init();{
delay(20);
LCD_CMD(0x01);
delay(4);}
UART3_Check();
GPS_Init()
RGBLED_Init ();
while(1){

if (distance >=100){
GPIO_PORTF_DATA_R |= 0x02;
}

if(UART3_read()=='$'){
	if(UART3_read()=='G'){
		if(UART3_read()=='P'){
			if(UART3_read()=='R'){
				if(UART3_read()=='M'){
					if(UART3_read()=='C'){
						for(g=0;g<48;g++){
							DATA[g]=UART3_read();}
						for(g=0;g<48;g++){
							LCD_WR(DATA[g]);
							delay(100);
							if(g==16){LCD_CMD(0x01);}
							if(g==32){LCD_CMD(0x01);}
						if(g==48){LCD_CMD(0x01);}
						}
		for(g=0;g<48;g++){						
		if(DATA[g]==','){
			CNT++;}
		if(DATA[g]==',' && CNT==3){	
		for(j=0;j<=6;j++){
			g=g+1;
    LNG[j]=DATA[g];
		}
		

		}
		if(c==',' && CNT==5){
		for(k=0;k<=6;k++){
			g=g+1;
		LAT[k]=DATA[g];
		}
		CNT=0;}
LONGIT=strtod(LNG,&ptr);
LATIT=strtod(LAT,&pts);
distance=DST( LATIT , LONGIT);
sprintf(text1,"%d",distance);
sprintf(text2,"%d",distance);
sprintf(text3,"%d",distance);
delay(20);
LCD_CMD(0x01);
delay(4);
LCD_WR('D');
LCD_WR('I');
LCD_WR('S');	
LCD_WR('T');
LCD_WR('A');
LCD_WR('N');
LCD_WR('C');
LCD_WR('E');
LCD_WR('=');
if(distance<10){
for(i=0;i<1;i++){
char c=text1[i];
LCD_WR(c);}
delay(1000);
}

if(distance<100&&distance>=10){
for(i=0;i<2;i++){
char c=text2[i];
LCD_WR(c);}
delay(1000);
}

if(distance>=100){
for(i=0;i<3;i++){
char c=text3[i];
LCD_WR(c);}
delay(1000);
}

	}
}
