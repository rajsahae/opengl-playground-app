#pragma once

#include <string>

class BMPImageReader
{
private:
    // Data read from the header of the BMP file
    unsigned int m_Width, m_Height;
    unsigned int m_ImageSize;   // = width*height*3

    // Actual RGB data
    unsigned char *m_Data;

public:

    BMPImageReader(const std::string filepath);
    ~BMPImageReader();

    inline unsigned char* Data() { return m_Data; }
    inline unsigned int Width() { return m_Width; }
    inline unsigned int Height() { return m_Height; }
    inline unsigned int Size() { return m_ImageSize; }
};
