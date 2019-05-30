#include <iostream>
#include<string.h>
#include <assert.h>
// Строка
// len - длина без символа \0
using namespace std;
class strings
{
public:
    strings (const char*s0); // конструктор для строки ""
    strings (); // конструктор по умолчанию
    strings (const strings &str); // контруктор копирующий
    ~strings() {delete[]s;}; // деструктор
    void print () {cout << s << endl;} // печать
    int length() { return len;}//  определение длины
    int cmp(strings &ss){ return strcmp(s,ss.s);} // сравнение строк
    strings &cpy( const strings &ss); // копирование строки (из ss в s)
    strings &cat( const strings &ss); // сцепление строк
    strings &str(const strings &s1, const strings &s2); // поиск подстроки s2 (в s1)
private:
    int len;
    char *s;
};
strings::strings(const char*s0):len(strlen(s0)) // конструктор для строки "" (создаёт объект)
{
    s=new char [len+1];
    assert(s!=0);
    strcpy(s,s0);
}
strings::strings(const strings &str):len(str.len) // конструктор копирующий выделяет память под объект(строка s размером len)
{
    s=new char[len+1];
    assert(s!=0);
    strcpy(s,str.s);
}
strings::strings():len(0) // конструктор по ум-ю (пустая строка )
{
    s=new char [len+1];
    s[0]='\0';
    assert(s!=0);
}
strings &strings:: cpy(const strings &ss) // копирование строки (из ss в s)
{
    if (this!=&ss) // не копируем строку саму в себя
    {
        char *s0; // создаём новую строку
        len=ss.len;
        s0 = new char[len+1]; // выделяем память (+ '\0' )
        assert(s!=0);
        strcpy(s0, ss.s);
        delete[]s;
        s=s0;
    }
    return *this;
}
strings &strings:: cat(const strings &ss) // сцепление строк
{ 
    len+=ss.len; // увеличиваем длину
    char *s0; // создаём новую строку
    s0=new char [len+1]; // выделяем память (+ '\0' )
    strcpy(s0,s); // копируем  исходную
    strcat(s0,ss.s); // сцепляем вторую строку
    s=s0;
    return *this;
}
strings &strings:: str(const strings &s1, const strings &s2)// поиск подстроки s2 (в s1)  ??
{
    char*p=strstr(s1.s,s2.s); // находим указатель
    if (p==0) // подстроки нет
    {
        len=0;
        char *s0; // создаём новую строку (путсую)
        s0=new char [1];
        s0[0]='\0';
        delete[]s;
        s=s0;
        return *this;
    }
    len=strlen(p); // определяем длину
    char *s0; // создаём новую строку
	s0=new char [len+1]; // выделяем память (+ '\0' )
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
