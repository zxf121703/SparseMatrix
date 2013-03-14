//Matrix.h

#include <iostream>
#include <stdexcept>
using namespace std;

enum Boolean { FALSE, TRUE};

struct Triple
{
	int value, row, col;
};

class Matrix; // forward declaration

class MatrixNode
{
friend class Matrix;
friend istream& operator>>(istream&, Matrix&);	 // for reading in a matrix
friend ostream& operator<<(ostream&, Matrix&);	// for printing on cli

private:
	MatrixNode *down, *right;
	Boolean head;
union {	// anonymous union
	MatrixNode *next; //for linking each head node
	Triple triple;
};
MatrixNode() {};
MatrixNode(Boolean, Triple*);  // constructor
};

MatrixNode::MatrixNode(Boolean b, Triple* t)
{
	head = b;
if (b) {right = next = this;} // row/column head node
else triple = *t;  // head node for list of headnodes OR element node
}

typedef MatrixNode* MatrixNodePtr;

class Matrix {
friend istream& operator>>(istream&, Matrix& m);  // for reading in a matrix
friend ostream& operator<<(ostream&, Matrix& m); //for printing on cli
private:
MatrixNode *headnode;
public:
Matrix() { }; //default constructor
Matrix(const Matrix& a); //copy constructor
~Matrix();  // destructor
//operations of sparsematrix
const Matrix operator=(const Matrix& a);
Matrix operator+(const Matrix& b) const;
Matrix operator-(const Matrix& b) const;
Matrix operator*(const Matrix& b) const;
Matrix Transpose() const;
};

Matrix::Matrix(const Matrix& a) {
headnode = new MatrixNode(FALSE,&(a.headnode->triple));
int p = max(a.headnode->triple.row,a.headnode->triple.col);
MatrixNodePtr *head = new MatrixNodePtr[p];  // initialize head nodes
for (int i = 0; i < p; i++)
head[i]  = new MatrixNode(TRUE, 0);
int CurrentRow = 0;
MatrixNode *last = head[0]; // last node in current row
MatrixNode* x = a.headnode->right;
while(x!=a.headnode) {
MatrixNode* y = x->right;
while(x!=y) {
if (y->triple.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
last = head[y->triple.row];
} //end of if
last = last->right = new MatrixNode(FALSE, &(y->triple));  // link new node into row list
head[y->triple.col]->next = head[y->triple.col]->next->down = last; // link into column list
CurrentRow = y->triple.row;
y=y->right;
}
x=x->next;
}

last->right = head[CurrentRow]; // close last row
for (int i = 0; i < a.headnode->triple.col; i++) head[i]->next->down = head[i]; // close all column lists
//link the header nodes together
for ( int i = 0; i < p-1 ; i++) head[i]->next = head[i+1];
head[p-1]->next = headnode;
headnode->right =  head[0];
delete [] head;
}

const Matrix Matrix::operator=(const Matrix& a)  {
headnode = new MatrixNode(FALSE,&(a.headnode->triple));
int p = max(a.headnode->triple.row,a.headnode->triple.col);
MatrixNodePtr *head = new MatrixNodePtr[p];  // initialize head nodes
for (int i = 0; i < p; i++)
head[i]  = new MatrixNode(TRUE, 0);
int CurrentRow = 0;
MatrixNode *last = head[0]; // last node in current row
MatrixNode* x = a.headnode->right;
while(x!=a.headnode) {
MatrixNode* y = x->right;
while(x!=y) {
if (y->triple.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
last = head[y->triple.row];
}
last = last->right = new MatrixNode(FALSE, &(y->triple));  // link new node into row list
head[y->triple.col]->next = head[y->triple.col]->next->down = last; // link into column list
CurrentRow = y->triple.row;
y=y->right;
}
x=x->next;
}

last->right = head[CurrentRow]; // close last row
for (int i = 0; i < a.headnode->triple.col; i++) head[i]->next->down = head[i]; // close all column lists
//link the header nodes together
for ( int i = 0; i < p-1 ; i++) head[i]->next = head[i+1];
head[p-1]->next = headnode;
headnode->right = head[0];
delete [] head;
return *this;
}

