#ifndef MLX_REGISTER_DEF_HPP_
#define MLX_REGISTER_DEF_HPP_

#include <cstdint>

namespace mlx {

namespace i2c {
static constexpr std::uint8_t mlx_i2c_addr = 0x33;
}
namespace reg {

namespace status {
static constexpr std::uint16_t REG_ADDR = 0x8000;
}
} // namespace reg

} // namespace mlx

#endif