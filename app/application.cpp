#include <SmingCore.h>

#include <configuration.h>
#include <webserver.h>

void onGotIP(IpAddress ip, IpAddress netmask, IpAddress gateway)
{
	startServer();
}

void onReady()
{
	WifiEvents.onStationGotIP(onGotIP);

	WifiAccessPoint.enable(false);
	WifiStation.enable(true);
	WifiStation.config("LETAI_QD2.4G", "qsc147wdv");
	WifiStation.connect();
}

void init()
{
	spiffs_mount();					// Mount file system, in order to work with files

    Settings.load();
    System.onReady(onReady);

	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(true); // Debug output to serial
}