#define LED5Delay rt_thread_mdelay(1)

#define LEDP1 LL_GPIO_PIN_11
#define LEDP2 LL_GPIO_PIN_12
#define LEDP3 LL_GPIO_PIN_13
#define LEDP4 LL_GPIO_PIN_14
#define LEDP5 LL_GPIO_PIN_15

void LED5Init(void);
void LEDALLNULL(void);
void LEDNULL(unsigned int Pin);
void LEDH(unsigned int Pin);
void LEDL(unsigned int Pin);
void DisplayCharge(void);
void DisplayPercent(void);
void DisplaySel1(void);
void DisplaySel2(unsigned char num);
void DisplaySel3(unsigned char num);
void LED5DisplayWait(void);
void LED5Display(unsigned char SOC,unsigned char state);
