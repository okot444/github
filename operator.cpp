// ��������� ������
// ����������� � ��������
/*
 ���������� :
 []
 + (assert ������� ����������)
 * ( ����������)
 =
 +=
 *=
 ! (����������������)   ������� ���������� �� �������� ������� ������� ����� �� �������.
 <<
 
1 2		1 3 5
3 4		2 4 6
5 6
 ]
 // ��� ������� �����������
 */
 //�������� 
#include <iostream>
#include <assert.h>
using namespace std;
class matrix;
class row
{
public:
    friend class matrix; // ������ � ������������
    int& operator [] (int i);// ���������� [] (int&)
private:
    int* copyr (const row& s);
    row (int n); // ��������� matrix ��� row ������
    int stl; // ������ ������ (���-�� �������)
    int* str; // ��-�� �� ������
};
int* row:: copyr (const row& s)// ����������� ������
{
    for ( int i=0; i<stl; i++)
        str[i] = s.str[i];
    return str;
}
row:: row (int n) : stl(n) // n- ������ ������,  �����������
{
    str = new int [n];// ������� ������ ��� ������
    assert (str !=0);
}
int& row::operator [] (int i)
{
    assert (i<=stl && i>=0);
    return str[i];
}

class matrix
{
public:
    matrix (int n = 0 , int j = 0 );
    ~matrix();
    matrix(const matrix&  a);
    
   	void values ();
    friend ostream& operator << (ostream& out, const matrix& a);
    matrix operator + (const matrix& a);
    matrix& operator += (const matrix& a);
    matrix operator * (const matrix& a);
    matrix& operator *= (const matrix& a);
    matrix& operator = (const matrix& a);
    row& operator [] (int j) const;
    matrix& operator ! ();
    
private:
	void print_row(int k) const;
	row** copyd( row** dst, row** const src, int src_len);// ����������� 
    void copy(row** dst, row** const src, int src_len);
    row** allocate(int len, int stl);
    void del( row**m, int len);
    
    row** addition(row** dst, int len,   row**  const src, int src_len );
    row** multiplication (row** dst, int len, row** const src, int src_len);
    row** transpose(  row** m, int sz1, int sz2 );
    row** rectangle(row** mas, int sz1, int sz2);
    void quadrate(row** mas, int sz1, int sz2);
    int calculate_ij (row**a,row**b,int len, int i, int j);
    
    row** m;
    int len; // ���-�� �����
};
matrix::matrix (int n, int j) : len (n)// �����������, n -  ������ ������, j- ���-�� ��������
{
    m = new row* [len];
    for ( int i=0; i<len ; i++)
        m[i] = new row(j);
    //cout<<"!"<<endl;
}
matrix:: matrix(const matrix& a): len (a.len) // ����������� ����������
{
    m = new row * [len];
    for (int i=0; i<len; i++){
        m[i] = new row(a[0].stl);
        m[i]->copyr(a[i]);   // �������� �������
    }
} 
void matrix:: print_row (int k) const //  k - ������ �� ������
{
    for (int i=0; i<m[0]->stl; i++)
        cout<<" "<<m[k]->str[i]<<"";
    //cout<<endl;
}
row** matrix::copyd(row** dst, row** const src, int src_len) // ����������� � ������� ������ �����������
// (� ���������� ������) ��� ������������
{
	row ** mx = allocate(src_len, src[0]->stl); // �������� ������ ��� ����� �������
	for (int i=0; i<src_len; i++)
		mx[i]->copyr(*src[i]);   // �������� �������
	del(dst,len);
	dst = mx; // �������� ������ �������
	len = src_len;
	return dst;
}
void matrix::copy( row** dst, row** const src, int sz1) // �����������
{
    //���������� �������
    for (int i=0; i<sz1; i++)
        dst[i]->copyr(*src[i]);//
}
row** matrix::allocate( int len, int stl)  // ������� �������� len x stl
// ��������� ������
{
    row ** mx = new row *[len]; // �������� ������ ��� ����� �������
    for (int i=0; i<len; i++)
		mx[i] = new row(stl);
    return mx;
}
void matrix:: del( row**mx, int len)// �������� �������
{
	for (int i=0; i<len; i++){// ������� ������ �������
		delete[] mx[i]->str;
		delete[] mx[i];	
	}
	delete[] mx;
	
}
row** matrix::rectangle(row** mas, int sz1, int sz2)
{
	row ** mx = allocate(sz2, sz1); // �������� ������ ��� ����� �������
    for (int i=0; i<sz2; i++)
        for (int j=0; j<sz1; j++)
            (*mx[i])[j] = (*mas[j])[i];
    del(mas,sz1);
    len = sz2; // �������� ������ ������� ???
    mas = mx;
    return mas;
}
void matrix::quadrate(row** mas, int sz1, int sz2)
{
	int i, j,temp;
    for(i=0; i<sz1; i++)
        for(j=i+1; j<sz2; j++){ // ������������ ��-�� �� ���������� // (sz2=sz1)
            temp = (*mas[i])[j];
            (*mas[i])[j] = (*mas[j])[i]; 
            (*mas[j])[i] = temp;
		}
}
row** matrix:: transpose( row** mas, int sz1, int sz2) // ��������������� ������������� �������
{
	if (sz1 != 0){ // ������� �� ������
    	if (sz1 != sz2) //  �������������
    	{
    		cout<< "rectangle"<<endl;
	        mas = rectangle(mas,sz1,sz2);
	    }
	    else// ����������
	    	quadrate(mas,sz1,sz2);
	    }
    return mas;
}
matrix& matrix:: operator ! ()
{
	m = transpose(m, len, m[0]->stl);
	return *this;
}
row** matrix:: addition(row** dst, int len, row** const src, int src_len) //  +
{
   // if (len == src_len){ // ���������� ����������
    for ( int i=0; i<len; i++ )
        for ( int j=0; j < (*src)->stl; j++ )
            (*this)[i][j] += (*src[i])[j];
    //}
    return dst;
}
int matrix::calculate_ij (row**a,row**b,int len, int i, int j)// ������� ij �������� ��� ���������	
{
	int s=0; // �������� 
	for (int k=0; k<len; k++)
		s += (*a[i])[k]* (*b[k])[j];
	return s;
}
row** matrix::multiplication (row** dst, int len, row** const src, int src_len) // *
{
	row ** mx = allocate(len, (*src)->stl);
	for ( int i=0; i<len; i++)
		for (int j=0; j<(*src)->stl; j++)
			(*mx[i])[j] = calculate_ij(dst,src,src_len,i,j); // ������� ij ��������		
	del(dst,len);
	dst = mx; // �������� ������ �������
    return dst;
}
matrix::~matrix()// ����������
{
    int i=0;
    for (; i<len; i++){
    	delete[] m[i]->str; // �������� ������
        delete[] m[i]; 
    }
    delete[] m;
}
matrix matrix:: operator + ( const matrix& a ) // �������� ������
{
    assert (len == a.len); // ���������� ������� ���������� �����������
    matrix temp (*this);
    temp += a;
    return temp;
}
matrix& matrix:: operator += ( const matrix& a )
{
    m = addition(m,len,a.m,a.len);
    return *this;
}
matrix matrix:: operator * ( const matrix& a ) // ��������� ������
{
    assert (m[0]->stl == a.len); // ��������� �����������
    matrix temp (*this);
    temp *= a;
    return temp;
}
matrix& matrix:: operator *= ( const matrix& a )
{
	assert (m[0]->stl == a.len);
    m = multiplication(m,len,a.m,a.len);
    return *this;
}
matrix& matrix:: operator = (const matrix& a)
{
    if (&a != this) // ���������, ��� �� ����������� ������ ����
        if (len == a.len) // ���� ����������
            copy(m,a.m,a.len);
        else 
        	m = copyd(m,a.m,a.len);
    return *this;
}
void matrix::values ()
{
	int k=0;
	for ( int i=0; i<len; i++)
		for (int j=0; j<m[0]->stl; j++)
			(*m[i])[j] = k++;
}

