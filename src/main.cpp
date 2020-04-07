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
		if (a < M_PI * 2)
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
		for (int i = 0; i < vectors.size() - 1; i++)
		{
			olc::vi2d vector1;
			olc::vi2d vector2;

			float nX = radius * vectors[i].first + (ScreenHeight() / 2);
			float nY = -radius * vectors[i].second + (ScreenHeight() / 2);

			vector1 = olc::vi2d(nX, nY);

			if (i == vectors.size() - 1)
			{
				float nX2 = radius * vectors[0].first + (ScreenHeight() / 2);
				float nY2 = -radius * vectors[0].second + (ScreenHeight() / 2);

				vector2 = olc::vi2d(nX2, nY2);
			}
			else
			{
				float nX2 = radius * vectors[i + 1].first + (ScreenHeight() / 2);
				float nY2 = -radius * vectors[i + 1].second + (ScreenHeight() / 2);

				vector2 = olc::vi2d(nX2, nY2);
			}
			DrawLine(vector1, vector2, olc::MAGENTA);
		}

		return true;
	}
	//variables for modifiying behaviour
#define multiplier 2
	float radius = 5.0f * multiplier;
	float thresholdMin = 5.0f * multiplier;
	float thresholdMax = 7.5f * multiplier;
	float speed = 0.03f * multiplier;
	bool directionSwap = false;
	float a = 0.0f;
	std::vector<std::pair<float,float>> vectors;
private:
	
};
int main()
{
	HeartCurve heartCurve;
	if (heartCurve.Construct(720, 720, 1, 1, false, true))
		heartCurve.Start();
	return 0;
}