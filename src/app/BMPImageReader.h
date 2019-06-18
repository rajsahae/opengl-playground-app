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

    BMPImageReader();
    ~BMPImageReader();

    bool Load(const std::string filepath);

    inline unsigned char* Data() const { return m_Data; }
    inline unsigned int Width() const { return m_Width; }
    inline unsigned int Height() const { return m_Height; }
    inline unsigned int Size() const { return m_ImageSize; }
};
