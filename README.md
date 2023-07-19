# Weather-Based-Irrigation-System


# Overview
The Smart Irrigation System with ESP32 and OpenWeatherAPI is an intelligent and efficient solution to optimize water usage in agricultural and gardening applications. By harnessing the power of the ESP32 microcontroller and utilizing real-time weather data from the OpenWeatherAPI, this system ensures that plants receive the right amount of water based on their actual environmental requirements.

# Features
* **Weather-based Irrigation**: The system fetches weather data from the OpenWeatherAPI for the current location, including temperature, humidity, and precipitation forecasts.

* **Intelligent Watering**: Using the retrieved weather data, the ESP32 calculates and adjusts the irrigation schedule to match the current weather conditions, preventing overwatering and water wastage.

* **Customizable Thresholds**: Users can set personalized watering thresholds for different weather conditions and plant types.

* **Real-time Monitoring**: The system provides real-time monitoring and status updates on soil moisture levels, weather conditions, and watering events through a user-friendly interface, provided by ThingSpeak.

# Components-Used
* ESP32 Microcontroller
* Soil Moisture Sensors
* Water Pump
* Relay Module
* Breadboard
* 9v Battery
* Wires

# How-It-Works
* The ESP32 connects to the OpenWeatherAPI and fetches weather data for the current location.

* The system reads soil moisture levels using soil moisture sensors placed in the irrigation area.

* Based on the received weather data and predefined watering thresholds, the ESP32 calculates the irrigation duration.

* The system activates the irrigation mechanism, ensuring that plants receive the appropriate amount of water based on the current weather conditions.

* Users can monitor the irrigation system through a web or mobile interface, with the help of Thingspeak cloud.
