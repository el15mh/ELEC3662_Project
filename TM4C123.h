//
// Created by Max Houghton on 04/11/2017.
//

#ifndef CALCULATOR_PROJECT_TM4C123_H
#define CALCULATOR_PROJECT_TM4C123_H

// PRE-PROCESSOR DERIVATIVES SECTION

// DEFINITIONS FOR PORT D


// DEFINITIONS FOR PORT E
#define GPIO_PORTE_DATA_R   (* ((volatile unsigned long *) 0x400243FC))
#define GPIO_PORTE_DIR_R    (* ((volatile unsigned long *) 0x40024400))
#define GPIO_PORTE_AFSEL_R  (* ((volatile unsigned long *) 0x40024420))
#define GPIO_PORTE_PUR_R    (* ((volatile unsigned long *) 0x40024510))
#define GPIO_PORTE_DEN_R    (* ((volatile unsigned long *) 0x4002451C))
#define GPIO_PORTE_AMSEL_R  (* ((volatile unsigned long *) 0x40024528))
#define GPIO_PORTE_PCTL_R   (* ((volatile unsigned long *) 0x4002452C))
#define GPIO_PORTE_LOCK_R   (* ((volatile unsigned long *) 0x40024520))
#define GPIO_PORTE_CR_R     (* ((volatile unsigned long *) 0x40024524))
#define SYSCTL_RCGC2_GPIOE  0x00000010  // Port E Clock Gating Control

// DEFINITIONS FOR THE PLL
#define SYSCTL_RIS_R        (* ((volatile unsigned long *) 0x400FE050))
#define SYSCTL_RCC_R        (* ((volatile unsigned long *) 0x400FE060))
#define SYSCTL_RCC2_R       (* ((volatile unsigned long *) 0x400FE070))

// DEFINITIONS FOR SYSTICK
#define NVIC_ST_CTRL_R      (* ((volatile unsigned long *) 0xE000E010))
#define NVIC_ST_RELOAD_R    (* ((volatile unsigned long *) 0xE000E014))
#define NVIC_ST_CURRENT_R   (* ((volatile unsigned long *) 0xE000E018))

/**
 * @brief TM4C123 Class to perform functions on the ports in order to read from and write to peripheral devices
 * and to use the clock to perform delays.
 * @author Max Houghton
 * @date Nov. 4 2017
 */

class TM4C123 {

public:

    /**
     * @details Constructor function
     */
    TM4C123();

    /**
     * @details Destructor function
     */
    ~TM4C123();

    /**
     * @brief Initialisation method for Port E
     * @details Initialise the clock and unlock, disable analog and set I/O directions on necessary pins.
     */
    void PortE_Init();

    /**
     * @brief Initialisation method for SysTick
     * @details Set the maximum reload value, clear 'current' value and enable SysTick with core clock.
     */
    void SysTick_Init();

    /**
     * @brief Initialisation method for the PLL
     * @details Configure the PLL by setting the crystal frequency to 16 MHz and the PLL to 400 MHz then divide by the
     * amount specified by the argument 'frequency' in order to set the desired system clock frequency.
     * @param frequency - This specifies the frequency of the PLL to run at - a small conversion is made to find
     * divisor needed to find the value to divide 400 by to set the right frequency.
     */
    void PLL_Init(unsigned long frequency);

    /**
     * @brief Delay method
     * @details Using the SysTick and PLL, decrement the argument delay in small delays of 12.5 ns.
     * @param delay - the value to count down from, units of the 80 MHz clock.
     */
    void SysTick_Wait(unsigned long delay);

    /**
     * @brief value to hold state of Port E input
     */
    unsigned long E_input;

    /**
     * @brief value to describe the contrast level of the LCD
     */
    double contrast;

private:



};

#endif //CALCULATOR_PROJECT_TM4C123_H