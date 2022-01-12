# Self-growing-garden: Internet of things for planting automatically
- Name: Qian Jin(Ashley)
- Student ID: uncfqji
- Email: unfnqji@ucl.ac.uk
- Date: 13, Dec, 2021
- Professor: Martin
## About

This is a fully automatic plant care system. It can realize automatic watering based on soil humidity, automatic temperature control based on air temperature, automatic humidity control based on air humidity, and automatic lighting based on light intensity. It also saves water resources while helping plants grow healthily.

This IOT garden has two mode:

If you are too busy to take care your plant, choose the self-growing mode:https://www.youtube.com/watch?v=yOcGHOeshqI

If you want to enjoy the pleasure of planting and get proffessional advise, chose the Infrared control mode:https://www.youtube.com/watch?v=JpR6kpfqF1I

***
## Background and Related Work
### Background
Taking care of plants indoors is difficult because we usually:
- Forget to water
- Water plant too much
- Don't know when to water
- Put plant in a too dry environment
- live in poor illumination room
- live in environment too warm or too cold 
To help people plant easier and more proffessional， I design this self-growing-garden based on Arduino and take my plant, a peace lily, as example.
<img width="483" alt="Screenshot 2021-12-15 at 11 03 17" src="https://user-images.githubusercontent.com/67747655/146175171-8295c011-b610-47d1-beda-74b9e357057a.png">


### Raleted Work
According to David(2021,para. 5.), Water, light, temperature and air are the four main environmental factors that influence plant growth. 
As for the peace lily:
- Temperature: peace lilies enjoy warm conditions between 20 and 30 °C during the day.
- Air: Peace Lily loves to be kept in humidity levels that are moderate or high. 40% and more humidity is advisable.
- Light: The illumination range peace lily enjoys is 2100–16825 lux.
- Water: Soil moisture of 30%-50% is more suitable for peace lily growth.
***

## Project Requirements

### User requirements
- Change temperature, humidity, light, moisture automatically.(Self-growing system)
- Know when to water, light, change temperature and humidity.(Indicator system)
- Know the plant's condition whenever and wherever.(Data visualisation)

### Design requirements
-
<img width="804" alt="Screenshot 2021-12-15 at 10 13 11" src="https://user-images.githubusercontent.com/67747655/146167707-446823e5-e3b1-4672-a82e-c498102e3686.png">


## Technical Development

This is the process of how this system works:
-
<img width="775" alt="Screenshot 2021-12-15 at 00 15 31" src="https://user-images.githubusercontent.com/67747655/146099650-455e53ae-cf6c-4d19-b8a6-6010bb047ba0.png">

The first step are building physical device (board, sensors and actuators)and test them one by one.
The second step are sending device data to MQTT and connecting to wifi for visualising better.
The third step is triggering related sensor to change the plant environment.
The last step are designing and printing enclosure for the system.

### Step1: Build physical device and test them
-<img width="775" alt="Screenshot 2021-12-15 at 12 00 51" src="https://user-images.githubusercontent.com/67747655/146183334-59bbfdff-f1db-4958-bb54-5130f8830ebb.png">

If you are building a multi-sensor system, do not forget to test them one by one. And I put the test file in the "test" folder. You can use it to check whether your sensor works. Running the code after connecting all the sensors will make it difficult for you to find out where the problem is. So, try not to do this.

#### Test1: Sensing soil moisture
This step is to judge whether the soil moisture sensor can work normally. First, you need to connect the soil moisture sensor into the circuit, and define the soilPin as A0. Then run the soil moisture test file with the arduino. The soil moisture data needs to be calculated as follows. The soil moisture data can then be viewed through the serial monitor. The test is successful when the soil moisture is within the normal range. 
  ```
  wetValue = analogRead(wetPin);
  wetValue *= 100;
  wetValue = wetValue/1023;
  ```
<img width="775" alt="Screenshot 2021-12-02 at 00 26 27" src="https://user-images.githubusercontent.com/67747655/149041259-b72104e7-afa1-41c4-9941-5e250fd93a46.png">

#### Test2: Watering plant automatically

According to David(2021,para. 5.), the suitale range of soil humidity for peace lily is from 30% to 60%. In this step, when the soil humidity is lower than 30%, run the water pump to start watering until the soil humidity reaches 60%. The pump stops running.

