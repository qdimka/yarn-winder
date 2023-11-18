HWCONFIG := spiffs
SPIFF_FILES = clientApp/dist
ARDUINO_LIBRARIES := ArduinoJson6 StepperDriver

COMPONENT_SOC := esp*
ENABLE_SMART_CONFIG = 1

COM_PORT = /dev/ttyUSB0

client-app:
	${Q} cd clientApp; rm -r dist
	$(Q) cd clientApp; npm run build-only

web-upload: web-pack spiffs-image-update
	$(ESPTOOL) -p $(COM_PORT) -b $(COM_SPEED_ESPTOOL) write_flash $(flashimageoptions) $(SPIFF_START_OFFSET) $(SPIFF_BIN_OUT)