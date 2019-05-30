// Итерационный метод (Гаусса-Зейделя)
#define ITER 7
#define EPS 0.000001
#define N 5
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int read_size(FILE*f);
double read_number_d(FILE *f);
double* create1 (int sz1);
double** create2 (int sz1, int sz2);
void print2 (double** m, int sz1, int sz2);
void print1(double* m, int sz1);
void print_int (int* m, int sz1);// печать одномерного массива
int max( double* x, double* temp,int sz1);
double resh_xi(double** m, double*x, int sz1, int sz2, int i);
double** copy( double**m, int sz1, int sz2);
int* copy1( int*m, int sz1) ;// копирование массива
double** read_file (FILE *f, int n1, int m1);

double** read_file (FILE *f, int n1, int m1){// чтwение матрицы в файле (воз-ет ук-ль на двумерный массив)
    
    if (n1>0 && m1>0){
		double** m = create2(n1, m1);
		
		int i;
		int j;
		printf("\nstr (n) - %i, stl (m) - %i\n\n",n1 , m1);
		for (i=0; i<n1; i++)
		    for ( j=0; j<m1; j++){
		        m[i][j] = read_number_d(f);
		        //printf("\n%lf",m[i][j]);
		    }
		print2(m, n1, m1);
		fclose(f);
		return m;
	}
	return 0;
}

void print2 (double** m, int sz1, int sz2)// печать двумерного массива
{
	printf("matrix :\n ");
    int i, j;
    for(i=0; i<sz1; i++)
    {
        for(j=0; j<sz2; j++)
            printf("%.3e  ",m[i][j]); //
           //printf(" %f  ",m[i][j]); //
        printf("\n");
    }
    printf("\n");
}
void print1 (double* m, int sz1)// печать одномерного массива
{
	printf("x: ");
	if (m==0){
		printf (" no  ");
		return;
	}
	for (int i=0; i<sz1; i++){
		printf (" %e", m[i]);
	}
	printf("\n");
}
void print_int (int* m, int sz1)// печать одномерного массива
{
	printf("int : ");
	for (int i=0; i<sz1; i++){
		printf (" %i", m[i]);
	}
	printf("\n");
}
double** create2 (int sz1, int sz2)// выделение памяти под двумерный массив, ф-я возвращает указатель на первый элемент
{
    double**t=(double**)malloc(sizeof(double*)*sz1); //создать указатели на строки sz1-кол-во элементов массива хранящего адреса
    int i;
    for(i=0; i<sz1; i++) //создание строк
        t[i]=(double*)malloc(sizeof(double)*sz2);//*(t+i)
    return t;
}
double* create1 (int sz1) // выделение памяти под одномерный массив, ф-я возвращает указатель на первый элемент
{
	double* x = (double*)malloc(sizeof(double)*sz1);
}
int* create1_int (int sz1) // выделение памяти под одномерный массив, ф-я возвращает указатель на первый элемент
{
	int* x = (int*)malloc(sizeof(int)*sz1);
}
void erase (double **m, int sz1, int sz2)// удаление памяти (двумерный массив)
{
    int i;
    for(i=0; i<sz1; i++) //удаление строк
        free(m[i]);
    free(m);
}
void erase1 (double *m, int sz1)// удаление памяти (одномерный массив)
{
    free(m);
}
int read_size(FILE*f) // считывание размерности матрицы с файла
{
    int i;
    fscanf(f, "%i", &i);
    //printf("\n%i",i);
    return i;
}
double read_number_d(FILE*f)
{
    double fl;
    fscanf(f, "%lf", &fl);
    // printf("\n%lf",fl);
    return fl;
}
void resh(double**m,double* x,int sz1, int sz2,double *max, double *dbl)
{
	*max=0. ;
	for (int i=0; i<sz1; i++){ // находим решение во свех строках
		*dbl = resh_xi(m,x,sz1,sz2,i);
		if (fabs( x[i] - *dbl) > *max) // сравниваем с max 
			*max = fabs(x[i] - *dbl);
		x[i] = *dbl;
	}
}
double* zeidel(double**m,double* x,int sz1, int sz2) // вычисление решения методом Гаусса-Зейделя
{
	printf("zeidel\n");
	for (int i=0; i<sz1; i++)
		x[i] = 0.; // начальное приближение
	double dbl = 0.;
	double max = 0.; // максимальная разность
	do{
		resh(m,x,sz1,sz2,&max,&dbl);
		print1(x,sz1);
	} while (max > EPS);	 // критерий близости
	return x;
}
double resh_xi(double**m,double* x,int sz1, int sz2, int i) // решение
// m[i][i] - x, который необходимо вычислить
{
	double d = 0.;
	int j=0;
	for (; j<i; j++)
		d -= m[i][j]*x[j];
	j++; // пропускаем диагональный
	for (; j<sz2-1; j++) // до последнего x
		d -= m[i][j]*x[j];
	d += m[i][sz2-1]; // свободный член (b)
	d /= m[i][i]; // коэффициент
	return d;
}
int monotone(double**m,double* x,int sz1, int sz2)// ф-я определения монотонности
// ф-я возвращает 0 - не монотонно(или монотонно возрастает), 1 - монотонно (убывает)
{
	printf ("monotone\n"); 
	double temp[sz1];
	int count = 0; //  счётчик монотонности
	for (int i=0; i<sz1; i++)
		x[i] = 0.; // начальное приближение
	double dbl=0.,max=0.,max2=0.;
	// max2 хранит предыдущий max
	for (int k=0; k<ITER; k++){ // 7 итераций 
		max2=max;
		resh(m,x,sz1,sz2,&max,&dbl);
		//print1(x,sz1);
		if (max <= max2 ) {// если монотонно убывает, то ++
			count++;
			if (count == N)
				return 1;	
		}
		else 
			count = 0;
	}
	
	return count >= N;
} 
void up (double **m, int sz1, int sz2, int a, int j) // поменять местами строки a и j  
{
    double* temp = m[a];
    m[a] = m[j];
    m[j] = temp;
}

