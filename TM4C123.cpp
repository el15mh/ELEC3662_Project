#include "TM4C123.h"

TM4C123::TM4C123()
{

}

TM4C123::~TM4C123()
{

}

void TM4C123::PortE_Init()
{
    volatile unsigned long delay;

    SYSCTL_RCC2_R |= 0x00000010;        // Activate clock on port E
    delay = SYSCTL_RCC2_R;

    GPIO_PORTE_CR_R = 0x0000000F;       // Allow changes on port E
    GPIO_PORTE_AMSEL_R = 0x00000000;    // Disable analog
    GPIO_PORTE_PCTL_R = 0x00000000;
    GPIO_PORTE_DIR_R = 0x00000002;      // Set I/O port directions
    GPIO_PORTE_AFSEL_R = 0x00000000;    // Disable alt functions
    GPIO_PORTE_PUR_R = 0x0000000;       // Enable pull-up on input pin
    GPIO_PORTE_DEN_R = 0x0000000F;      // Enable digital I/O on PE0-3
}

void TM4C123::PLL_Init(unsigned long frequency)
{
    unsigned long n = 400/frequency - 1;

    SYSCTL_RCC2_R |= 0x80000000;    // Use RCC2
    SYSCTL_RCC2_R |= 0x00000800;    // Bypass PLL whilst initialising
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x000007C0) + 0x00000540; // clear XTAL field and configure for 16 MHz
    SYSCTL_RCC2_R &= ~0x00000070;   // Configure for main oscillator source
    SYSCTL_RCC2_R &= ~0x00002000;   // Activate the PLL
    SYSCTL_RCC2_R |= 0x4000000;     // Set the desired system divider (400 MHz)
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x1FC00000) + (n<<22);    // Configure clock frequency using function argument

    while ((SYSCTL_RIS_R & 0x00000040) == 0){} // Wait for the PLLRIS bit

    SYSCTL_RCC2_R &= ~0x00000800;
}

void TM4C123::SysTick_Init()
{
    NVIC_ST_CTRL_R = 0;             // Disable SysTick during setup
    NVIC_ST_RELOAD_R = 0x00FFFFFF;  // Maximum reload value
    NVIC_ST_CURRENT_R = 0;          // Clear 'current' value
    NVIC_ST_CTRL_R = 0x00000005;
}

void TM4C123::SysTick_Wait(unsigned long delay)
{
    NVIC_ST_RELOAD_R = delay - 1;   // Number of counts to wait
    NVIC_ST_CURRENT_R = 0;          // Clear the register

    while ((NVIC_ST_CTRL_R & 0x00010000) == 0) {}
}