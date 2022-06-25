#include <iostream>

class Bytemap
{
public:
    Bytemap(std::string gradient);
    ~Bytemap();
    void load(int value, int row, int column);
    void print_Bytemap();
    void print_Projection();
    void prepare_projection();
    void move_frame_to_film(int frame);
protected:
    int row_count=70;
    int column_count=270;
    int bytemap[70][270];
    char projection[70][270];
    char film[50][100][270];
    std::string gradient;
};