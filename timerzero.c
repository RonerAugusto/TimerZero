/*
 * File:   timerzero.c
 * Author: roner
 *
 * Created on 16 de Abril de 2017, 17:00
 */


#define  _XTAL_FREQ 4000000 
#include "Configuration.h"
#include <xc.h>



/*********function */

void interrupt testtime();


/*******variable*****/

int count = 0x00;
int time = 0xff;

void main(void) {



    CMCON = 0x07; //disable comparator 
    OPTION_REG = 0x81; //disable pull upsri  and pre scale  1/4 

    /************IOS map ********/

    TRISBbits.TRISB0 = 0x01; // just pin RB0 as input 
    TRISBbits.TRISB7 = 0x00; // pin RB7 as output
    TRISAbits.TRISA0 = 0x00; //just pin RA0 as output 


    /*******start of pins */
    PORTBbits.RB0 = 0x00; // start RB0 in 0 volts
    PORTBbits.RB7 = 0x00; // start RB7 in 0 volts




    /**************register timer0 interrupt *********/



    INTCONbits.T0IE = 0x01; // tmr0 over flow interrupt enable
    INTCONbits.T0IF = 0x00; //clear flag over flow 


    /********register external interrupt*/
    INTCONbits.PEIE = 0x01; //peripheral interrupt enable 
    INTCONbits.GIE = 0x01; //global interrupt enable 
    INTCONbits.INTE = 0x01; // external interrupt enable
    INTCONbits.INTF = 0x00; // flag 




    ei(); //all interruptions are enable 


    while (1) {



    }




}

void interrupt testtime() {


    /*******timer interruption********/

    if (INTCONbits.T0IF == 0x01) {



        INTCONbits.T0IF = 0x00; //clear flag of interruption 
        count++; //increment counter

        if (count == time) { //check   whether the cycle buil one second 


            PORTAbits.RA0 = ~PORTAbits.RA0; //invert the state 
            count = 0x00;

        }

    }




    /*****external interruption*****/

    if (INTCONbits.INTF == 0x01) {


        INTCONbits.INTF = 0x00;


        PORTBbits.RB7 = ~PORTBbits.RB7;

        //__delay_ms(3000);



    }
}













