// base address for peripherals
#define PERIPH_BASE			(0x40000000UL)
// offset for AHB1 peripheral bus
#define AHB1PERIPH_OFFSET	(0x00020000UL)
// base address for AHB1 peripherals
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET)
// offset for GPIO
#define GPIOA_OFFSET		(0x0000UL)
#define GPIOC_OFFSET		(0x0800UL)
// base address for GPIO
#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET)
#define GPIOC_BASE			(AHB1PERIPH_BASE + GPIOC_OFFSET)
// offset for RCC
#define RCC_OFFSET			(0x3800UL)
// base address for RCC
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)
// offset for AHB1EN register
#define AHB1EN_R_OFFSET		(0x30UL)
// address of AHB1EN register
#define RCC_AHB1EN_R		(*(volatile unsigned int *) (RCC_BASE + AHB1EN_R_OFFSET))
// offset for mode register
#define MODE_R_OFFSET		(0x00UL)
// address of GPIOA mode register
#define GPIOA_MODE_R		(*(volatile unsigned int *) (GPIOA_BASE + MODE_R_OFFSET))
// offset for output data register
#define OD_R_OFFSET			(0x14UL)
// offset for input data register
#define ID_R_OFFSET			(0x10UL)
// address of GPIO output data register
#define GPIOA_OD_R			(*(volatile unsigned int *) (GPIOA_BASE + OD_R_OFFSET))
#define GPIOC_ID_R			(*(volatile unsigned int *) (GPIOC_BASE + ID_R_OFFSET))
// bit mask for enabling GPIO
#define GPIOAEN				(1U << 0)
#define GPIOCEN				(1U << 2)
// bit mask for GPIO pins
#define PIN5				(1U << 5)
#define PIN13				(1U << 13)
// aliases for pins
#define LED_PIN				PIN5
#define USR_BTN				PIN13

int main(void)
{
	// enable clock access to GPIOA
	RCC_AHB1EN_R |= GPIOAEN;
	RCC_AHB1EN_R |= GPIOCEN; // and GPIOC

	GPIOA_MODE_R |= (1U << 10);
	GPIOA_MODE_R &= ~(1U << 11);

	// infinite loop
	while(1)
	{
		// user button is set to high by default
		if (!(GPIOC_ID_R & USR_BTN))
		{
			// set PA5(LED_PIN) high
			GPIOA_OD_R |= LED_PIN;
		}
		else
		{
			// set PA5(LED_PIN) low
			GPIOA_OD_R &= ~(LED_PIN);
		}
	}

}
