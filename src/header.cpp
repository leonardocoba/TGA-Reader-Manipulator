#include "header.h"
using namespace std;

Image::Image(const string& x) {
    fstream inFile(x, ios_base::in | ios_base::binary);
    if (!inFile.is_open()) {
        cout << "Error opening file" << endl;

    }

    inFile.read((char *) (&header.idLength), 1);
    inFile.read((char *) (&header.colorMapType), 1);
    inFile.read((char *) (&header.dataTypeCode), 1);
    inFile.read(reinterpret_cast<char *>(&header.colorMapOrigin), 2);
    inFile.read(reinterpret_cast<char *>(&header.colorMapLength), 2);
    inFile.read((char *) (&header.colorMapDepth), 1);
    inFile.read(reinterpret_cast<char*>(&header.xOrigin), 2);
    inFile.read(reinterpret_cast<char*>(&header.yOrigin), 2);
    inFile.read(reinterpret_cast<char*>(&header.width), 2);
    inFile.read(reinterpret_cast<char*>(&header.height), 2);
    inFile.read((char *) (&header.bitsPerPixel), 1);
    inFile.read((char *) (&header.imageDescriptor), 1);


    vector<vector<unsigned char>> tempVector(header.width * header.height, vector<unsigned char>(3));
    unsigned char tempColor;
    for (int i = 0; i < header.width * header.height; i++) {
        for (int j = 0; j < 3; j++) {
            inFile.read((char *) (&tempColor), 1);
            tempVector[i][j] = tempColor;
        }
    }
    pixels = tempVector;
    inFile.close();
}

