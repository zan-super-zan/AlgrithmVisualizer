#pragma once

#include <random>

class Random
{
public:
	static void Init()
	{
		s_RandomEngine.seed(std::random_device{}());
	}

	static int Int(int min, int max)
	{
		std::uniform_int_distribution<int> dist(min, max);
		return dist(s_RandomEngine);
	}

	static float Float()
	{
		std::uniform_real_distribution<float> dist(0.0f, 1.0f);
		return dist(s_RandomEngine);
	}

	static float FloatRange(float min, float max)
	{
		std::uniform_real_distribution<float> dist(min, max);
		return dist(s_RandomEngine);
	}

private:
	// Mersenne Twister 19937 engine
	static std::mt19937 s_RandomEngine;
};


