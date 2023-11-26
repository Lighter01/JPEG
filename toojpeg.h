#ifndef TOOJPEG_H
#define TOOJPEG_H


// This is a compact baseline JPEG/JFIF writer, written in C++ (but looks like C for the most part).
// Its interface has only one function: writeJpeg() - and that's it !
//
// basic example:
// => create an image with any content you like, e.g. 1024x768, RGB = 3 bytes per pixel
// auto pixels = new unsigned char[1024*768*3];
// => you need to define a callback that receives the compressed data byte-by-byte from my JPEG writer
// void myOutput(unsigned char oneByte) { fputc(oneByte, myFileHandle); } // save byte to file
// => let's go !
// TooJpeg::writeJpeg(myOutput, mypixels, 1024, 768);

namespace TooJpeg
{
// write one byte (to disk, memory, ...)
typedef void (*WRITE_ONE_BYTE)(unsigned char);
// this callback is called for every byte generated by the encoder and behaves similar to fputc
// if you prefer stylish C++11 syntax then it can be a lambda, too:
// auto myOutput = [](unsigned char oneByte) { fputc(oneByte, output); };

// output       - callback that stores a single byte (writes to disk, memory, ...)
// pixels       - stored in RGB format or grayscale, stored from upper-left to lower-right
// width,height - image size
// isRGB        - true if RGB format (3 bytes per pixel); false if grayscale (1 byte per pixel)
// quality      - between 1 (worst) and 100 (best)
// downsample   - if true then YCbCr 4:2:0 format is used (smaller size, minor quality loss) instead of 4:4:4, not relevant for grayscale
// comment      - optional JPEG comment (0/NULL if no comment), must not contain ASCII code 0xFF
bool writeJpeg(WRITE_ONE_BYTE output, const void* pixels, unsigned short width, unsigned short height,
               bool isRGB = true, unsigned char quality = 90, bool downsample = false, const char* comment = nullptr);
} // namespace TooJpeg


#endif // TOOJPEG_H