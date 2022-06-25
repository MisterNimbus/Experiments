#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
#include "bytemap.cpp"


int main(){;

    Bytemap * bytemap = new Bytemap(" .-:=+*#%@@@@@");
    
    #define PI 3.14159265
    int row_size=70;
    int column_size=270;
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

    for(int frame = 0; frame < 50; frame++){
        for(int row=0; row < row_size; row++){
            for(int column=0; column < column_size; column++){
                
                float distance_to_origin = sqrt((row-(row_size/2))*(row-(row_size/2))+(column-(column_size/2))*(column-(column_size/2)));
                float primary = 5*sin(2*PI*((0.05*distance_to_origin)-(frame*.05)))*pow(2,-0.008*distance_to_origin);
                float secondary = (5*sin(2*PI*(0.12*distance_to_origin)));
                float offset = 5;
                float drop1=(( primary + offset))*pow(2,-0.016*distance_to_origin);

                float distance_to_origin2 = sqrt((row-(row_size/5))*(row-(row_size/5))+(column-(column_size/6))*(column-(column_size/6)));
                float primary2 = 2*sin(2*PI*((0.1*distance_to_origin2)-(frame*.05)));
                float offset2 = 2;
                float drop2=(( primary2 + offset2))*pow(2,-0.016*distance_to_origin2);

                bytemap->load( (int)((drop1)), row, column);
            }
        }
        bytemap->prepare_projection();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        bytemap->print_Projection();
    }
    return 0;
}