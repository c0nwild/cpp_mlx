#ifndef I2C_WRAPPER_HPP_
#define I2C_WRAPPER_HPP_

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <optional>
#include <string>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

namespace i2c {

class MLX_I2C {
public:
  // Diese Funktion muss manuell ausgeführt werden.
  bool const init();
  std::optional<std::uint16_t> read_word(std::uint16_t reg_addr);
  bool write_word(std::uint16_t reg_addr, std::uint16_t data_word);
  std::optional<std::uint16_t> read_to_buffer(std::uint16_t reg_addr,
                                              std::vector<uint16_t> &buffer,
                                              std::uint16_t length);

  MLX_I2C() = delete;
  explicit MLX_I2C(std::string i2c_filename, std::uint8_t i2c_addr)
      : i2c_addr_(i2c_addr), i2c_filename_(i2c_filename){};
  virtual ~MLX_I2C() {
    if (i2c_filehandle_) {
      close(i2c_filehandle_.value());
    }
  }

private:
  bool select_register(std::uint8_t reg_addr);
  std::optional<int> file_open(std::string filename, std::int8_t fileops);
  bool init_i2c_communication();
  std::uint8_t i2c_addr_;
  std::string i2c_filename_;
  std::optional<int> i2c_filehandle_;
};

} // namespace i2c
#endif