First need to connect the water pipe, water pump and water pump driver according to the circuit diagram. The water pump driver contains two motors, which are defined as digital pin8,9 respectively.

Use function(pump_judge) to determine whether the soil needs watering：
```
void pump_judge(){
  if( wetValue > HIGH_TH ){
    closePump();
  }else if( wetValue < LOW_TH ){
    openPump();
  }
}
```
Use function(open pump) and function(close pump) to realize the switch of the pump.
```
void openPump(){
  pump_sta = 1;
  analogWrite(MOTOR_INA1, 150);
  analogWrite(MOTOR_INA2 , 0);
}

void closePump(){
  pump_sta = 0;
  analogWrite(MOTOR_INA1, 0);
  analogWrite(MOTOR_INA2 , 0);
}
```
Now when I put the soil moisture sensor in the water cup (humidity greater than 30%), the pump won't run, when I put it in the air (humidity less than 30%), the pump runs and starts watering automatically, once I put the sensor again Into the water, the watering process stops immediately.（You can see the vedio in test folder）

#### Test3: Sensing temperature and humidity with DHT22 and visualizing with LCD

DHT22 can sense the temperature and humidity in the air. Define it as digital pin 4 according to the circuit diagram. Then connect the LCD to the circuit. Finally, run the test file and the environment data will be displayed in LCD.

<img width="846" alt="Screenshot 2022-01-12 at 01 15 37" src="https://user-images.githubusercontent.com/67747655/149046553-a88c531e-25bc-4ea5-90f9-1b43950d4b94.png">

#### Test4: Sensing illumination

First, you need to connect the illumination sensor into the circuit, and define the illumination Pin as A2. Then run the illumination test file with the arduino.  The illumination value can then be viewed through the serial monitor. The test is successful when the illumination value is within the normal range. 
- <img width="851" alt="Screenshot 2021-12-02 at 00 34 58" src="https://user-images.githubusercontent.com/67747655/149047033-a7069c38-1ab1-42c6-9a8f-4695076b6892.png">

#### Test5: LED indicator

When the environmental data value is not within the normal range, the LED indicator will light up to remind the user to pay attention. First you need to connect the three LED lights according to the circuit diagram, and then run the test file, which defines the temperature range as 20-30°C and the humidity range as 40%-55%. The range of light intensity is 2100-16855 lux, then initialise the LED to digital pin3,5,11.
- <img width="700" alt="Screenshot 2021-12-02 at 14 55 22" src="https://user-images.githubusercontent.com/67747655/149050782-ad8184a0-2477-4f62-9b7c-8b305152758f.png">

#### Test6: Fan test

This step is to test if the fan is working properly. First connect the fan and board according to the circuit diagram. Then run the test file. When the fan starts to rotate, it means that there is no problem with the actuator, and the test is successful.
- <img width="500" alt="Screenshot 2022-01-12 at 02 05 53" src="https://user-images.githubusercontent.com/67747655/149051026-9ad3b580-83e8-45c8-baec-2161aa98e799.png">

#### Test7: Neopixel test
In order not to affect the growth of plants in the case of insufficient natural light, the system has added an automatic lighting function. Because blue and red light are favorable light for plant growth, these two colors were chosen. This is achieved through Neopixel. First, you need to connect neopixel and board according to the circuit diagram, and then run the test file, which calls the Adafruit_NeoPixel library.
```
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, 170, 56, 30);
    pixels.show();
```
- <img width="194" alt="Screenshot 2022-01-12 at 02 07 35" src="https://user-images.githubusercontent.com/67747655/149051154-42182a4e-42cd-4166-b692-3647c0f15cb4.png">

### Step 2 Data Visualisation

I design 3 visualisation methods,different visualisations used for different use cases:
- When I am at CE lab and near to the plant, I will look the LCD to get data information:
- <img width="775" alt="Screenshot 2021-12-13 at 19 22 07" src="https://user-images.githubusercontent.com/67747655/145874765-0968d037-4af6-4011-b3b8-b5b20f88c031.png">
- When I want to know how to actuate  to my plants, I will follow the LED indicator:
- <img width="793" alt="Screenshot 2022-01-12 at 02 14 13" src="https://user-images.githubusercontent.com/67747655/149051740-12312e7a-90e2-4942-8169-a0c3e33bb69d.png">
- When I'm at other places far away from my plant:
- <img width="775" alt="Screenshot 2021-12-13 at 20 43 37" src="https://user-images.githubusercontent.com/67747655/145885823-c7cbb4d8-0934-4f65-9350-281a6346a33d.png">

