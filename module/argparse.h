//
// Created by yukari on 2022/3/30.
//

#ifndef SNACNER_ARGPARSE_H
#define SNACNER_ARGPARSE_H
#include <algorithm>
#include <map>
using namespace std;

struct  argument{
    string cAbArgname;
    string cArgname;
    int nDataLens;
    string cData;
    bool cDefault;
    string cHelp;
    bool has;
};

class argparse {
private:
    string cDescription;
    argument **Arguments = new argument*[5];
    vector<string> Argument_names;
    int nCount=0;
    bool bReadStatus=false;
    vector<string> Has_Argument_Flag;
    map<string,argument*> Argument_maps;
public:
    void add_description(string help); //添加总描述
    argparse& parse_args(int argc,char** argv); //载入argv
    argparse& add_argument(string cAbArgname,string cArgname); //添加参数
    argparse& add_argument(string cAbArgname,string cArgname,string cDefault); //添加参数带默认值
    argparse& add_argument_help(string help);//添加参数描述
    ~argparse();
    argument operator[](string _argname);
};

void checkArgs (char arg[]);
#endif //SNACNER_ARGPARSE_H
