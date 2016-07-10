
/*
【接    线】
             VCC ->  3.3V
             GND ->  GND
             SCL ->  E1
             SDA ->  E0
             SA0 ->  GND

【Note    】 采集回来数据通过UART4 （E24，E25）发送到上位机参看
***************************************************************************/
#include "include.h"

/*!
 *  @brief      Init2100()函数
 *  @since      v5.0
 *  @note       初始化2100
 */

Gyro_Data Gyro_data;
Acc_Data Acc_data;
Q_Angle Q_angle;




void Init2100()
{

  i2c_write_reg(I2C0, SlaveAddress2100, 0x0d, 0x02);

  i2c_delay();

  i2c_write_reg(I2C0, SlaveAddress2100, CTRL_REG1_2100, 0x02);

  i2c_delay();
  Gyro_info.counter = 0;
  Gyro_info.Gyro_Sum = 0;
  Gyro_info.RampThresholdValue = 2000;
  Gyro_info.Need_Delay_Counter = 0;

}
/*!
 *  @brief      Init8700()函数
 *  @since      v5.0
 *  @note       初始化8700
 */
void Init8700()
{
  i2c_write_reg(I2C0, SlaveAddress8700, CTRL_REG1_8700, 0x05);

  i2c_delay();

}
/*!
 *  @brief      Init_TLY()
 *  @since      v5.0
 *  @note       初始化陀螺仪模块
 */
void Init_TLY()
{
  i2c_init(I2C0, 400 * 1000);

  Init2100();//加速度计

  Init8700();//陀螺仪
}

/*******************************************************************************
* Function Name  : Acc_read()
* Description    : read acceletate data
* Input          : buf to save acc data
* Output         : None
* Return         : None
* Editor         ：wenhai
***************************************************************************/
void Acc_read()
{
  static unsigned int temp[6];
  temp[0] =  i2c_read_reg(I2C0, SlaveAddress8700, OUT_X_MSB_REG);
  i2c_delay();
  temp[1] =  i2c_read_reg(I2C0, SlaveAddress8700, OUT_X_LSB_REG);
  i2c_delay();
//temp[2] =  i2c_read_reg(I2C0,SlaveAddress8700,OUT_Y_MSB_REG);
  // i2c_delay();
  // temp[3] =  i2c_read_reg(I2C0,SlaveAddress8700,OUT_Y_LSB_REG);
  // i2c_delay();
  temp[4] =  i2c_read_reg(I2C0, SlaveAddress8700, OUT_Z_MSB_REG);
  i2c_delay();
  temp[5] =  i2c_read_reg(I2C0, SlaveAddress8700, OUT_Z_LSB_REG);
  i2c_delay();
  Acc_data.x = ((int16)((0x0000 | (temp[0] << 8)) + temp[1])) - 140;
  // Acc_datas.y = ((int16)((0x0000 | (temp[2]<<8)) + temp[3]))-65;
  Acc_data.z = ((int16)((0x0000 | (temp[4] << 8)) + temp[5]));

}
/*******************************************************************************
* Function Name  : Gyro_read()
* Description    : read gyro data
* Input          : buf to save gyro data
* Output         : None
* Return         : None
* Editor         ：wenhai
***************************************************************************/
void Gyro_read()
{
  static unsigned int temp[6];
  // temp[0] =  i2c_read_reg(I2C0,SlaveAddress2100,OUT_X_MSB_REG);
  // i2c_delay();
  // temp[1]=  i2c_read_reg(I2C0,SlaveAddress2100,OUT_X_LSB_REG);
  // i2c_delay();
  temp[2] =  i2c_read_reg(I2C0, SlaveAddress2100, OUT_Y_MSB_REG);
  i2c_delay();
  temp[3] =  i2c_read_reg(I2C0, SlaveAddress2100, OUT_Y_LSB_REG);
  i2c_delay();
  //temp[4] =  i2c_read_reg(I2C0, SlaveAddress2100, OUT_Z_MSB_REG);
  //i2c_delay();
  //temp[5] =  i2c_read_reg(I2C0, SlaveAddress2100, OUT_Z_LSB_REG);
  //i2c_delay();
  //Gyro_data.x = (((int16)((0x0000 | (temp[0] << 8)) + temp[1])) - 51) * -0.01563; //jiaodu bushi hudu
  Gyro_data.y = (((int16)((0x0000 | (temp[2] << 8)) + temp[3])) + 92) * -0.01563; //*15.63/1000
  //Gyro_data.z = (((int16)((0x0000 | (temp[4] << 8)) + temp[5])) + 4) * 0.01563;
// Gyro_data.x = ((0x0000 | (temp[0]<<8)) + temp[1])*0.0002725;

}


