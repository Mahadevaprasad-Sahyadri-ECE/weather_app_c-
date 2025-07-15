#include <iostream>
#include <string>
#include <curl/curl.h>    // libcurl
#include "json.hpp"       // nlohmann JSON (json.hpp must be in the same folder)

using namespace std;
using json = nlohmann::json;

// Callback function for curl to write response data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    string city = "mangalore";   // Change the city name here if you want
    string apiKey = "0a3e627ff4d5d76e31ab3c9e245c6649";   // Use your OpenWeather API key
    string url = "https://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey;

    cout << "Requesting URL: " << url << endl;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl) {
        cerr << "Failed to initialize curl" << endl;
        curl_global_cleanup();
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    // ✅ Disable SSL certificate verification for testing purpose
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 1;
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    cout << "Raw response: " << readBuffer << endl;

    try {
        auto j = json::parse(readBuffer);

        if (j.contains("cod") && j["cod"] != 200) {
            cerr << "API Error: " << j["message"] << endl;
            return 1;
        }

        cout << "======================" << endl;
        cout << "City: " << j["name"] << endl;
        cout << "Temperature: " << j["main"]["temp"] << " K" << endl;
        cout << "Weather: " << j["weather"][0]["description"] << endl;
        cout << "======================" << endl;

    } catch (const json::parse_error& e) {
        cerr << "JSON parse error: " << e.what() << endl;
        return 1;
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}
