#include<iostream>
#include"hospital.h"
using namespace std;

void temp_func(date d)
{
	cout << d << endl;
}

int main()
{
	date d1;
	// functions for date testing
	temp_func(d1);
	temp_func(date(17, 1, 2002));

	// functions for patient record testing
	patientrecord p1(123, "saboor", date(17, 1, 2002), "none", 0);
	patientrecord p2(345, "irtaza", "none", 1);
	cout << p1;
	cout << p2;
	system("pause");
	return 0;
}