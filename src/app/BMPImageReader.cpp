
#include "BMPImageReader.h"

BMPImageReader::BMPImageReader() :
    m_Width(0), m_Height(0), m_ImageSize(0), m_Data(nullptr)
{
}

bool BMPImageReader::Load(const std::string filepath)
{
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins

    FILE * file = fopen(filepath.c_str(), "rb");
    if (!file)
    {
        printf("Image could not be opened\n");
        return false;
    }

    if ( fread(header, 1, 54, file)!=54 )
    { // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return false;
    }

    if (header[0] != 'B' || header[1] != 'M')
    { // If first two bytes of header are not BM
        printf("Not a correct BMP header\n");
        return false;
    }

    // Read ints from the byte array
    dataPos     = *(int*)&(header[0x0A]);
    m_Width     = *(int*)&(header[0x12]);
    m_Height    = *(int*)&(header[0x16]);
    m_ImageSize = *(int*)&(header[0x22]);

    // Some BMP files are misformatted, guess missing information
    if (m_ImageSize == 0)
        m_ImageSize = m_Width * m_Height * 3; // 3 : one byte for each Red, Green and Blue component

    if (dataPos == 0)
        dataPos = 54; // The BMP header is done that way

    // Create a buffer
    m_Data = new unsigned char [m_ImageSize];

    // Read the actual data from the file into the buffer
    fread(m_Data, 1, m_ImageSize, file);

    //Everything is in memory now, the file can be closed
    fclose(file);

    return true;
}

BMPImageReader::~BMPImageReader()
{
    delete m_Data;
}
