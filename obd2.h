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

#ifndef INCLUDE_OBD2
#define INCLUDE_OBD2

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <math.h>
 
 
/** Part 1: Functions to access the OBD2 adapter
 *
 */
  
/**
 * Initialize the OBD2 access.
 * Must be called before using any of the other functions.
 * @param obd2_device the name of the device on which the OBD2 adapter is attached
 * @return true on when the OBD2 _dongle_ could be accessed.
 * @note this command does _not_ check the connection to the vehicle OBD bus 
 *   as this may depend on other conditions (such as ignition state) 
 * @note CHECK this may block for a while as bluetooth connection setup can take up to 3.5 sec
 */
bool obd2_init(const char* obd2_device); 

/**
 * Release the OBD2 access.
 * @return true on success.
 */
bool obd2_deinit(); 

/**
 * Read the engine RPM from OBD2
 * @param engine_rpm returns the engine rpm in 1/min
 * @param timestamp returns a system timestamp in ms (milliseconds) derived from clock_gettime(CLOCK_MONOTONIC);
 * @return true on success.
 */
bool obd2_read_engine_rpm(float* engine_rpm, uint64_t* timestamp);

/**
 * Read the vehicle speed from OBD2
 * @param engine_load returns the engine load in %
 * @param timestamp returns a system timestamp in ms (milliseconds) derived from clock_gettime(CLOCK_MONOTONIC);
 * @return true on success.
 */
bool obd2_read_engine_load(float* engine_load, uint64_t* timestamp);

/**
 * Read the vehicle speed from OBD2
 * @param vehicle_speed returns the vehicle speed in km/h
 * @param timestamp returns a system timestamp in ms (milliseconds) derived from clock_gettime(CLOCK_MONOTONIC);
 * @return true on success.
 */
bool obd2_read_vehicle_speed(float* vehicle_speed, uint64_t* timestamp);

/**
 * Read the ambient air temperature from OBD2
 * @param ambient_air_temperature returns the ambient air temperature in °C
 * @param timestamp returns a system timestamp in ms (milliseconds) derived from clock_gettime(CLOCK_MONOTONIC);
 * @return true on success.
 */
bool obd2_read_ambient_air_temperature(float* ambient_air_temperature, uint64_t* timestamp);


/** Part 2: Utility functions and conversion factors
 *
 */

/**
 * Get system timestamp
 * @return returns a system timestamp in ms (milliseconds) derived from clock_gettime(CLOCK_MONOTONIC);
 */
uint64_t obd2_get_timestamp(); 


#ifdef __cplusplus
}
#endif

#endif //INCLUDE_OBD2