### Step 3 Integrate all test files
Consolidate all test files into one file
 
#### Mode1:
The final arduino file of the automatic mode of the self-growing garden divides the unused functions in the test file into 5 types and organizes them into categories:
- MQTT SETTING
- Read Sensor Data Function
- Actuation Function
- Trigger Function
- Visualisation Function

Eventually all functions can run simultaneously.

#### Mode2:
When users want to enjoy taking care of their own plants. Code for IR mode can be uploaded to override automatic mode.
First, you need to connect the bluetooth receiver and the board. Define the bluetooth module as digital pin7. Then run the IR-Key file, open the serial monitor, and press different keys on the remote control to see the codes corresponding to different keys. Take note of these codes.
- <img width="725" alt="Screenshot 2021-12-06 at 17 46 16" src="https://user-images.githubusercontent.com/67747655/149053203-30da7617-8db4-45b8-98cd-ce554cd98aca.png">

Then define each kay, and each sensor and actuator. Use the following statement to associate each kay with actuation functions.
<img width="635" alt="Screenshot 2022-01-12 at 02 33 28" src="https://user-images.githubusercontent.com/67747655/149053506-f45d3339-2efb-4bc0-a9f4-f80b685fd09a.png">

### Step 4 Enclosure

To protect the circuit and make it look clear, I used Fusion360 to create an enclousure model(Export in stl format), then open the stl in a slicer and optimise the settings. Finally, I use 3D printer to print the enclosure.
-
<img width="775" alt="Screenshot 2021-12-15 at 00 07 57" src="https://user-images.githubusercontent.com/67747655/146098987-404e0e8f-ec10-40b9-8b32-339e96ee2307.png">
Then I packaged the enclosure with sensors and sctuators.
-
<img width="951" alt="Screenshot 2021-12-15 at 00 10 53" src="https://user-images.githubusercontent.com/67747655/146099183-be778164-4b94-4c8f-b301-27811a784424.png">

Finally, I used my power bank to power the device. And wrote a intruction ducument for people who want to use it.
- <img width="490" alt="Screenshot 2021-12-15 at 11 16 37" src="https://user-images.githubusercontent.com/67747655/146177254-f4ee2ac6-1f4f-409c-a1fc-11823a0884bf.png">

## In the future

- Use eagle to create printed circuit boards (PCBs)  to reduce the size of the device.
- Printer a bigger and more suitable enclosure, because the 3D printer of CE lab can only print models up to 25*25*25 cm model.
***
## Ready to start your plant journey? Make it right now!
***
## References
- Arduino Forum. 2021. Using digital pin 0 and 1 just like any other Digital Pin?. [online] Available at: <https://forum.arduino.cc/t/using-digital-pin-0-and-1-just-like-any-other-digital-pin/462591>; [Accessed 12 December 2021].
- Rhoades, H., 2021. Indoor Peace Lily Plants: Growing A Peace Lily Plant. [online] Gardening Know How. Available at: <https://www.gardeningknowhow.com/houseplants/peace-lily/peace-lily-plants.htm>; [Accessed 12 December 2021].
- Amrita Prasad, 2021. Air plants to jade, cacti, peace lily: Here are the most Instagrammable WFH plants. The times of India (Bombay, India), pp.The times of India (Bombay, India), 2021–02-22.
- Söderby, K., 2021. Sending Data over MQTT. [online] Docs.arduino.cc. Available at: <https://docs.arduino.cc/tutorials/uno-wifi-rev2/uno-wifi-r2-mqtt-device-to-device>; [Accessed 12 December 2021].
- Blum, J., 2020. Exploring Arduino tools and techniques for engineering wizardry / Jeremy Blum 2nd ed., Indianapolis, Ind.: Wiley.
Rhoades, H., 2021. Indoor Peace Lily Plants: Growing A Peace Lily Plant. [online] Gardening Know How. Available at: <https://www.gardeningknowhow.com/houseplants/peace-lily/peace-lily-plants.htm>; [Accessed 12 December 2021].








