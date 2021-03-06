#include<reg52.h>
//*********************************************************************************************************
// Configuracion de pines del LCD
//*********************************************************************************************************
extern bit RS;                                                                   
extern bit EN;                           
extern bit D4;
extern bit D5;
extern bit D6;
extern bit D7;
sbit RS = P2^0;                                                                   
sbit EN = P2^1;                            
sbit D4 = P2^4;
sbit D5 = P2^5;
sbit D6 = P2^6;
sbit D7 = P2^7;
//*********************************************************************************************************
// Delay Bloqueante Mili Segundos (con cristal externo de 12MHz @ 1MIPS)
//*********************************************************************************************************
void delay(int a){
   int i, j;
   for(i=0;i<a;i++){
      for(j=0;j<50;j++);
   }
}
//*********************************************************************************************************
// Funcion que escribe en puerto
//*********************************************************************************************************
void lcdPort(char a){
   if(a & 1) D4 = 1; 
	 else D4 = 0;
   if(a & 2) D5 = 1; 
	 else D5 = 0;
   if(a & 4) D6 = 1; 
	 else D6 = 0;
   if(a & 8) D7 = 1; 
	 else D7 = 0;
}
//*********************************************************************************************************
// Funcion que envia comando
//*********************************************************************************************************
void lcdCmd(char a){ 
   RS = 0;
   lcdPort(a);
   EN = 1;
   delay(5);
   EN = 0;
}
//*********************************************************************************************************
// Borrado de LCD
//*********************************************************************************************************
lcdClear(){
   lcdCmd(0);
   lcdCmd(1);
}
//*********************************************************************************************************
// Funcion para ir a la posicion especifica
//*********************************************************************************************************
void lcdGotoxy(char a, char b){
   char temp,z,y;
   if(a==1){
     temp = 0x80 + b;
      z = temp>>4;
      y = temp & 0x0F;
      lcdCmd(z);
      lcdCmd(y);
   }else{ 
      if(a==2){
         temp = 0xC0 + b;
         z = temp>>4;
         y = temp & 0x0F;
         lcdCmd(z);
         lcdCmd(y);
      }
   }		
}
//*********************************************************************************************************
// Inicializa LCD
//*********************************************************************************************************
void lcdInit(){
   lcdPort(0x00);
   delay(200);
   lcdCmd(0x03);
   delay(50);
   lcdCmd(0x03);
   delay(110);
   lcdCmd(0x03);
   lcdCmd(0x02);    
   lcdCmd(0x02);
   lcdCmd(0x08);    
   lcdCmd(0x00); 
   lcdCmd(0x0C);     
   lcdCmd(0x00);    
   lcdCmd(0x06);   
}
//*********************************************************************************************************
// Funcion para escribir caracter
//*********************************************************************************************************
void lcdWriteChar(char a){
   char temp,y;
   temp = a&0x0F; 
   y = a&0xF0;   
   RS = 1;
   lcdPort(y>>4);
   EN = 1;
   delay(5);
   EN = 0;
   lcdPort(temp);
   EN = 1;
   delay(5);
   EN = 0;
}
//*********************************************************************************************************
// Funcion para escribir string
//*********************************************************************************************************
void lcdWriteString(char *a){
   int i;
   for(i=0;a[i]!='\0';i++)
      lcdWriteChar(a[i]);
}
//*********************************************************************************************************
// Funcion principal
//*********************************************************************************************************
void main(){
   lcdinit();                                  
   while(1){                                   
      lcdGotoxy(1,1);
      lcdWriteString("   UTN INSPT   ");
      lcdGotoxy(2,1);
      lcdWriteString(" LCD con 8051  ");
   }
}
