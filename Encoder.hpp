#ifndef ENCODER_HPP
#define ENCODER_HPP

#ifdef __cplusplus

#include "main.h"

/// @brief STM32CubeIDEのHALライブラリをラップしている
class Encoder
{
public:
    /// @param htim エンコーダモードになっているタイマハンドラ
    Encoder(TIM_HandleTypeDef *htim) : htim_{htim} {}
    ~Encoder()
    {
        stop();
    }

    void start(void)
    {
        HAL_TIM_Encoder_Start(htim_, TIM_CHANNEL_ALL);
    }

    void stop(void)
    {
        HAL_TIM_Encoder_Stop(htim_, TIM_CHANNEL_ALL);
    }

    void reset(void)
    {
        pos = 0;
    }

    /// @return 現在の変位．int64_t型
    /// @note この関数を呼び出すと，内部でエンコーダのカウンタがリセットされる
    int64_t getPos(void)
    {
        const uint32_t raw_speed = htim_->Instance->CNT;
        htim_->Instance->CNT = 0;
        pos += *((int32_t *)(&raw_speed));
        return pos;
    }

    /// @return 現在の速度．int32_t型
    /// @note この関数を呼び出すと，内部でエンコーダのカウンタがリセットされる
    int32_t getSpeed(void)
    {
        const uint32_t raw_speed = htim_->Instance->CNT;
        htim_->Instance->CNT = 0;
        pos += *((int32_t *)(&raw_speed));
        return *((int32_t *)(&raw_speed));
    }

private:
    TIM_HandleTypeDef *htim_;
    int64_t pos = 0;
};

#endif // __cplusplus

#endif // ENCODER_HPP