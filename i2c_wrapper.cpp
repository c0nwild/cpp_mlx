#include "i2c_wrapper.hpp"
#include <array>

namespace i2c {
bool const MLX_I2C::init() {
  i2c_filehandle_ = file_open(i2c_filename_, O_RDWR);
  if (!i2c_filehandle_) {
    return false;
  }
  init_i2c_communication();
  return true;
}

std::optional<std::uint16_t> MLX_I2C::read_word(std::uint16_t reg_addr) {
  std::array<std::uint8_t, 2> buffer = {0};
  buffer[0] = (reg_addr >> 8);
  buffer[1] = (reg_addr & 0x00FF);
  if (write(i2c_filehandle_.value(), &buffer[0], 2) != 2) {
    return std::nullopt;
  }
  if (read(i2c_filehandle_.value(), &buffer[0], 2) != 2) {
    return std::nullopt;
  }
  return ((buffer[0] << 8 || buffer[1]));
}

bool MLX_I2C::write_word(std::uint16_t reg_addr, std::uint16_t data_word) {
  std::array<std::uint8_t, 4> buffer = {0};
  buffer[0] = (reg_addr >> 8);
  buffer[1] = (reg_addr & 0x00FF);
  buffer[2] = (data_word >> 8);
  buffer[3] = (data_word & 0x00FF);
  if (write(i2c_filehandle_.value(), &buffer[0], 4) != 4) {
    return false;
  }

  return true;
}

std::optional<std::uint16_t>
MLX_I2C::read_to_buffer(std::uint16_t reg_addr, std::vector<uint16_t> &buffer,
                        std::uint16_t length) {
  for (std::uint16_t register_addr = reg_addr;
       register_addr < register_addr + length; ++register_addr) {
    auto return_value = read_word(register_addr);
    if (return_value) {
      buffer.push_back(return_value.value());
    } else {
      return std::nullopt;
    }
  }
  return buffer.size();
}

bool MLX_I2C::select_register(std::uint8_t reg_addr) {
  std::array<std::uint8_t, 2> buffer = {0};
  buffer[0] = (reg_addr >> 8);
  buffer[1] = (reg_addr & 0x00FF);
  if (write(i2c_filehandle_.value(), &buffer[0], 2) != 2) {
    return false;
  }
  return true;
}

std::optional<int> MLX_I2C::file_open(std::string filename,
                                      std::int8_t fileops) {
  auto filehandle = open(filename.c_str(), fileops);
  if (filehandle < 0) {
    return std::nullopt;
  } else {
    return filehandle;
  }
}

bool MLX_I2C::init_i2c_communication() {

  auto return_value = ioctl(i2c_filehandle_.value(), I2C_SLAVE, i2c_addr_);
  if (return_value < 0) {
    return false;
  }
  return true;
};

} // namespace i2c