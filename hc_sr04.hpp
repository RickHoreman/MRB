#ifndef __HC_SR04_HPP__
#define __HC_SR04_HPP__

#include "hwlib.hpp"
#include "rtos.hpp"
#include <string>
#include "pid_controller.hpp"

class HC_SR04 : public rtos::task<>{
private:
    hwlib::target::pin_out trigger;
    hwlib::target::pin_in echo;
    rtos::pool<int> & distancePool;
    PID_Controller & pidController;
public:
    HC_SR04(const hwlib::target::pins & triggerPin, const hwlib::target::pins & echoPin, rtos::pool<int> & distancePool, PID_Controller & pidController):
        task("HC_SR04"),
        trigger(triggerPin),
        echo(echoPin),
        distancePool(distancePool),
        pidController(pidController)
    {
        trigger.write(false);
    }

    void main(){
        distancePool.write(read());
        pidController.setFirstRead();
        for(;;){
            distancePool.write(read());
            release();
        }
    }

    int read(){                     //Average time varies wildy from roughly 1ms to over 6 times that, depending on distance.
        uint_fast64_t echoTime = 0; //Although it takes roughly 3ms for an object at ~50cm, which will be the max distance in my system.
        trigger.write(true);
        hwlib::wait_us(10);
        trigger.write(false);
        for(unsigned int i=0; i<1000000; i++){
            if(echo.read()){
                echoTime = hwlib::now_us();
                break;
            }
        }
        for(unsigned int i=0; i<1000000; i++){
            if(!echo.read()){
                int distance = ((hwlib::now_us() - echoTime) *0.34) /2; //Distance in mm
                if(distance <= 4000){ //Sensor is rated for up to 4 meters
                    return distance; //anything higher can be considered out of range
                }else{               //or noise/jibberish
                    return 4001;
                }
            }
        }
        return -1;
    }
};

#endif // __HC_SR04_HPP__
