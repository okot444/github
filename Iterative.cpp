// ������������ ����� (������-�������)
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
void print_int (int* m, int sz1);// ������ ����������� �������
int max( double* x, double* temp,int sz1);
double resh_xi(double** m, double*x, int sz1, int sz2, int i);
double** copy( double**m, int sz1, int sz2);
int* copy1( int*m, int sz1) ;// ����������� �������
double** read_file (FILE *f, int n1, int m1);

double** read_file (FILE *f, int n1, int m1){// ��w���� ������� � ����� (���-�� ��-�� �� ��������� ������)
    
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

void print2 (double** m, int sz1, int sz2)// ������ ���������� �������
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
void print1 (double* m, int sz1)// ������ ����������� �������
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
void print_int (int* m, int sz1)// ������ ����������� �������
{
	printf("int : ");
	for (int i=0; i<sz1; i++){
		printf (" %i", m[i]);
	}
	printf("\n");
}
double** create2 (int sz1, int sz2)// ��������� ������ ��� ��������� ������, �-� ���������� ��������� �� ������ �������
{
    double**t=(double**)malloc(sizeof(double*)*sz1); //������� ��������� �� ������ sz1-���-�� ��������� ������� ��������� ������
    int i;
    for(i=0; i<sz1; i++) //�������� �����
        t[i]=(double*)malloc(sizeof(double)*sz2);//*(t+i)
    return t;
}
double* create1 (int sz1) // ��������� ������ ��� ���������� ������, �-� ���������� ��������� �� ������ �������
{
	double* x = (double*)malloc(sizeof(double)*sz1);
}
int* create1_int (int sz1) // ��������� ������ ��� ���������� ������, �-� ���������� ��������� �� ������ �������
{
	int* x = (int*)malloc(sizeof(int)*sz1);
}
void erase (double **m, int sz1, int sz2)// �������� ������ (��������� ������)
{
    int i;
    for(i=0; i<sz1; i++) //�������� �����
        free(m[i]);
    free(m);
}
void erase1 (double *m, int sz1)// �������� ������ (���������� ������)
{
    free(m);
}
int read_size(FILE*f) // ���������� ����������� ������� � �����
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
	for (int i=0; i<sz1; i++){ // ������� ������� �� ���� �������
		*dbl = resh_xi(m,x,sz1,sz2,i);
		if (fabs( x[i] - *dbl) > *max) // ���������� � max 
			*max = fabs(x[i] - *dbl);
		x[i] = *dbl;
	}
}
double* zeidel(double**m,double* x,int sz1, int sz2) // ���������� ������� ������� ������-�������
{
	printf("zeidel\n");
	for (int i=0; i<sz1; i++)
		x[i] = 0.; // ��������� �����������
	double dbl = 0.;
	double max = 0.; // ������������ ��������
	do{
		resh(m,x,sz1,sz2,&max,&dbl);
		print1(x,sz1);
	} while (max > EPS);	 // �������� ��������
	return x;
}
double resh_xi(double**m,double* x,int sz1, int sz2, int i) // �������
// m[i][i] - x, ������� ���������� ���������
{
	double d = 0.;
	int j=0;
	for (; j<i; j++)
		d -= m[i][j]*x[j];
	j++; // ���������� ������������
	for (; j<sz2-1; j++) // �� ���������� x
		d -= m[i][j]*x[j];
	d += m[i][sz2-1]; // ��������� ���� (b)
	d /= m[i][i]; // �����������
	return d;
}
int monotone(double**m,double* x,int sz1, int sz2)// �-� ����������� ������������
// �-� ���������� 0 - �� ���������(��� ��������� ����������), 1 - ��������� (�������)
{
	printf ("monotone\n"); 
	double temp[sz1];
	int count = 0; //  ������� ������������
	for (int i=0; i<sz1; i++)
		x[i] = 0.; // ��������� �����������
	double dbl=0.,max=0.,max2=0.;
	// max2 ������ ���������� max
	for (int k=0; k<ITER; k++){ // 7 �������� 
		max2=max;
		resh(m,x,sz1,sz2,&max,&dbl);
		//print1(x,sz1);
		if (max <= max2 ) {// ���� ��������� �������, �� ++
			count++;
			if (count == N)
				return 1;	
		}
		else 
			count = 0;
	}
	
	return count >= N;
} 
void up (double **m, int sz1, int sz2, int a, int j) // �������� ������� ������ a � j  
{
    double* temp = m[a];
    m[a] = m[j];
    m[j] = temp;
}

