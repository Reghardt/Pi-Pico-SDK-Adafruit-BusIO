#include "Adafruit_I2CDevice.h"

// #define DEBUG_SERIAL Serial

/*!
 *    @brief  Create an I2C device at a given address
 *    @param  addr The 7-bit I2C address for the device
 *    @param  theWire The I2C bus to use, defaults to &Wire
 */
Adafruit_I2CDevice::Adafruit_I2CDevice(i2c_inst_t *i2cBus, uint8_t addr)
{
  priv_i2cBus = i2cBus;
  priv_address = addr;
  priv_maxBufferSize = 32;
}

/*!
 *    @brief  Write a buffer or two to the I2C device. Cannot be more than
 * getMaxBufferSize() bytes.
 *    @param  buffer Pointer to buffer of data to write. This is const to
 *            ensure the content of this buffer doesn't change.
 *    @param  len Number of bytes from buffer to write
 *    @param  prefix_buffer Pointer to optional array of data to write before
 * buffer. Cannot be more than getMaxBufferSize() bytes. This is const to
 *            ensure the content of this buffer doesn't change.
 *    @param  prefix_len Number of bytes from prefix buffer to write
 *    @param  stop Whether to send an I2C STOP signal on write
 *    @return True if write was successful, otherwise false.
 */
bool Adafruit_I2CDevice::write(const uint8_t *buffer, size_t len, bool stop,
                               const uint8_t *prefix_buffer,
                               size_t prefix_len)
{
  // if ((len + prefix_len) > getMaxBufferSize())
  // {
  //   return false;
  // }

  // Write the prefix data (usually an address)
  if ((prefix_len != 0) && (prefix_buffer != nullptr))
  {
    if (i2c_write_blocking(priv_i2cBus, priv_address, prefix_buffer, prefix_len, stop) != prefix_len)
    {
      return false;
    }
  }

  // Write the data itself
  if (i2c_write_blocking(priv_i2cBus, priv_address, buffer, len, stop) != len)
  {
    return false;
  }
  return true;
}

/*!
 *    @brief  Read from I2C into a buffer from the I2C device.
 *    Cannot be more than getMaxBufferSize() bytes.
 *    @param  buffer Pointer to buffer of data to read into
 *    @param  len Number of bytes from buffer to read.
 *    @param  stop Whether to send an I2C STOP signal on read
 *    @return True if read was successful, otherwise false.
 */
bool Adafruit_I2CDevice::read(uint8_t *buffer, size_t len, bool stop)
{
  size_t pos = 0;
  while (pos < len)
  {
    size_t read_len =
        ((len - pos) > getMaxBufferSize()) ? getMaxBufferSize() : (len - pos);
    bool read_stop = (pos < (len - read_len)) ? false : stop;
    if (!priv_read(buffer + pos, read_len, read_stop))
      return false;
    pos += read_len;
  }
  return true;
}

bool Adafruit_I2CDevice::priv_read(uint8_t *buffer, size_t len, bool stop)
{
  size_t recv = i2c_read_blocking(priv_i2cBus, priv_address, buffer, len, stop);
  return true;
}

/*!
 *    @brief  Returns the 7-bit address of this device
 *    @return The 7-bit address of this device
 */
uint8_t Adafruit_I2CDevice::getAddress() { return priv_address; }
