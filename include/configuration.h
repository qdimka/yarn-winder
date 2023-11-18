#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SmingCore.h>
#include <Data/Stream/MemoryDataStream.h>
#include <ArduinoJson.h>

const char APP_SETTINGS_FILE[] = "configuration.conf"; // leading point for security reasons :)

struct Configuration {

    long StepsPerRevolution;
    float GearRatio;

    void load()
    {
        DynamicJsonDocument doc(1024);

        if(Json::loadFromFile(doc, APP_SETTINGS_FILE)) {
            JsonObject settings = doc["settings"];

            StepsPerRevolution = settings["stepsPerRevolution"].as<long>();
            GearRatio = settings["gearRatio"].as<float>();
        }
    }

    void save()
    {
        DynamicJsonDocument doc(1024);

        auto settings = doc.createNestedObject("settings");

        settings["stepsPerRevolution"] = StepsPerRevolution;
        settings["gearRatio"] = GearRatio;

        Json::saveToFile(doc, APP_SETTINGS_FILE);
    }

    bool exist()
    {
        return fileExist(APP_SETTINGS_FILE);
    }
};

extern Configuration Settings;

#endif  // CONFIGURATION_H