int equal (int*m2, int sz1) // ��������� ������
{
	for (int i=0; i<sz1; i++)
			if (m2[i] != i)
				return 0; // �� �����
	return 1; // �����
} 
void sum (double*ms, double **m,int sz1, int sz2) // ������� ������� ����
{
	for (int i=0; i<sz1; i++)
		ms[i] = 0.;
	for (int i=0; i<sz1; i++)
		for (int j=0; j<sz2; j++)
			ms[i] += fabs(m[i][j]);
}
int dus(double**mx,int sz1, int sz2)  // �������� ������������ ������� ����������
// ���������� 0 - ��� �� �����������, 1 - �����������
{
	double temp=0;
	int i=0,j=0;
	while (i<sz1){
		for (; j<i; j++)
			temp+= fabs(mx[i][j]);
		// ���������� ������������
		j++;
		for (; j<sz2; j++)
			temp+= fabs(mx[i][j]);
		if  ( temp > mx[i][i] ) // ������������ �� �����������
			return 0;
		i++;
	}
//	printf("i- %i",i);
	if (i == sz1)		
		return 1;
	return 0;
}
int check_diagonal(double**m,int sz1, int sz2)  // �������� ������� ����� �� ���������, 
//�-� ���������� 0 - �� ��������� ���� ����, 1 - ��� �����
{
	
	for (int i=0; i<sz1; i++)
		if (m[i][i] == 0.)
			return 0;
	printf("no 0 in diag\n");
	return 1;
}
int check_diagonal_2(double**m,int* m2,int sz1)  // �������� ������� ����� �� ���������, 
//�-� ���������� 0 - �� ��������� ���� ����, 1 - ��� �����
{
	
	for (int i=0; i<sz1; i++)
		if (m[m2[i]][i] == 0.)
			return 0;
//	printf("no 0");
	return 1;
}
int change(double**m,int*m2,int **mx0,int sz1, int sz2,int i,double*ms) // ����������� ������ 
// m - �������� ������ (�������)
// m2 - ������ � ����������������� ��������
// ms - ������ ����
// mx0 - ������ ��� 0 �� ���������

// �-� ����������
// 0 - ��� ����������
// 1 - ������� ��� 0 �� ���������
// 2 - �� �������� �������� 
{
	if ( check_diagonal_2(m,m2,sz1)){
		*mx0 = copy1(m2,sz1); // ��������� ������������
		int j;
		for (j=0; j<sz1; j++){ // �������� ��  ������������ ������������� �������� (���)
			if (ms[j] - fabs(m[m2[j]][j]) > fabs(m[m2[j]][j]))
				break;
		}
		if (j==sz1) 
			return 0; // ��� ����������
	
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
	
	if(equal(m2,sz1)){ // ����������
		if (*mx0 == NULL) //������������ ��� ����� �� ��������� ���
			return 2;
		return 1;
	}
	else// ���� ������������ �� ������� � �����������
		change(m,m2,mx0,sz1,sz2,i,ms);
}
double** copy( double**m, int sz1, int sz2) // ����������� �������
{
	double ** temp = create2(sz1,sz2);
	for ( int i=0; i<sz1; i++)
		for (int j=0; j<sz2; j++)
			temp[i][j] = m[i][j];	
	return temp;
}
int* copy1( int*m, int sz1) // ����������� �������
{
	int * temp = create1_int(sz1);
	for ( int i=0; i<sz1; i++)
			temp[i] = m[i];	
	return temp;
}
double** rearrange (double**m, int*m2, int sz1, int sz2) // ������������ ����� � ������� m  �������������� ��������� ������� m2
{
	double** temp = (double**)malloc(sizeof(double*)*sz1); // ������ � ����������� �� ������ �������
	for (int i=0; i<sz1; i++)
		temp[i] = m[m2[i]]; 
	free(m);
	return temp;
}
double* method (int n, int m , double**mx)
{
	double* x = create1(n);
	 if (check_diagonal(mx,n,m) ){ // �� ��������� ��� �����
        	if (dus(mx,n,m) == 1){ // ���� ��� �����������
        		printf ("dus \n");
        		return x = zeidel(mx,x,n,m);
        	}
        		
        	else { // ����� ������ � ��������� ������������
        		if (monotone(mx,x,n,m))
        			return x = zeidel(mx,x,n,m);
				else {
					printf("increases monoton. \n");
					return 0;
				}
			}
		}
		else{ // ���� �� ���������
			printf(" 0 in diagonal \n");
			double *ms = create1(n);// ������ ����
			sum(ms,mx,n,m); // ���������� ������� ����
			int m2[n] ; //copy(mx,n,m);
			for (int i=0;i<n;i++)
				m2[i]=i;
			int * mx0 = NULL; // ��� ������������ ��� 0 �� ���������
			int c = change(mx,m2,&mx0,n,m,0,ms) ;
			if ( c == 0 ){ // ������������
				printf("done \n");
				mx = rearrange(mx,m2,n,m);// ����������� ������ � �������� ������� �������������� ������� m2
				print2(mx,n,m);
				return x = zeidel (mx,x,n,m);
			}
			else {
				if ( c == 1 ){ //������� ��� 0 �� ���������
					printf("monotone  \n");
					print_int(mx0,n);
					mx=rearrange(mx,mx0,n,m);
					print2(mx,n,m);
					if (monotone(mx,x,n,m)) // ������ � ��������� ������������
        				return x = zeidel(mx,x,n,m);
        			else{
						printf("increases monoton.");
						return 0;
					}
				}
				else  // ������ �������� ������
					return 0;
			}
			erase1(ms,n);// ������� ������ ����
		}
}
int main() {
    double**mx; // �������
    int n,m;
    FILE*f = fopen("f.txt", "r");
    if (f){
        n = read_size(f); // ������ ������������
        m = read_size(f);
        printf("\nstr (n) - %i, stl (m) - %i\n\n",n , m);
        
        mx = read_file(f,n,m); // ������ �������
        fclose(f);
        double *x; // ��� �������
      	x = method(n,m,mx);
      	printf("end\n\n");
     	print1(x,n); // ����� �������
		erase1(x,n);// ������� ������ ��� �������
    }
}
