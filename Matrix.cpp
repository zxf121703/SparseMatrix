//Matrix.cpp

#include <iostream>
#include <stdexcept>
#include "Matrix.h"
using namespace std;

void display() {
cout << endl;
cout << "******************************稀疏矩阵链接表运算器******************************" <<endl;
cout << "1:				稀疏矩阵的加法运算" <<endl;
cout << "2:				稀疏矩阵的减法运算" <<endl;
cout << "3:				稀疏矩阵的乘法运算" <<endl;
cout << "4:				稀疏矩阵的转置运算" <<endl;
cout << "0:				退出系统                               @xuefu    "<<endl;
cout << "********************************************************************************" <<endl;
}

int main()
{
char key,confirmKey;

while(1) {
display();
cout << "请选择操作（-4）：";
cin >> key;
if(key=='0')
break;

switch (key) {
case '1': {
try {
Matrix m;
Matrix n;
Matrix result;
cout << endl << "请按相关要求依次输入两个稀疏矩阵进行加法运算！" <<endl<<endl;
cin >> m;
cout << endl;
cin >> n;
cout << "您输入的两个矩阵依次为：\n";
cout << m << endl << n <<endl;
cout << "相加的两个稀疏矩阵已输入完毕，是否继续？（y/n）:";
cin >> confirmKey;

if(confirmKey=='y' || confirmKey=='Y') {
cout << endl << "两个的稀疏矩阵相加的和为：" <<endl;
result=m+n;
cout << result <<endl;
}
}catch(exception &e) {
cout<<"Error:"<<e.what()<<endl;
}
};
break;
case '2': {
try {
Matrix m;
Matrix n;

cout << endl << "请按相关要求依次输入两个稀疏矩阵进行减法运算！" <<endl<<endl;
cin >> m;
cout << endl;
cin >> n;
cout << "您输入的两个矩阵依次为：\n";
cout << m << endl << n <<endl;
cout << endl << "相减的两个稀疏矩阵已输入完毕，是否继续？（y/n）:";
cin >> confirmKey;
if(confirmKey=='y' || confirmKey=='Y') {
cout << endl << "两个的稀疏矩阵相减的差为：" <<endl;
m = m - n;
cout << m <<endl;
}
}catch(exception &e) {
cout<<"Error:"<<e.what()<<endl;
}
};
break;
case '3': {
try {
Matrix m;
Matrix n;

cout << endl << "请按相关要求依次输入两个稀疏矩阵进行乘法运算！" <<endl<<endl;
cin >> m;
cout << endl;
cin >> n;
cout << "您输入的两个矩阵依次为：\n";
cout << m << endl << n <<endl;
cout << endl << "相乘的两个稀疏矩阵已输入完毕，是否继续？（y/n）:";
cin >> confirmKey;
if(confirmKey=='y' || confirmKey=='Y') {
cout << endl << "两个的稀疏矩阵相乘的积为：" <<endl;
m = m*n;
cout << m <<endl;
}
}catch(exception &e) {
cout<<"Error:"<<e.what()<<endl;
}
};
break;
case '4': {
try {
Matrix m;
Matrix result;

cout << endl << "请按相关要求一个稀疏矩阵进行转置运算！" <<endl<<endl;
cin >> m;
cout << "您输入的稀疏矩阵为：\n";
cout << m << endl;
cout << endl << "稀疏矩阵已输入完毕，是否继续？（y/n）:";
cin >> confirmKey;
if(confirmKey=='y' || confirmKey=='Y') {
cout << endl << "您输入的稀疏矩阵转置后为：" <<endl;
result = m.Transpose();
cout << result <<endl;
}
}catch(exception &e) {
cout<<"Error:"<<e.what()<<endl;
}
};
break;
default: {
cout << endl << "您选择错误，请重新输入！" <<endl;
};
break;
}
}
cout << endl << "您已退出系统，欢迎下次光临！" <<endl<<endl;

return 0;

}

