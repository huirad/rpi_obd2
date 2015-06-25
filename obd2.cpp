/**************************************************************************
 * @brief Access library for OBD2 data
 *
 * @details Encapsulate OBD2 access for a minimum set of PIDs
 * An OBD2 adapter with ELM327 compatible command set is assumed
 * @see http://elmelectronics.com/DSheets/ELM327DS.pdf
 * An extensive list of OBD2 PIDs is given in
 * @see https://en.wikipedia.org/wiki/OBD-II_PIDs
 *
 *
 * @copyright Copyright (C) 2015, Helmut Schmidt
 * 
 * @license MPL-2.0 <http://spdx.org/licenses/MPL-2.0>
 *
 **************************************************************************/

//provided interface
#include <obd.h>
//standard c library functions
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <math.h>


/**
 * INTERNAL FUNCTIONS
 * 
 * 
 */


static bool obd2_send_command(const char* cmd)
{
}


static bool obd2_decode_response(const char* cmd)
{
  //make minimum assumptions!
  //check for SID/PID
}

static bool obd2_request_pid(const unsigned char sid, const unsigned char sid)
{
}

static bool obd2_receive_pid(const unsigned char sid, const unsigned char sid)
{
}



/**
 * EXTERNAL FUNCTIONS provided by this module
 * @ref obd2.h
 * 
 * 
 */
 
bool obd2_init(const char* obd2_device)
{
  //only open the device with appropriate settings (?canonical?)
  //but try to check ATZ response (provide back device ID/version)?
  //better not canonical ==> check for ">" prompt ????
  //Take care: bluetooth connection setup may take long!
}

bool obd2_deinit()
{
  //only close device
}

bool obd2_read_engine_rpm(float* engine_rpm, uint64_t* timestamp)
{
}

bool obd2_read_engine_load(float* engine_load, uint64_t* timestamp)
{
}

bool obd2_read_vehicle_speed(float* vehicle_speed, uint64_t* timestamp)
{
}

bool obd2_read_ambient_air_temperature(float* ambient_air_temperature, uint64_t* timestamp)
{
}


uint64_t obd2_get_timestamp()
{
  struct timespec time_value;
  if (clock_gettime(CLOCK_MONOTONIC, &time_value) != -1)
  {
    return (time_value.tv_sec*1000 + time_value.tv_nsec/1000000);
  }
  else
  {
    return 0xFFFFFFFFFFFFFFFF;
  }
}


