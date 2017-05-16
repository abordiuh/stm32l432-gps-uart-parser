/**
 ******************************************************************************
 *  FILE          : gps_parser.c
 *  PROJECT       : PROG 8125 - Assignment #4
 *  PROGRAMMER    : Artem Bordiuh
 *  FIRST VERSION : 2017-04-04
 *  DESCRIPTION   : Source file for functions prototypes which works with string
 *  				and functions for process of GGA NMEA data
 ******************************************************************************/

/*Including header*/
#include "gps_parser.h"

/**
 * @brief  Retrieving specific part of the string
 * @param  Pointer to input string
 * @param  Start position of the required part of the string
 * @param  Length of the required part of the string
 * @retval Constant pointer to a resulting string
 */
const char* subString(const char* in_str, int8_t offset, int8_t len) {
    int8_t instr_length = strlen(in_str);
    if (offset + len > instr_length) {
        return NULL;
    }
    char *outstr = malloc((sizeof(in_str)+1));
    strncpy(outstr, in_str + offset, len);
    strcat(outstr, "\0");
    return outstr;
}

/**
 * @brief  Truncate the income string by delimeter
 * @param  Input array of chars (array of chars as a string required by strtok)
 * @param  Output array of strings
 * @param  char Delimeter
 * @retval Number of elements in result array
 */
int32_t truncateStr(char instr[], char *outstr[], const char delimeter) {
    char *tempBuff;
    int32_t numberOfRawsOutArray = 0;
    tempBuff = strtok(instr, &delimeter);
    while (tempBuff != NULL) {
        strcpy(outstr[numberOfRawsOutArray], tempBuff);//(outstr[numberOfRawsOutArray], tempBuff);
        strcat(outstr[numberOfRawsOutArray], "\0");
        numberOfRawsOutArray++;
        tempBuff = strtok(NULL, &delimeter);
    }
    return numberOfRawsOutArray;
}

/**
 * @brief  Parsing truncated array as a GGA NMEA message to a struct
 * @param  Input array of chars (array of chars as a string required by strtok)
 * @param  Number of rows in input array of truncated array
 * @retval Struct with parsed GGA NMEA message
 */
GPGGA_Message parseGPGGA(char* inStrMessage[], int32_t numb_of_raws){
	GPGGA_Message gpggam_data;
    gpggam_data.utc_time[0] = atoi(subString(inStrMessage[1],0,2));
    gpggam_data.utc_time[1] = atoi(subString(inStrMessage[1],2,2));
    gpggam_data.utc_time[2] = atoi(subString(inStrMessage[1],4,2));

    gpggam_data.latitude = atof(subString(inStrMessage[2],0,8));
    gpggam_data.lat_direction = *subString(inStrMessage[3],0,1);
    gpggam_data.longitude = atof(subString(inStrMessage[4],0,8));
    gpggam_data.lon_direction = *subString(inStrMessage[5],0,1);
    gpggam_data.fix_quality = atoi(subString(inStrMessage[6],0,1));
    gpggam_data.num_sattelites = atoi(subString(inStrMessage[7],0,2));
    gpggam_data.h_duration = atof(subString(inStrMessage[8],0,3));
    gpggam_data.altitude = atof(subString(inStrMessage[9],0,5));
    gpggam_data.altitude_unit = *subString(inStrMessage[10],0,1);
    gpggam_data.height_of_geoid = atof(subString(inStrMessage[11],0,4));
    gpggam_data.hog_unit = *subString(inStrMessage[12],0,1);
    gpggam_data.checksum = strtoul(subString(inStrMessage[13],1,2), NULL, 16);
    return gpggam_data;
}

/**
 * @brief  Printing GGA NMEA message back to UART
 * @param  Structure with parsed GGA NMEA data
 * @retval None
 */
void uart_print_gpgga_message(const GPGGA_Message *gpgga_data){
	printf("\r\nTime: %d:%d:%d UTC\r\n",gpgga_data->utc_time[0],gpgga_data->utc_time[1],gpgga_data->utc_time[2]);
	printf("Latitude: %.3f", 1234.1234);
    printf(" %c \r\n", gpgga_data->lat_direction);
    printf("Longitude: %f ", gpgga_data->longitude);
    printf(" %c \r\n", gpgga_data->lon_direction);
    printf("Fix quality: %d \r\n", gpgga_data->fix_quality);
    printf("Number of satellites: %d \r\n", gpgga_data->num_sattelites);
    printf("Horizontal dilution: %f \r\n", gpgga_data->h_duration);
    printf("Altitude: %f", gpgga_data->altitude);
    printf(" %c \r\n", gpgga_data->altitude_unit);
    printf("Height of geoid: %f", gpgga_data->height_of_geoid);
    printf(" %c \r\n", gpgga_data->hog_unit);
    printf("Checksum: %lu ~\r\n", gpgga_data->checksum);
}
