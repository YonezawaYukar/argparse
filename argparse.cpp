//
// Created by yukari on 2022/3/30.
//

#include "argparse.h"

string argparse::cProgramName = ""; //程序名称
string argparse::cDescription = ""; //程序描述
bool argparse::bReadStatus = false; //读取状态
argument *argparse::nullarg = new argument();
argument *argparse::argCursor = argparse::nullarg;
bool argparse::bPathParse = false; //是否解析文件名
map<string, argument *> argparse::Argument_maps; //名称与argument指针的映射关系 名称是去掉-的参数

bool checkArgs(const char arg[]) {
    for (int i = 0; arg[i] != '\0'; i++) {
        //48-57 65-90 97-122 95 45
        if (!(
                48 <= arg[i] <= 57 ||
                65 <= arg[i] <= 90 ||
                97 <= arg[i] <= 122 ||
                arg[i] == 95 ||
                arg[i] == 45
        ))
            return false;
    }
    return true;
}

argparse::argparse() {
    this->add_description("This is a default description");
    this->add_argument("-H")
            ->add_help("input your help.")
            ->add_alias("--help")
            ->add_default("show this help message and exit.");
}

argparse *argparse::add_description(string help) {
    argparse::cDescription = help;
    return this;
}

argument *argparse::add_argument(string cArgname) {
    if (!checkArgs(cArgname.c_str()))argparse::excption();
    cArgname = argparse::get_argname(cArgname);
    argument *MapSearch = argparse::index_argument(cArgname);
    if (MapSearch || MapSearch->isEmpty()) {
        argument *_argument = new argument;
        _argument->cArgname = cArgname;
        argparse::Argument_maps.insert(std::make_pair(cArgname, _argument));
        return _argument;
    } else {
        return MapSearch;
    }

    //return this;
}

void argparse::excption() {
    return;
}

argparse::~argparse() {
    delete argparse::nullarg;
    for (map<string, argument *>::iterator i = argparse::Argument_maps.begin();
         i != argparse::Argument_maps.end(); i++) {
        delete i->second;
    }
}

bool argparse::parse_args(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        char *_argv = argv[i];
        if (_argv[0] == '-' && argparse::index_argument(argparse::get_argname(_argv))) { //是参数
            argparse::bReadStatus = true; //开启读模式
            argparse::index_argument(argparse::get_argname(_argv))->setHas();
            argparse::argCursor = argparse::index_argument(argparse::get_argname(_argv));
        } else if (argparse::bReadStatus) {
            argparse::argCursor->setData(_argv);
        } else {
            continue;//抛掉参数值
        }
    }
    return true;
}

string &argparse::operator[](const string &_argname) {
    argument *MapSearch = argparse::index_argument(argparse::get_argname(_argname));
    return MapSearch->get();
}

argument *argparse::get(string cArgname) {
    argument *MapSearch = argparse::index_argument(argparse::get_argname(cArgname));
    return MapSearch;
}

argument *argument::add_help(string help) {
    this->cHelp = help;
    return this;
};//添加参数描述
argument *argument::add_default(string data) {
    this->setData(data);
    this->cDefault = true;
    return this;
};//添加参数默认值
argument *argument::add_alias(string _argname) {
    this->cAliasName = _argname;
    return this;
};//添加参数别名
argument *argument::set_must() {
    this->bMust = true;
    return this;
}

argument::argument() {
    this->cHelp = "";
    this->bHas = false;
};