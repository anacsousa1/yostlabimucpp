// A basic set LED color example
// This example code is compatible with all 3-Space Sensors connected via USB, serial, or Bluetooth
#include "threespace_api_export.h"
#include <Windows.h>
#include <stdio.h>
// For a full list of commands refer to the 3-Space Manual of your sensor
#define TSS_SET_LED_COLOR 0xee

#pragma comment(lib, "Setupapi.lib")
#pragma comment(lib, "BluetoothAPIs.lib")

int main(){
	TSS_ComPort port;
	port.port_name = new char[64];
	tss_device_id dongle_id;
	tss_device_id device_id;
	TSS_ERROR error = TSS_NO_ERROR;

	float red[3] = { 1.0f, 0.0f, 0.0f };
	float blue[3] = { 0.0f, 0.0f, 1.0f };
	float green[3] = { 0.0f, 1.0f, 1.0f };
	
	printf("====Creating a Three Space Dongle from Search====\n");
	tss_findSensorPorts(TSS_DONGLE);
	error = tss_getNextSensorPort(port.port_name, &port.device_type, &port.connection_type);


	// tss_findSensorPorts(TSS_FIND_ALL_KNOWN ^ TSS_DONGLE);	
	// error = tss_getNextSensorPort(port.port_name, &port.device_type, &port.connection_type);

	if (error == TSS_NO_ERROR){
		// error = tss_createSensor(port.port_name, &device_id);
		error = tss_createDongle(port.port_name, &dongle_id);


		if (error){
			printf("Failed to create TSS Dongle on %s!\n", port.port_name);
			tss_deinitAPI();
			printf("Finished press Enter to continue");
			getchar();
			return 0;
		}else{
			printf("==================================================\n");
			printf("Created a TSS Dongle on %s!\n", port.port_name);

			//Connect sensor
				//stuff

				//Change color
					// printf("Setting the LED color of the device to RED.\n");			
					// error = tss_sensor_setLEDColor(device_id, red, NULL);
					// if (!error)	{
					// 	printf("\tLED should be be RED\n");
					// }else{
					// 	printf("\tTSS_Error: %s\n", tss_error_string[error]);
					// }
					// printf("Press enter to change LED color to Green.\n");
					// getchar();

					// printf("==================================================\n");
					// printf("Setting the LED color of the device to GREEN.\n");

					// error = tss_sensor_setLEDColor(device_id, green, NULL);
					// if (!error)	{
					// 	printf("\tLED should be be GREEN\n");
					// }else{
					// 	printf("\tTSS_Error: %s\n", tss_error_string[error]);
					// }
					// printf("Press enter to change LED color to Blue.\n");
					// getchar();
					
					// printf("==================================================\n");
					// printf("Setting the LED color of the device to BLUE.\n");

					// error = tss_sensor_setLEDColor(device_id, blue, NULL);
					// if (!error)	{
					// 	printf("\tLED should be be BLUE\n");
					// }else{
					// 	printf("\tTSS_Error: %s\n", tss_error_string[error]);
					// }

				// printf("==================================================\n");
				// tss_removeSensor(device_id);

			tss_removeDongle(dongle_id);
		}
	}else{
		printf("Failed to get the port!\n");
		tss_deinitAPI();
		printf("Finished press Enter to continue\n");
		getchar();
		return 0;
	}

	tss_deinitAPI();

	printf("Finished press Enter to continue");
	getchar();
	return 0;
}