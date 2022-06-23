#include <iostream>
#include <math.h>
#include "bytemap.cpp"


int main(){;

    Bytemap * bytemap = new Bytemap("  .:-=+*#%@");
    int input_bytemap[8][8];
    
    #define PI 3.14159265
    int row_size=50;
    int column_size=200;
    int offset = 0;
    bool inc = true;
    
    
    for(int row=0; row < row_size; row++){
        for(int column=0; column < column_size; column++){
            bytemap->load( (int)((5*(sin(2*PI*(offset+column)/100))+5)) , row, column);
        }
        if(offset==10)
        {
            inc=false;
        }
        else if (offset==0)
        {
            inc=true;
        }
        if(inc){offset+=(int)((5*(sin(2*PI*(row)/18))+5)/(0.2*row));}else{offset-=(int)((5*(sin(2*PI*(row)/75))+5));}
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
bytemap->prepare_projection();
    bytemap->print_Projection();

    for(int row=0; row < row_size; row++){
        for(int column=0; column < column_size; column++){

            float distance_to_origin = sqrt((row-(row_size/2))*(row-(row_size/2))+(column-(column_size/2))*(column-(column_size/2)));
            float primary = 5*sin(2*PI*(0.15*distance_to_origin));
            float secondary = (5*sin(2*PI*(0.01*distance_to_origin)));
            float offset = 5*2; 
            float drop1=(primary + secondary + offset)/2;

            bytemap->load( (int)(drop1), row, column);
        }
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    bytemap->prepare_projection();
    bytemap->print_Projection();

    for(int row=0; row < row_size; row++){
        for(int column=0; column < column_size; column++){

            float distance_to_origin = sqrt((row-(row_size/2))*(row-(row_size/2))+(column-(column_size/2))*(column-(column_size/2)));
            float primary = 5*sin(2*PI*(0.15*distance_to_origin));
            float secondary = (5*sin(2*PI*(0.01*distance_to_origin)));
            float offset = 5*2; 
            float drop1=(primary + secondary + offset)/2;

            float distance_to_origin2 = sqrt((row-(row_size/4))*(row-(row_size/4))+(column-(column_size/4))*(column-(column_size/4)));
            float primary2 = 5*sin(2*PI*(0.25*distance_to_origin2));
            float secondary2 = (5*sin(2*PI*(0.03*distance_to_origin2)));
            float offset2 = 5*2; 
            float drop2=(primary2 + secondary2 + offset2)/2;

            bytemap->load( (int)((drop1 + drop2)/2), row, column);
        }
    }


    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    //bytemap->print_Bytemap();
    bytemap->prepare_projection();
    bytemap->print_Projection();

    for(int row=0; row < row_size; row++){
        for(int column=0; column < column_size; column++){

            float distance_to_origin = sqrt((row-(row_size/2))*(row-(row_size/2))+(column-(column_size/2))*(column-(column_size/2)));
            float primary = 5*sin(2*PI*(0.15*distance_to_origin));
            float secondary = (5*sin(2*PI*(0.01*distance_to_origin)));
            float offset = 2+ 5*2; 
            float drop1=(primary + secondary + offset)/2;

            float distance_to_origin2 = sqrt((row-(row_size/4))*(row-(row_size/4))+(column-(column_size/4))*(column-(column_size/4)));
            float primary2 = 3*sin(2*PI*(0.25*distance_to_origin2));
            float secondary2 = 3*sin(2*PI*(0.03*distance_to_origin2));
            float offset2 = 3*2; 
            float drop2=(primary2 + secondary2)/2;

            bytemap->load( (int)((drop1 + drop2)/2), row, column);
        }
    }


    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    //bytemap->print_Bytemap();
    bytemap->prepare_projection();
    bytemap->print_Projection();

    return 0;
}