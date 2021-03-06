#include "pwmlib.h"

PWM::PWM(int address,bool debug)
{
        fd = wiringPiI2CSetup(0x40);
        Address = address;
        Debug = debug;
        if(Debug)
                printf("Reseting PCA9685\n");
        wiringPiI2CWriteReg8(fd, MODE1, 0x00);

}

void PWM::setPWMFreq(int freq)
{
                prescaleval = 25000000.0f;
                prescaleval /= 4096.0;
                prescaleval /= (float)freq;
                prescaleval -= 1.0;
                if(Debug)
                {
                    printf("Setting PWM frequency to %d Hz\n", freq);
                        printf("Estimated pre-scale: %lf\n", prescaleval);
                }
                prescale = floor(prescaleval + 0.5);
                if(Debug)
                {
                        printf("Final pre-scale: %lf\n", prescale);
                }
                int oldmode = wiringPiI2CReadReg8(fd, MODE1);
                int newmode = (oldmode & 0x7F) | 0x10;
                wiringPiI2CWriteReg8(fd, MODE1, newmode);
                wiringPiI2CWriteReg8(fd, PRESCALE,(int)floor(prescale));
                wiringPiI2CWriteReg8(fd, MODE1, oldmode);
                sleep(0.005);
                wiringPiI2CWriteReg8(fd, MODE1, oldmode | 0x80);


}

void PWM::setPWM(int channel, int on, int off)
{
                        wiringPiI2CWriteReg8(fd, LED0_ON_L+4*channel, on & 0xFF);
                        wiringPiI2CWriteReg8(fd, LED0_ON_H+4*channel, on >> 8);
                        wiringPiI2CWriteReg8(fd, LED0_OFF_L+4*channel, off & 0xFF);
                        wiringPiI2CWriteReg8(fd, LED0_OFF_H+4*channel, off >> 8);
                        
}