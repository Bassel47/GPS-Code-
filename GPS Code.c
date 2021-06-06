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
