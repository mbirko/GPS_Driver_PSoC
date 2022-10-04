#pragma once

#include <stdint.h>

class PI
{
public:
	PI(int16_t Kp, int16_t Ki, uint8_t shift, int16_t maxOut, int16_t minOut, int16_t maxErrorSum, int16_t minErrorSum);
	void setPoint(int32_t setPoint);
	int32_t	update(int32_t input);

private:
	int32_t Kp_;
	int32_t Ki_;
	int32_t maxOut_;
	int32_t minOut_;
	int32_t setPoint_;
	int64_t errorSum_;

	uint8_t shift_;

	int64_t maxErrorSum_;
	int64_t minErrorSum_;
};