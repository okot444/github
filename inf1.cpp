#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
static const int M=9;

class skin;
struct node;
 
struct xy
{
	int x;
	int y;
};

class cell //абстрактный класс, не позволяет содавать объекты, имеет хотя бы 1 чисто виртуальную ф-ю
{
	public:
        cell(int x, int y) { point.x = x; point.y = y;} 
        virtual int state () const = 0; //состояние клетки
		virtual cell * changestate (skin& S) = 0; //клетка переходит к следующему состоянию
	protected:
		void setxy(int i, int j); //установить координаты клетки 
		xy point;
		//int x;//координаты клетки на участке кожи
		//int y;
};
class healthy: public cell
{
	public:
		healthy(int i, int j):cell(i,j){} ; //конструктор по умолчанию
		int state () const { return 0; } //вид клетки
		cell * changestate(skin& S) {return this;} //клетка переходит к следующему состоянию
};
class immune: public cell
{
	public:
		immune(int i, int j, int s=4):cell(i,j),count(i) {} //конструктор по умолчанию
		int state () const { return 1; } //состояние клетки
		cell * changestate(skin& S); //клетка переходит к следующему состоянию
	protected:
		int count; // счётчик
};
cell * immune::changestate(skin& S) //изменение состояния клетки
{
	count--;
	cell * q = this;
	if (count == 0) // иммунная переходит в здоровую
	//(удалить клетку и создать новую)
	{
		q=new healthy(point.x, point.y);
		delete this;
	}
	return q;
}
class infected: public immune
{
	public:
		infected(int i, int j, int s=6): immune(i,j,s){} 
		int state () const { return 2; } //вид клетки
		cell * changestate(skin& S); 
	protected:
		void infect(skin& S); // заражение
};

cell * infected::changestate(skin& S)  //изменение состояния клетки
// заражает рядом находящиеся клетки
{
	infect(S);
	count--;
	cell * q = this;
	if (count == 0){
		q = new immune(point.x, point.y);
		delete this;
	}
	return q;
}

struct node
{
	cell ** info; 
	node * next;
};
class skin
{
	public:
		
		skin(); 
		~skin();
		void print() const; //вывод на печать
		friend class infected;
		cell * getcell(int i, int j); //получить клетку с координатами i, j
		node * gethead(); //получить текущее значение головы (для уменьшения счётчика в конце цикла)
		void MakeInf(int i, int j); //удалить предыдущую клетку и создать новую заражённую
		void infection(); // заражение клеток, проход по списку
	private:
		cell * sk[M][M]; // 
		//cell sk[M][M];
		node * head; //список заражённых и иммунных клеток
}; 

void infected::infect(skin& s) //заражение
{
	int i,j, random_number;
    cell * cc;
	for(i=-1; i<2; i++) //заражение рядом лежащих (здоровых) клеток
        for(j=-1; j<2; j++){ // 
			cc = s.getcell(point.x+i,point.y+j);
			// random_number = first_value + rand() % last_value;  last_value - ширина выборки
			random_number = rand() %2;
			if (  cc->state() == 0 && random_number) // 
			//клетка здоровая, вероятность != 0, 
                s.MakeInf(point.x+i, point.y+j); 
		}
}
skin::skin()
{
	int i, j;
	for(i=1; i<M-1; i++)
		for(j=1; j<M-1; j++)
				sk[i][j]=new healthy(i,j);
	delete sk[M/2][M/2]; //центральная
	sk[M/2][M/2] = new infected (M/2,M/2);
	j = 0;
	for (i=0; i<M;i++)
		sk[i][j] = new infected (i,j);
	j = M-1;
	for (i=0;i<M; i++)
		sk[i][j] = new infected (i,j);
	i = 0;
	for (j=1;j<M-1; j++)
		sk[i][j] = new infected (i,j);
	i = M-1;
	for (j=1;j<M-1; j++)
		sk[i][j] = new infected (i,j);
    head = new node;
    head->info = &(sk[M/2][M/2]); // изначально заражена центральная клетка
    head->next = NULL;
    
    
}
skin:: ~skin()
{
	int i, j;
	for(i=0; i<M; i++)
		for(j=0; j<M; j++)
			delete sk[i][j];
}

cell * skin::getcell(int i, int j) //получить клетку с координатами i, j
{
	if (i>=0 && i<M && j>=0 && j<M)
		return sk[i][j];
	return 0;
}
//удалить предыдущую клетку и создать новую заражённую
void skin:: MakeInf(int i, int j)
{
	delete sk[i][j];
	sk[i][j]= new infected(i,j);
    //head=addhead(head, &(s[i][j]));
	node*q = new node;
	q->info  = &sk[i][j];
	q->next = head;
	head = q;

}
void skin:: infection() //прохождение по списку и обработка счётчиков
{
	node * p;
	int f, f1;
//	while ( head ) // пока список зараженных не пустой
//	{
	for (int i=0; i<9; i++){
		p = head;
		f = 0;
		while ( p ) // проход по списку заражённых
		{
			*(p->info) = (*(p->info))->changestate(*this);
			p=p->next;
		}
		if ((*(head->info))->state()==0)
			head=0;
		cout<<endl;
		print();
}
//cout<<(*(head->info))->state()<<endl;
  //  }
    //node* p = head;
   // *(p->info) = (*(p->info))->changestate(*this);
   // print();
}

void skin::print() const //вывод на печать
{
	int l;
	int i, j;
	for(i=0; i<M; i++){
		for(j=0; j<M; j++)
            cout<< sk[i][j]->state();
		cout<<endl;
    }
    cout<<endl;
}
int main()
{
	skin a;
	a.print();
	a.infection();
	//a.infection();
}
