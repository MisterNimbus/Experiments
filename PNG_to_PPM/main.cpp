#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct pixel
{
    int R;
    int G;
    int B;
};

struct PNM
{
    string pnmMagicNumber;
    int width, height, range;
    vector<vector<pixel>> pixelMap;
};

void printPNM(PNM pnm){
    
    
    cout << "Magic Number: " << pnm.pnmMagicNumber << endl;
    cout << "Width: " << pnm.width << endl;
    cout << "Height: " <<  pnm.height << endl;
    cout << "Value Range: " << pnm.range << endl;
    cout << endl << endl;
    for(int y = 0; y < pnm.pixelMap.size(); y++){
            for(int x = 0; x < pnm.pixelMap[y].size(); x++){
                if(pnm.pixelMap[y][x].R/100 >1){
                    cout << " " << pnm.pixelMap[y][x].R << " ";
                }
                else if(pnm.pixelMap[y][x].R/10 > 1){
                    cout << "  " << pnm.pixelMap[y][x].R << " ";
                }
                else{
                    cout << "  " << pnm.pixelMap[y][x].R << "  ";
                }

                if(pnm.pixelMap[y][x].G/100 >1){
                    cout << pnm.pixelMap[y][x].G << " ";
                }
                else if(pnm.pixelMap[y][x].G/10 > 1){
                    cout << " " << pnm.pixelMap[y][x].G << " ";
                }
                else{
                    cout << " " << pnm.pixelMap[y][x].G << "  ";
                }

                if(pnm.pixelMap[y][x].B/100 >1){
                    cout << pnm.pixelMap[y][x].B << " |";
                }
                else if(pnm.pixelMap[y][x].B/10 > 1){
                    cout << " " << pnm.pixelMap[y][x].B << " |";
                }
                else{
                    cout << " " << pnm.pixelMap[y][x].B << "  |";
                }
            }
            cout << endl;
        }
        
}

void PNMtoPixelMap(bool userInput, string * pnmName, PNM * pnm){
    
    if(userInput){
        cout << "Name of the PNM file (E.g: example.png): ";
        cin >> *pnmName;
        cout << endl;
    }

    string pnmMagicNumberBuffer = "", widthBuffer="", heightBuffer="", rangeBuffer="";
    fstream pnmFile;
    pnmFile.open(*pnmName, fstream::in | fstream::binary);
    pnmFile >> pnmMagicNumberBuffer;
    pnmFile >> widthBuffer;
    pnmFile >> heightBuffer;
    if( pnmMagicNumberBuffer != "P4"){
    pnmFile >> rangeBuffer;
    }else{
        rangeBuffer = 1;
    }

    pnm->pnmMagicNumber = pnmMagicNumberBuffer;
    pnm->width = stoi(widthBuffer);
    pnm->height = stoi(heightBuffer);
    pnm->range = stoi(rangeBuffer);

    pnmFile >> noskipws;

    vector<vector<pixel>> pixelMap;
    vector<pixel> pixelRow;
    pixel pixelBuffer;
    unsigned char Red, Green, Blue;

    for(int y=0; y < pnm->height; y++)
        {
        for(int x=0; x < pnm->width; x++){
            do{
            pnmFile >> Red;
            }while((int)Red == 10);
            pixelBuffer.R = (int)Red;

            do{
            pnmFile >> Green;
            }while((int)Green == 10);
            pixelBuffer.G = (int) Green;

            do{
            pnmFile >> Blue;
            }while((int)Blue == 10);
            pixelBuffer.B = (int)Blue;

            pixelRow.push_back(pixelBuffer);
        }
        pixelMap.push_back(pixelRow);
        pixelRow = {};
    }
    pnm->pixelMap=pixelMap;
    pnmFile.close();
}

