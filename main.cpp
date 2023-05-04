
#include <fcntl.h>
#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
#include <unistd.h>

#include "i2c_wrapper.hpp"
#include "mlx_register_def.hpp"

int main() {
  std::uint8_t i2c_number = 1;
  auto filename = "/dev/i2c-1";

  i2c::MLX_I2C mlx_i2c(filename, mlx::i2c::mlx_i2c_addr);
  if (!mlx_i2c.init()) {
    std::cout << "That was nothing" << std::endl;
    return 0;
  }

  while (true) {
    auto status_register = mlx_i2c.read_word(mlx::reg::status::REG_ADDR);

    if (status_register)
      std::cout << "SREG: " << status_register.value() << std::endl;

    sleep(1);
  }

  return 0;
}