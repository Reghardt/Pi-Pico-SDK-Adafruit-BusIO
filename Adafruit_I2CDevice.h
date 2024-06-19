#pragma once
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

///< The class which defines how we will talk to this device over I2C
class Adafruit_I2CDevice
{
public:
  Adafruit_I2CDevice(i2c_inst_t *i2cBus, uint8_t addr);

  uint8_t getAddress();

  bool read(uint8_t *buffer, size_t len, bool stop = true);
  bool write(const uint8_t *buffer, size_t len, bool stop = true,
             const uint8_t *prefix_buffer = nullptr, size_t prefix_len = 0);

  /*!   @brief  How many bytes we can read in a transaction
   *    @return The size of the Wire receive/transmit buffer */
  size_t getMaxBufferSize() { return priv_maxBufferSize; }

private:
  i2c_inst_t *priv_i2cBus;
  uint8_t priv_address;
  size_t priv_maxBufferSize;
  bool priv_read(uint8_t *buffer, size_t len, bool stop);
};
