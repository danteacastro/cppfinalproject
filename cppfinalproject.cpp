
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>        
#include <algorithm>

#include "course.h"

using namespace std;

course::course()
{
}

course::course(string title, string desc, string num, int sem, int credits)
{
	this->title = title;
	this->description = desc;
	this->course_num = num;
	this->semester = sem;
	this->credits = credits;
}


void course::printInfo()
{
	cout << setw(5) << this->semester << setw(12) << this->course_num << setw(15) << this->title << setw(9) << this->credits << setw(8);
}

courseTaken::courseTaken(string title, string desc, string num, int sem, int credits, string instructor, char grade) :
	course(title, desc, num, sem, credits)
{
	this->grade = grade;
	this->instructor = instructor;
}


void courseTaken::printInfo()
{
	course::printInfo();
	cout << setw(8) << grade;
}


void readRequiredCourses(vector<course*>& course_list, string filename)
{
	string line;
	string line1;
	string name;
	string descr;
	string num;
	int sem;
	int cred;

	std::ifstream infile(filename);
	if (!infile.is_open())
	{
		cout << " infile - " << filename << "  cannot be open \n";
		return;
	}

	cout << " In Progress Courses file opened.\n";
	int count = 0;
	while (getline(infile, line))
	{
		stringstream inputSS(line);
		stringstream iss;
		//iss = stringstream(line1);
		getline(inputSS, name, ',');
		getline(inputSS, descr, ',');
		getline(inputSS, num, ',');
		getline(inputSS, line1, ',');
		sem = stoi(line1);
		getline(inputSS, line1, ',');
		cred = stoi(line1);

		course_list.push_back(new course(name, descr, num, sem, cred));
		//cout << " " << name << " XXX"  << descr << " XXX\n";
		count++;
	}

	cout << " " << count << " In Progress Courses Loaded.\n";
}

void SortList(vector<course* >& course_list)
{

	sort(course_list.begin(), course_list.end(), [](const course* course1, const course* course2) {
		return course1->getSemester() < course2->getSemester();
		});
}

void readCoursesTaken(vector<course*>& course_list, string filename)
{
	string line;
	string line1;
	string name;
	string descr;
	string num;
	int sem;
	int cred;
	string instructor;
	char grade;

	std::ifstream infile(filename);
	if (!infile.is_open())
	{
		cout << " infile - " << filename << "  cannot be open \n";
		return;
	}
	cout << " Taken Courses file opened.\n";

	int count = 0;
	while (getline(infile, line))
	{
		stringstream inputSS(line);
		stringstream iss;
		//iss = stringstream(line1);
		getline(inputSS, name, ',');
		getline(inputSS, descr, ',');
		getline(inputSS, num, ',');
		getline(inputSS, line1, ',');
		sem = stoi(line1);
		getline(inputSS, line1, ',');
		cred = stoi(line1);
		getline(inputSS, instructor, ',');
		getline(inputSS, line1, ',');
		grade = line1[0];
		course_list.push_back(new courseTaken(name, descr, num, sem, cred, instructor, grade));
		//cout << " " << name << " XXX"  << descr << " XXX\n";
		count++;
	}

	cout << " " << count << " Taken Courses Loaded.\n";

}



int main()
{
	vector<course* > requiredCourses;
	vector<course*> takenCourses;
	readRequiredCourses(requiredCourses, "ipcourses.csv");

	readCoursesTaken(takenCourses, "tcourses.csv");

	SortList(requiredCourses);
	SortList(takenCourses);

	cout << endl << " Transcript for Dante Castro:\n\n";

	cout << " Courses Taken for Credit :\n";
	cout << "  Sem     CourseID    Course Name    Credits   Grade \n";
	int semester = 1;
	int semesterCredits = 0;
	int totalCredits = 0;
	double semesterGPA = 0;
	int totalGPA = 0;
	int count = 0;
	for (int i = 0; i < takenCourses.size(); i++)
	{

		courseTaken* tk = (courseTaken*)takenCourses[i];

		if (semester == takenCourses[i]->getSemester())
		{
			count++;
			semesterCredits += takenCourses[i]->getCredits();

		}
		else {
			cout << "                                         Semester Credits : " << semesterCredits << "\n";
			cout << "                                         Semester GPA     : " << setprecision(4) << semesterCredits / count << "\n";
			semesterCredits = takenCourses[i]->getCredits();
			count = 1;
			semester = takenCourses[i]->getSemester();

		}
		tk->printInfo();
		totalCredits += takenCourses[i]->getCredits();
		cout << "\n";
	}
	//cout << " Current Semester : " << semester <<"\n";
	semester += 1;

	cout << "                                         Semester Credits : " << semesterCredits << "\n";
	cout << "                                         Semester GPA     : " << setprecision(4) << semesterCredits / count << "\n";

	for (int j = 0; j < requiredCourses.size(); j++)
	{
		if (requiredCourses[j]->getSemester() == semester)
		{
			requiredCourses[j]->printInfo();
			totalCredits += requiredCourses[j]->getCredits();
			cout << "\n";
		}
	}

	cout << "                                         Total Credits : " << totalCredits << "\n";
	


	for (int i = 0; i < requiredCourses.size(); i++)
	{

	}
	for (auto p : requiredCourses)
	{
		delete p;
	}
	requiredCourses.clear();

	for (auto p : takenCourses)
	{
		delete (courseTaken*)p;
	}
	takenCourses.clear();

}