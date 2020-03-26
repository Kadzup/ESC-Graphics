#include "Image.h"

Image::~Image()
{
    buffer.clear();
}

Image::Image(const Image& _image)
{
    Init(_image.width, _image.height);
    SetFileName(_image.outFileName);
    backgroundColor = _image.backgroundColor;
    Setup();
}

Image::Image(int64_t _width, int64_t _height)
{
    Init(_width, _height);
    Setup();
}

Image::Image(int64_t _width, int64_t _height, const string& _outFileName)
{
    Init(_width, _height);
    SetFileName(_outFileName);
    Setup();
}

Image::Image(int64_t _width, int64_t _height, const RGBColor& _backgroundColor)
{
    Init(_width, _height);
    backgroundColor = _backgroundColor;
    Setup();
}

Image::Image(int64_t _width, int64_t _height, const string& _outFileName, const RGBColor& _backgroundColor)
{
    Init(_width, _height);
    SetFileName(_outFileName);
    backgroundColor = _backgroundColor;
    Setup();
}

void Image::Init(int64_t _width, int64_t _height)
{
    assert(_width > 0 and _height > 0);
    width = _width;
    height = _height;
    outFileName = "image.bmp";
    buffer.clear();
    backgroundColor = RGBColor(255, 255, 255);
}

void Image::Setup()
{
    try {
    	//buffer = vector<vector<RGBColor> >(width, vector<RGBColor>(height));
        for (int64_t i = 0; i < height; i++)
        {
            buffer.push_back(vector <RGBColor>());
            for (int64_t j = 0; j < width; j++)
            {
                buffer[i].push_back(backgroundColor);
            }
        }
    }
    catch (std::bad_alloc & ba) {
        std::cerr << "_BMP ERROR: bad_alloc error (Can't create image buffer) -> " << ba.what() << std::endl;
        assert(false);
    }
}

void Image::SetPixel(const Point& point, const RGBColor& color, bool ignore_err = false)
{
    if (ignore_err and not(point.x >= 0 and point.y >= 0 and point.x < width-1 and point.y < height-1)) return;
    assert(point.x >= 0 and point.y >= 0 and point.x < width and point.y < height);
    buffer[point.y][point.x] = color;
}

void Image::DrawLine(const Point& begin, const Point& end, const RGBColor& color)
{
    if (abs(end.y - begin.y) < abs(end.x - begin.x)) {
        if (begin.x > end.x) {
            DrawLineLow(end.x, end.y, begin.x, begin.y, color);
        }
        else {
            DrawLineLow(begin.x, begin.y, end.x, end.y, color);
        }
    }
    else {
        if (begin.y > end.y) {
            DrawLineHigh(end.x, end.y, begin.x, begin.y, color);
        }
        else {
            DrawLineHigh(begin.x, begin.y, end.x, end.y, color);
        }
    }
}

void Image::DrawLineLow(int64_t x0, int64_t y0, int64_t x1, int64_t y1, const RGBColor& color)
{
    int64_t dx = x1 - x0;
    int64_t dy = y1 - y0;
    int64_t yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    int64_t D = (dy << 1) - dx;
    int64_t y = y0;
    for (int64_t x = x0; x <= x1; ++x) {
        SetPixel(Point{ x, y }, color, true);
        if (D > 0) {
            y += yi;
            D -= (dx << 1);
        }
        D += (dy << 1);
    }
}

void Image::DrawLineHigh(int64_t x0, int64_t y0, int64_t x1, int64_t y1, const RGBColor& color)
{
    int64_t dx = x1 - x0;
    int64_t dy = y1 - y0;
    int64_t xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int64_t D = (dx << 1) - dy;
    int64_t x = x0;
    for (int64_t y = y0; y <= y1; ++y) {
        SetPixel(Point{ x, y }, color, true);
        if (D > 0) {
            x += xi;
            D -= (dy << 1);
        }
        D += (dx << 1);
    }
}

void Image::DrawCircle(const Point& center, const int64_t& r, const RGBColor& outlineColor, const int64_t& outlineWidth = 1, bool fill = false, const RGBColor& fillColor = COLOR_WHITE)
{
    int64_t sq_r = r * r;
    for (int64_t dx = -r; dx <= r; ++dx) {
        for (int64_t dy = -r; dy <= r; ++dy) {
            int64_t sq_dist = dx * dx + dy * dy;
            if (sq_dist <= sq_r) {
                
                Point point;
                point.x = center.x + dx;
                point.y = center.y + dy;
            	
                if (outlineWidth > 1)
                    SetPixel(point, outlineColor, true);
                else
                    SetPixel(point, fillColor, true);
            }
        }
    }
    if (outlineWidth > 1)
    {
        DrawCircle(center, r - outlineWidth, outlineColor, 1, fill, fillColor);
    }
}

