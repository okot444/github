// Карты
/*
достоинство 
 0 - 6
 1 - 7
 2 - 8
 3 - 9
 4 - 10
 5 - Валет
 6 - Дама
 7 - Король
 8 - Туз
масть
 0 - черви
 1 - бубны
 2 - трефы
 3 - пики
 */
#include <iostream>
#include <assert.h>
#include <time.h>
using namespace std;
class desk;
class queue;
class card // класс карты
{
private:
    int point;  // индекс
    int next;   // след. карта
public:
    card( int i = -1 ); //
    void print() const ; //  печать карты
    int setpt(const int i) { return point = i; } // изменяет возвращает point
    int setnt(const int i) { return next = i; } // изменяет возвращает  next
    int getpt() { return point; }//возвращает point
    int getnt() { return next; }//возвращает  next
    int compare (card &c1);// сравнение карт
};
card::card ( int i)
{
    point = i;
    next = i;
}
void card::print() const
{
    
    switch (point %9) {
        case 0:
            cout << "6" ; break;
        case 1:
            cout << "7" ; break;
        case 2:
            cout << "8" ; break;
        case 3:
            cout << "9" ; break;
        case 4:
            cout << "10" ; break;
        case 5:
            cout << "V" ; break;
        case 6:
            cout << "D" ; break;
        case 7:
            cout << "K" ; break;
        case 8:
            cout << "T" ; break;
        default:
            break;
    }
    switch (point%4) {
        case 0:
            cout << "♥ " ; break;
        case 1:
            cout << "♦ ";break;
        case 2:
            cout << "♣ ";break;            
        case 3:
            cout << "♠ ";break;
        default:
            break;
    }
    cout<<next<<endl;
}
// = 0  (c1 = c2)
// < 0  (c1 < c2)
// > 0  (c1 > c2)
int card::compare (card &c2)// ф-я сравнения карт
{
    if (point%9 < c2.getpt()%9)
        return -1;
    else
    {
        if (point%9 > c2.getpt()%9)
            return 1;
        else
            return 0;
    }
}
class desk // класс колода
{
private:
    static const int n = 36;
    card m[n];  // массив 36 карт
public:
    desk (); // конструктор
    void shufflee (); // перемешать карты
    void shufflee1 (); // перемешать карты
    void shufflee2 (); // перемешать карты
    void handout (queue &q1, queue &q2); // раздать карты
    void print() const; //  печать колоды
    card &getcard (int i) { return m[i]; } // получает индекс карты и возвращает карту в колоде
};
void desk::print() const //  печать колоды
{
    for (int i = 0; i < n; i++)
        m[i].print ();
    cout<<'.'<<endl;
}
void desk :: shufflee() // перемешать карты
{
    cout<<"shuffle"<<endl;
    srand(time(NULL));
    for (int i=0; i<n; i++)
    {
        int j = rand()%n;
        int temp = m[i].getpt();
        m[i].setpt(m[j].getpt()); //  меняем местами i-тое и j-тое
        m[j].setpt(temp);
    }
}
void desk ::shufflee1 () // перемешать карты
{
    cout<<"shuffle1"<<endl;
}
desk::desk () // конструктор
{
    for (int i = 0; i < n; i++)
        //card(i) = i;
        m[i] = i;
}
//
class queue // класс очередь
{
public:
	queue () { tail = -1;}
    int empty() { return tail == -1; } // пустота
    int full() { return 0; } //полнота
    queue& enqueue(card &c);// добавление в очередь
    card& dequeue();// извлечение из хвоста // возвращает tail->next
    card& top() { return u->getcard(u->getcard(tail).getnt()); }// возвращает верхнюю карту в очереди
    void qprint() const;// печать очереди
    static void reset (desk &m) { u = &m;}
    queue& take_all (queue &table); // все карты со стола передать одному игроку
    int tail;
    static desk * u;// ук-ль на колоду
private:
    
    
};
desk* queue::u = 0;
card& queue::dequeue() // взять из очереди карту (возвращает карту), перед вызовом проверить на пустоту
// берём из головы, tail не изменяется (если карта не последняя)
{
    if ( u->getcard(tail).getnt() == tail)
    {
        int temp = tail;
        tail = -1;
        return u->getcard(temp);
    }
	int temp = (u->getcard(tail).getnt());// сохраняем next хвоста
	u->getcard(tail).setnt(u->getcard(temp).getnt());//изменяем next в хвосте
	u->getcard(temp).setnt(temp);// изменяем next вытянутой карты
	return u->getcard(temp);  // возвращаем карту
}
queue &queue:: enqueue(card &c) // добавление в очередь , перед вызовом проверить на полноту
{
    if (tail == -1){
        tail = c.getnt();
        return *this;
    }
	int temp = u->getcard(tail).getnt();
	u->getcard(tail).setnt(c.getnt()); // изменяем next в хвосте
	c.setnt(temp);// изменяем next в добавляемой карте
	tail=u->getcard(tail).getnt();// изменяем хвост
    
    return *this;
}
queue &queue:: take_all (queue &table)// взять карты со стола
{
    if (tail != -1){ // если у игрока есть карты
        int temp = u->getcard(tail).getnt(); // сохраняем next последней карты игрока
        u->getcard(tail).setnt((table.u)->getcard(table.tail).getnt()); // изменяем next последней карты игрока
        (table.u)->getcard(table.tail).setnt(temp);// изменяем next последней карты на столе
    }
    tail = table.tail;
    table.tail = -1; // обнуляем стол
    return *this;
}
void queue ::qprint() const // печать очереди
{
    if (tail == -1) // ???
    {
        cout<< "empty "<< endl;
        return ;
    }
    int p = u->getcard(tail).getnt();
    while (p != tail) // доходим до последнего
    {
        u->getcard(p).print();
        p = u->getcard(p).getnt();
    }
    u->getcard(p).print();
    cout<<endl;
}
void desk:: handout(queue &q1, queue &q2) // раздать карты
{
    cout<<"handout"<<endl;
    for (int i=0; i<n; i+=2)
        q1.enqueue(m[i]);
    for (int i=1; i<n-1; i+=2)
        q2.enqueue(m[i]);
}
void add_table (queue &q,card &c1, card &c2)
{
    
    if (!q.full())
        q.enqueue(c1);
    if (!q.full())
        q.enqueue(c2);
    cout <<"table "<<endl;q.qprint();cout<<endl;
}
void check(queue &q1,queue &q2) // проверить есть ли у игроков карты
{
    if (q1.empty())
        q1.enqueue(q2.dequeue()); // кладём к 1му игроку карту от 2го
    if (q2.empty())
        q2.enqueue(q1.dequeue()); // или кладём ко 2му игроку карту от 1го
}
void cmp(queue &q1,queue &q2,queue &q) // сравниваем карты и добавляем на стол
{
    if (q1.top().compare(q2.top()) < 0) // -1
    {
        cout<<q1.top().compare(q2.top())<<endl;
        add_table(q, q1.dequeue(), q2.dequeue());
        q2.take_all(q);
        q1.qprint();
        q2.qprint();
    }
    else
        if (q1.top().compare(q2.top()) > 0) // 1
        {
            cout<<q1.top().compare(q2.top())<<endl;
            add_table(q, q1.dequeue(), q2.dequeue());
            q1.take_all(q);
            q1.qprint();
            q2.qprint();
        }
        else // 0
        {
            cout<<q1.top().compare(q2.top())<<endl;
            add_table(q, q1.dequeue(), q2.dequeue());
            check (q1,q2); // проверить есть ли у игроков карты
            add_table(q, q1.dequeue(), q2.dequeue());
            check (q1,q2);
            cmp(q1,q2,q);
        }
}
/*
 if ( !q.full() ){
    if ( !q1.empty() ){
        q.enqueue(q1.dequeue());
        if ( !q2.empty() )
        q.enqueue(q2.dequeue());
    else
    q.enqueue(q1.dequeue());
    }
else{
    q.enqueue(q2.dequeue());
    q.enqueue(q2.dequeue());
 }
 */
void game(queue &q1, queue &q2, queue &q)
{
    while (!q1.empty() && !q2.empty())
    {
        cmp(q1, q2, q);
    }
    if (q1.empty())
        cout<< "q2 wins"<<endl;
    else
        if (q2.empty())
            cout<<"q1 wins"<<endl;
        else
            cout<<"draw!"<<endl;
    cout <<"!!table "<<endl;q.qprint();cout<<endl;
    cout <<"!!q1 "<<endl;q1.qprint();cout<<endl;
    cout <<"!!q2 "<<endl;q2.qprint();cout<<endl;
    
}

int main ()
{
    desk(m);
    m.print();
    
    m.shufflee1();
    m.print();
    
    queue(g1);
    queue(g2);
    queue(table);
    
    queue::reset(m);
    m.handout( g1, g2); //????
    cout<<"g1 "<<endl; g1.qprint();
    cout<< "g2 "<<endl;g2.qprint();
    cout<<endl;
    
    //game(g1, g2, table);
    
   

}
