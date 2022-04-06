//
// Created by yukari on 2022/3/30.
//

#ifndef SNACNER_ARGPARSE_H
#define SNACNER_ARGPARSE_H
#include <algorithm>
#include <map>
#include <string>
using namespace std;
class argument {
public:
    string cArgname;//全写参数名
    string cAliasName;//添加别名
    string cHelp; //参数描述
    bool bMust = false;//是否为必须 此处暂时不实现 有待考虑
    argument();

    argument *add_help(string help);//添加参数描述
    argument *add_default(string data);//添加参数默认值
    argument *add_alias(string _argname);//添加参数别名
    argument *set_must();//设置该参数为必须参数 _nocite是当该参数不存在时的提示
    string &get() { return this->cData; }

    void setHas() { this->bHas = true; }

    void setData(string data) {
        this->cData = data;
        this->nDataLens = data.length();
    }

    int getLen() { return this->nDataLens; }

    bool isHas() { return this->bHas; }

    bool isEmpty() {
        if (!cArgname.length())return true;
        return false;
    }

private:
    string cData; //参数值 未来需要改成模板
    int nDataLens = 0; //数据长度
    bool cDefault = false; //是否是默认值
    bool bHas = false; //是否存在该参数
};

class argparse {
private:
    static string cProgramName; //程序名称
    static string cDescription; //程序描述
    static bool bReadStatus; //读取状态
    static argument *argCursor;
    static bool bPathParse; //是否解析文件名
    static map<string, argument *> Argument_maps; //名称与argument指针的映射关系 名称是去掉-的参数
    static argument *index_argument(string _argname) {
        if (argparse::Argument_maps.find(_argname) != argparse::Argument_maps.end()) {
            return argparse::Argument_maps[_argname];
        } else {
            return argparse::nullarg;
        }
    }

    static string get_argname(string _argname) {
        while (_argname[0] == '-')_argname.erase(_argname.begin());
        return _argname;
    }

    static void excption();

public:
    argparse();

    argparse *add_description(string help); //添加总描述
    static bool parse_args(int argc, char **argv); //载入argv
    argument *add_argument(string cArgname); //添加参数
    argparse *set_path_parse(bool path = true) {
        argparse::bPathParse = path;
        return this;
    }

    argument *get(string cArgname);

    string &operator[](const string &_argname);

    static argument *nullarg;

    ~argparse();
};

bool checkArgs(const char *arg);
#endif //SNACNER_ARGPARSE_H
