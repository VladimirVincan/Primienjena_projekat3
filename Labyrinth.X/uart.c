#include "uart.h"

void initUART1(void)
{
    U1BRG= BAUD_RATE_9600; //ovim odredjujemo baudrate
    U1MODEbits.ALTIO=0; //biramo koje pinove koristimo za komunikaciju osnovne ili alternativne
    IEC0bits.U1RXIE=1; //omogucavamo rx1 interupt
    U1STA&=0xfffc;
    U1MODEbits.UARTEN=1; //ukljucujemo ovaj modul
    U1STAbits.UTXEN=1; //ukljucujemo predaju
}

void WriteUART1_char(unsigned int data)
{
	while(!U1STAbits.TRMT);
    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
}

void WriteUART1_int(unsigned int data)
{
    char str[6];
    sprintf(str,"%d",data);
    WriteUART1_string(str);
}

void WriteUART1_intx10(unsigned int data)
{
	unsigned char temp;
    temp=data/10000;
	WriteUART1_char(temp+'0');
	data=data-temp*10000;
	temp=data/1000;
	WriteUART1_char(temp+'0');
	data=data-temp*1000;
	temp=data/100;
	WriteUART1_char(temp+'0');
	data=data-temp*100;
	temp=data/10;
	WriteUART1_char(temp+'0');
	data=data-temp*10;
	WriteUART1_char(data+'0');
}


void WriteUART1_string(register const char *s){
    while(*s)
        WriteUART1_char(*s++);
}

/**************************************************************/

void initUART2(void)
{
    U2BRG = 0x0207; // baud rate 9600
    U2STA &= 0xfffc;
    IEC1bits.U2RXIE = 1; // enable RX2 interrupt
    U2MODEbits.UARTEN = 1; // UARTEN: UART Enable bit
    U2STAbits.UTXEN = 1; // transmition ON
}

void WriteUART2_char(unsigned int data)
{
    U2TXREG = data;
    while(!U2STAbits.TRMT){}
}

void WriteUART2_int(unsigned int data)
{
    unsigned char temp;
    temp=data/1000;
    WriteUART2_char(temp+'0');
    data=data-temp*1000;
    temp=data/100;
    WriteUART2_char(temp+'0');
    data=data-temp*100;
    temp=data/10;
    WriteUART2_char(temp+'0');
    data=data-temp*10;
    WriteUART2_char(data+'0');
}

void WriteUART2_string(const char * s)
{
    while(*s)
        WriteUART2_char(*s++);
} 
