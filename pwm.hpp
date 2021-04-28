#ifndef __PWM_HPP__
#define __PWM_HPP__

void pwm(const int & pulseWidth, hwlib::target::pin_out & pin){
    pin.write(true);
    hwlib::wait_us(1000 + pulseWidth);
    pin.write(false);
    hwlib::wait_us(18800 - pulseWidth);
}

#endif // __PWM_HPP__
