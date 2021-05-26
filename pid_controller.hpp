#ifndef __PID_CONTROLLER_HPP__
#define __PID_CONTROLLER_HPP__

#include "hwlib.hpp"
#include "rtos.hpp"
#include <string>
#include <array>

class PID_Controller : public rtos::task<>{
private:
    hwlib::target::pin_out servo;
    rtos::pool<int> & distancePool;
    rtos::flag firstReadFlag;

    //Debug things
    unsigned int counter=0;
    std::array<int, 1000> loopTimes;
    std::array<int, 1000> pulseWidths;
    //
public:
    PID_Controller(const hwlib::target::pins & servoPin, rtos::pool<int> & distancePool):
        task(0, "PID_Controller"),//0th priority should be the very highest prio
        servo(servoPin),
        distancePool(distancePool),
        firstReadFlag(this, "firstReadFlag")
    {}

    void main(){
        wait(firstReadFlag);
        int startTime=0; //Debug
        for(unsigned int i=0; i<1000; i++){
            startTime = hwlib::now_us(); //Debug
            pwm(distancePool.read()/*Swap this out for some PID derived thing*/, servo);
            //rtos::display_statistics();
            loopTimes[counter] = hwlib::now_us() - startTime; //Debug
            counter++; //Debug
        }
        rtos::display_statistics();
        printDebug(); //Debug, obviously :)
    }

    void setFirstRead(){
        firstReadFlag.set();
    }

    void pwm(int pulseWidth, hwlib::target::pin_out & pin){
        pin.write(true);
        if(pulseWidth > 1000) pulseWidth = 1000;//Temporary
        pulseWidths[counter] = pulseWidth; //Debug
        hwlib::wait_us(1000 + pulseWidth); //Busy because this timing is VERY important
        pin.write(false);
        hwlib::wait_us(18000 - pulseWidth); //Should be able to fit in easily 5 or maybe even 6 or more measurements with the distance sensor. (depends on distance)
    }                //^This^ number might need tweaking!

    void printDebug(){
        hwlib::cout << "Counter: " << counter << "\n";
        int loopTimeSum = 0;
        for(unsigned int i=0; i<counter; i++){
            loopTimeSum += loopTimes[i];
        }
        hwlib::cout << "Average full loop time: " << loopTimeSum/counter << "\n";
        hwlib::cout << "All pulsewidths for the servo pwm: "; for(int pulseWidth : pulseWidths){hwlib::cout<<pulseWidth<<" ";} hwlib::cout<<"\n";
    }
};

#endif // __PID_CONTROLLER_HPP__
