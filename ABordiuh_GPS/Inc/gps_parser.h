/**
 ******************************************************************************
 *  FILE          : gps_parser.h
 *  PROJECT       : PROG 8125 - Assignment #4
 *  PROGRAMMER    : Artem Bordiuh
 *  FIRST VERSION : 2017-04-04
 *  DESCRIPTION   : Header file for functions prototypes which works with string
 *  				and functions for process of GGA NMEA data
 ******************************************************************************/

#ifndef GPS_PARSER_H_
#define GPS_PARSER_H_

/* Includes */
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "stm32l4xx_hal.h"

/* Fix quality data enum:
    0 = invalid
    1 = GPS fix (SPS)
    2 = DGPS fix
    3 = PPS fix
    4 = Real Time Kinematic
    5 = Float RTK
    6 = estimated (dead reckoning) (2.3 feature)
    7 = Manual input mode
    8 = Simulation mode
*/
enum fixQualityE {
    invalid = 0, gps_fix, dgps_fix, pps_fix, real_time_kinematic,
    float_rtk, estimated, manual_input_mode, simulation_mode
};

/*Structure and type for storing GGA NMEA parsed message (location info)*/
typedef struct gpgga_message{
    //time int array with 0-hours 1-min 2-sec
    int8_t utc_time[3];
    float latitude;
    int8_t lat_deg;
    int8_t lat_min;
    int8_t lat_sec;
    char lat_direction;
    float longitude;
    int8_t lon_deg;
    int8_t lon_min;
    int8_t lon_sec;
    char lon_direction;
    int8_t fix_quality;
    int8_t num_sattelites;
    float h_duration;
    float altitude;
    char altitude_unit;
    float height_of_geoid;
    char hog_unit;
    long checksum;
} GPGGA_Message;

/**
 * @brief  Retrieving specific part of the string
 * @param  Pointer to input string
 * @param  Start position of the required part of the string
 * @param  Length of the required part of the string
 * @retval Constant pointer to a resulting string
 */
const char* subString(const char* in_str, int8_t offset, int8_t len);

/**
 * @brief  Truncate the income string by delimeter
 * @param  Input array of chars (array of chars as a string required by strtok)
 * @param  Output array of strings
 * @param  char Delimeter
 * @retval Number of elements in result array
 */
int32_t truncateStr(char instr[], char *outstr[], const char delimeter);

/**
 * @brief  Parsing truncated array as a GGA NMEA message to a struct
 * @param  Input array of chars (array of chars as a string required by strtok)
 * @param  Number of rows in input array of truncated array
 * @retval Struct with parsed GGA NMEA message
 */
GPGGA_Message parseGPGGA(char* inStrMessage[], int32_t numb_of_raws);

/**
 * @brief  Printing GGA NMEA message back to UART
 * @param  Structure with parsed GGA NMEA data
 * @retval None
 */
void uart_print_gpgga_message(const GPGGA_Message *gpgga_data);

#endif /* GPS_PARSER_H_ */
