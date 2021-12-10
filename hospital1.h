/*
* Abdul Saboor
* 20L-1113
* BDS-3A1
* 
* This file contains all the classes required for the implementation of hospital's records
*/

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

	friend class TNode;
	friend class hospitalData;
};
#endif

// Implementaion of TNode class
#ifndef TNODE_H
#define TNODE_H
class TNode
{
	patientRecord record;
	TNode* leftChild, * rightChild;

public:
	// constructors of class
	TNode(patientRecord P, TNode* left, TNode* right)
		:record(P), leftChild(left), rightChild(right) {}
	friend class hospitalData;
};
#endif

// Implementation of Hospital Data class
#ifndef HOSPITALDATA_H
#define HOSPITALDATA_H
class hospitalData
{
	TNode* root;
	int size;

	// private helper functions
	void clear(TNode* ptr)
	{
		if (ptr != nullptr)
		{
			clear(ptr->leftChild);
			clear(ptr->rightChild);
			delete ptr;
		}
	}
	void inorderPrintAdmitted(TNode* curr, int &count) const
	{
		if (curr != nullptr)
		{
			inorderPrintAdmitted(curr->leftChild, count); // visisting left child
			if (curr->record.status == true)
			{
				count++;
				cout << curr->record; // printing current data
			}
			inorderPrintAdmitted(curr->rightChild,count); // visiting right child
		}
	}


public:
	hospitalData() // default constructor
		:root(nullptr), size(0) {}
	~hospitalData() // destructor of class
	{
		clear(this->root);
		root = nullptr;
		size = 0;
	}
	
	// insertion and swapping
	void insert(patientRecord P) // wrapper for insertion function
	{
		this->insert(this->root, P);
		this->size++;
	}
											
	// deletion
	void remove(int const temp_id) // wrapper function
	{
		bool check;
		this->remove(temp_id, this->root, check);
		if (check)
			this->size--;
	}
	void remove(int const x, TNode*& t, bool &check) // main deletion function
	{
		if (t == nullptr)
		{
			check = false;
			return;
		}
		if (x < t->record.id)
			remove(x, t->leftChild, check);
		else if (t->record.id < x)
			remove(x, t->rightChild, check);
		else if (t->leftChild != nullptr && t->rightChild != nullptr)
		{
			t->record = findmax(t->leftChild)->record;
			remove(t->record.id, t->rightChild, check);
		}
		else
		{
			TNode* oldNode = t;
			if (t->rightChild != nullptr)
				t = t->rightChild;
			else
				t = t->leftChild;
			delete oldNode;
			t = nullptr;
			check = true;
		}
	}
	TNode* findmin(TNode* t) // function to find successor
	{
		while (t->leftChild != nullptr)
			t = t->leftChild;
		return t;
	}
	TNode* findmax(TNode* t) // function to find successor
	{
		while (t->rightChild != nullptr)
			t = t->rightChild;
		return t;
	}


	// printing a record
	void print(int const temp_id)
	{
		TNode* temp = this->root;
		while (true)
		{
			if (temp == nullptr)
			{
				cout << "No record found for patient id: " << temp_id << endl;
				return;
			}
			else if (temp->record.id < temp_id)
				temp = temp->rightChild;
			else if (temp_id < temp->record.id)
				temp = temp->leftChild;
			else
			{
				cout << temp->record;
				return;
			}
		}
	}

	// printing all patients
	void printAdmitted() // wrapper function
	{
		if (size == 0)
			cout << "No records to print" << endl;
		else 
		{
			int temp_size = 0;
			cout << "------------- Patient Records -------------" << endl;
			inorderPrintAdmitted(this->root,temp_size);
			if(temp_size>0)
				cout << "Total Records : " << temp_size << endl;
			else
				cout << "No patients are currently admitted" << endl;
			cout << "-------------------------------------------" << endl;
		}
	}

	// searching
	void search(patientRecord &ret_val, int temp_id, int temp_level)
	{
		if (!this->search(this->root, temp_id, temp_level, 0, ret_val))
		{
			cout << "The corresponding Id could not be found" << endl;
		}
	}

	// Splitting function
	void split()
	{
		int median_pos = size / 2;
		int median = -1, temp_count = 0;
		node_rec(this->root, temp_count, median_pos, median);
		// code to find median
		patientRecord temp(this->root->record); // temporary copy of root for returning record
		search(temp, median, 0);
	}

// private helper fnctions
private:
	void insert(TNode*& ptr, patientRecord P)
	{
		if (ptr == nullptr)
			ptr = new TNode(P, nullptr, nullptr);
		else if (ptr->record.id == P.id)
			ptr->record = P;
		else if (ptr->record.id > P.id) // goto left child
		{
			insert(ptr->leftChild, P); // node is inserted
			rightRotate(ptr);
		}
		else // goto right child
		{
			insert(ptr->rightChild, P); // going to right child
			leftRotate(ptr);
		}
	}
	void rightRotate(TNode*& x)
	{
		TNode* y = x->leftChild;
		x->leftChild = y->rightChild;
		y->rightChild = x;
		x = y;
	}
	void leftRotate(TNode*& x)
	{
		TNode* y = x->rightChild;
		x->rightChild = y->leftChild;
		y->leftChild = x;
		x = y;
	}

	bool search(TNode*& ptr, int temp_id, int level, int level_check, patientRecord& ret_ptr)
	{
		if (ptr == nullptr)
			return false;
		else if (ptr->record.id == temp_id)
		{
			ret_ptr = ptr->record;
			return true;
		}
		else if (ptr->record.id > temp_id)
		{
			if (search(ptr->leftChild, temp_id, level, (level_check+1), ret_ptr))
			{
				if (level_check >= level)
					rightRotate(ptr);
				return true;
			}
			return false;
		}
		else
		{
			if (search(ptr->rightChild, temp_id, level, (level_check+1), ret_ptr))
			{
				if (level_check >= level)
					leftRotate(ptr);
				return true;
			}
			return false;
		}
	}

	void node_rec(TNode* ptr, int& curr_count, int tally, int &ret_val) // node to give record of a desired node
	{
		if (ptr != nullptr)
		{
			node_rec(ptr->leftChild, curr_count, tally, ret_val);
			curr_count++;
			if (curr_count == tally)
			{
				ret_val = ptr->record.id;
				return;
			}
			node_rec(ptr->rightChild, curr_count, tally, ret_val);
		}
	}
};
#endif