#include "pch.h"
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
class HeartCurve : public olc::PixelGameEngine
{
public:
	HeartCurve()
	{
		sAppName = "I <3 u";
	}
public:
	bool OnUserCreate() override
	{
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		//paint background black again to clear old frames
		Clear(olc::BLACK);
		//animation loop
		if (a < 3.14159*2)
		{
			//magic math
			float x = 16 * std::pow(std::sin(a), 3);
			float y = (13 * std::cos(a) - 5 * std::cos(2 * a) - 2 * std::cos(3 * a) - std::cos(4 * a));
			//save incremental steps for time based drawing
			vectors.push_back(std::make_pair(x, y));
			//step speed
			a += 0.01;
		}
		//after completeing animation begin beating animation
		else
		{
			if (radius < thresholdMax && directionSwap == false)
			{
				radius += speed;
				directionSwap = false;
			}
			else if (radius > thresholdMax || directionSwap == true)
			{
				if (radius < thresholdMin)
				{
					radius = thresholdMin;
					directionSwap = false;
				}
				else
				{
					radius -= speed;
					directionSwap = true;
				}
			}
			
		}
		//for each pair of vectors draw a point
		for (auto& vector : vectors)
		{
			float nX = radius * vector.first + (ScreenHeight() / 2);
			float nY = -radius * vector.second + (ScreenHeight() / 2);
			Draw(nX, nY);
		}

		return true;
	}
	//variables for modifiying behaviour
#define multiplier 1
	float radius = 5.0f * multiplier;
	float thresholdMin = 5.0f * multiplier;
	float thresholdMax = 7.5f * multiplier;
	float speed = 0.03f * multiplier;
	bool directionSwap = false;
	float a = 0.0f;
	std::vector<std::pair<float,float>> vectors;
};
int main()
{
	HeartCurve heartCurve;
	if (heartCurve.Construct(256, 256, 2, 2, false, true))
		heartCurve.Start();
	return 0;
}