int PixelMaptoPNM(bool userInput, PNM pnm, string * pnmName){

    if(userInput){
        cout << "Name of the PNM file to be created (E.g: example.png): ";
        cin >> *pnmName;
        cout << endl;
    }
    ofstream target;
    target.open(* pnmName, ios::out);
    string content = pnm.pnmMagicNumber;
    content += ' ';
    content += to_string(pnm.width) + ' ' + to_string(pnm.height);
    content += ' ';
    if( pnm.pnmMagicNumber != "P4"){
        content += to_string(pnm.range);
        content += ' ';
    }
    target << content;
    string buffer;
    for(int y = 0; y < pnm.pixelMap.size(); y++){
        for(int x = 0; x < pnm.pixelMap[y].size(); x++){
            //buffer += uint8_t(pnm.pixelMap[y][x].R);
            //buffer += uint8_t(pnm.pixelMap[y][x].G);
            //buffer += uint8_t(pnm.pixelMap[y][x].B);
            buffer += (pnm.pixelMap[y][x].R);
            buffer += (pnm.pixelMap[y][x].G);
            buffer += (pnm.pixelMap[y][x].B);
            if(sizeof(buffer) > 60){
                //buffer += '\n';
                target << buffer <<char(0x0A)<<  endl;
                buffer = "";
            }
        }
            
    }
    target << buffer << endl;
    /*
    for(int i=0; i < content.size(); i++){
        if(content[i]=='\r'){
            cout << "===================";
            content.erase(content[i]);
        }
    }*/
    //content.erase( remove(content.begin(), content.end(), '\r'), content.end() );
    target.close();
    if(target.fail()){return 1;}
    return 0;
}

int PNMtoPNG(bool userInput, string * pnmName, string * pngName){
if(userInput){
        cout << "Name of the PNM file (E.g: example.png): ";
        cin >> *pnmName;
        cout << "Name of the PNG file to be created (E.g: example.png): ";
        cin >> *pngName;
        cout << endl;
    }
    string command = "pnmtopng " + *pnmName + ">" + *pngName;
    return system(command.c_str());
}

int convertPNGtoPNM(bool userInput, string * pngName, string * pnmName){
    if(userInput){
        cout << "Name of the PNG file (E.g: example.png): ";
        cin >> *pngName;
        cout << "Name of the PNM file to be created (E.g: example.ppm): ";
        cin >> *pnmName;
        cout << endl;
    }
    string command = "pngtopnm " + *pngName + ">" + *pnmName;
    return system(command.c_str());
}

// insert an int function as the call parameter.
int successFailed(int call){
    if(call){
        cout << endl;
        cout << "========" << endl;
        cout << " Failed " << endl;
        cout << "========" << endl;
        return 1;
    }else{
        cout << endl;
        cout << "=========" << endl;
        cout << " Success " << endl;
        cout << "=========" << endl;
        return 0;
    }
}

int grayscaleAverage(PNM * pnm){
    for(int y = 0; y < pnm->height; y++)
        for(int x = 0; x < pnm->width; x++){
            int greyTone = (pnm->pixelMap[y][x].R + pnm->pixelMap[y][x].G + pnm->pixelMap[y][x].B) / 3;
            pnm->pixelMap[y][x].R = greyTone;
            pnm->pixelMap[y][x].G = greyTone;
            pnm->pixelMap[y][x].B = greyTone;
        }
    return 0;
}

int turnToASCII(PNM * pnm){
    for(int y = 0; y < pnm->height; y++)
        for(int x = 0; x < pnm->width; x++){
            int greyTone = (pnm->pixelMap[y][x].R + pnm->pixelMap[y][x].G + pnm->pixelMap[y][x].B) / 3;
            pnm->pixelMap[y][x].R = greyTone;
            pnm->pixelMap[y][x].G = greyTone;
            pnm->pixelMap[y][x].B = greyTone;
        }{}
    return 0;
}

int grayscaleLuminosity(PNM * pnm){
    for(int y = 0; y < pnm->height; y++)
        for(int x = 0; x < pnm->width; x++){
            int greyTone = pnm->pixelMap[y][x].R * 0.21 + pnm->pixelMap[y][x].G *0.72 + pnm->pixelMap[y][x].B * 0.07;
            pnm->pixelMap[y][x].R = greyTone;
            pnm->pixelMap[y][x].G = greyTone;
            pnm->pixelMap[y][x].B = greyTone;
        }
    return 0;
}

int main(){
    system("cls");
    string pngName = "LennaPaint.png";
    string pnmName = "converted.ppm";

    successFailed(convertPNGtoPNM(false, &pngName, &pnmName));

    PNM pnm;
    PNMtoPixelMap(false, &pnmName, &pnm);

    //grayscaleLuminosity(&pnm);

    pnmName="output.pmm";
    PixelMaptoPNM(false, pnm, &pnmName);
    
    string pngOutput = "output.png";
    successFailed(PNMtoPNG(false, &pnmName, &pngOutput));

    //system("pause");
    return 0;
}