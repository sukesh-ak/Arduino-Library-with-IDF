#include <stdio.h>

// Converted code from this Arduino example
// examples/Example13_PVT/Example1_AutoPVT/Example1_AutoPVT.ino

#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

SFE_UBLOX_GNSS myGNSS;
static const char *TAG = "MAIN";

// Enabling C++ compile
extern "C" { void app_main(); }

void app_main(void)
{
    Wire.begin();

    if (myGNSS.begin() == false)
    {
        ESP_LOGE(TAG,"u-blox GNSS not detected at default I2C address. Please check wiring. Freezing.");
        while (1);
    }

    myGNSS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
    myGNSS.setNavigationFrequency(2); //Produce two solutions per second
    myGNSS.setAutoPVT(true); //Tell the GNSS to "send" each solution
    //myGNSS.saveConfiguration(); //Optional: Save the current settings to flash and BBR


    // loop replacement of Arduino
    // But usually in ESP-IDF tasks are used to handle logic
    while(1)
    {
        if (myGNSS.getPVT() && (myGNSS.getInvalidLlh() == false))
        {
            Serial.println();
            long latitude = myGNSS.getLatitude();
            long longitude = myGNSS.getLongitude();

            ESP_LOGE(TAG,"Lat: %ld, Lon: %ld (degrees * 10^-7)", latitude, longitude);
        }
    }
}