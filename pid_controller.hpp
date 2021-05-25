#ifndef __PID_CONTROLLER_HPP__
#define __PID_CONTROLLER_HPP__

class PID_Controller : public rtos::task<> {
private:
    hwlib::target::pin_out servo;
    rtos::pool<int> & distancePool;
public:
    PID_Controller(const std::string & name, const hwlib::target::pins & servoPin, rtos::pool<int> & distancePool):
        task(0, name),//0th priority should be the very highest prio
        servo(servoPin),
        distancePool(distancePool)
    {}

    void main(){
        for(;;){
            pwm(distancePool.read()/*Swap this out for some PID derived thing*/, servo);
        }
    }

    void pwm(const int & pulseWidth, hwlib::target::pin_out & pin){
        pin.write(true);
        hwlib::wait_us_busy(1000 + pulseWidth); //Busy because this timing is VERY important
        pin.write(false);
        hwlib::wait_us(18800 - pulseWidth); //Should be able to fit in easily 5 or maybe even 6 or more measurements with the distance sensor. (depends on distance)
    }               //^This^ number might need tweaking!
};

#endif // __PID_CONTROLLER_HPP__
