#include <stdio.hpp>
#include <kbd.hpp>

#define INIT_CNT_REG_TIMER 0x380
#define CURRENT_CNT_REG_TIMER 0x390
#define TIMER_REG 0x320
#define LAPIC_ID ioport_in(0x020)
#define LAPIC_VER ioport_in(0x030)




