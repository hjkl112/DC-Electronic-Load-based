#ifndef __MCP4725_H__
#define __MCP4725_H__

#include "stdint.h"

#define MCP4725_ADDR					 0x60
void MCP4725_WriteData_Volatge(uint16_t Vout);

#endif
