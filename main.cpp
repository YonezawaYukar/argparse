#include <iostream>
#include "module/argparse.h"
using namespace std;

int main(int argc,char** argv) {
    // -A -B yukar --test 123
    argparse arg = argparse();
    arg.add_argument("-A");
    arg.add_argument("-B");
    arg.add_argument("--test");
    arg.parse_args(argc, argv);
    cout << arg.get("A")->isHas() << endl << arg["B"] << endl << arg["test"];
    return 0;
}
