/*
 * RS232.cpp
 *
 *  Created on: 21 Apr 2015
 *      Author: Thomas Eiband
 *
 *      thomas.eiband@tum.de
 */

#include "RS232.h"
#include <iostream>

using namespace std;

RS232::RS232(char* deviceName) : deviceName(deviceName)
{
    if (rs232_open())
        exit(EXIT_FAILURE);

    // already done in rs232_open
    // set_interface_attr (B2400, 0);
}

void RS232::debugHEX(char *buf) const
{
    for (int i=0; i < (buf[0]+2); i++) {
        printf("0x%x,", (unsigned char)buf[i]);
    }
}

int RS232::set_interface_attr(int speed, int parity) const
{

    /* Set up the control structure */
     struct termios toptions;

     /* Get currently set options for the tty */
     tcgetattr(fd, &toptions);

    /* Set custom options */

    /* 9600 baud */
     cfsetispeed(&toptions, speed);
     cfsetospeed(&toptions, speed);
     /* 8 bits, no parity, no stop bits */
     toptions.c_cflag &= ~PARENB;
     toptions.c_cflag &= ~CSTOPB;
     toptions.c_cflag &= ~CSIZE;
     toptions.c_cflag |= CS8;
     /* no hardware flow control */
     toptions.c_cflag &= ~CRTSCTS;
     /* enable receiver, ignore status lines */
     toptions.c_cflag |= CREAD | CLOCAL;
     /* disable input/output flow control, disable restart chars */
     toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
     /* disable canonical input, disable echo,
     disable visually erase chars,
     disable terminal-generated signals */
     toptions.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);
     /* disable output processing */
     toptions.c_oflag &= ~OPOST;

     /* no minimum time to wait before read returns */
     toptions.c_cc[VTIME] = 0;

    /* commit the options */
     tcsetattr(fd, TCSANOW, &toptions);

    /* Wait for the Arduino to reset */
     usleep(1000*1000);

     /* Flush anything already in the serial buffer */
     tcflush(fd, TCIOFLUSH);

     // TODO: return 1 if an error occurs
     return 0;
}

int RS232::rs232_open(void)
{
  fd = open (deviceName, O_RDWR | O_NOCTTY);
  if (fd < 0)
  {
    cerr << "ERROR RS232: Error opening serial port " << deviceName << endl;
    return 1;
  }
  else
  {
    cout << "RS232: Open port: " << deviceName << endl;
    if (set_interface_attr(baudrate, 0))
        return 1;
    return 0;
  }

}

int RS232::rs232_close(void) const
{

  if (fd != 0) {
    close(fd);
    cout << "RS232: Connection closed" << endl;
  }
  else
    cerr << "ERROR RS232: Connection could not be closed" << endl;

  return 0;
}

int RS232::rs232_write(const char *msg, int size) const
{
  int n;

  // flush input buffer of serial port after writing.
  // TODO: necessary???
  tcflush(fd,TCIFLUSH);

  n = write (fd, msg, size);
  cout << "DEBUG RS232: " << n << " bytes writen" << endl;



  return n;
}

int RS232::rs232_read(char* buf, unsigned int size, unsigned int time) const
{

    int n = read(fd, buf, size);
    cout << "DEBUG RS232: " << n << " bytes received" << endl;

    // tcflush(fd,TCIFLUSH);

    /*
    u_int16_t n = 0;
    fd_set set;
    int rv;

    struct timeval timeout;
    timeout.tv_usec = time * 1000;

    FD_ZERO(&set);
    FD_SET(fd, &set);

    // Maximum Response Time in u-seconds
    usleep(time*1000);

    rv = select(fd + 1, &set, NULL, NULL, &timeout);

    if(rv == -1)
        cerr << "ERROR RS232: read error" << endl;
    else if(rv == 0)
        cerr << "ERROR RS232: read timeout" << endl;
    else {
        n = read(fd, buf, size);
        // cout << "DEBUG RS232: " << n << " bytes read" << endl;
        // debugHEX(buf);
    }

    if (n <= 0) {
        cerr << "ERROR RS232: no bytes received" << endl;
        exit(EXIT_FAILURE);
    }
    else
        return n;
    */
}

RS232::~RS232()
{
    close(fd);
}
