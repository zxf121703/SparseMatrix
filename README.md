实现功能：

1.读入矩阵并按本节所述表示法建立矩阵：
istream& operator>>(istream&, Matrix&);
2.输出矩阵m的元素。为此设计一个合理的输出格式。输出可只输出非零元素，同时还可以行序或列序排列。但为了更于清晰明了地显示，本报告则按常规完整输出，即零与非零元素均按序输出（精华）：				
ostream& operator<<(ostream&, Matrix&);
3.复制构造函数，用稀疏矩阵a初始化稀疏矩阵*this ：
Matrix(const Matrix& a);
4.赋值操作符重载，把稀疏矩阵a赋值给*this ：
const Matrix operator=(const Matrix& a);
5.析构函数，回收稀疏矩阵*this中的所有结点到可用空间链表中：
~Matrix();
6.稀疏矩阵的加法，创建并返回稀疏矩阵*this+b ：
Matrix operator+(const Matrix& b) const;
7.稀疏矩阵的减法，创建并返回稀疏矩阵*this-b ：
Matrix operator-(const Matrix& b) const;
8.稀疏矩阵的乘法，创建并返回稀疏矩阵*this*b ：
Matrix operator*(const Matrix& b) const;
9.稀疏矩阵的转置，创建并返回*this的转置 ：
Matrix Transpose() const;

操作：

矩阵的数据在程序运行的时候由用户提供，先由用户输入稀疏矩阵的行数、列数和非零元素个数。再根据非零元个数，输入这些非零元，还需要用户为这些非零元输入行、列和非零元的值。这样，一个稀疏矩阵就输入完成。接着就选择相应的操作运算并获得运算结果的输出。若退出系统，可直接按0退出
