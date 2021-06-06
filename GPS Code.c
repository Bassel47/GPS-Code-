int main (){
while(1){
int i;
char text3[3];
char text2[2];
char text1[1];
int distance = 185 ;
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
delay(3000);
}

if(distance<100&&distance>=10){
for(i=0;i<2;i++){
char c=text2[i];
LCD_WR(c);}
delay(3000);
}

if(distance>=100){
for(i=0;i<3;i++){
char c=text3[i];
LCD_WR(c);}
delay(3000);
}
}
	}
}
