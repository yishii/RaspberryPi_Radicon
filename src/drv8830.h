#ifndef __DRV8830_H__
#define __DRV8830_H__

class DRV8830
{
 public:
  static const int MOTOR_STANDBY = 0;
  static const int MOTOR_REVERSE = 1;
  static const int MOTOR_FORWARD = 2;
  static const int MOTOR_BRAKE = 3;

  DRV8830(int fd,int slave_address);
  ~DRV8830();
  int control(int power,int type);

 private:
  int i2c_fd;
  int i2c_slaveaddr;
};


#endif /* __DRV8830_H__ */
