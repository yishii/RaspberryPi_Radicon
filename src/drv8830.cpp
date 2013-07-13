/*
  TI's DRV8830 device driver

  Coded by Yasuhiro ISHII
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "drv8830.h"

DRV8830::DRV8830(int fd,int slave_address)
{
  i2c_fd = fd;
  i2c_slaveaddr = slave_address;
}

DRV8830::~DRV8830()
{
  i2c_fd = -1;
  i2c_slaveaddr = 0;
}

int DRV8830::control(int power,int type)
{
  unsigned char buff[2];
  int result;

  if(type != MOTOR_STANDBY &&
     type != MOTOR_REVERSE &&
     type != MOTOR_FORWARD &&
     type != MOTOR_BRAKE) {
    printf("Err\n");
    return 0;
  }

  // set slave address to i2c driver
  ioctl(i2c_fd,I2C_SLAVE,i2c_slaveaddr);

  // create data to send to DRV8830
  buff[0] = 0x00;
  buff[1] = (unsigned char)(power << 2) | (unsigned char)(type & 0x03);

  // invoke command to DRV8830
  result = write(i2c_fd,buff,2);

  if(result != 2){
    return(0);
  } else {
    return(1);
  }
}
