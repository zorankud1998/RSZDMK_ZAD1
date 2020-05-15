#include <LiquidCrystal.h>
#include <util/delay.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
unsigned char redosled [] = {5,5,5,5};
unsigned char odgovor [] = {5,5,5,5};
unsigned char uneto = 0;

char ocitaj_taster()
{
  char taster = 0;
  unsigned char row;
  
  MCUCR &= ~0x10;
  PORTD = 0x0f; 
  
  for(row = 0x80; row != 0x08; row >>= 1)
  {
    DDRD = row;
	_delay_ms(2);
    
    switch(row | ((~PIND) & 0x0f))
    {
      case 0x88:
      	taster = '1'; break;
      case 0x84:
      	taster = '2'; break;
      case 0x82:
      	taster = '3'; break;
      case 0x81:
      	taster = 'A'; break;
		
	  case 0x48:
      	taster = '4'; break;
      case 0x44:
      	taster = '5'; break;
      case 0x42:
      	taster = '6'; break;
      case 0x41:
      	taster = 'B'; break;
		
	  case 0x28:
      	taster = '7'; break;
      case 0x24:
      	taster = '8'; break;
      case 0x22:
      	taster = '9'; break;
      case 0x21:
      	taster = 'C'; break;
		
	  case 0x18:
      	taster = '*'; break;
      case 0x14:
      	taster = '0'; break;
      case 0x12:
      	taster = '#'; break;
      case 0x11:
      	taster = 'D'; break;
    }
  }
  
  return taster;
}



void igra()
{
  	znakovi();
  	lcd.home();
  	for(unsigned char i=0; i<4; i++)
    {
      redosled[i] = rand()%4;
      lcd.write(byte(redosled[i]));
    }
  	_delay_ms(2000);
  	lcd.clear();
  	lcd.print("____");
  	lcd.setCursor(0,0);
  	lcd.cursor();
  	uneto = 1;
}


void znakovi()
{
	byte srce[] = {
  		B00000,
  		B00000,
 		B11011,
  		B11111,
  		B11111,
  		B11111,
  		B01110,
  		B00100
	};
  	lcd.createChar(0, srce);
  	byte karo[] = {
  		B00100,
  		B01110,
  		B01110,
  		B11111,
  		B11111,
  		B01110,
  		B01110,
 	 	B00100
	};
  	lcd.createChar(1, karo);
  	byte tref[] = {
  		B00000,
  		B01110,
  		B01110,
  		B11111,
  		B11111,
  		B00100,
  		B00100,
  		B01110
	};
  	lcd.createChar(2, tref);
  	byte pik[] = {
  		B00000,
  		B00100,
  		B01110,
  		B11111,
  		B11111,
  		B11011,
  		B00100,
  		B01110
	};
  	lcd.createChar(3, pik);
}

int main()
{
  	lcd.begin(16, 2);
  	char counter = -1;
	char staro;
  	char novo;
  	char pozicija = 0;
  
	while(1)
    { 
	  char taster = ocitaj_taster();
     novo = taster;
      if(staro != novo)
      {
        staro = novo;
      	if (taster == '*')
      	{
        	igra();
      	}
      	if(taster == '2' && uneto == 1)
      	{
        	counter++;
          	if(counter > 3){counter = 0;}
      		lcd.write(byte(counter));
          	odgovor[pozicija] = counter;
        	lcd.setCursor(pozicija , 0);
      	}
        if(taster == '8' && uneto == 1)
      	{
        	counter--;
          	if(counter < 0){counter = 3;}
      		lcd.write(byte(counter));
          	odgovor[pozicija] = counter;
        	lcd.setCursor(pozicija , 0);
      	}
        if(taster == '4' && uneto == 1)
      	{
          	if(pozicija > 0) {pozicija--;}
          	lcd.setCursor(pozicija , 0);
      	}
        if(taster == '6' && uneto == 1)
      	{
          	if(pozicija < 3) {pozicija++;}
          	lcd.setCursor(pozicija , 0);
      	}
        if(taster == '5' && uneto == 1)
        {
          uneto = 0;
          unsigned char tacno = 1;
          lcd.setCursor(0,1);
          for(unsigned char i = 0 ; i<4 ; i++)
          {
          		lcd.write(byte(redosled[i]));
            	if(redosled[i] != odgovor[i]){tacno = 0;}
          }
          if(tacno == 1){lcd.print(" Pogodili ste");}
          if(tacno == 0){lcd.print(" Niste pogodili");}
        }
      }
    }
  
  	return 0;
}