Matrix Matrix::operator +(const Matrix &a) const {
Matrix c;
if(headnode->triple.row!=a.headnode->triple.row || headnode->triple.col!=a.headnode->triple.col) {
throw domain_error(" 相加的两个矩阵的行数与列数对应不相等，无法相加！");
}
int k=0;  //for storing the new value of the headnode of result of adding
int p = max(headnode->triple.row,headnode->triple.col);
c.headnode = new MatrixNode(FALSE,&(headnode->triple));
MatrixNodePtr *head = new MatrixNodePtr[p];  // initialize head nodes
for(int i = 0;i < p;i++)
head[i] = new MatrixNode(TRUE,0);
int CurrentRow = 0;
MatrixNode* last = head[0];  //last node in current row
MatrixNode* x = headnode->right;
MatrixNode* y = a.headnode->right;

while(x!=headnode || y!=a.headnode) {
MatrixNode* b = x->right;
MatrixNode* e = y->right;
while(b!=x && e!=y) {
if(b->triple.col > e->triple.col) {
if (e->triple.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
last = head[e->triple.row];
}
last = last->right = new MatrixNode(FALSE, &(e->triple));  // link new node into row list
head[e->triple.col]->next = head[e->triple.col]->next->down = last; // link into column list
CurrentRow = e->triple.row;
e = e->right;
k++;
}
else if(b->triple.col < e->triple.col) {
if (b->triple.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
last = head[b->triple.row];
}
last = last->right = new MatrixNode(FALSE, &(b->triple));  // link new node into row list
head[b->triple.col]->next = head[b->triple.col]->next->down = last; // link into column list
CurrentRow = b->triple.row;
b = b->right;
k++;
}
else {
Triple t;
t.row = b->triple.row;
t.col = e->triple.col;
t.value = b->triple.value + e->triple.value;
if (t.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
last = head[t.row];
}
last = last->right = new MatrixNode(FALSE, &t);  // link new node into row list
head[t.col]->next = head[t.col]->next->down = last; // link into column list
CurrentRow = t.row;
b = b->right;
e = e->right;
k++;
}
}

while(b==x && e!=y) {
if (e->triple.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
last = head[e->triple.row];
}
last = last->right = new MatrixNode(FALSE, &(e->triple));  // link new node into row list
head[e->triple.col]->next = head[e->triple.col]->next->down = last; // link into column list
CurrentRow = e->triple.row;
e = e->right;
k++;
}


while(b!=x && e==y) {
if (b->triple.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
last = head[b->triple.row];
}
last = last->right = new MatrixNode(FALSE, &(b->triple));  // link new node into row list
head[b->triple.col]->next = head[b->triple.col]->next->down = last; // link into column list
CurrentRow = b->triple.row;
b = b->right;
k++;
}
x = x->next;
y = y->next;
}

c.headnode->triple.value = k;
last->right = head[CurrentRow]; // close last row
for (int i = 0; i < c.headnode->triple.col; i++) head[i]->next->down = head[i]; // close all column lists
//link the header nodes together
for ( int i = 0; i < p-1 ; i++) head[i]->next = head[i+1];
head[p-1]->next = c.headnode;
c.headnode->right = head[0];
delete [] head;
return c;
}

Matrix Matrix::operator-(const Matrix &a) const {
Matrix c;
if(headnode->triple.row!=a.headnode->triple.row || headnode->triple.col!=a.headnode->triple.col) {
throw domain_error(" 相减的两个矩阵的行数与列数对应不相等，无法相减！");
}
int k=0,p;
p = max(headnode->triple.row,headnode->triple.col);
c.headnode = new MatrixNode(FALSE,&(headnode->triple));
MatrixNodePtr *head = new MatrixNodePtr[p];  // initialize head nodes
for(int i = 0;i < p;i++)
head[i] = new MatrixNode(TRUE,0);
int CurrentRow = 0;
MatrixNode* last = head[0];  //last node in current row
MatrixNode* x = headnode->right;
MatrixNode* y = a.headnode->right;

while(x!=headnode || y!=a.headnode) {
MatrixNode* b = x->right;
MatrixNode* e = y->right;
while(b!=x && e!=y) {
if(b->triple.col > e->triple.col) {
Triple t;
t.row = e->triple.row;
t.col = e->triple.col;
t.value = -(e->triple.value);
if (e->triple.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
last = head[e->triple.row];
}
last = last->right = new MatrixNode(FALSE, &t);  // link new node into row list
head[t.col]->next = head[t.col]->next->down = last; // link into column list
CurrentRow = t.row;
e = e->right;
k++;
}
else if(b->triple.col < e->triple.col) {
if (b->triple.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
last = head[b->triple.row];
}
last = last->right = new MatrixNode(FALSE, &(b->triple));  // link new node into row list
head[b->triple.col]->next = head[b->triple.col]->next->down = last; // link into column list
CurrentRow = b->triple.row;
b = b->right;
k++;
}
else {
Triple t;
t.row = b->triple.row;
t.col = e->triple.col;
t.value = b->triple.value - e->triple.value;
if (t.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
last = head[t.row];
}
last = last->right = new MatrixNode(FALSE, &t);  // link new node into row list
head[t.col]->next = head[t.col]->next->down = last; // link into column list
CurrentRow = t.row;
b = b->right;
e = e->right;
k++;
}
}


while(b==x && e!=y) {
Triple t;
t.row = e->triple.row;
t.col = e->triple.col;
t.value = -(e->triple.value);
if (e->triple.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
last = head[e->triple.row];
}
last = last->right = new MatrixNode(FALSE, &t);  // link new node into row list
head[t.col]->next = head[t.col]->next->down = last; // link into column list
CurrentRow = t.row;
e = e->right;
k++;
}


while(b!=x && e==y) {
if (b->triple.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
last = head[b->triple.row];
}
last = last->right = new MatrixNode(FALSE, &(b->triple));  // link new node into row list
head[b->triple.col]->next = head[b->triple.col]->next->down = last; // link into column list
CurrentRow = b->triple.row;
b = b->right;
k++;
}
x = x->next;
y = y->next;
}
c.headnode->triple.value = k;
last->right = head[CurrentRow]; // close last row
for (int i = 0; i < c.headnode->triple.col; i++) head[i]->next->down = head[i]; // close all column lists
//link the header nodes together
for ( int i = 0; i < p-1 ; i++) head[i]->next = head[i+1];
head[p-1]->next = c.headnode;
c.headnode->right = head[0];
delete [] head;
return c;
}

