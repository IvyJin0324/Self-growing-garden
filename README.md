# Self-growing-garden: Internet of things for planting automatically
- Name: Qian Jin(Ashley)
- Student ID: uncfqji
- Email: unfnqji@ucl.ac.uk
- Date: 13, Dec, 2021
- Professor: Martin
## About

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
<img width="775" alt="Screenshot 2021-12-13 at 18 26 25" src="https://user-images.githubusercontent.com/67747655/145867668-c39490c3-1dc1-4b5a-a3d4-d326b77e4ae8.png">
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
### Step 3 Actuation code

### Step 4 Data Visualisation

I design 3 visualisation methods,different visualisations used for different use cases:
- When I am at CE lab and near to the plant, I will look the LCD to get data information:
<img width="775" alt="Screenshot 2021-12-13 at 19 22 07" src="https://user-images.githubusercontent.com/67747655/145874765-0968d037-4af6-4011-b3b8-b5b20f88c031.png">
- When I want to know how to actuate  to my plants, I will follow the LED indicator:

- When I'm at other places far away from my plant:
-