ostream& operator << (ostream& out, const matrix& a)//?   ����� � �����
{
    cout<< "<<"<<endl;
    for (int i=0; i<a.len; i++){
        a.print_row(i);
        out<< endl;
    }
    return out;
}

row& matrix::operator [] (int j) const
{
    assert (j<=len && j>=0); //
    return *m[j];//?
}
int main()
{
    matrix m (3,3), c(3,4);
    
    m.values(),c.values();
    c[0][0] = 0;
   // cout<<"m"<<m<<endl;
    
	matrix m1(m);
	cout<<"m1(m) "<<m1;
	cout<<"!m1"<<(!m1)<<endl<<endl;
    cout<<"m"<<m<<"c"<<c<<endl;
    cout<<"m*c"<<m*c<<endl;
    matrix q(1,1);
    q=m*c;
	cout<<!q<<endl;
    cout<<"!m*c"<<(!(m*c))<<endl;
    matrix t(3,3);
    t.values();
    cout<<"t"<<t<<endl;
    cout<<"m+t"<<m+t<<endl;
    
}

/*ostream& operator << (ostream& out, const matrix& a)
{
    cout<< "<<"<<endl;
    for (int i=0; i<a.len; i++){
        a.m[i]->print_row();
        out<< endl;
    }
    return out;
}*/

/*void matrix:: print () const
{
    cout<< "matrix: "<< endl;
    for (int i=0; i<len; i++){
        m[i]->print_row();
        cout<<endl;
    }
    cout<<endl;
}*/

/*row** matrix::multiplication (row** dst, int len, row** const src, int src_len) // *
{
	row ** mx = allocate(len, (*src)->length());
	for ( int i=0; i<len; i++)
		for (int j=0; j<(*src)->length(); j++)
			(*mx[i])[j] =0;
	for ( int i=0; i<len; i++)
		for (int j=0; j<(*src)->length(); j++){
			
			for (int k=0; k<src_len; k++){
			(*mx[i])[j] += (*dst[i])[k]*(*src[k])[j];
			//cout<< "mx "<<i<<j<<" "<<(*mx[i])[j]<<" += "<<"dst "<< i<<k<<" "<<(*dst[i])[k]<<" * "
		//	<< "src "<<k<<j<<" "<<(*src[k])[j]<<endl;
			}
		}
	del(dst,len);
	dst = mx; // �������� ������ �������
    return dst;
}*/

