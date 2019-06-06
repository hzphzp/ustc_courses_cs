/*****************************************************************************************************
  Name:
      Arithmetic Core 
  Function:
      generate arithmetic problems randomly as settings from user, calculate these problems
  Author:
      Zhikai Chen
      Zhipeng Huang
  API for UI:
      UI can call the class Core() and its method generate(), before you use the function of
      generate(), you MUST define two string arrays, such as string* Problems and string* Results.
      After that you can use "generate(Problems, Results)" to generate these problems, these problems
      will be stored in the array "Problems" and their results will be stored in the array "Results"
  Communication:
      www.cnblogs.chenzhik.com
******************************************************************************************************
  产品名称：
      四则运算计算核心
  功能：
      按照UI接收的用户要求，用setting方法进行设置，用generate方法进行生成题目，用calculate方法计算出结果
  开发者：
      陈志锴，黄志鹏
  UI接口：
      UI必须定义：一个Core类的对象core，一个string* problem来存储生成的题目，一个string* result来存储对应的答案
      UI可以调用：Core内的Generate方法，调用形式为core.Generate(string* problem,string* result )
      这么做的结果：generate会将题目和结果存储在两个string*内，供UI提供给用户
      题目的配置在Core的Setting方法里面，调用形式是core.Setting(string option, string key)
      或者是core.Setting(string option, int key)
      其中option可选：
      	"precision" = 2;(或者其他的整数)
	    "calculate_kind" ="integer"(整数);(或者"fraction"(分数), "decimal"(小数))
	    "ProblemNum" = 10;(或者其他的整数)
        "OperandNum" =7;(或者其他的整数)
        "KindofOperator" = "+-*/^";(或者他的子集)
        "lrange" = 0(或者其他的整数);
        "hrange" = 99(或者其他的整数);
        ps:括号前是没有这项配置时的默认配置
           ！！！UI组应该保证Setting输入的正确性！！！
*******************************************************************************************************/
使用示例：
将压缩包解压到工程目录下
vs 调试-》属性-》c++-》常规-》附加包含目录-》core-debug里面的include目录（如果是release版的话就是core-release里面的include目录）
vs 调试-》属性-》链接器-》常规-》附加库目录-》core-debug里面的lib目录（如果是release版的话就是core-release目录的lib目录）
在文件头部添加：
#include<core.h>
#pragma comment(lib, "ArithmeticCore.lib")
用Setting进行配置，如果不配置就是默认的整数运算配置
示例代码如下：
#include<iostream>
#include<core.h>
#pragma comment(lib, "ArithmeticCore.lib")
using namespace std;
int main()
{
	core firstcore;
	firstcore.Setting("calculate_kind", "integer");
	firstcore.Setting("ProblemNum", 20);
	firstcore.Setting("OperandNum", 8);
	firstcore.Setting("hrange", 49);
	string* problem;
	string* result;
	firstcore.Generate(problem, result);
	for (int i = 0; i < 20; i++)
	{
		cout << problem[i] << endl;
		cout << result[i] << endl;
	}
	return 0;
}
