# Self-growing-garden: Internet of things for planting automatically
- Name: Qian Jin(Ashley)
- Student ID: uncfqji
- Email: unfnqji@ucl.ac.uk
- Date: 13, Dec, 2021
- Professor: Martin
## About
This IOT garden has two mode:
If you are too busy to take care your plant, choose the self-growing mode:

If you want to enjoy the pleasure of plating and get proffessional advise, chose the Infrered control mode:

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
<img width="775" alt="Screenshot 2021-12-13 at 18 22 57" src="https://user-images.githubusercontent.com/67747655/145867227-fc0be8b0-9504-4950-b35e-bf7f044295dd.png">


## Technical Development

This is the process of how to make this system:
-
<img width="451" alt="Screenshot 2021-12-15 at 00 15 31" src="https://user-images.githubusercontent.com/67747655/146099650-455e53ae-cf6c-4d19-b8a6-6010bb047ba0.png">
-
The first step are building physical device and gathering environment sensor.
The second step is determining whether the data is within the reasonable range.
The third step is triggering related sensor to change the plant environment.
The last step is visualising data.

### Step1: Build physical device and test them
-
<img width="775" alt="Screenshot 2021-12-13 at 18 31 44" src="https://user-images.githubusercontent.com/67747655/145868346-128783f1-b078-4a90-aa53-0765fae97895.png">
If you are building a multi-sensor system, do not forget to test them one by one. And I put the test file in the "test" folder. You can use it to check whether your sensor works. Running the code after connecting all the sensors will make it difficult for you to find out where the problem is. So, try not to do this.

### Step2: Trigger to actuation

This code is conditionally starting the actuation functions:
```
// Soil moisture Trigger
void pump_Trigger(){
  if( wetValue > 60 ){
    closePump();
  }else if( wetValue < 30 ){
    openPump();
  }
}

// Temperature Trigger
void temperature_Trigger(){
  if( temp < 20 ){
    openheater();
  }else if (temp >30){
    opencooler();
    }else{
      closetemp();
  }
}

// Humidity Trigger
void humidity_Trigger(){
  if( hum > 55 ){
    closeFAN();
  }else if (hum < 40){
    openFAN();
  }
}

// Light Trigger
void light_Trigger(){
  if( lightValue < 2100 ){
    openlight();
  }else if (lightValue > 16865){
    closelight();
  }
}
```
### Step 3 Actuation
- Open/close air-conditioner to change temperature
- Open/close fan to change humidity
- Open/close light matrix to increase illumination
- Open/close pump to water plant


### Step 4 Data Visualisation

I design 3 visualisation methods,different visualisations used for different use cases:
- When I am at CE lab and near to the plant, I will look the LCD to get data information:
<img width="775" alt="Screenshot 2021-12-13 at 19 22 07" src="https://user-images.githubusercontent.com/67747655/145874765-0968d037-4af6-4011-b3b8-b5b20f88c031.png">
- When I want to know how to actuate  to my plants, I will follow the LED indicator:

- When I'm at other places far away from my plant:
-
<img width="775" alt="Screenshot 2021-12-13 at 20 43 37" src="https://user-images.githubusercontent.com/67747655/145885823-c7cbb4d8-0934-4f65-9350-281a6346a33d.png">


### Step 5 Enclosure
To protect the circuit and make it look clear, I used Fusion360 to create an enclousure model(Export in stl format), then open the stl in a slicer and optimise the settings. Finally, I use 3D printer to print the enclosure.
-
<img width="775" alt="Screenshot 2021-12-15 at 00 07 57" src="https://user-images.githubusercontent.com/67747655/146098987-404e0e8f-ec10-40b9-8b32-339e96ee2307.png">
Then I packaged the enclosure with sensors and sctuators.
-
<img width="951" alt="Screenshot 2021-12-15 at 00 10 53" src="https://user-images.githubusercontent.com/67747655/146099183-be778164-4b94-4c8f-b301-27811a784424.png">

## In the future

- Use eagle to create printed circuit boards (PCBs)  to reduce the size of the device.
- Printer a bigger and more suitable enclosure, because the 3D printer of CE lab can only print models up to 25*25*25 cm model.

## References
Arduino Forum. 2021. Using digital pin 0 and 1 just like any other Digital Pin?. [online] Available at: <https://forum.arduino.cc/t/using-digital-pin-0-and-1-just-like-any-other-digital-pin/462591>; [Accessed 12 December 2021].
Rhoades, H., 2021. Indoor Peace Lily Plants: Growing A Peace Lily Plant. [online] Gardening Know How. Available at: <https://www.gardeningknowhow.com/houseplants/peace-lily/peace-lily-plants.htm>; [Accessed 12 December 2021].
Amrita Prasad, 2021. Air plants to jade, cacti, peace lily: Here are the most Instagrammable WFH plants. The times of India (Bombay, India), pp.The times of India (Bombay, India), 2021–02-22.
Söderby, K., 2021. Sending Data over MQTT. [online] Docs.arduino.cc. Available at: <https://docs.arduino.cc/tutorials/uno-wifi-rev2/uno-wifi-r2-mqtt-device-to-device>; [Accessed 12 December 2021].
Blum, J., 2020. Exploring Arduino tools and techniques for engineering wizardry / Jeremy Blum 2nd ed., Indianapolis, Ind.: Wiley.
Rhoades, H., 2021. Indoor Peace Lily Plants: Growing A Peace Lily Plant. [online] Gardening Know How. Available at: <https://www.gardeningknowhow.com/houseplants/peace-lily/peace-lily-plants.htm>; [Accessed 12 December 2021].








