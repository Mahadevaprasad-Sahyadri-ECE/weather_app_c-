# weather_app_c-

# 🌦️ C++ Weather Forecasting App

A simple command-line weather application built with **C++**, using **libcurl** for HTTP requests and **nlohmann/json** for parsing JSON responses. It fetches live weather data from the **OpenWeatherMap API** and displays it in the terminal.

---

## 🚀 Features

* Fetch real-time weather for a city
* Uses **libcurl** for API requests
* Parses JSON using **nlohmann/json**
* Displays city name, temperature, and weather description
* Includes basic error handling and debug logs

---

## 🛠️ Technologies

* **C++ (MinGW)**
* **libcurl** (HTTP/S communication)
* **nlohmann/json** (Header-only JSON parser)
* **OpenWeatherMap API**

---

## 🖥️ How to Compile & Run

1️⃣ Place `weather.cpp` and `json.hpp` in the same folder
2️⃣ Ensure `libcurl.dll` is placed in the same folder after compilation

**Compile (Windows Command Prompt):**

```bash
g++ weather.cpp -o weather -I"D:/app/curl32/include" -L"D:/app/curl32/lib" -lcurl -lws2_32 -lwinmm -lz
```

**Run:**

```bash
weather.exe
```

---

## 📊 Sample Output

```
Requesting URL: https://api.openweathermap.org/data/2.5/weather?q=mangalore&appid=YOUR_API_KEY
Raw response: { ... }
======================
City: "Mangalore"
Temperature: 296.98 K
Weather: "overcast clouds"
======================
Press Enter to exit...
```

---

## ⚠️ Notes

* SSL certificate check is disabled in this project (for learning/testing)
* Replace `"YOUR_API_KEY"` with your valid OpenWeather API key
* libcurl must be correctly linked during compilation

---

## ✨ Future Enhancements

* Add user input for city names
* Convert temperature from Kelvin to Celsius/Fahrenheit
* Enable SSL certificate verification with CA bundle
* Create GUI-based version using Qt

---

## 👨‍💻 Author

**Mahadeva Prasad** — Learning API integration with C++

---
