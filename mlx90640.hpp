#ifndef MLX90640_HPP_
#define MLX90640_HPP_

#include <memory>

#include "i2c_wrapper.hpp"
#include "mlx90640_data.hpp"

class MLX90640 {
public:
  int DumpEE(std::vector<std::uint16_t> &eeData);
  int SynchFrame();
  int TriggerMeasurement();
  int GetFrameData(std::vector<std::uint16_t> &frameData);
  int ExtractParameters(std::vector<std::uint16_t> &eeData,
                        paramsMLX90640 *mlx90640);
  float GetVdd(uint16_t *frameData, const paramsMLX90640 *params);
  float GetTa(uint16_t *frameData, const paramsMLX90640 *params);
  void GetImage(uint16_t *frameData, const paramsMLX90640 *params,
                float *result);
  void CalculateTo(uint16_t *frameData, const paramsMLX90640 *params,
                   float emissivity, float tr, float *result);
  int SetResolution(uint8_t resolution);
  int GetCurResolution();
  int SetRefreshRate(uint8_t refreshRate);
  int GetRefreshRate();
  int GetSubPageNumber(uint16_t *frameData);
  int GetCurMode();
  int SetInterleavedMode();
  int SetChessMode();
  void BadPixelsCorrection(uint16_t *pixels, float *to, int mode,
                           paramsMLX90640 *params);

  MLX90640() = delete;
  explicit MLX90640(std::unique_ptr<i2c::MLX_I2C> mlx_i2c)
      : mlx_i2c_(std::move(mlx_i2c)){};
  virtual ~MLX90640() = default;

private:
  void ExtractVDDParameters(std::vector<std::uint16_t> &eeData,
                            paramsMLX90640 *mlx90640);
  void ExtractPTATParameters(std::vector<std::uint16_t> &eeData,
                             paramsMLX90640 *mlx90640);
  void ExtractGainParameters(std::vector<std::uint16_t> &eeData,
                             paramsMLX90640 *mlx90640);
  void ExtractTgcParameters(std::vector<std::uint16_t> &eeData,
                            paramsMLX90640 *mlx90640);
  void ExtractResolutionParameters(std::vector<std::uint16_t> &eeData,
                                   paramsMLX90640 *mlx90640);
  void ExtractKsTaParameters(std::vector<std::uint16_t> &eeData,
                             paramsMLX90640 *mlx90640);
  void ExtractKsToParameters(std::vector<std::uint16_t> &eeData,
                             paramsMLX90640 *mlx90640);
  void ExtractAlphaParameters(std::vector<std::uint16_t> &eeData,
                              paramsMLX90640 *mlx90640);
  void ExtractOffsetParameters(std::vector<std::uint16_t> &eeData,
                               paramsMLX90640 *mlx90640);
  void ExtractKtaPixelParameters(std::vector<std::uint16_t> &eeData,
                                 paramsMLX90640 *mlx90640);
  void ExtractKvPixelParameters(std::vector<std::uint16_t> &eeData,
                                paramsMLX90640 *mlx90640);
  void ExtractCPParameters(std::vector<std::uint16_t> &eeData,
                           paramsMLX90640 *mlx90640);
  void ExtractCILCParameters(std::vector<std::uint16_t> &eeData,
                             paramsMLX90640 *mlx90640);
  int ExtractDeviatingPixels(std::vector<std::uint16_t> &eeData,
                             paramsMLX90640 *mlx90640);
  int CheckAdjacentPixels(uint16_t pix1, uint16_t pix2);
  float GetMedian(float *values, int n);
  int IsPixelBad(uint16_t pixel, paramsMLX90640 *params);
  int ValidateFrameData(uint16_t *frameData);
  int ValidateAuxData(uint16_t *auxData);

  std::unique_ptr<i2c::MLX_I2C> mlx_i2c_;
  std::vector<uint16_t> eeData_;
};

#endif