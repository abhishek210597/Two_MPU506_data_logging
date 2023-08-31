#include<math.h>
#include <Wire.h>

#include <SD.h>
#include <SPI.h>




const int MPU2=0x69,MPU1=0x68;
long AcX1, AcY1, AcZ1,AcX2, AcY2, AcZ2;
float gForceX, gForceY, gForceZ;

float AccX1,AccY1,AccZ1,GyX1,GyY1,GyZ1;
float AccX2,AccY2,AccZ2,GyX2,GyY2,GyZ2;
float rotX2, rotY2, rotZ2;
float rotX1, rotY1, rotZ1;
//NewPing sonar(4,5,3000);
void setup() {
 // pinMode(13,OUTPUT);
  //pinMode(8,OUTPUT);
  Serial.begin(9600);

  Wire.begin();

  
    Wire.begin(); 
    Wire.beginTransmission(MPU1);
    Wire.write(0x6B);// PWR_MGMT_1 register 
    Wire.write(0); // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);Wire.begin(); 
    Wire.beginTransmission(MPU2);
    Wire.write(0x6B);// PWR_MGMT_1 register 
    Wire.write(0); // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);

  
}



void loop() {


  //get values for first mpu having address of 0x68   
  GetMpuValue1(MPU1);
  
  //get values for second mpu having address of 0x69
  GetMpuValue2(MPU2);

  Serial.print(millis());
  Serial.print(",");
  Serial.print(AccX1 * 9.8);
  Serial.print(",");
  Serial.print(AccY1 * 9.8);
  Serial.print(",");
  Serial.print(AccZ1 * 9.8);
  Serial.print(",");
  Serial.print(rotX1);
  Serial.print(",");
  Serial.print(rotY1);
  Serial.print(",");
  Serial.print(rotZ1);
  Serial.print(",");
  Serial.print(AccX2 * 9.8);
  Serial.print(",");
  Serial.print(AccY2 * 9.8);
  Serial.print(",");
  Serial.print(AccZ2 * 9.8);
  Serial.print(",");
  Serial.print(rotX2);
  Serial.print(",");
  Serial.print(rotY2);
  Serial.print(",");
  Serial.println(rotZ2);

}



//----------------------------------------------\user defined functions\-------------------------------------------------- 
      
 
 void GetMpuValue1(const int MPU){ 
   
      Wire.beginTransmission(MPU); 
      Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) 
      Wire.endTransmission(false);
      Wire.requestFrom(MPU, 14, true); // request a total of 14 registers 
      AcX1=Wire.read()<<8| Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
      AcY1=Wire.read()<<8|  Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
      AcZ1=Wire.read()<<8| Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) 
      //Tmp1=Wire.read()<<8| Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L) 
      GyX1=Wire.read()<<8| Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L) 
      GyY1=Wire.read()<<8| Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L) 
      GyZ1=Wire.read()<<8| Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L) 
    
    processAccelData1();
     
     }
     
     
  void processAccelData1() {
  AccX1= gForceX = AcX1 / 16384.0;
  AccY1= gForceY = AcY1 / 16384.0;
  AccZ1= gForceZ = AcZ1 / 16384.0;
  
  rotX1=(GyX1/131.0);
  rotY1=(GyY1/131.0);
  rotZ1=(GyZ1/131.0);
  



    // ## conversion from bits to real-world values
    // accel_factor = ((2.0**15.0)-1.0)/2.0 # conversion using sensitivity (+- 2g or 2*9.8)
    // gyro_factor = ((2.0**15.0)-1.0)/250.0 # conversion using sensitivity (250 deg/sec)
  
}
     



 void GetMpuValue2(const int MPU){ 
   
      Wire.beginTransmission(MPU); 
      Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) 
      Wire.endTransmission(false);
      Wire.requestFrom(MPU, 14, true); // request a total of 14 registers 
      AcX2=Wire.read()<<8| Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
      AcY2=Wire.read()<<8|  Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
      AcZ2=Wire.read()<<8| Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) 
     // Tmp2=Wire.read()<<8| Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L) 
      GyX2=Wire.read()<<8| Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L) 
      GyY2=Wire.read()<<8| Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L) 
      GyZ2=Wire.read()<<8| Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L) 
    
      processAccelData2();

     }



     void processAccelData2() {
    AccX2= gForceX = AcX2 / 16384.0;
    AccY2= gForceY = AcY2 / 16384.0;
    AccZ2= gForceZ = AcZ2 / 16384.0;
  
  rotX2=(GyX2/131.0);
  rotY2=(GyY2/131.0);
  rotZ2=(GyZ2/131.0);



    // ## conversion from bits to real-world values
    // accel_factor = ((2.0**15.0)-1.0)/2.0 # conversion using sensitivity (+- 2g)
    // gyro_factor = ((2.0**15.0)-1.0)/250.0 # conversion using sensitivity (250 deg/sec)



  
}