int equal (int*m2, int sz1) // равенство матриц
{
	for (int i=0; i<sz1; i++)
			if (m2[i] != i)
				return 0; // не равны
	return 1; // равны
} 
void sum (double*ms, double **m,int sz1, int sz2) // подсчёт массива сумм
{
	for (int i=0; i<sz1; i++)
		ms[i] = 0.;
	for (int i=0; i<sz1; i++)
		for (int j=0; j<sz2; j++)
			ms[i] += fabs(m[i][j]);
}
int dus(double**mx,int sz1, int sz2)  // проверка Достаточного условия сходимости
// возвращает 0 - ДУС не выполняется, 1 - выполняется
{
	double temp=0;
	int i=0,j=0;
	while (i<sz1){
		for (; j<i; j++)
			temp+= fabs(mx[i][j]);
		// пропускаем диагональный
		j++;
		for (; j<sz2; j++)
			temp+= fabs(mx[i][j]);
		if  ( temp > mx[i][i] ) // диагональный не преобладает
			return 0;
		i++;
	}
//	printf("i- %i",i);
	if (i == sz1)		
		return 1;
	return 0;
}
int check_diagonal(double**m,int sz1, int sz2)  // проверка наличия нулей на диагонали, 
//ф-я возвращает 0 - на диагонали есть ноль, 1 - нет нулей
{
	
	for (int i=0; i<sz1; i++)
		if (m[i][i] == 0.)
			return 0;
	printf("no 0 in diag\n");
	return 1;
}
int check_diagonal_2(double**m,int* m2,int sz1)  // проверка наличия нулей на диагонали, 
//ф-я возвращает 0 - на диагонали есть ноль, 1 - нет нулей
{
	
	for (int i=0; i<sz1; i++)
		if (m[m2[i]][i] == 0.)
			return 0;
//	printf("no 0");
	return 1;
}
int change(double**m,int*m2,int **mx0,int sz1, int sz2,int i,double*ms) // переставить строки 
// m - исходный массив (матрица)
// m2 - массив с перестановленными строками
// ms - массив сумм
// mx0 - массив без 0 на диагонали