void Image::DrawRectangle(const Point& topLeft, const Point& bottomRight, const RGBColor& outlineColor, const int64_t& outlineWidth = 1, bool fill = false, const RGBColor& fillColor = COLOR_WHITE)
{
    if (fill)
    {
        FillRectangle(topLeft, bottomRight, fillColor);
    }

    DrawLine(topLeft, Point{bottomRight.x, topLeft.y}, outlineColor);
    DrawLine(Point{ bottomRight.x, topLeft.y }, bottomRight, outlineColor);
    DrawLine(bottomRight, Point{ topLeft.x, bottomRight.y }, outlineColor);
    DrawLine(Point{ topLeft.x, bottomRight.y }, topLeft, outlineColor);

    if (outlineWidth > 1) {
        DrawRectangle(Point{ topLeft.x + 1, topLeft.y + 1 }, Point{ bottomRight.x - 1, bottomRight.y - 1 }, outlineColor, outlineWidth - 1, fill, fillColor);
    }

}

void Image::FillRectangle(const Point& topLeft, const Point& bottomRight, const RGBColor& fillColor)
{
    int64_t x1 = topLeft.x, y1 = topLeft.y;
    int64_t x2 = bottomRight.x, y2 = bottomRight.y;
	
    while (y1 != y2)
    {
        DrawLine(Point{ x1, y1 }, Point{ x2, y1 }, fillColor);

        y1++;
    }

}

void Image::SetFileName(const string& _outFileName)
{
    outFileName = _outFileName;
	
    if (_outFileName.find(".bmp") == -1)
        outFileName += ".bmp";
}

void Image::Save(const string& _outFileName)
{
    SetFileName(_outFileName);
    Save();
}

void Image::Save()
{

    outFile.open(outFileName, ofstream::binary);
    if (not outFile.is_open()) {
        std::cerr << "_BMP ERROR: Can't open file to write data." << std::endl;
        assert(false);
    }

    unsigned int headers[13];
    int paddedSize, extraBytes;

    extraBytes = 4 - ((width * 3) % 4);         // How many bytes of padding to add to each
                                                // horizontal line - the size of which must
                                                // be a multiple of 4 bytes.

    if (extraBytes == 4) {
        extraBytes = 0;
    }

    paddedSize = ((width * 3) + extraBytes) * height;

    headers[0] = paddedSize + 54;      // bfSize (whole file size)
    headers[1] = 0;                    // bfReserved (both)
    headers[2] = 54;                   // bfOffbits
    headers[3] = 40;                   // biSize
    headers[4] = width;  // biWidth
    headers[5] = height; // biHeight

    // Would have biPlanes and biBitCount in position 6, but they're shorts.
    // It's easier to write them out separately (see below) than pretend
    // they're a single int

    headers[7] = 0;                    // biCompression
    headers[8] = paddedSize;           // biSizeImage
    headers[9] = 0;                    // biXPelsPerMeter
    headers[10] = 0;                    // biYPelsPerMeter
    headers[11] = 0;                    // biClrUsed
    headers[12] = 0;                    // biClrImportant

    // Headers BEGIN

    outFile << 'B' << 'M';

    for (int i = 0; i <= 5; ++i) {
        outFile << (uint8_t)((headers[i] & 0x000000ff));
        outFile << (uint8_t)((headers[i] & 0x0000ff00) >> 8);
        outFile << (uint8_t)((headers[i] & 0x00ff0000) >> 16);
        outFile << (uint8_t)((headers[i] & (uint32_t)0xff000000) >> 24);
    }

    // These next 4 characters are for the biPlanes and biBitCount fields.

    outFile << (uint8_t)1 << (uint8_t)0 << (uint8_t)24 << (uint8_t)0;

    for (int i = 7; i <= 12; ++i) {
        outFile << (uint8_t)((headers[i] & 0x000000ff));
        outFile << (uint8_t)((headers[i] & 0x0000ff00) >> 8);
        outFile << (uint8_t)((headers[i] & 0x00ff0000) >> 16);
        outFile << (uint8_t)((headers[i] & (uint32_t)0xff000000) >> 24);
    }

    // Headers END

    uint8_t colorBuffer[3];

    // BMP image format is written from bottom to top
    for (int64_t y = height - 1; y >= 0; --y) {
        for (int64_t x = 0; x < width; ++x) {
            // Also, it's written in (b,g,r) format
            outFile << buffer[y][x].b << buffer[y][x].g << buffer[y][x].r;
        }
        // BMP lines must be of lengths divisible by 4.
        if (extraBytes) {
            for (int i = 1; i <= extraBytes; ++i) {
                outFile << (uint8_t)0;
            }
        }
    }

    outFile.close();
}

RGBColor Image::GetPixelColor(const Point& point) const
{
    if (point.x <= buffer[0].size()-1 && point.y <= buffer.size()-1)
        return buffer[point.x][point.y];
    else
        return backgroundColor;
}