# GMP RT Shell Module 

所有的输入作为表达式处理。不考虑使用命令的场景。
可以为内部变量绑定一个外部访问的名字，用名字可以访问这一变量参与运算和赋值。

提供一组内部函数可以参与数学运算。输出等。

基本语法和C(应该更像m语言)一样

mtr_id_kp = 2*5;

提供以下功能函数

print("输出字符串或者数字")

print(variable)

获得GMP RT Shell的版本
version()


// 利用队列组织的变量
typedef struct _tag_rtsh_variable_usr
{
    // name of the variable

    // variable property
    // ?
    
    // type of the variable
    // string, real, ctrl_gt, bool

    // content of the variable

    // pointer to next variable struct 

};

// 固定长度的数组
typedef struct _tag_rtsh_variable_sys
{
    // name of the variable

    // variable property
    // ?
    
    // type of the variable
    // string, real, ctrl_gt, bool

    // content of the variable

};

typedef struct _tag_rtsh_variable_tmp
{
     // variable property
    // ?
    
    // type of the variable
    // string, real, ctrl_gt, bool

    // content of the variable

};

char* keyword[] = 
{"",  // NULL 
"all"
};

typedef struct _tag_internal_function
{
    // function name

    // function type

    // function pointer

};

typedef strcut _tag_rtsh_entity
{
    // internal variables
    // Seach periority: 

    // key word

    // function list

    // exp fifo

};

// function call list
typedef struct _tag_atom_instraction
{
    // function pointer

    // parameter pointer
    // pointer array to variables
}

typedef strcut _tag_rtsh_expression
{
    // temporary variables
    // search periority

    // Script variables
    // search periority:

    // compile result
    atom_instraction array;


}

有几个结构体用于保存变量表

+ 内部变量（具名变量，左值）
+ 脚本变量（具名变量，左值）
+ 临时变量（右值暂存区，只有一个具体的地址存放这个变量）

有几个结构体来存放支持的操作

+ 关键字
+ 数学运算符表
+ 基本函数表
+ 外部函数表（由用户指定的函数调用）

循环嵌套会有递归出现，至少需要一个heap来保存循环逻辑。

能不能实现逻辑？
最基本的判断和循环

if <exp> // 认为以下出现的几个词为关键字。

elif <exp>

else 

endif

有一个字符串作为输入

get_token() // 获得下一个token

有一个翻译函数将一个字符串输入翻译成函数调用序列

有一个eval函数用于执行函数调用该序列

基本思路，先能够识别并计算一个表达式。
能够实现函数调用。
截下来实现计算的


