#include "hwlib.hpp"
#include "pwm.hpp"

int main() {
    hwlib::wait_ms(1000);
    hwlib::cout << "Good to go" << '\n';

    hwlib::target::pin_adc potentiometer(hwlib::target::ad_pins::a0);
    hwlib::target::pin_out servo(hwlib::target::pins::d52);
    // potentiometer.refresh();
    // int potValue = potentiometer.read();;
    // int lowestPotValue = 0;
    // int highestPotValue = 4500;
    // int angle=0;

    for(;;){
        //potentiometer.refresh();
        //potValue = potentiometer.read();
        //if(potValue < lowestPotValue) lowestPotValue = potValue;
        //if(potValue > highestPotValue) highestPotValue = potValue;
        //angle = ((potValue - lowestPotValue) / (highestPotValue - lowestPotValue)) * 1000;
        //angle = ((potValue - lowestPotValue) * 1000) / ((highestPotValue - lowestPotValue));
        //hwlib::cout << angle << '\n';

        for(int i=0; i<1000; i+=10){
            pwm(i, servo);
        }
    }
}