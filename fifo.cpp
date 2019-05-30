// очередь (магазин)
using namespace std;
#define LEN 5 
#include <iostream>
class queue
{
public:
    void enqueue(char c);
    char dequeue();
    char front();
    int full();
    int empty();
    void reset();
   
private:
	int next(int v) {return (v+1)%(LEN+1);}// ф-я возвращает позицию следующего
    char s[LEN+1]; // LEN - кол-во элементов
    int r, t; // t- конец r- начало
    
};
void queue:: reset() // подготовка к работе
{
    r = 1,t = 0;
}
void queue:: enqueue(char c) // поместить в голову
{
    t = next(t);
    s[t] = c;
}
char queue:: dequeue() // извлечение из головы
{
    int temp=r;
    r = next(r);
    return  s[temp]; // возвращаем извлечённое значение
}
char queue:: front() // ф-я возвращает элемент в голове
{
    return s[r];
}
int queue:: empty() // проверка на пустоту
{
    return next(t) == r ;
}
int queue:: full()//проверка на полноту
{
    return  next(next(t)) == r;
}

int main()
{
    queue queue;
    queue.reset();
    int i=0;
    char str[]="Queue";
    while (str[i] && !queue.full()) // пока не закончится строка или не заполнится стек
        queue.enqueue(str[i++]);
    while (!queue.empty()) // пока стек не пустой
        cout<<queue.dequeue();
   

}

