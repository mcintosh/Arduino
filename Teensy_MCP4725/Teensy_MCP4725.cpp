/**************************************************************************/
/*! 
    @file     Teensy_MCP4725.cpp original Adafruit_MCP4725.cpp
    @author   K.Townsend (Adafruit Industries)
	@license  BSD (see license.txt)
	
	I2C Driver for Microchip's MCP4725 I2C DAC

	This is a library for the Adafruit MCP4725 breakout
	----> http://www.adafruit.com/products/935
		
	Adafruit invests time and resources providing this open source code, 
	please support Adafruit and open-source hardware by purchasing 
	products from Adafruit!

	@section  HISTORY

    v1.0 - First release
    v1.0  - First release
    Modified by J.A. Korten March 25th 2014 for Teensy 3.1
    johan.a.korten [ at ] gmail com
*/
/**************************************************************************/
#include <i2c_t3.h>
#ifdef I2C_DEBUG
    #include <rbuf.h> // linker fix
#endif

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "Teensy_MCP4725.h"

/**************************************************************************/
/*! 
    @brief  Instantiates a new MCP4725 class
*/
/**************************************************************************/
Teensy_MCP4725::Teensy_MCP4725() {
}

/**************************************************************************/
/*! 
    @brief  Setups the HW
*/
/**************************************************************************/
void Teensy_MCP4725::begin(uint8_t addr) {
  _i2caddr = addr;
  // Wire.begin(); 
  Wire.begin(I2C_MASTER, addr, I2C_PINS_18_19, I2C_PULLUP_INT, I2C_RATE_400);

}
 
/**************************************************************************/
/*! 
    @brief  Sets the output voltage to a fraction of source vref.  (Value
            can be 0..4095)

    @param[in]  output
                The 12-bit value representing the relationship between
                the DAC's input voltage and its output voltage.
    @param[in]  writeEEPROM
                If this value is true, 'output' will also be written
                to the MCP4725's internal non-volatile memory, meaning
                that the DAC will retain the current voltage output
                after power-down or reset.
*/
/**************************************************************************/
void Teensy_MCP4725::setVoltage( uint16_t output, bool writeEEPROM )
{
  //uint8_t twbrback = TWBR;
  //TWBR = ((F_CPU / 400000L) - 16) / 2; // Set I2C frequency to 400kHz
  Wire.beginTransmission(_i2caddr);
  if (writeEEPROM)
  {
    Wire.write(MCP4726_CMD_WRITEDACEEPROM);
  }
  else
  {
    Wire.write(MCP4726_CMD_WRITEDAC);
  }
  Wire.write(output / 16);                   // Upper data bits          (D11.D10.D9.D8.D7.D6.D5.D4)
  Wire.write((output % 16) << 4);            // Lower data bits          (D3.D2.D1.D0.x.x.x.x)
  Wire.endTransmission();
  //TWBR = twbrback;
}
