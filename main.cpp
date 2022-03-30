#include <iostream>
#include <vector>
#include "module/argparse.h"
#include <algorithm>
using namespace std;

int main(int argc,char** argv) {
    // -A -B yukar --test 123
    argparse test = argparse();
    test.add_description("test");
    test.add_argument("-A","--abc")
        .add_argument_help("a233")
        .add_argument("-B","--Bbc")
        .add_argument("-T","--test")
        ;
    test.parse_args(argc,argv);
    cout<< test["-A"].has<<endl; //A参数是否存在
    cout<< test["-B"].cData<<endl; //B参数的内容
    cout<<test["-T"].nDataLens<<endl; //C参数的长度
    return 0;
}
