/*
  Radicon sample for RaspberryPi (and some other linux-based system)

  Coded by Yasuhiro ISHII,2013
*/
#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "drv8830.h"

#define I2C_SLAVEADDR_MOTOR_L 0x64
#define I2C_SLAVEADDR_MOTOR_R 0x68

#define MOTOR_POWER 0x20

int main(void)
{
  struct input_event event;
  int fd;
  int flag;

  printf("radicon start\n");

  fd = open("/dev/i2c-1",O_RDWR);
  if(fd < 0){
    printf("i2c open error\n");
    return(-1);
  }

  DRV8830 motor_l(fd,I2C_SLAVEADDR_MOTOR_L);
  DRV8830 motor_r(fd,I2C_SLAVEADDR_MOTOR_R);

  flag = 1;
  while(flag == 1){
    read(0,&event,sizeof(event));

    if(event.type == EV_KEY && event.value != 0){
      switch(event.code){
      case KEY_UP:
	printf("UP is pressed\n");
	motor_l.control(MOTOR_POWER,DRV8830::MOTOR_FORWARD);
	motor_r.control(MOTOR_POWER,DRV8830::MOTOR_FORWARD);
	break;
      case KEY_DOWN:
        printf("DOWN is pressed\n");
        motor_l.control(MOTOR_POWER,DRV8830::MOTOR_REVERSE);
        motor_r.control(MOTOR_POWER,DRV8830::MOTOR_REVERSE);
        break;
      case KEY_LEFT:
        printf("LEFT is pressed\n");
        motor_l.control(MOTOR_POWER,DRV8830::MOTOR_FORWARD);
        motor_r.control(MOTOR_POWER,DRV8830::MOTOR_REVERSE);
        break;
      case KEY_RIGHT:
        printf("RIGHT is pressed\n");
        motor_l.control(MOTOR_POWER,DRV8830::MOTOR_REVERSE);
        motor_r.control(MOTOR_POWER,DRV8830::MOTOR_FORWARD);
        break;
      default:
	printf("Other key is pressed\n");
	printf("type = %x\n",event.type);
	printf("value = %x\n",event.value);
	flag = 0;
	break;
      }
    } else if(event.value == 0){
      motor_l.control(0x00,DRV8830::MOTOR_BRAKE);
      motor_r.control(0x00,DRV8830::MOTOR_BRAKE);
    }
  }

  return(1);
}
