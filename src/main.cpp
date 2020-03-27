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
		// called once per frame, draws random coloured pixels
		/*for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));
		return true;*/
		for (float a = 0 ; a < 3.14159*2; a+=0.01)
		{
			float r = 5;
			float x = r * 16 * std::pow(std::sin(a), 3) + (ScreenWidth() / 2);
			float y = -r * (13 * std::cos(a) - 5 * std::cos(2 * a) - 2 * std::cos(3 * a) - std::cos(4 * a)) + (ScreenHeight() / 2);
			Draw(x, y);
		}
		
		return true;
	}
};
int main()
{
	HeartCurve heartCurve;
	if (heartCurve.Construct(256, 240, 4, 4))
		heartCurve.Start();
	return 0;
}