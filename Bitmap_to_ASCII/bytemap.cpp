#include "bytemap.h"

Bytemap::Bytemap(std::string gradient):gradient(gradient){
}

void Bytemap::load(int value, int row, int column){
    this->bytemap[row][column] = value;
}

void Bytemap::print_Bytemap(){
    for(int row=0; row < row_count; row++){
        for(int column=0; column < column_count; column++){
            std::cout << this->bytemap[row][column];
        }
        std::cout << std::endl;
    }
}
void Bytemap::print_Projection(){
    for(int row=0; row < row_count; row++){
        for(int column=0; column < column_count; column++){
            std::cout << this->projection[row][column];
        }
        std::cout << std::endl;
    }
}

void Bytemap::prepare_projection(){
    for(int row=0; row < row_count; row++){
        for(int column=0; column < column_count; column++){
            
            this->projection[row][column] = gradient[bytemap[row][column]];
        }
    }
}