// Быстрая сортировка
/*

	массив
	7 4 -3 0 9 10
	
*/
#include <iostream>
#include <assert.h>
using namespace std;


template <class Atype> class man
{
	public:
		man ();
		Atype& operator [] (int i) const; // name/adress
		friend ostream& operator << (ostream& out, const man <Atype> &ob)
		// реализация friend должна быть в классе
		{
			int i=0;
			for (;i<ob.n; i++)
				out<<ob.name[i]<<' ';
			out<<endl;
			return out;
		}
	private:
		static const int n = 30; //???
		char name[n];
		char* adress;	// 40
};
template <class Atype> man <Atype>:: man () // конструктор
{
	name[n];
	
}
template <class Atype> Atype& man<Atype>:: operator [] (int i) const// name
{
	assert (i <= n && i>=0); //
    return *name;
}
template <class Stype> void qsort (Stype*item, int left, int right)
{
	int i = left, j = right;
	Stype x = item [(left + right) / 2], y;
	do 
	{
		while ( item[i]<x && i<right )
			i++;
		while (x<item[j] && j>left)
			j--;
		if (i<=j){
			y = item [i];
			item[i] = item[j];
			item[j] = y;
			i++;
			j--;
		}
	} while (i <= j); // пока границы не пересекутся
	if ( left < j )
		qsort( item, left, j);
	if ( i < right )
		qsort (item, i, right);
}


template <class Stype> void print (Stype* item, int size)
{
	for (int i=0; i<size; i++)
		cout<< item[i]<< "  ";
	cout<<endl;
}




int main ()
{
	//int a[6] = {7,4,-3,0,9,10}; 
//	float b[7] = { 0.5, 2.3, 1.7, -5.2, 8.0, 10.2, 7};
//	char c[5] = { 'q', 't', 'w', 'e', 'r'}; // создаются шаблоны qsort char  и print сhar
	man <char> men[5];
	print(men,1); 
	
	/*print (a,6);
	qsort(a,0,5);
	print (a,6);
	print (b,7);
	qsort(b,0,6);
	print (b,7);
	print (c,5);
	qsort(c,0,4);
	print (c,5);*/
	
}
