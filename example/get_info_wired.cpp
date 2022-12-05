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
	tss_device_id device_id;
	TSS_ERROR error = TSS_NO_ERROR;
	
	// Create sensor
	printf("====Creating a Three Space Device from Search====\n");
	tss_findSensorPorts(TSS_FIND_ALL_KNOWN ^ TSS_DONGLE);
	
	error = tss_getNextSensorPort(port.port_name, &port.device_type, &port.connection_type);

	if (error == TSS_NO_ERROR){
		error = tss_createSensor(port.port_name, &device_id);

		if (error){
			printf("Failed to create TSS Sensor on %s!\n", port.port_name);
			tss_deinitAPI();
			printf("Finished press Enter to continue");
			getchar();
			return 0;
		}else{
			printf("==================================================\n");
			printf("Created a TSS Sensor on %s!\n", port.port_name);
            printf("====Starting Streaming====\n");

            error = tss_sensor_startStreamingWired(device_id, TSS_STREAM_TARED_ORIENTATION_AS_QUATERNION, 1000, TSS_STREAM_DURATION_INFINITE, 0);

			TSS_Stream_Packet packet;
            for (int i = 0; i < 10; i++){
				printf("Press Enter to get next packet.\n");
				getchar();
				error = tss_sensor_getLastStreamingPacket(device_id, &packet);
				printf("Quaternion: (%.03f,%.03f,%.03f,%.03f)\n", packet.taredOrientQuat[0], packet.taredOrientQuat[1], packet.taredOrientQuat[2], packet.taredOrientQuat[3]);
			}

			tss_sensor_stopStreamingWired(device_id);			

			printf("==================================================\n");
			tss_removeSensor(device_id);
		}
	}else{ // Connection fails
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