void Image::Write(string x) {
    ofstream outputFile(x,ios_base::out | ios_base::binary);
    if (!outputFile.is_open()) {
        cout << "Error: Not opening Fam" << endl;
    }
    outputFile.write((char*)&header.idLength, 1);
    cout << header.idLength << endl;
    outputFile.write((char*)&header.colorMapType, 1);
    outputFile.write((char*)&header.dataTypeCode, 1);
    outputFile.write((char*)&header.colorMapOrigin, 2);
    outputFile.write((char*)&header.colorMapLength, 2);
    outputFile.write((char*)&header.colorMapDepth, 1);
    outputFile.write((char*)&header.xOrigin, 2);
    outputFile.write((char*)&header.yOrigin, 2);
    outputFile.write((char*)&header.width, 2);
    outputFile.write((char*)&header.height, 2);
    outputFile.write((char*)&header.bitsPerPixel, 1);
    outputFile.write((char*)&header.imageDescriptor, 1);
    for (int i=0; i < header.width * header.height; i++){
        for (int j = 0; j < 3; j++){
            outputFile.write((char*)&pixels[i][j], 1);
        }
    }
    outputFile.close();
}
void Image::subtract(Image x) {
    for (int i = 0; i < header.width * header.height; i++) {
        for (int j = 0; j < 3; j++) {
            int result = static_cast<int>(this->pixels[i][j]) - static_cast<int>(x.pixels[i][j]);
            if (result >= 255){
                this->pixels[i][j] = static_cast<unsigned char>(255);
            }
            else if (result <= 0) {
                this->pixels[i][j] = static_cast<unsigned char>(0);
            } else {
                this->pixels[i][j] = static_cast<unsigned char>(result);
            }
        }
    }
}
void Image::multiply(Image x) {
    for (int i = 0; i < header.width * header.height; i++) {
        for (int j = 0; j < 3; j++) {
            float normalized_this = static_cast<float>(this->pixels[i][j]) / 255.0f;
            float normalized_x = static_cast<float>(x.pixels[i][j]) / 255.0f;
            float result = normalized_this * normalized_x;
            result = (result * 255.0f) + 0.5f;
            if (result >= 255){
                result = 255;
            }
            else if (result <= 0){
                result = 0;
            }
            this->pixels[i][j] = static_cast<unsigned char>(result);
        }
    }
}
void Image::screen(Image x) {
    for (int i = 0; i < header.width * header.height; i++) {
        for (int j = 0; j < 3; j++) {
            float normalized_this = static_cast<float>(this->pixels[i][j]) / 255.0f;
            float normalized_x = static_cast<float>(x.pixels[i][j]) / 255.0f;
            float result = (1 - ((1 - normalized_this) * (1 - normalized_x)));
            result = (result * 255.0f) + 0.5f;
            this->pixels[i][j] = static_cast<unsigned char>(result);
        }
    }
}
void Image::overlay(Image x) {
    for (int i = 0; i < header.width * header.height; i++) {
        for (int j = 0; j < 3; j++) {
            float normalized_this = static_cast<float>(this->pixels[i][j]) / 255.0f;
            float normalized_x = static_cast<float>(x.pixels[i][j]) / 255.0f;
            if (normalized_x > 0.5){
                float result = (1-((2*(1-normalized_this)*(1-normalized_x))));
                result = (result * 255.0f) + 0.5f;
                this->pixels[i][j] = static_cast<unsigned char>(result);
            }
            else{
                float result = (2 * normalized_x * normalized_this);
                result = (result * 255.0f) + 0.5f;
                this->pixels[i][j] = static_cast<unsigned char>(result);
            }
            }
        }
}
void Image::onlyred(){
    for (int i = 0; i < header.width * header.height; i++) {
        for (int j = 0; j < 3; j++) {
            this->pixels[i][j] = this->pixels[i][2];
        }
    }
}
void Image::onlygreen(){

    for (int i = 0; i < header.width * header.height; i++) {
        for (int j = 0; j < 3; j++) {
            this->pixels[i][j] = this->pixels[i][1];
        }
    }
}
void Image::onlyblue(){
    for (int i = 0; i < header.width * header.height; i++) {
        for (int j = 0; j < 3; j++) {
            this->pixels[i][j] = this->pixels[i][0];
        }
    }
}
void Image::combine(Image green, Image blue) {
    for (int i = 0; i < header.width * header.height; i++) {
        this->pixels[i][1] = green.pixels[i][1];
    }
    for (int i = 0; i < header.width * header.height; i++) {
        this->pixels[i][0] = blue.pixels[i][0];
    }
}
void Image::flip() {
    vector<vector<unsigned char>> tempVector(header.width * header.height, vector<unsigned char>(3));
    for (int i = header.width * header.height - 1; i >-1; i--){
        for (int j =0; j <3; j++){
            tempVector[(header.width * header.height -1)-i][j] = this->pixels[i][j];
        }
    }
    this->pixels = tempVector;
}
void Image::addred(string bgrValue) {
    int num = stoi(bgrValue);
    for (int i = 0; i < header.width * header.height; i++) {
        int newVal = static_cast<int>(this->pixels[i][2]) + num;
        if (newVal > 255) {
            newVal = 255;
        }
        if (newVal < 0){
            newVal = 0;
        }
        this->pixels[i][2] = static_cast<unsigned char>(newVal);
    }
}
void Image::addblue(string bgrValue) {
    int num = stoi(bgrValue);
    for (int i = 0; i < header.width * header.height; i++) {
        int newVal = static_cast<int>(this->pixels[i][0]) + num;
        if (newVal > 255) {
            newVal = 255;
        }
        if (newVal < 0){
            newVal = 0;
        }
        this->pixels[i][0] = static_cast<unsigned char>(newVal);
    }
}
void Image::addgreen(string bgrValue) {
    int num = stoi(bgrValue);
    for (int i = 0; i < header.width * header.height; i++) {
        int newVal = static_cast<int>(this->pixels[i][1]) + num;
        if (newVal > 255) {
            newVal = 255;
        }
        if (newVal < 0){
            newVal = 0;
        }
        this->pixels[i][1] = static_cast<unsigned char>(newVal);
    }
}
void Image::scalered(string bgrScale) {
    int num = stoi(bgrScale);
    for (int i = 0; i < header.width * header.height; i++) {
        int newVal = static_cast<int>(this->pixels[i][2]) * num;
        if (newVal > 255) {
            newVal = 255;
        }
        if (newVal < 0){
            newVal = 0;
        }
        this->pixels[i][2] = static_cast<unsigned char>(newVal);
    }
}
void Image::scaleblue(string bgrScale) {
    int num = stoi(bgrScale);
    for (int i = 0; i < header.width * header.height; i++) {
        int newVal = static_cast<int>(this->pixels[i][0]) * num;
        if (newVal > 255) {
            newVal = 255;
        }
        if (newVal < 0){
            newVal = 0;
        }
        this->pixels[i][0] = static_cast<unsigned char>(newVal);
    }
}
void Image::scalegreen(string bgrScale) {
    int num = stoi(bgrScale);
    for (int i = 0; i < header.width * header.height; i++) {
        int newVal = static_cast<int>(this->pixels[i][1]) * num;
        if (newVal > 255) {
            newVal = 255;
        }
        if (newVal < 0){
            newVal = 0;
        }
        this->pixels[i][1] = static_cast<unsigned char>(newVal);
    }
}
