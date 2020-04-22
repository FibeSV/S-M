#include <iostream>
#include <math.h>
#include <fstream> // Для работы с файлами 
#include <sstream> 
#include <algorithm>
using namespace std;
// Задаем функцию
struct vec { double x[3]; int len = 3; };
double e = 0.001;
//Тау, используемая в методе
double t = 0.618;
double R(vec x0, double l, vec d) {
	vec corr;
	for (int i = 0; i < corr.len; i++) {
		corr.x[i] = x0.x[i] + l * d.x[i];
	}
	return (2 * corr.x[0] * corr.x[0] + corr.x[1] * corr.x[1]
		- 2 * corr.x[0] * corr.x[1] - 6 * corr.x[0]
		+ corr.x[2] + 4 / corr.x[2] + 10);
}
double searchmin(vec dir, vec& y, double dl) {
	int n = 1; double a, b, x1, x2, xmin;
	if (R(y, 0, dir) < R(y, dl, dir)) {
		dl = -dl;
	}
	while (R(y, (n - 1) * dl, dir) > R(y, (n)* dl, dir)) {
		n++;
	}
	a = (n - 2) * dl; b = (n)* dl;
	//считаем функцию методом золотого сечения в цикле
	while (abs(b - a) > e) {
		// Считаем х1 и х2
		x1 = b - t * (b - a); x2 = a + t * (b - a);
		if (R(y, x1, dir) < R(y, x2, dir))
		{
			b = x2;
		}
		else if (R(y, x2, dir) <= R(y, x1, dir))
		{
			a = x1;
		}
		xmin = 0.5 * (a + b);
	}
	y.x[0] += xmin*dir.x[0];
	y.x[1] += xmin*dir.x[1];
	y.x[2] += xmin*dir.x[2];
	return xmin;
}
double norm(vec x) {
	double sum = 0;
	for (int i = 0; i < x.len; i++) {
		sum = sum + abs(x.x[i]);
	}
	return sum;
}
bool usl(vec x, vec y) {
	for (int i = 0; i < x.len; i++) {
		x.x[i] -= y.x[i];
	}
	if (norm(x) < e) {
		return false;
	}
	else return true;
}
void grsh(vec(&d)[3], vec l) {
	vec a[3], b[3], d1[3];
	for (int i = 0; i < d[0].len; i++) {
		if (l.x[i] == 0) {
			a[i] = d[i];
		}
		else {
			for (int j = i; j < d[i].len; j++) {
				a[i].x[0] += l.x[j] * d[j].x[0];
				a[i].x[1] += l.x[j] * d[j].x[1];
				a[i].x[2] += l.x[j] * d[j].x[2];
			}
		};
	}
	for (int j = 0; j < d[0].len; j++) {
		if (j == 0) {
			b[j] = a[j];
			d1[j].x[0] = b[j].x[0] / norm(b[j]);
			d1[j].x[1] = b[j].x[1] / norm(b[j]);
			d1[j].x[2] = b[j].x[2] / norm(b[j]);
		}
		else {
			b[j] = a[j];
			for (int i = 0; i < j; i++) {
				b[j].x[0] -= a[j].x[0] * d1[i].x[0] * d1[i].x[0];
				b[j].x[1] -= a[j].x[1] * d1[i].x[1] * d1[i].x[1];
				b[j].x[2] -= a[j].x[2] * d1[i].x[2] * d1[i].x[2];


			}
			d1[j].x[0] = b[j].x[0] / norm(b[j]);
			d1[j].x[1] = b[j].x[1] / norm(b[j]);
			d1[j].x[2] = b[j].x[2] / norm(b[j]);
		}
	}
}
void output(vec y, int& k) {
	k++;
	cout << k << "\t" << R(y,0,y) << "\t" << y.x[0]<< "\t" <<y.x[1] << "\t" << y.x[2]<< endl;
}
int main() {
	// Точность 

	// Шаг лямбды
	double dl = 0.2;
	//Переменные для направлений
	vec d[3];
	double dn[4][4];
	int k=0;
	//Точки x,y,z
	vec x, y;
	d[0].x[0] = 1; d[0].x[1] = 0; d[0].x[2] = 0;
	d[1].x[0] = 0; d[1].x[1] = 1; d[1].x[2] = 0;
	d[2].x[0] = 0; d[2].x[1] = 0; d[2].x[2] = 1;
	// Начальная точка
	x.x[0] = -1; x.x[1] = -2; x.x[2] = 0.5;
	//Задаем начальные направления
	y = x;
	output(y, k);
	do {
		x = y;
		vec n;
		for (int i = 0; i < y.len; i++) {
			vec dir = d[i];
			n.x[i] = searchmin(dir, y, dl);

		}
		grsh(d, n);
		output(y, k);
	} while (usl(x, y));
}

//if (R(x[1], x[2], x[3], 0, d[i][1], d[i][2], d[i][3]) < R(x[1], x[2], x[3], dl, d[1][1], d[1][2], d[1][3])) 
	//dl = -dl;
