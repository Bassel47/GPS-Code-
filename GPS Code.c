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
double DST(double lat1, double lon1, double lat2, double lon2) {
double theta, dist;
if ((lat1 == lat2) && (lon1 == lon2)) {
return 0;
}
else {
theta = lon1 - lon2;
dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
dist = acos(dist);
dist = rad2deg(dist);
dist = dist * 60 * 2560.8651;
return (dist);
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
void LCD_CMD(unsigned char cmd){
GPIO_PORTA_DATA_R = 0 ;
GPIO_PORTB_DATA_R = cmd ;
GPIO_PORTA_DATA_R |= EN ;
delay(2);
GPIO_PORTA_DATA_R &= ~EN ;
if(cmd<4) delay(2); else delayus(40);}
	
	
void GPS_Init(){
SYSCTL_RCGCUART_R |=SYSCTL_RCGCUART_R3 ;
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2 ;
while ((SYSCTL_PRGPIO_R & 0x04) == 0);	
GPIO_PORTC_LOCK_R = 0x4C4F434B;
GPIO_PORTC_CR_R |= 0x40 ;
GPIO_PORTC_DEN_R |= 0x40;
GPIO_PORTC_AFSEL_R |= 0x40;    
GPIO_PORTC_AMSEL_R |= 0x00;
GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&=~0x0F000000)|0x0F000000; 
UART3_CTL_R = 0x0000;
UART3_IBRD_R = 104;
UART3_FBRD_R = 11;
UART3_LCRH_R = 0x60;
UART3_CTL_R = 0x0301;
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
while(1){
int i;
char text3[3];
char text2[2];
char text1[1];
int distance = 185 ;
GPS_Init()
RGBLED_Init ();
if (distance >=100){
GPIO_PORTF_DATA_R |= 0x02;
}
sprintf(text1,"%d",distance);
sprintf(text2,"%d",distance);
sprintf(text3,"%d",distance);
LCD_Init();{
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
}
