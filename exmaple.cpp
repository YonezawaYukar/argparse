#include <iostream>
#include "argparse.h"
using namespace std;

int main(int argc,char** argv) {
    argparse arg = argparse();
    arg.add_argument("-A");
    arg.add_argument("-B");
    arg.add_argument("--test");
    arg.add_argument("--default")->add_default("Default");
    argparse::parse_args(argc, argv);
    cout<< arg.get("A")->isHas() <<endl;
    cout<< arg["B"]<<endl;
    cout<< arg["test"]<<endl;
    cout<< arg.get("default")->get() <<" is default"<<endl;
    return 0;
}
