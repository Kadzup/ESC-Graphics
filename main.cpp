#include "Image.h"

const float pi = 3.141596 / 5;

void setFractal(float x, float y, float r, float angle, int deep, Image& img) {
	double h = 2 * r * cos(pi);

	for (int i = 0; i < 5; i++) {

		float ang2 = angle + pi * i * 2,
			x2 = x - h * cos(ang2),
			y2 = y - h * sin(ang2),
			rad2 = r / (2 * cos(pi) + 1),
			ang3 = angle + 3.141596 + (2 * i + 1) * pi;

		for (int j = 0; j < 4; j++) {
			img.DrawLine(x, y, (x + rad2 * cos(ang3 + j * pi * 2)), (y + rad2 * sin(ang3 + j * pi * 2)), COLOR_BLACK);
			img.DrawLine(x, y, (x + rad2 * cos(ang3 + (j + 1) * pi * 2)), (y + rad2 * sin(ang3 + (j + 1) * pi * 2)), COLOR_BLACK);
		}

		if (deep > 0)
			setFractal(x2, y2, r / (2 * cos(pi) + 1), angle + 3.141596 + (2 * i + 1) * pi, deep - 1, img);
	}
}

void kochCurve(Point p1, Point p2, int times, Image& img) {
	Point p3, p4, p5;
	double theta = pi / 3;

	if (times > 0) {
		p3 = { (int)((2 * p1.x + p2.x) / 3),(int)((2 * p1.y + p2.y) / 3) };
		p5 = { (int)((2 * p2.x + p1.x) / 3),(int)((2 * p2.y + p1.y) / 3) };

		p4 = { (int)(p3.x + (p5.x - p3.x) * cos(theta) + (p5.y - p3.y) * sin(theta)), (int)(p3.y - (p5.x - p3.x) * sin(theta) + (p5.y - p3.y) * cos(theta)) };

		kochCurve(p1, p3, times - 1, img);
		kochCurve(p3, p4, times - 1, img);
		kochCurve(p4, p5, times - 1, img);
		kochCurve(p5, p2, times - 1, img);
	}

	else {
		img.DrawLine(p1, p2, COLOR_BLACK);
	}
}

void DrawStar(Image& img, Point center)
{
	int incr = 200;
	
	img.DrawLine({center.x, center.y - incr}, {center.x + incr, center.y + incr/2}, COLOR_BLACK);
	img.DrawLine({ center.x + incr, center.y + incr / 2 }, {center.x - incr, center.y + incr/2}, COLOR_BLACK);
	img.DrawLine({ center.x - incr, center.y + incr / 2 }, { center.x, center.y - incr }, COLOR_BLACK);

	img.DrawLine({ center.x, center.y + incr }, { center.x + incr, center.y - incr / 2 }, COLOR_BLACK);
	img.DrawLine({ center.x + incr, center.y - incr / 2 }, { center.x - incr, center.y - incr / 2 }, COLOR_BLACK);
	img.DrawLine({ center.x - incr, center.y - incr / 2 }, { center.x, center.y + incr }, COLOR_BLACK);
}

void DrawEmoji(Image &img, Point center)
{
	img.DrawCircle(center, 200, COLOR_ORANGE, 3, true, COLOR_YELLOW);

	img.DrawCircle({ center.x, center.y + 40 }, 100, COLOR_ORANGE, 2, true, COLOR_WHITE);

	img.DrawRectangle({ center.x - 100, center.y - 80 }, { center.x + 100, center.y + 50 }, COLOR_YELLOW, 1, true, COLOR_YELLOW);

	img.DrawLine({ center.x - 100, center.y + 50 }, { center.x + 100, center.y + 50 }, COLOR_ORANGE);
	img.DrawLine({ center.x - 100, center.y + 51 }, { center.x + 100, center.y + 51 }, COLOR_ORANGE);
	img.DrawLine({ center.x - 100, center.y + 52 }, { center.x + 100, center.y + 52 }, COLOR_ORANGE);

	img.DrawLine({ center.x - 80, center.y + 55 }, { center.x - 80, center.y + 95 }, COLOR_GREY);
	img.DrawLine({ center.x + 80, center.y + 55 }, { center.x + 80, center.y + 95 }, COLOR_GREY);

	img.DrawLine({ center.x - 60, center.y + 55 }, { center.x - 60, center.y + 115 }, COLOR_GREY);
	img.DrawLine({ center.x + 60, center.y + 55 }, { center.x + 60, center.y + 115 }, COLOR_GREY);

	img.DrawLine({ center.x - 40, center.y + 55 }, { center.x - 40, center.y + 125 }, COLOR_GREY);
	img.DrawLine({ center.x + 40, center.y + 55 }, { center.x + 40, center.y + 125 }, COLOR_GREY);

	img.DrawLine({ center.x - 20, center.y + 55 }, { center.x - 20, center.y + 135 }, COLOR_GREY);
	img.DrawLine({ center.x + 20, center.y + 55 }, { center.x + 20, center.y + 135 }, COLOR_GREY);

	img.DrawLine({ center.x, center.y + 55 }, { center.x, center.y + 135 }, COLOR_GREY);
	
	img.DrawLine({ center.x-80, center.y + 95 }, { center.x+80, center.y + 95 }, COLOR_GREY);
	
	img.DrawCircle({ center.x-80, center.y-100}, 50, COLOR_ORANGE, 2, true, COLOR_WHITE);
	img.DrawCircle({ center.x+80, center.y-100}, 50, COLOR_ORANGE, 2, true, COLOR_WHITE);

	img.DrawCircle({ center.x - 80, center.y - 100 }, 10, COLOR_BLACK, 2, true, COLOR_BLACK);
	img.DrawCircle({ center.x + 80, center.y - 100 }, 10, COLOR_BLACK, 2, true, COLOR_BLACK);	
}

int main()
{
	string pathName = "out/";

	Image img(720, 720,  "image.bmp", COLOR_WHITE);

	Point center{ img.GetWidth() / 2, img.GetHeight() / 2 };

	//setFractal(center.x, center.y, 70, 0, 7, img);
	/*Point p1, p2;
	p1 = { 10,720/2 - 10 };
	p2 = { 720/2 - 10,720/2 - 10 };

	kochCurve(p1, p2, 2, img);*/
	//DrawStar(img, center);

	DrawEmoji(img, center);
	img.Save();

	return 0;
}
