#include <iostream>
#include<string.h>
#include <assert.h>
// ������
// len - ����� ��� ������� \0
using namespace std;
class strings
{
public:
    strings (const char*s0); // ����������� ��� ������ ""
    strings (); // ����������� �� ���������
    strings (const strings &str); // ���������� ����������
    ~strings() {delete[]s;}; // ����������
    void print () {cout << s << endl;} // ������
    int length() { return len;}//  ����������� �����
    int cmp(strings &ss){ return strcmp(s,ss.s);} // ��������� �����
    strings &cpy( const strings &ss); // ����������� ������ (�� ss � s)
    strings &cat( const strings &ss); // ��������� �����
    strings &str(const strings &s1, const strings &s2); // ����� ��������� s2 (� s1)
private:
    int len;
    char *s;
};
strings::strings(const char*s0):len(strlen(s0)) // ����������� ��� ������ "" (������ ������)
{
    s=new char [len+1];
    assert(s!=0);
    strcpy(s,s0);
}
strings::strings(const strings &str):len(str.len) // ����������� ���������� �������� ������ ��� ������(������ s �������� len)
{
    s=new char[len+1];
    assert(s!=0);
    strcpy(s,str.s);
}
strings::strings():len(0) // ����������� �� ��-� (������ ������ )
{
    s=new char [len+1];
    s[0]='\0';
    assert(s!=0);
}
strings &strings:: cpy(const strings &ss) // ����������� ������ (�� ss � s)
{
    if (this!=&ss) // �� �������� ������ ���� � ����
    {
        char *s0; // ������ ����� ������
        len=ss.len;
        s0 = new char[len+1]; // �������� ������ (+ '\0' )
        assert(s!=0);
        strcpy(s0, ss.s);
        delete[]s;
        s=s0;
    }
    return *this;
}
strings &strings:: cat(const strings &ss) // ��������� �����
{ 
    len+=ss.len; // ����������� �����
    char *s0; // ������ ����� ������
    s0=new char [len+1]; // �������� ������ (+ '\0' )
    strcpy(s0,s); // ��������  ��������
    strcat(s0,ss.s); // �������� ������ ������
    s=s0;
    return *this;
}
strings &strings:: str(const strings &s1, const strings &s2)// ����� ��������� s2 (� s1)  ??
{
    char*p=strstr(s1.s,s2.s); // ������� ���������
    if (p==0) // ��������� ���
    {
        len=0;
        char *s0; // ������ ����� ������ (������)
        s0=new char [1];
        s0[0]='\0';
        delete[]s;
        s=s0;
        return *this;
    }
    len=strlen(p); // ���������� �����
    char *s0; // ������ ����� ������
	s0=new char [len+1]; // �������� ������ (+ '\0' )
    strcpy(s0,p);
    delete[]s;
    s=s0;
    return *this;
}
int main()
{
    strings a("01003"),b,c("00"),d("5"),f;
    a.cpy(a).print();
    b.print();
    
    a.cat(b.cpy(c)).print();
    
    b.str(a,c).print();
    
    f.cpy(b.str(a,c)).print();
    
    int len=a.length();
    cout<<"len "<<len<<endl;
    int cmp=b.cmp(f);
    cout<<"cmp "<<cmp<<endl;
    
}
