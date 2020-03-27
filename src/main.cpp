#include "pch.h"
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
// Override base class with your custom functionality
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
		// Called once at the start, so create things here
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		if (a < 3.14159*2)
		{
			float x = r * 16 * std::pow(std::sin(a), 3) + (ScreenWidth() / 2);
			float y = -r * (13 * std::cos(a) - 5 * std::cos(2 * a) - 2 * std::cos(3 * a) - std::cos(4 * a)) + (ScreenHeight() / 2);
			vectors.push_back(std::make_pair(x, y));
			a += 0.01;
		}
		else
		{
			/*if (r < 8.5f && upDown == false)
			{
				r += 0.01f;
				upDown = false;
			}
			else if (r > 8.5f || upDown == true)
			{
				if (r < 5.0f)
				{
					r = 5.0f;
					upDown = false;
				}
				r -= 0.01f;
				upDown = true;
			}*/
			
		}	
		for (auto& vector : vectors)
		{
			Draw(vector.first, vector.second);
		}

		return true;
	}
	float r = 5.0f;
	bool upDown = false;
	float a = 0.0f;
	std::vector<std::pair<float,float>> vectors;
};
int main()
{
	HeartCurve heartCurve;
	if (heartCurve.Construct(256, 240, 4, 4))
		heartCurve.Start();
	return 0;
}