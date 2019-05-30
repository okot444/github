// ������� (�������)
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
	int next(int v) {return (v+1)%(LEN+1);}// �-� ���������� ������� ����������
    char s[LEN+1]; // LEN - ���-�� ���������
    int r, t; // t- ����� r- ������
    
};
void queue:: reset() // ���������� � ������
{
    r = 1,t = 0;
}
void queue:: enqueue(char c) // ��������� � ������
{
    t = next(t);
    s[t] = c;
}
char queue:: dequeue() // ���������� �� ������
{
    int temp=r;
    r = next(r);
    return  s[temp]; // ���������� ����������� ��������
}
char queue:: front() // �-� ���������� ������� � ������
{
    return s[r];
}
int queue:: empty() // �������� �� �������
{
    return next(t) == r ;
}
int queue:: full()//�������� �� �������
{
    return  next(next(t)) == r;
}

int main()
{
    queue queue;
    queue.reset();
    int i=0;
    char str[]="Queue";
    while (str[i] && !queue.full()) // ���� �� ���������� ������ ��� �� ���������� ����
        queue.enqueue(str[i++]);
    while (!queue.empty()) // ���� ���� �� ������
        cout<<queue.dequeue();
   

}

