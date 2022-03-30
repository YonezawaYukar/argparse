//
// Created by yukari on 2022/3/30.
//

#include <backward.hpp>
#include "argparse.h"

void checkArgs(const char arg[]){
    for(int i=0;arg[i]!='\0';i++){
        //48-57 65-90 97-122 95 45
        if(!(
                48<=arg[i]<=57 ||
                65<=arg[i]<=90 ||
                97<=arg[i]<=122||
                        arg[i]==95||
                        arg[i]==45
        ))throw "Argname not allowed!";
    }
}
argparse& argparse::add_argument(string cAbArgname, string cArgname,string cDefault) {
    //判断cAbArgname是否合法
    checkArgs(cAbArgname.c_str());
    checkArgs(cArgname.c_str());
    argument* _argument = new argument;
    (*_argument).cArgname = cArgname;
    (*_argument).cAbArgname = cAbArgname;
    if( cDefault.length() > 0){
        (*_argument).cDefault = true;
        (*_argument).cData = cDefault;
        (*_argument).nDataLens = cDefault.length();
    }else{
        (*_argument).cDefault = false;
    }
    this->Arguments[this->nCount] = _argument;
    this->nCount++;
    this->Argument_names.push_back(cArgname);
    this->Argument_names.push_back(cAbArgname);
    this->Argument_maps.insert(std::make_pair(cArgname,_argument));
    this->Argument_maps.insert(std::make_pair(cAbArgname,_argument));
    return *this;
}

argparse& argparse::add_argument(string cAbArgname, string cArgname) {
    return add_argument(cAbArgname,cArgname,"");
}

argparse::~argparse() {
    for(int i=0;i<this->nCount;i++){
        delete this->Arguments[i];
    }
    delete[] this->Arguments;
}

argparse &argparse::add_argument_help(string help) {
    if(help.length() > 0){
        (this->Arguments[this->nCount-1])->cHelp = help;
    }
    return *this;
}
/*
 *  在遇到-开头的参数时，判断是否在参数表中，并且判断是否处于Read状态
 */
argparse &argparse::parse_args(int argc, char **argv) {
    for(int i=1;i<argc;i++){
        //cli参数较少 所以可以使用双层循环
        //对于大数据 应该写一个hash函数
        char* _argv = argv[i];
        if(_argv[0] == '-' &&std::find(this->Argument_names.begin(),this->Argument_names.end(),_argv) != this->Argument_names.end() ) { //是参数
                this->bReadStatus = true;//进入读取状态
                this->Has_Argument_Flag.push_back(_argv);//标记存在该参数
        }
        else if(this->bReadStatus){ //在读取状态，且不是参数名
            //那么该参数就是最后一个设置read状态的
            string _ArgName = (this->Has_Argument_Flag.end()-1)->c_str();
            argument* _Arg = this->Argument_maps[_ArgName];
            (*_Arg).cData = _argv;
            (*_Arg).nDataLens = _Arg->cData.length();
        }else{
            continue;//抛掉该参数
        }
    }
    for(vector<string>::iterator it = this->Has_Argument_Flag.begin();it!=this->Has_Argument_Flag.end();it++){
        this->Argument_maps[it->data()]->has = true;
    }
    return *this;
}

void argparse::add_description(string help) {
    if(help.length() > 0){
        this->cDescription = help;
    }
    return;
}

argument argparse::operator[](string _argname) {
    if(this->Argument_maps.find(_argname) != this->Argument_maps.end()){
        return *this->Argument_maps[_argname];
    }
    argument hora;
    return hora;
}

