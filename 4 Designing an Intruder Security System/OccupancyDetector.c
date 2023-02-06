/*
 * OccupancyDetector.c
 *
 *  Created on: Jan 30, 2023
 *      Author: russty
 */


#include <msp430.h>

char state = 0;                       // Global Variable to track if the LED should be on or off

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    // Configure GPIO
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction
    P6DIR |= BIT6;



    P2OUT |= BIT3;                          // Configure P2.3 as pulled-up
    P2REN |= BIT3;                          // P2.3 pull-up register enable
    P2IES &= ~BIT3;                         // P2.3 Low --> High edge
    P2IE |= BIT3;                           // P2.3 interrupt enabled

    P4DIR &= ~BIT1;             // Configure P4.1 to an Input
    P4OUT |= BIT1;                          // Configure P2.3 as pulled-up
    P4REN |= BIT1;                          // P2.3 pull-up register enable

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    P2IFG &= ~BIT3;                         // P2.3 IFG cleared

    __bis_SR_register(GIE);                 // Enter LPM3 w/interrupt

    while(1)
    {
        // @TODO You will need to modify this code to change between blinking the Red LED or the Green LED
        if (ToggleEnable) {
            P1OUT ^= BIT0;                  // P1.0 = toggle
            P6OUT &= ~BIT6;
        }
        else {
            P1OUT &= ~BIT0;                 // Set P1.0 to 0
            P6OUT ^= BIT6;
        }
        __delay_cycles(100000);
    }
}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    // @TODO You might need to modify this based on your approach to the lab
    P2IFG &= ~BIT3;                         // Clear P1.3 IFG
    state = 0;                   // Enable if the toggle should be active
}




