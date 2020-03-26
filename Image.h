#pragma once
#include "RGBColor.h"
#include "Point.h"

#include <string>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
using std::string;
using std::int64_t;
using std::uint32_t;
using std::uint8_t;
using std::ofstream;

class Image
{
public:
    ~Image();
    Image() { width = height = 0; };
    Image(int64_t _width, int64_t _height);
    Image(int64_t _width, int64_t _height, const std::string& _outFileName);
    Image(int64_t _width, int64_t _height, const RGBColor& _backgroundColor);
    Image(int64_t _width, int64_t _height, const std::string& _outFileName, const RGBColor& _backgroundColor);
    Image(const Image& _image);

    /*
     Set Pixel on current Image
	 using X,Y position and
	 RGB color for Pixel
	 */
    void SetPixel(const Point& point, const RGBColor& color, bool ignore_err);

	/*
	 Draw Line on current Image
	 using 2 Points coordinates
	 X,Y position of First Point
	 X,Y position of Second Point
	 RGB color for Line
	 */
    void DrawLine(const Point& begin, const Point& end, const RGBColor& color);
   
    /*
     Draw Circle on current Image
	 using center Point coordinates
	 X,Y position of Center Point
	 Radius of Circle As Integer
	 Outline color As RGB Color
	 Outline Width As Integer - default=1
	 Fill circle flag As Boolean - default=False
	 Fill color As RGB Color - default=White
	*/
    void DrawCircle(const Point& center, const int64_t& r, const RGBColor& outlineColor, const int64_t& outlineWidth, bool fill, const RGBColor& fillColor);

	/*
     Draw Rectangle on current Image
	 using two Points coordinates
	 X,Y position of Top Left Point
	 X,Y position of Bottom Right Point
	 Outline color As RGB Color
	 Outline Width As Integer - default=1
	 Fill circle flag As Boolean - default=False
	 Fill color As RGB Color - default=White
	*/
    void DrawRectangle(const Point& topLeft, const Point& bottomRight, const RGBColor& outlineColor, const int64_t& outlineWidth, bool fill, const RGBColor& fillColor);

    /* Change Out File Name */
    void SetFileName(const std::string& _outFileName);

    /* Fill Rectangle Area with color */
	void FillRectangle(const Point& topLeft, const Point& bottomRight, const RGBColor& fillColor);

    /* Save Image */
    void Save(const std::string& _outFileName);
    /* Save Image */
    void Save();

	/* Get Image Width */
    inline int64_t GetWidth() const { return this->width; }
	/* Get Image Height */
    inline int64_t GetHeight() const { return this->height; }

	/* Get BackGround Color */
    inline RGBColor GetBGColor() const { return backgroundColor; }

    Image& operator = (const Image& img)
    {
        if (this == &img)
            return *this;
    	
        this->width = img.width;
        this->height = img.height;
        this->buffer = img.buffer;
        this->outFileName = img.outFileName;
        this->backgroundColor = img.backgroundColor;

        return *this;
    }

    /* Get Color of Pixel on current Point coordinate */
    RGBColor GetPixelColor(const Point& point) const;

private:
    void Init(int64_t _width, int64_t _height);
    void Setup();

    void DrawLineLow(int64_t x0, int64_t y0, int64_t x1, int64_t y1, const RGBColor& color);
    void DrawLineHigh(int64_t x0, int64_t y0, int64_t x1, int64_t y1, const RGBColor& color);
	
    int64_t width;
    int64_t height;
    ofstream outFile;
    string outFileName;
    RGBColor backgroundColor;
    vector<vector<RGBColor>> buffer;
};
