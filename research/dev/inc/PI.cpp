#include "PI.hpp"

/**
 * @brief Construct a new PI::PI object	
 * 
 * @param Kp Proportional gain
 * @param Ki Integral gain
 * @param shift Fixed point shift
 * @param maxOut Maximum output
 * @param minOut Minimum output
 * @param maxErrorSum Maximum error sum
 * @param minErrorSum Minimum error sum
 */
PI::PI(int16_t Kp, int16_t Ki, uint8_t shift, int16_t maxOut, int16_t minOut, int16_t maxErrorSum, int16_t minErrorSum)
{
	Kp_ = Kp;
	Ki_ = Ki;
	maxOut_ = maxOut;
	minOut_ = minOut;
	setPoint_ = 0;
	errorSum_ = 0;
	shift_ = shift;
	maxErrorSum_ = maxErrorSum << shift_;
	minErrorSum_ = minErrorSum << shift_;
}

/**
 * @brief Set the set point of the PI
 * 
 * @param setPoint The set point
 */
void PI::setPoint(int32_t setPoint)
{
	setPoint_ = setPoint;
}

/**
 * @brief Update the PI
 * 
 * @param input The input from the sensor
 * @return int32_t The output to the actuator
 */
int32_t PI::update(int32_t input)
{
	int32_t error = setPoint_ - input; // Calculate the error
	errorSum_ += error; // Add the error to the error sum

	/* Check if the error sum is too high or too low */
	if (errorSum_ > maxErrorSum_)
	{
		errorSum_ = maxErrorSum_;
	}
	else if (errorSum_ < minErrorSum_)
	{
		errorSum_ = minErrorSum_;
	}

	/* Calculate the pTerm and iTerm */
	int32_t pTerm = Kp_ * error;
	int64_t iTerm = Ki_ * errorSum_;

	/* Calculate the output */
	int32_t output = (pTerm + iTerm) >> shift_;

	/* Check if the output is too high or too low */
	if(output > maxOut_)
	{
		output = maxOut_;
	}
	else if(output < minOut_)
	{
		output = minOut_;
	}
	
	return output;
}