void Imu_calculate()
{
  static float gyro_z_tmp[4];
  static int gyro_z_counter = 0;
  Gyro_read();
  //Acc_read();

//z轴四次平均
  gyro_z_tmp[gyro_z_counter] = Gyro_data.z;
  gyro_z_counter++;
  if (gyro_z_counter >= 4)
    gyro_z_counter = 0;

  Gyro_data.z = 0;
  for (int i = 0; i < 4; i++)
    Gyro_data.z += gyro_z_tmp[gyro_z_counter];

  Gyro_data.z = Gyro_data.z / 4;
///////////////////////////////////////////////////////////

//上坡
  Gyro_info.Gyro_Sum = 0;
  Gyro_info.Gyroscope_Fifo[Gyro_info.counter] = Gyro_data.y;
  Gyro_info.counter++;
  if (Gyro_info.counter == GYRO_LENGTH)
    Gyro_info.counter = 0;

  for (int i = 0; i < GYRO_LENGTH; i++) //70长度
    Gyro_info.Gyro_Sum += Gyro_info.Gyroscope_Fifo[i];
  Gyro_info.Gyro_Sum -= 65; //0偏

  if (Gyro_info.Need_Delay_Counter > 0)
    Gyro_info.Need_Delay_Counter--;
  if ( ( Gyro_info.Gyro_Sum > Gyro_info.RampThresholdValue ) &&  //第一次上坡
       ( Gyro_info.Ramp_Over_0_1st == 0 ) &&
       ( Gyro_info.Ramp_Less_0 == 0) &&
       ( Gyro_info.Ramp_Over_0_2nd == 0 ) &&
       ( Gyro_info.Need_Delay_Counter == 0 ) )
  {
    Gyro_info.RampUpDown = 1;
    Gyro_info.Ramp_Over_0_1st = 1;
    Gyro_info.Ramp_Less_0 = 0;
    Gyro_info.Ramp_Over_0_2nd = 0;

    Car_state.pre = Car_state.now;      //上坡
    Car_state.now = Ramp_Up;
  }
  if ( ( Gyro_info.Gyro_Sum < -(Gyro_info.RampThresholdValue + 500)) &&
       ( Gyro_info.Ramp_Over_0_1st == 1) &&
       ( Gyro_info.Ramp_Less_0 == 0) &&
       ( Gyro_info.Ramp_Over_0_2nd == 0) )
  {
    Gyro_info.RampUpDown = 0;
    Gyro_info.Ramp_Over_0_1st = 1;
    Gyro_info.Ramp_Less_0 = 1;
    Gyro_info.Ramp_Over_0_2nd = 0;

    Car_state.pre = Car_state.now;      //下坡
    Car_state.now = Ramp_Down;
  }
  if ( ( Gyro_info.Gyro_Sum > Gyro_info.RampThresholdValue) &&
       ( Gyro_info.Ramp_Over_0_1st == 1) &&
       ( Gyro_info.Ramp_Less_0 == 1) &&
       (Gyro_info.Ramp_Over_0_2nd == 0))
  {
    Gyro_info.RampUpDown = 0;
    Gyro_info.Ramp_Over_0_1st = 0;
    Gyro_info.Ramp_Less_0 = 0;
    Gyro_info.Ramp_Over_0_2nd = 0;
    Gyro_info.Need_Delay_Counter  = 200;
  }
  if (( Gyro_info.Ramp_Over_0_1st == 0) &&
      ( Gyro_info.Ramp_Less_0 == 0) &&
      ( Gyro_info.Ramp_Over_0_2nd == 0) )
  {
    Gyro_info.RampUpDown = 0;
  }

}
///////////////////////////////////////////////////////

/* Q_angle.gyro =Q_angle.result + (0.005*Gyro_data.y);
 if(Acc_data.z>17090)
     Acc_data.z=17090;
 if(Acc_data.z<1)
     Acc_data.z=1;
 Q_angle.acc = acosf(Acc_data.z/17100.0)*57.29578;
 if (Acc_data.x > 0.0f)
 {
   Q_angle.acc =  (-1) * Q_angle.acc;
 }
 Q_angle.result = (Q_angle.acc*0.0) + Q_angle.gyro*1;
*/

