#include <Arduino.h>
#include <stdio.h>
#include <math.h>
#include <avr/io.h>
#include<string.h>
#include "hd44780/HD44780.hpp"
#include "uartLib/uart.hpp"



void sort();
void screen();


	String shuffleDezenas;
	String sortDezenas;
	String dezenas;
	String shuffleDezenas1;
	String sortDezenas1;
	String dezenas1;
	char shufflesDezenaschar[16];
	char sortDezenaschar[16];
	char dezenaschar[16];
	int numbers[11];
	int lottery[11];
	char dezenas11[1000000];
	int counter=0;
    int i,j;
	//byte
	int maxDraw = 6, maxDezenas = 60;
	unsigned int z,x;


	byte botoes = 5;
	int estadoBotoes = 0;


#define LED1 PB5 // LED1 deifnition
#define LED2 PB4 // LED2 deifnition
#define LED3 PB3 // LED2 deifnition
#define LED4 PB2 //LED3 definition

int main(){


	 LCD_Initalize();
	   DDRB |= ((1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5)); // Direction of port line (1 - output)
	     PORTB |= (1<<PORTB2) | (1<<PORTB3) | (1<<PORTB4) | (1<<PORTB5); // Output register (1 - do not light)
	     // BUTTONS CONTROLLER
	     DDRD &= ~(1<<DDD0) | ~(1<<DDD1) | ~(1<<DDD2) | ~(1<<DDD3); // Direction of port line (0 - input)
		  int k;

		  //here i will creat the page when i show the numbers of balls that i will take and the range of them

		  screen();

		  for(;;){
			  int k;


			  // this will increase the number of numbers generate
			 	  if(!(PIND & 1<<PIND3)){
			 	    maxDraw = constrain(maxDraw + 1, 1, 10);
			 	    _delay_ms(400);
			 	    screen();
			 	  }

			 	  //this will decrease the number of numbers generate
			 	  if(!(PIND & 1 <<PIND2)){
			 	    maxDraw = constrain(maxDraw - 1, 1, 10);
			 	    _delay_ms(400);
			 	    screen();
			 	  }


			 	  // this if will increase the range of draw numbers
			 	  if(!(PIND & 1<<PIND1)){
			 	    maxDezenas = constrain(maxDezenas + 1, 10, 99);
			 	    	if(maxDezenas==99){

			 	    		maxDezenas=10;
			 	    	}
				 	    _delay_ms(200);
			 	    screen();
			 	  }




					//here i will start taking my random balls


			 	  if(!(PIND & 1<<PIND0)){  // este pin é o mais a esquerda

			 		  	 LCD_Clear();

			 		  	 // here i want to creat the balls i will bet

			 		  		 numbers[0]=9;numbers[1]=7;numbers[2]=32;numbers[3]=7;numbers[4]=66;numbers[5]=12;numbers[6]=83;numbers[7]=43;
			 		  		 numbers[8]=57;numbers[9]=27;
			 		  		 // this for will create a suspense while generating the numbers/balls
			 	    for (byte rep = 1; rep <= 9; rep++) {
			 	    	LCD_GoTo(0,1);

			 	      _delay_ms(100);

			 	      counter=0;
			 	      	LCD_GoTo(0,0);
			 	      	//here will write the numbers in the superior part of the arduino
			 	      for (k = 1; k <= maxDraw / 2; k++) {
			 	    	  	  int tttt;
			 	    	  shuffleDezenas1=random(0,maxDezenas);
			 	    	  z=shuffleDezenas1.length()+1;
			 	    	  tttt=shuffleDezenas1.toInt();
			 	    	  shuffleDezenas1.toCharArray(shufflesDezenaschar,z);
			 	    	  LCD_WriteText(shufflesDezenaschar);
			 	    	  LCD_WriteText(" ");
			 	    	  lottery[counter]=tttt;
			 	    	  counter++;
			 	      }


			 	      LCD_GoTo(0,1);
			 	      // here will write in the down part of the arduino
			 	      for (k = maxDraw / 2 + 1; k <= maxDraw; k++) {
			 	    	  int ww;

			 	    	 shuffleDezenas1=random(0,maxDezenas); // shuffleDezenas is a string , random generate number between 0 and maxDezenas
			 	    	 z=shuffleDezenas1.length()+1; // to char array i need the length of the string
			 	    	  shuffleDezenas1.toCharArray(shufflesDezenaschar,z);
			 	    	  ww=shuffleDezenas1.toInt();
			 	    	 LCD_WriteText(shufflesDezenaschar);
			 	    	 LCD_WriteText(" ");
			 	    	lottery[counter]=ww; // shufflesdezenaschar = 56
			 	    	counter++;
			 	      }//

			 	    } // este é para o for de rep

			 	    	_delay_ms(300);
			 	 	 i=0;j=0;

			 	 	 //here i will see if the numbers of the lottery corresponde to mine
			 				 	int tt=0;
			 				     if(maxDraw==2){

			 				 	  	 while(i<=1){  // [0]=9 , [1]=7 -> numbers , lottery -> [0]=7 , [1]=9
			 				 	  		 while(j<=1){
			 				 	  			 if(numbers[i]==lottery[j]){
			 				 	  				 tt++;
			 				 	  			 }
			 				 	  			 j++;
			 				 	  		 }
			 				 	  		 i++;
			 				 	  		 j=0;
			 				 	  	 }

			 				 	  	 if(tt>=maxDraw){
			 				 	  		 LCD_Clear();
			 				 	  		 LCD_GoTo(0,1);
			 				 	  		 LCD_WriteText("winner");
			 				 	  	 }
			 	  }

			 	  }




		  }


}




// thsi function will show our inicial screen
	void screen() {                 // LCD print routine
		int y;
		char t[12];
	  LCD_GoTo(0, 0);
	  LCD_WriteText("LOTTERY|");
	  LCD_GoTo(0, 1);
	  LCD_WriteText("WINNER |");
	  LCD_GoTo(8, 0);
	  LCD_WriteText("TOT|DRAW");
	  LCD_GoTo(9,1);

	  sprintf(t, "%d", maxDezenas);
	  // tot maxDezenas
	 LCD_WriteText(t);
	  LCD_WriteText("| ");
	  if (maxDraw < 10) {
		  sprintf(t, "%d", maxDraw);
		  LCD_WriteText("0");
		  LCD_WriteText(t);
	  }
	  else {

		  sprintf(t, "%d", maxDraw);
		  LCD_WriteText(t);	  }

	}







