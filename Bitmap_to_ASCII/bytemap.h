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
protected:
    int row_count=50;
    int column_count=200;
    int bytemap[50][200];
    char projection[50][200];
    std::string gradient;
};