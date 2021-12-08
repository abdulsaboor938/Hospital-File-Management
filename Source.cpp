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
	patientRecord p1(2, "saboor", date(17, 1, 2002), "none", 0);
	patientRecord p2(4, "irtaza", "none", 1);
	patientRecord p3(3, "irtaza", "none", 1);
	patientRecord p4(1, "irtaza", "none", 1);
	patientRecord p5(10, "irtaza", "none", 1);

	//cout << p1;
	//cout << p2;

	hospitalData* h1 = nullptr;
	h1 = new hospitalData();
	h1->printAdmitted();
	h1->insert(p1);
	h1->insert(p2);
	h1->insert(p3);
	h1->insert(p4);
	h1->insert(p5);
	h1->search(p5, 3, 2);
	cout << p5 << endl;
	h1->printAdmitted();
	h1->remove(3);
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