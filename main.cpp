
#include <fcntl.h>
#include <fmt/core.h>
#include <optional>
#include <string>
#include <type_traits>
#include <unistd.h>

#include "i2c_wrapper.hpp"
#include "mlx_register_def.hpp"

int main() {
  std::uint8_t i2c_number = 1;
  auto filename = fmt::format("/dev/i2c-{}", i2c_number);

  i2c::MLX_I2C mlx_i2c(filename, mlx::i2c::mlx_i2c_addr);
  mlx_i2c.init();

  while (true) {
    auto status_register = mlx_i2c.read_word(mlx::reg::status::REG_ADDR);

    fmt::print("Status reg: 0x{} \n", status_register.value());
    sleep(1);
  }

  return 0;
}