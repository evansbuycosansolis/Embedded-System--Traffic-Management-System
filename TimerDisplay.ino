#include <TM1637Display.h>

#define CLK1 14
#define DIO1 18

TM1637Display display(CLK1,DIO1);

void setup()
{

}

void loop() {
 display.print(i);
 delay(100);
 i--;
  }
}
