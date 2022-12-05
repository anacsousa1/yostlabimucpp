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
	U8 logical_id{0};
	U32 serial_number{301993563};
	TSS_ERROR error = TSS_NO_ERROR;

	float red[3] = { 1.0f, 0.0f, 0.0f };
	float blue[3] = { 0.0f, 0.0f, 1.0f };
	float green[3] = { 0.0f, 1.0f, 1.0f };
	
	printf("====Creating a Three Space Dongle from Search====\n");
	tss_findSensorPorts(TSS_DONGLE);
	error = tss_getNextSensorPort(port.port_name, &port.device_type, &port.connection_type);

	if (error == TSS_NO_ERROR){
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
			error = tss_dongle_setSerialNumberAtLogicalID(dongle_id, logical_id, serial_number, NULL);
			if (error){
				printf("Failed to set serial number at logical ID %d!\n", logical_id);
				tss_deinitAPI();
				printf("Finished press Enter to continue");
				getchar();
				return 0;
			}else{
				error = tss_dongle_getWirelessSensor(dongle_id, logical_id, &device_id);

				if (error){
					printf("Failed to create TSS Sensor on 0!\n");
					tss_deinitAPI();
					printf("Finished press Enter to continue");
					getchar();
					return 0;
				}else{
					printf("==================================================\n");
					printf("Getting the filtered tared quaternion orientation.(xyzw)\n");
					float quat[4];
					U32 timestamp;

					error = tss_sensor_getTaredOrientationAsQuaternion(device_id, quat, &timestamp);
					if (!error)	{
					printf("Quaternion: %f, %f, %f, %f Timestamp=%u\n", quat[0], quat[1], quat[2], quat[3], timestamp);
					}else{
						printf("TSS_Error: %s\n", tss_error_string[error]);
					}

					printf("==================================================\n");
					printf("Getting the Corrected Component Sensor Data.\n");
					float gyro[3];
					float accel[3];
					float compass[3];
					error = tss_sensor_getCorrectedSensorData(device_id, gyro, accel, compass, NULL);
					if (!error){
						printf("Gyro:  %f, %f, %f\n", gyro[0], gyro[1], gyro[2]);
						printf("Accel: %f, %f, %f\n", accel[0], accel[1], accel[2]);
						printf("Comp:  %f, %f, %f\n", compass[0], compass[1], compass[2]);
					}else{
						printf("TSS_Error: %s\n", tss_error_string[error]);
					}

					printf("==================================================\n");
					printf("Getting the LED color  of the device.\n");
					float color[3];
					error = tss_sensor_getLEDColor(device_id, color, NULL);
					if (!error){
						printf("Color: %f, %f, %f\n", color[0], color[1], color[2]);
					}else{
						printf("TSS_Error: %s\n", tss_error_string[error]);
					}

					printf("==================================================\n");
					printf("Getting the battery percent remaining.\n");
					U8 battery_percent;
					error = tss_sensor_getBatteryPercentRemaining(device_id,&battery_percent,NULL);
					if (!error){
						printf("Battery: %d\n", battery_percent);
					}else{
						printf("TSS_Error: %s\n", tss_error_string[error]);
					}					
				}		
			}		

			printf("==================================================\n");
			tss_removeSensor(device_id);
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