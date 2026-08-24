#ifndef _AT_COMMAND_SCANNER_H
#define _AT_COMMAND_SCANNER_H

#include <Arduino.h>

void initATCommandScanner(Stream& serialPort);
void pollATCommandScanner();

#endif // _AT_COMMAND_SCANNER_H
