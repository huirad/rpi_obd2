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
 * @return true on success.
 */
bool obd2_init(const char* obd2_device); 

/**
 * Release the OBD2 access.
 * @return true on success.
 */
bool obd2_deinit(); 

/**
 * Read the vehicle speed from the OBD2
 * @param vehicle_speed returns the vehicle speed in km/h
 * @param timestamp returns a system timestamp in ms (milliseconds) derived from clock_gettime(CLOCK_MONOTONIC);
 * @return true on success.
 */
bool obd2_read_vehicle_speed(unsigned char* vehicle_speed, uint64_t* timestamp);


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
