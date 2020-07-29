using namespace std;

class course
{
private:
	string title;
	string description;
	string course_num;
	int semester;
	int credits;

public:
	course();
	course(string title, string desc, string num, int sem, int credits);
	void printInfo();
	int getSemester() const { return semester; };
	int getCredits() const { return credits; };
};

class courseTaken : public course
{
private:
	char grade;
	string instructor;

public:
	courseTaken();
	courseTaken(string title, string desc, string num, int sem, int credits, string instructor, char grade);
	void printInfo();
};

// This method is used to sort the given course list
void SortList(vector<course* >& course_list);
// This method is used to read from the requiredCourse list file
void readRequiredCourses(vector<course* >&, string);
// This method is used to read from the taken course list file
void readCoursesTaken(vector<course* >&, string);