// ф-я возвращает
// 0 - дус выполяется
// 1 - матрица без 0 на диагонали
// 2 - не решается Зейделем 
{
	if ( check_diagonal_2(m,m2,sz1)){
		*mx0 = copy1(m2,sz1); // сохранить перестановку
		int j;
		for (j=0; j<sz1; j++){ // проверка на  преобладание диагонального элемента (ДУС)
			if (ms[j] - fabs(m[m2[j]][j]) > fabs(m[m2[j]][j]))
				break;
		}
		if (j==sz1) 
			return 0; // дус выполнился
	
	}
	
	if (i<sz1-1){ 
		int temp = m2[i];
		m2[i]=m2[i+1];
		m2[i+1] = temp;
		i++;
	}
	else 
		i=0;
	int j;
	
	if(equal(m2,sz1)){ // одинаковые
		if (*mx0 == NULL) //перестановки без нулей на диагонали нет
			return 2;
		return 1;
	}
	else// пока перестановка не совпадёт с изначальной
		change(m,m2,mx0,sz1,sz2,i,ms);
}
double** copy( double**m, int sz1, int sz2) // копирование матрицы
{
	double ** temp = create2(sz1,sz2);
	for ( int i=0; i<sz1; i++)
		for (int j=0; j<sz2; j++)
			temp[i][j] = m[i][j];	
	return temp;
}
int* copy1( int*m, int sz1) // копирование массива
{
	int * temp = create1_int(sz1);
	for ( int i=0; i<sz1; i++)
			temp[i] = m[i];	
	return temp;
}
double** rearrange (double**m, int*m2, int sz1, int sz2) // перестановка строк в матрице m  соответственно элементам массива m2
{
	double** temp = (double**)malloc(sizeof(double*)*sz1); // массив с указателями на строки матрицы
	for (int i=0; i<sz1; i++)
		temp[i] = m[m2[i]]; 
	free(m);
	return temp;
}
double* method (int n, int m , double**mx)
{
	double* x = create1(n);
	 if (check_diagonal(mx,n,m) ){ // на диагонали нет нулей
        	if (dus(mx,n,m) == 1){ // если ДУС выполняется
        		printf ("dus \n");
        		return x = zeidel(mx,x,n,m);
        	}
        		
        	else { // иначе решить с контролем монотонности
        		if (monotone(mx,x,n,m))
        			return x = zeidel(mx,x,n,m);
				else {
					printf("increases monoton. \n");
					return 0;
				}
			}
		}
		else{ // нули на диагонали
			printf(" 0 in diagonal \n");
			double *ms = create1(n);// массив сумм
			sum(ms,mx,n,m); // вычисление массива сумм
			int m2[n] ; //copy(mx,n,m);
			for (int i=0;i<n;i++)
				m2[i]=i;
			int * mx0 = NULL; // для перестановки без 0 на диагонали
			int c = change(mx,m2,&mx0,n,m,0,ms) ;
			if ( c == 0 ){ // перестановка
				printf("done \n");
				mx = rearrange(mx,m2,n,m);// переставить строки в исходной матрице соответственно массиву m2
				print2(mx,n,m);
				return x = zeidel (mx,x,n,m);
			}
			else {
				if ( c == 1 ){ //матрица без 0 на диагонали
					printf("monotone  \n");
					print_int(mx0,n);
					mx=rearrange(mx,mx0,n,m);
					print2(mx,n,m);
					if (monotone(mx,x,n,m)) // решить с контролем монотонности
        				return x = zeidel(mx,x,n,m);
        			else{
						printf("increases monoton.");
						return 0;
					}
				}
				else  // решить зейделем нельзя
					return 0;
			}
			erase1(ms,n);// удалить массив сумм
		}
}
int main() {
    double**mx; // матрица
    int n,m;
    FILE*f = fopen("f.txt", "r");
    if (f){
        n = read_size(f); // чтение размерностей
        m = read_size(f);
        printf("\nstr (n) - %i, stl (m) - %i\n\n",n , m);
        
        mx = read_file(f,n,m); // чтение матрицы
        fclose(f);
        double *x; // для решений
      	x = method(n,m,mx);
      	printf("end\n\n");
     	print1(x,n); // вывод решений
		erase1(x,n);// удалить массив под решения
    }
}
