#include <iostream>
#include "header.h"
#include <fstream>
using namespace std;
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2 || string(argv[1]) == "--help") {
        cout << "Project 2: Image Processing, Spring 2023\n"
                "\nUsage:\n"
                "    ./project2.out [output] [firstImage] [method] [...]" << endl;
        return 0;
    }
    string outputFileName = argv[1];
    if (outputFileName.find(".tga") == string::npos || outputFileName.find("output/") == string::npos){
        cout << "Invalid file name." << endl;
        return 1;
    }
    string sourceFileName = argv[2];
    if (sourceFileName.find(".tga") == string::npos) {
        cout << "Invalid file name." << endl;
        return 1;
    }
    ifstream sourceFile(sourceFileName);
    if (!sourceFile.good()) {
        cout << "File does not exist." << endl;
        return 1;
    }
    Image trackingFileImage = Image(sourceFileName);
    for (int i = 3; i < argc; i++) {
        string method = argv[i];
        if (method == "multiply") {
            // Check if second file name argument is provided
            if (i + 1 >= argc){
                cout << "Missing argument." << endl;
                return 1;
            }
            if (string(argv[i + 1]).find(".tga") == string::npos){
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            string secondFileName = argv[++i];
            if (!ifstream(secondFileName).good()) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            Image secondImage = Image(secondFileName);
            trackingFileImage.multiply(secondImage);
        }
        else if (method == "flip") {
            trackingFileImage.flip();
        }
        else if (method == "subtract") {
            if (i + 1 >= argc || string(argv[i + 1]).find(".tga") == string::npos) {
                cout << "Missing argument or invalid file name." << endl;
                return 1;
            }
            string secondFileName = argv[++i];
            if (!ifstream(secondFileName).good()) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            Image secondImage = Image(secondFileName);
            trackingFileImage.subtract(secondImage);
        }
        else if (method == "screen") {
            if (i + 1 >= argc || string(argv[i + 1]).find(".tga") == string::npos) {
                cout << "Missing argument or invalid file name." << endl;
                return 1;
            }
            string secondFileName = argv[++i];
            if (!ifstream(secondFileName).good()) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            Image secondImage = Image(secondFileName);
            trackingFileImage.screen(secondImage);
        } else if (method == "overlay") {
            if (i + 1 >= argc || string(argv[i + 1]).find(".tga") == string::npos) {
                cout << "Missing argument or invalid file name." << endl;
                return 1;
            }
            string secondFileName = argv[++i];
            if (!ifstream(secondFileName).good()) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            Image secondImage = Image(secondFileName);
            trackingFileImage.overlay(secondImage);
        } else if (method == "combine") {
            if (i + 2 >= argc || string(argv[i + 1]).find(".tga") == string::npos ||
                string(argv[i + 2]).find(".tga") == string::npos) {
                cout << "Missing argument or invalid file name." << endl;
                return 1;
            }
            string secondFileName = argv[++i];
            if (!ifstream(secondFileName).good()) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            string thirdFileName = argv[++i];
            if (!ifstream(thirdFileName).good()) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }

            Image secondImage = Image(secondFileName);
            Image thirdImage = Image(thirdFileName);
            trackingFileImage.combine(secondImage, thirdImage);
        } else if (method == "onlyred") {
            trackingFileImage.onlyred();
        }
        else if (method == "onlygreen") {
            trackingFileImage.onlygreen();
        }
        else if (method == "onlyblue") {
            trackingFileImage.onlyblue();
        }
        else if (method == "addred") {
            if (i + 1 >= argc){
                cout << "Missing argument." << endl;
                return 1;
            }
        string num = argv[++i];
            try {
                int tempNum = stoi(num);
            }
            catch (invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 1;
            }
        trackingFileImage.addred(num);
        }
        else if (method == "addblue") {
            if (i + 1 >= argc){
                cout << "Missing argument." << endl;
                return 1;
            }
            string num = argv[++i];
            try {
                int tempNum = stoi(num);
            }
            catch (invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 1;
            }
            trackingFileImage.addblue(num);
        }
        else if (method == "addgreen") {
            if (i + 1 >= argc){
                cout << "Missing argument." << endl;
                return 1;
            }
            string num = argv[++i];
            try {
                int tempNum = stoi(num);
            }
            catch (invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 1;
            }
            trackingFileImage.addgreen(num);
        }
        else if (method == "scalered") {
            if (i + 1 >= argc){
                cout << "Missing argument." << endl;
                return 1;
            }
            string num = argv[++i];
            try {
                int tempNum = stoi(num);
            }
            catch (invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 1;
            }
            trackingFileImage.scalered(num);
        }
        else if (method == "scalegreen") {
            if (i + 1 >= argc){
                cout << "Missing argument." << endl;
                return 1;
            }
            string num = argv[++i];
            try {
                int tempNum = stoi(num);
            }
            catch (invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 1;
            }
            trackingFileImage.scalegreen(num);
        }
        else if (method == "scaleblue") {
            if (i + 1 >= argc){
                cout << "Missing argument." << endl;
                return 1;
            }
            string num = argv[++i];
            try {
                int tempNum = stoi(num);
            }
            catch (invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 1;
            }
            trackingFileImage.scaleblue(num);
        }
        else{
            cout << "Invalid method name." << endl;
            return 1;
        }
    }
    trackingFileImage.Write(outputFileName);
    }

