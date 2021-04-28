#include "hwlib.hpp"

int main() {
    hwlib::wait_ms(1000);
    hwlib::cout << "Good to go" << '\n';

    hwlib::target::pin_adc potentiometer(hwlib::target::ad_pins::a0);

    for(;;){
        potentiometer.refresh();
        hwlib::cout << potentiometer.read() << '\n';
    }
  
}