#include "hwlib.hpp"
#include "rtos.hpp"
#include <string>
#include "pid_controller.hpp"
#include "hc_sr04.hpp"

int main() {
    hwlib::wait_ms(1000);
    hwlib::cout << "Good to go" << '\n';

    //hwlib::target::pin_adc potentiometer(hwlib::target::ad_pins::a0);
    //hwlib::target::pin_out servo(hwlib::target::pins::d52);
    rtos::pool<int> distancePool;
    PID_Controller pidController(hwlib::target::pins::d52, distancePool);
    HC_SR04 distanceSensor(hwlib::target::pins::d53, hwlib::target::pins::d51, distancePool, pidController);

    // potentiometer.refresh();
    // int potValue = potentiometer.read();;
    // int lowestPotValue = 0;
    // int highestPotValue = 4500;
    // int angle=0;

    rtos::run();

    uint_fast64_t startTime = hwlib::now_us();
    unsigned int cycles = 1000;
    for(unsigned int i=0; i<cycles; i++){
    //for(;;){
        //potentiometer.refresh();
        //potValue = potentiometer.read();
        //if(potValue < lowestPotValue) lowestPotValue = potValue;
        //if(potValue > highestPotValue) highestPotValue = potValue;
        //angle = ((potValue - lowestPotValue) / (highestPotValue - lowestPotValue)) * 1000;
        //angle = ((potValue - lowestPotValue) * 1000) / ((highestPotValue - lowestPotValue));
        //hwlib::cout << angle << '\n';

        // for(int i=1; i<1000; i++){
        //     for(int j=0; j<1000; j+=i){
        //         pwm(j, servo);
        //     }
        // }

        //distanceSensor.read();
        //hwlib::cout << distanceSensor.read() << "\n";
    }
    uint_fast64_t endTime = hwlib::now_us();

    hwlib::cout << "Time in micro seconds\nTotal time: " << endTime - startTime << " (for " << cycles << " cycles). Time per cycle: " << (endTime - startTime) /cycles << "\n";
}