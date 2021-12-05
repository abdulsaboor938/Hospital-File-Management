/*
* This file contains all the classes required for the implementation of hospital's records
*/

// Implementation of date class
#include<iostream>
#include<ctime>
using namespace std;

// Implementation of Date class
#ifndef DATE_H
#define DATE_H
class date
{
	int day;
	int month;
	int year;

public:
	date();
	date(int, int, int);
	void set_day(int);
	void set_month(int);
	void set_year(int);

	int get_day()const;
	int get_month()const;
	int get_year()const;

	friend ostream& operator<<(ostream&, const date&);
};

// Implementation of date class functions
date::date()
{
	time_t now = time(0);

	int t = (int)now;
	year = (t / 31556926) + 1970;
	t %= 31556926;
	month = (t / 2629743) + 1;
	t %= 2629743;
	day = (t / 86400) + 1;
}
date::date(int d, int m, int y)
{
	set_day(d);
	set_month(m);
	set_year(y);
}
ostream& operator << (ostream& out, const date& D)
{
	out << D.day << "/" << D.month << "/" << D.year;
	return out;
}
void date::set_year(int x)
{
	year = x;
	date temp;
	int t = temp.get_year();
	while (year < 1900 || year > t)
	{
		cout << "Please Enter a valid year (1990 - " << t << ") : ";
		cin >> year;
	}
}
void date::set_month(int x)
{
	month = x;
	while (month < 1 || month>12)
	{
		cout << "Please Enter a valid month (1 - 12) : ";
		cin >> month;
	}
}
void date::set_day(int x)
{
	day = x;
	int max_d = 30;
	if ((year % 4 == 0) && month == 2)
		max_d = 29;
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		max_d = 31;
	while (day<1 || day>max_d)
	{
		cout << "Please Enter a valid day (1 - " << max_d << ") : ";
		cin >> day;
	}
}
int date::get_day() const
{
	return day;
}
int date::get_month() const
{
	return month;
}
int date::get_year() const
{
	return year;
}
#endif

// Implementation of Patient Record class
#ifndef PATIENTRECORD_H
#define PATIENTRECORD_H
class patientRecord
{
	int id;
	string name;
	date a_date;
	string disease;
	bool status; // (admitted: 1 / discharged: 0)

public:
	// All public class functions
	patientRecord(int temp_id, string temp_name, string temp_disease, bool temp_status) :
		id(temp_id), name(temp_name), a_date(date()), disease(temp_disease), status(temp_status) {} // default constructor without date
	patientRecord(int temp_id, string temp_name, date temp_date, string temp_disease, bool temp_status) :
		id(temp_id), name(temp_name), a_date(temp_date), disease(temp_disease), status(temp_status) {} // overloaded constructor without date

	// stream output function
	friend ostream& operator << (ostream& out, const patientRecord& P)
	{
		out << "-------------------------------------------" << endl;
		out << "Patient record of  : " << P.name << endl;
		out << "    ID             : " << P.id << endl;
		out << "    Admission Date : " << P.a_date << endl;
		out << "    Disease        : " << P.disease << endl;
		if(P.status==1)
			out << "    Status         : Admitted" << endl;
		else
			out << "    Status         : Discharged" << endl;
		out << "-------------------------------------------" << endl << endl;
		return out;
	}

	template<class T>
	friend class Tnode;
};
#endif

// Implementaion of TNode class
#ifndef TNODE_H
#define TNODE_H
class TNode
{
	patientRecord record;
	patientRecord* leftChild, * rightChild;

public:
	// constructors of class
	TNode(patientRecord P, patientRecord* left, patientRecord* right)
		:record(P), leftChild(left), rightChild(right) {}
	friend class hospitalData;
};
#endif