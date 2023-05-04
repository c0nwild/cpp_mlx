#ifndef MLX90640_DATA_HPP_
#define MLX90640_DATA_HPP_

#include <cstdint>

static constexpr std::uint8_t MLX90640_NO_ERROR = 0;
static constexpr std::uint8_t MLX90640_I2C_NACK_ERROR = 1;
static constexpr std::uint8_t MLX90640_I2C_WRITE_ERROR = 2;
static constexpr std::uint8_t MLX90640_BROKEN_PIXELS_NUM_ERROR = 3;
static constexpr std::uint8_t MLX90640_OUTLIER_PIXELS_NUM_ERROR = 4;
static constexpr std::uint8_t MLX90640_BAD_PIXELS_NUM_ERROR = 5;
static constexpr std::uint8_t MLX90640_ADJACENT_BAD_PIXELS_ERROR = 6;
static constexpr std::uint8_t MLX90640_EEPROM_DATA_ERROR = 7;
static constexpr std::uint8_t MLX90640_FRAME_DATA_ERROR = 8;
static constexpr std::uint8_t MLX90640_MEAS_TRIGGER_ERROR = 9;

#define BIT_MASK(x) (1UL << (x))
#define REG_MASK(sbit, nbits) ~((~(~0UL << (nbits))) << (sbit))

static constexpr std::uint16_t MLX90640_EEPROM_START_ADDRESS = 0x2400;
static constexpr std::uint16_t MLX90640_EEPROM_DUMP_NUM = 832;
static constexpr std::uint16_t MLX90640_PIXEL_DATA_START_ADDRESS = 0x0400;
static constexpr std::uint16_t MLX90640_PIXEL_NUM = 768;
static constexpr std::uint16_t MLX90640_LINE_NUM = 24;
static constexpr std::uint16_t MLX90640_COLUMN_NUM = 32;
static constexpr std::uint16_t MLX90640_LINE_SIZE = 32;
static constexpr std::uint16_t MLX90640_COLUMN_SIZE = 4;
static constexpr std::uint16_t MLX90640_AUX_DATA_START_ADDRESS = 0x0700;
static constexpr std::uint16_t MLX90640_AUX_NUM = 64;
static constexpr std::uint16_t MLX90640_STATUS_REG = 0x8000;
static constexpr std::uint16_t MLX90640_INIT_STATUS_VALUE = 0x0030;
#define MLX90640_STAT_FRAME_MASK BIT_MASK(0)
#define MLX90640_GET_FRAME(reg_value) 0 //(reg_value & MLX90640_STAT_FRAME_MASK)
#define MLX90640_STAT_DATA_READY_MASK BIT_MASK(3)
#define MLX90640_GET_DATA_READY(reg_value)                                     \
  (reg_value & MLX90640_STAT_DATA_READY_MASK)

#define MLX90640_CTRL_REG 0x800D
#define MLX90640_CTRL_TRIG_READY_MASK BIT_MASK(15)
#define MLX90640_CTRL_REFRESH_SHIFT 7
#define MLX90640_CTRL_REFRESH_MASK REG_MASK(MLX90640_CTRL_REFRESH_SHIFT, 3)
#define MLX90640_CTRL_RESOLUTION_SHIFT 10
#define MLX90640_CTRL_RESOLUTION_MASK                                          \
  REG_MASK(MLX90640_CTRL_RESOLUTION_SHIFT, 2)
#define MLX90640_CTRL_MEAS_MODE_SHIFT 12
#define MLX90640_CTRL_MEAS_MODE_MASK BIT_MASK(12)

#define MLX90640_MS_BYTE_SHIFT 8
#define MLX90640_MS_BYTE_MASK 0xFF00
#define MLX90640_LS_BYTE_MASK 0x00FF
#define MLX90640_MS_BYTE(reg16)                                                \
  ((reg16 & MLX90640_MS_BYTE_MASK) >> MLX90640_MS_BYTE_SHIFT)
#define MLX90640_LS_BYTE(reg16) (reg16 & MLX90640_LS_BYTE_MASK)
#define MLX90640_MSBITS_6_MASK 0xFC00
#define MLX90640_LSBITS_10_MASK 0x03FF
#define MLX90640_NIBBLE1_MASK 0x000F
#define MLX90640_NIBBLE2_MASK 0x00F0
#define MLX90640_NIBBLE3_MASK 0x0F00
#define MLX90640_NIBBLE4_MASK 0xF000
#define MLX90640_NIBBLE1(reg16) ((reg16 & MLX90640_NIBBLE1_MASK))
#define MLX90640_NIBBLE2(reg16) ((reg16 & MLX90640_NIBBLE2_MASK) >> 4)
#define MLX90640_NIBBLE3(reg16) ((reg16 & MLX90640_NIBBLE3_MASK) >> 8)
#define MLX90640_NIBBLE4(reg16) ((reg16 & MLX90640_NIBBLE4_MASK) >> 12)

#define POW2(x) pow(2, (double)x)

#define SCALEALPHA 0.000001

struct paramsMLX90640 {
  std::int16_t kVdd;
  std::int16_t vdd25;
  float KvPTAT;
  float KtPTAT;
  std::uint16_t vPTAT25;
  float alphaPTAT;
  std::int16_t gainEE;
  float tgc;
  float cpKv;
  float cpKta;
  std::uint8_t resolutionEE;
  std::uint8_t calibrationModeEE;
  float KsTa;
  float ksTo[5];
  std::int16_t ct[5];
  uint16_t alpha[768];
  uint8_t alphaScale;
  std::int16_t offset[768];
  std::int8_t kta[768];
  std::uint8_t ktaScale;
  std::int8_t kv[768];
  std::uint8_t kvScale;
  float cpAlpha[2];
  std::int16_t cpOffset[2];
  float ilChessC[3];
  std::uint16_t brokenPixels[5];
  std::uint16_t outlierPixels[5];
};

#endif