Matrix Matrix::operator*(const Matrix& a) const {
Matrix c;
if(headnode->triple.col!=a.headnode->triple.row) {
throw domain_error(" 第一个矩阵的列数与与之相乘的矩阵的行数不相等，无法相乘！");

}
Triple s;
int k=0,p,m,n;
s.row = headnode->triple.row;
s.col = a.headnode->triple.col;
s.value = 0;  //just a temporary value of the headnode ,it will be changed later
p = max(a.headnode->triple.col,headnode->triple.row);
c.headnode = new MatrixNode(FALSE,&s);
MatrixNodePtr *head = new MatrixNodePtr[p];  // initialize head nodes
for(int i = 0;i < p;i++)
head[i] = new MatrixNode(TRUE,0);
int CurrentRow = 0;
MatrixNode* last = head[0];   //last node in current row
MatrixNode* x = headnode->right;
while(x!=headnode) {
int j = a.headnode->triple.col;  //this is my puzzle but necessary when I debug it. The same as the above :Transpose()

MatrixNode* y = a.headnode->right;

while(y!=a.headnode&&j>0) {

MatrixNode* e = y->down;
int sum = 0;  //for storing the new value of the multply of each row and col
MatrixNode* b = x->right;

while(e!=y && b!=x) {  //the key step for multiply
m = b->triple.row;
n = e->triple.col;
if(b->triple.col == e->triple.row) {
sum += ((b->triple.value)*(e->triple.value));
e = e->down;
b = b->right;
}
else if(b->triple.col < e->triple.row)
b = b->right;
else
e = e->down;
}


if(sum!=0) {  //store the result to Matrix c
Triple t;
t.row = m;
t.col = n;
t.value = sum;
if (t.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
CurrentRow = t.row;
last = head[CurrentRow];
}
last = last->right = new MatrixNode(FALSE, &t);  // link new node into row list
head[t.col]->next = head[t.col]->next->down = last; // link into column list
k++;

}
y = y->next;
j--;
}
x = x->next;
}

c.headnode->triple.value = k;
last->right = head[CurrentRow]; // close last row
for (int i = 0; i < c.headnode->triple.col; i++)
head[i]->next->down = head[i]; // close all column lists
//link the header nodes together
for ( int i = 0; i < p-1 ; i++)
head[i]->next = head[i+1];
head[p-1]->next = c.headnode;
c.headnode->right = head[0];
delete [] head;
return c;
}
Matrix Matrix::Transpose() const {
Matrix c;
if (!headnode) {
throw domain_error("Matrix destroyed");
}
Triple s;
s.row = headnode->triple.col;
s.col = headnode->triple.row;
s.value = headnode->triple.value;
int p = max(headnode->triple.row,headnode->triple.col);
c.headnode = new MatrixNode(FALSE,&s);
MatrixNodePtr *head = new MatrixNodePtr[p];  // initialize head nodes
for(int i = 0;i < p;i++)
head[i] = new MatrixNode(TRUE,0);
int CurrentRow = 0;
MatrixNode* last = head[0];   //last node in current row
MatrixNode* x = headnode->right;

int j = headnode->triple.col;

while(x!=headnode && j > 0) {
MatrixNode* y = x->down; //warning down, not right
while(y!=x) {
Triple t;
t.row = y->triple.col;
t.col = y->triple.row;
t.value = y->triple.value;

if(t.row > CurrentRow) {  //close current row
last->right = head[CurrentRow];
CurrentRow = t.row;
last = head[CurrentRow];
}

last=last->right=new MatrixNode(FALSE,&t);   // link new node into row list
head[t.col]->next=head[t.col]->next->down=last;  // link into column list
y = y->down;
}
x = x->next;
j--;
}
last->right = head[CurrentRow]; // close last row
for (int i = 0; i < c.headnode->triple.col; i++)
head[i]->next->down = head[i]; // close all column lists
//link the header nodes together
for ( int i = 0; i < p-1 ; i++)
head[i]->next = head[i+1];
head[p-1]->next = c.headnode;
c.headnode->right = head[0];
delete [] head;
return c;
}


