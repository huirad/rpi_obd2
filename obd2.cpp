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
 * INTERNAL DEFINES
 * 
 * 
 */

#define OBD_SID_01 0x01
TODO finde nicer name

#define OBD_PID_LOAD_PCT 0x04
#define OBD_PID_RPM 0x0C
#define OBD_PID_VSS 0x0D
#define OBD_PID_MAF 0x10
#define OBD_PID_RUNTIM 0x1F
#define OBD_PID_AAT 0x46



/**
 * INTERNAL FUNCTIONS
 * 
 * 
 */


/**
 * Open OBD2 ELM327 device for with given baud rate
 * @ref http://tldp.org/HOWTO/Serial-Programming-HOWTO/x115.html
 * @param gps_device [IN] device, e.g. "/dev/rfcomm0"
 * @param baudrate [IN] baud rate (see definitions in <asm/termbits.h>) 
 * @note for bluetooth SPP connections the baudrate is normally ignored
 * @return file descriptor of OBD2 device
 */
static int obd2_open_device(const char* obd2_device, unsigned int baudrate)
{
  int fd,c, res;
  struct termios oldtio,newtio;

/* 
  Open modem device for reading and writing and not as controlling tty
  because we don't want to get killed if linenoise sends CTRL-C.
*/
    fd = open(obd2_device, O_RDWR | O_NOCTTY ); 
    if (fd <0) 
    {
        return fd; 
    }

    tcgetattr(fd,&oldtio); /* save current serial port settings */
    bzero(&newtio, sizeof(newtio)); /* clear struct for new port settings */

/* 
  BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
  CRTSCTS : output hardware flow control (only used if the cable has
            all necessary lines. See sect. 7 of Serial-HOWTO)
  CS8     : 8n1 (8bit,no parity,1 stopbit)
  CLOCAL  : local connection, no modem contol
  CREAD   : enable receiving characters
*/
    newtio.c_cflag = GNSS_BAUDRATE | CS8 | CLOCAL | CREAD;
 
/*
  IGNPAR  : ignore bytes with parity errors
  ICRNL   : map CR to NL (otherwise a CR input on the other computer
            will not terminate input)
  otherwise make device raw (no other input processing)
*/
    newtio.c_iflag = IGNPAR;
 
/*
 Raw output.
*/
    newtio.c_oflag = 0;
 
/*
  ICANON  : enable canonical input
  disable all echo functionality, and don't send signals to calling program
*/
    newtio.c_lflag = ICANON; TODO CHECK DISABLE
 
/* 
  initialize all control characters 
  default values can be found in /usr/include/termios.h, and are given
  in the comments, but we don't need them here
*/
    newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */ 
    newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
    newtio.c_cc[VERASE]   = 0;     /* del */
    newtio.c_cc[VKILL]    = 0;     /* @ */
    newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
    newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
    newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
    newtio.c_cc[VSWTC]    = 0;     /* '\0' */
    newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */ 
    newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
    newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
    newtio.c_cc[VEOL]     = 0;     /* '\0' */
    newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
    newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
    newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
    newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
    newtio.c_cc[VEOL2]    = 0;     /* '\0' */

/* 
  now clean the modem line and activate the settings for the port
*/
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);

/* 
  Done
*/
    return fd;
}




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
 
static pthread_t g_obd2_thread;
static int g_obd2_fd = -1;


bool obd2_init(const char* obd2_device, unsigned int baudrate)
{
  //only open the device with appropriate settings (?canonical?)
  //but try to check ATZ response (provide back device ID/version)?
  //better not canonical ==> check for ">" prompt ????
  //Take care: bluetooth connection setup may take long!
  //??!! raw mode http://stackoverflow.com/questions/15028953/sending-binary-data-over-bluetooth-rfcomm-spp-converts-0x0a-to-0x0d-0x0a
  
  bool retval = true;
  
  g_obd2_fd = obd2_open_device(obd2_device, baudrate);
  if (g_obd2_fd >= 0)
  {
    TODO ATZ
  }
  else
  {
    retval = false;
  }

  return retval;
}

bool obd2_deinit()
{
  //only close device
}

bool obd2_read_engine_load(float* engine_load, uint64_t* timestamp)
{
  // `0104` Engine load: returns 1 byte (A): LOAD_PCT[%] = A*100/255

}


bool obd2_read_engine_rpm(float* engine_rpm, uint64_t* timestamp)
{
  //`010C` Engine RPM: returns 2 bytes (A,B): RPM [1/min] = ((A*256)+B)/4
  
}


bool obd2_read_vehicle_speed(float* vehicle_speed, uint64_t* timestamp)
{
  //`010D` Vehicle Speed: returns 1 byte (A): VSS [km/h] = A
}

bool obd2_read_ambient_air_temperature(float* ambient_air_temperature, uint64_t* timestamp)
{
  // `0146` Ambient air temperature: returns 1 byte (A): AAT[°C] =  A-40

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


#ifdef OBD2_TEST
int main()
{
  bool result;
  float value;
  uint64_t timestamp, start, stop;
  
  start = obd2_get_timestamp();  
  result = obd2_init("/dev/rfcomm0", B38400);
  if (result)
  {
    printf("INIT OK [DURATION = %d ms]\n", stop-start);
  }
  else
  {
    printf("INIT FAILURE [DURATION = %d ms]\n", stop-start);
    return();
  }

  start = obd2_get_timestamp();
  result = obd2_read_engine_rpm(&value, &timestamp);
  stop = obd2_get_timestamp();
  if (result)
  {
    printf("RPM=%f [DURATION = %d ms]\n", value, stop-start);
  }
  else
  {
    printf("RPM read failure\n");
  }

  start = obd2_get_timestamp();
  result = obd2_read_vehicle_speed(&value, &timestamp);
  stop = obd2_get_timestamp();
  if (result)
  {
    printf("VSS=%f [DURATION = %d ms]\n", value, stop-start);
  }
  else
  {
    printf("VSS read  failure\n");
  }

  start = obd2_get_timestamp();
  result = obd2_read_ambient_air_temperature(&value, &timestamp);
  stop = obd2_get_timestamp();
  if (result)
  {
    printf("AAT=%f [DURATION = %d ms]\n", value, stop-start);
  }
  else
  {
    printf("AAT read failure\n");
  }
  
  start = obd2_get_timestamp();  
  result = obd2_deinit();
  stop = obd2_get_timestamp();
  if (result)
  {
    printf("DEINIT OK [DURATION = %d ms]\n", stop-start);
  }
  else
  {
    printf("DEINIT FAILURE [DURATION = %d ms]\n", stop-start);
  }  
  
}
#endif //#ifdef OBD2_TEST