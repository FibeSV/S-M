#include <iostream>
#include <math.h>
#include <fstream> // ��� ������ � ������� 
#include <sstream> 
#include <algorithm>
using namespace std;
// ������ �������
struct vec { double x[3] = {0.0,0.0,0.0}; int len = 3; };
double e = 0.001;
//���, ������������ � ������
double t = 0.618;
int kol = 0, sumkol =0;
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
	kol = 1; double a, b, x1, x2, xmin;
	if (R(y, 0, dir) < R(y, dl, dir)) {
		dl = -dl;
	}
	while (R(y, (kol - 1) * dl, dir) > R(y, (kol)* dl, dir)) {
		kol++;
	}
	a = (kol - 2) * dl; b = (kol)* dl;
	//������� ������� ������� �������� ������� � �����
	while (abs(b - a) > e) {
		// ������� �1 � �2
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
		kol++;
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
vec proj(vec a, vec b) {
	double scal = (a.x[0] * b.x[0] + a.x[1] * b.x[1] + a.x[2] * b.x[2]) / (b.x[0] * b.x[0] + b.x[1] * b.x[1] + b.x[2] * b.x[2]);
	vec d;
	for (int i = 0; i < 3; i++)
		d.x[i] = scal * b.x[i];
	return d;
}
void prov(vec d[3]) {
	cout << (d[0].x[0] * d[1].x[0] + d[0].x[1] * d[1].x[1] + d[0].x[2] * d[1].x[2]) << endl;
	cout << (d[0].x[0] * d[2].x[0] + d[0].x[1] * d[2].x[1] + d[0].x[2] * d[2].x[2]) << endl;
	cout << (d[2].x[0] * d[1].x[0] + d[2].x[1] * d[1].x[1] + d[2].x[2] * d[1].x[2]) << endl;
	if ((abs(d[0].x[0] * d[1].x[0] + d[0].x[1] * d[1].x[1] + d[0].x[2] * d[1].x[2]) < e) and
		(abs(d[0].x[0] * d[2].x[0] + d[0].x[1] * d[2].x[1] + d[0].x[2] * d[2].x[2]) < e) and
		(abs(d[2].x[0] * d[1].x[0] + d[2].x[1] * d[1].x[1] + d[2].x[2] * d[1].x[2]) < e)) {
		cout << "������� ������������" << endl;
	}
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
				vec temp = proj(a[j],b[i]);
				b[j].x[0] -= temp.x[0];
				b[j].x[1] -= temp.x[1];
				b[j].x[2] -= temp.x[2];
				/*b[j].x[0] -= a[j].x[0] * d1[i].x[0] * d1[i].x[0];
				b[j].x[1] -= a[j].x[1] * d1[i].x[1] * d1[i].x[1];
				b[j].x[2] -= a[j].x[2] * d1[i].x[2] * d1[i].x[2];*/
			}
			d1[j].x[0] = b[j].x[0] / norm(b[j]);
			d1[j].x[1] = b[j].x[1] / norm(b[j]);
			d1[j].x[2] = b[j].x[2] / norm(b[j]);
		}
	}
	for (int i=0;i<3;i++)
	d[i] = d1[i];
}
void output(vec y, int& k) {
	k++;

	cout << k << "\t" << sumkol <<"\t"<< R(y,0,y) << "\t" << y.x[0]<< "\t" <<y.x[1] << "\t" << y.x[2]<< endl;
}
int main() {
	// �������� 

	// ��� ������
	double dl = 0.2;
	//���������� ��� �����������
	vec d[3];
	double dn[4][4];
	int k=0;
	//����� x,y,z
	vec x, y;
	d[0].x[0] = 1; d[0].x[1] = 0; d[0].x[2] = 0;
	d[1].x[0] = 0; d[1].x[1] = 1; d[1].x[2] = 0;
	d[2].x[0] = 0; d[2].x[1] = 0; d[2].x[2] = 1;
	// ��������� �����
	x.x[0] = -1; x.x[1] = -2; x.x[2] = 0.5;
	//������ ��������� �����������
	y = x;
	output(y, k);
	do {
		x = y;
		sumkol = 0;
		vec n;
		for (int i = 0; i < y.len; i++) {
			vec dir = d[i];
			n.x[i] = searchmin(dir, y, dl);
			sumkol += kol;
			
		}
		grsh(d, n);
		prov(d);
		output(y, k);
	} while (usl(x, y));
}

//if (R(x[1], x[2], x[3], 0, d[i][1], d[i][2], d[i][3]) < R(x[1], x[2], x[3], dl, d[1][1], d[1][2], d[1][3])) 
	//dl = -dl;
