#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include <vector>

class Image{
public:
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };
public:
    vector<vector<unsigned char>> pixels;
    explicit Image(const string& x);
    void Write(string x);
    void subtract(Image x);
    void multiply(Image x);
    void screen(Image x);
    void overlay(Image x);
    void onlyred();
    void onlygreen();
    void onlyblue();
    void combine(Image green, Image blue);
    void flip();
    void addred(string bgrValue);
    void addgreen(string bgrValue);
    void addblue(string bgrValue);
    void scalered(string bgrScale);
    void scaleblue(string bgrScale);
    void scalegreen(string bgrScale);
private:
    Header header{};
};


#endif