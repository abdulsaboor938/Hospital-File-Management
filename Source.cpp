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
	//temp_func(d1);
	//temp_func(date(17, 1, 2002));

	// functions for patient record testing
	patientRecord p1(123, "saboor", date(17, 1, 2002), "none", 0);
	patientRecord p2(345, "irtaza", "none", 1);
	//cout << p1;
	//cout << p2;

	hospitalData* h1 = nullptr;
	h1 = new hospitalData();
	h1->printAdmitted();
	h1->insert(p2);
	h1->insert(p1);
	h1->printAdmitted();
	h1->print(123);
	h1->print(000);
	system("pause");
	system("cls");
	h1->printAdmitted();
	h1->~hospitalData();
	h1->printAdmitted();
	system("pause");
	return 0;
}