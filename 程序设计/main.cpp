#include <iostream>
#include <fstream>
#include "field.h"
#include "units.h"
#include "engine.h"
using namespace std;

int main(int argc, char* argv[])
{
    string filename = "/home/wu/Desktop/judger_student/data/4_task4/8.in";
    ifstream ifs;
    ifs.open(filename.c_str());
    if (!ifs) {
        cout << "Cannot open the file: " << filename << endl;
        return -1;
    }

    Field* f = loadMap(ifs);

    // Field* f = new Field(11, 11);
    if (f == nullptr) {
        cout << "Failed to load map!" << endl;
        return -1;
    }
    play(*f, ifs, cout);

    delete f;
    ifs.close();
    return 0;
}