istream& operator>>(istream& is, Matrix& matrix)
// Read in a matrix and set up its linked representation.
// An auxiliary array \fIhead\fR is used.
{
Triple s;
int p;
cout <<  "请依次输入矩阵的行数，列数和非零元素个数："<<endl;
input:		is >> s.row >> s.col >> s.value;   // matrix dimensions ,input is just a mark name
if (s.row > s.col)
p = s.row;
else
p = s.col;

// set up headnode for list of head nodes.
matrix.headnode = new MatrixNode(FALSE, &s);

if (p == 0) {
matrix.headnode->right = matrix.headnode;
cout<<"请重新输入矩阵的行数，列数和非零元素值："<<endl;
goto input;  //jump to input

}
// at least one row or column

MatrixNodePtr *head = new MatrixNodePtr[p];  // initialize head nodes

for (int i = 0; i < p; i++)
head[i]  = new MatrixNode(TRUE, 0);

int CurrentRow = 0;
MatrixNode *last = head[0]; // last node in current row

cout<<"请依次输入非零元素所在的行，列和值(一定要按行序依次输入！)："<<endl;
for (int i = 0; i < s.value; i++)  // input triples
{
Triple t;
is >> t.row >> t.col >> t.value;
if (t.row > CurrentRow) {  // close current row
last->right = head[CurrentRow];
CurrentRow = t.row;
last = head[CurrentRow];
}
last = last->right = new MatrixNode(FALSE, &t);  // link new node into row list
head[t.col]->next = head[t.col]->next->down = last; // link into column list
}

last->right = head[CurrentRow]; // close last row

for (int i = 0; i < s.col; i++) head[i]->next->down = head[i]; // close all column lists

// link the head nodes together
for ( int i = 0; i < p-1 ; i++) head[i]->next = head[i+1];
head[p-1]->next = matrix.headnode;
matrix.headnode->right =  head[0];
delete [] head;
return is;
}

ostream& operator<<(ostream& os, Matrix& m)
{
/*   print all value by order ,but there is a shortcome that they may cannot align:
0  0  4
0  23  3
21  0  1
*/
int n = m.headnode->triple.row;
MatrixNode *x = m.headnode;
if (!x) return os << "Matrix destroyed" << endl;
x = x->right;
os << endl;
while (x != m.headnode && n > 0) {
MatrixNode* y = x->right;
int j = -1; //a mark for printing the zero and value

while(y!=x ) {
for(int i = 0;i < y->triple.col-j-1;i++)
os << 0 << "\t";
os << y->triple.value << "\t";
j = y->triple.col;
y = y->right;
}
//print the rest zero
for(int i = 0;i < m.headnode->triple.col-j-1;i++)
os << 0 << "\t";
os<<endl;

n--;
x = x->next;
}
return os;

}

MatrixNode *av = 0;   // field. @av@ is a global variable of type @MatrixNode\(**@ and points to its first node.

Matrix::~Matrix()
// Return all nodes to the @av@ list. This list is a chain linked via the \fIright\fR

{
if(!headnode->right)
return; // no nodes to dispose
MatrixNode *x = headnode->right;
MatrixNode *y;
headnode->right = av; av = headnode; // return @headnode@

while (x != headnode) { // erase by rows

y = x->right;
x->right = av;
av = y;
x = x->next; // next row

}
headnode = 0;
}


