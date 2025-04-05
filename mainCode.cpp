/* C++ PROs Student Managment System
   Omar Alaa 180 A6
   Ahmed Hassanen 187 D2
   Charles tamer 188 B5
   Ahmed Mohamed C1 113
*/
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

const int MaxStudent = 1000;
const int MaxCourses = 15;
const int MaxEnrollments = 1000;

int StudentCount = 0;
int CourseCount = 0;
class Course;
class Student;
class Enrollment
{
private:
	string EnrollmentID;
	string Grade;
public:
	time_t EnrollmentDate = time(nullptr);
	Enrollment()
	{
		EnrollmentID = "";
		Grade = "";
	}
	Enrollment(string EnrollmentID, string Grade) :EnrollmentID(EnrollmentID), Grade(Grade) {}
	void setEnrollmentID(string EnrollmentID)
	{
		this->EnrollmentID = EnrollmentID;
	}
	string getEnrollmentID()
	{
		return EnrollmentID;
	}
	void setGrade(string Grade)
	{
		this->Grade = Grade;
	}
	string getGrade()
	{
		return Grade;
	}
};

class Student;

class Course
{
public:
	string CName;
	string CID;
	string InstName;
	int CreditHours;
	Student* EnrolledStudents[MaxStudent];
	int EnrolledStudentsCount = 0;

	Course()
	{
		CName = "";
		CID = "";
		InstName = "";
		CreditHours = 0;
	}

	void EnrollStudent(Student* student);
	void WithdrawStudentCourseClass(const string& StudentID);
};

class Student
{
private:
	float CGPA;
public:
	string SName;
	string SID;
	int NumCompCourses;
	string DateOfBirth;
	int PhoneNumber;
	Enrollment Enrollments[MaxEnrollments];
	Course* EnrolledCourses[MaxCourses];
	int EnrolledCoursesCount = 0;

	Student()
	{
		SName = "";
		SID = "";
		CGPA = 0.0;
		NumCompCourses = 0;
		DateOfBirth = "";
		PhoneNumber = 0;
	}

	Student(float CGPA, string SName, string SID, int NumCompCourses, string DateOfBirth, int PhoneNumber) :CGPA(CGPA), SName(SName), SID(SID), NumCompCourses(NumCompCourses), DateOfBirth(DateOfBirth), PhoneNumber(PhoneNumber) {}

	void setCGPA(float CGPA)
	{
		this->CGPA = CGPA;
	}

	float getCGPA() const
	{
		return CGPA;
	}

	void EnrollInCourse(const string& enrollmentID, time_t& enrollmentDate, const string& grade)
	{
		if (EnrolledCoursesCount < MaxEnrollments)
		{
			Enrollment enrollment;
			enrollment.setEnrollmentID(enrollmentID);
			enrollment.EnrollmentDate = enrollmentDate;
			enrollment.setGrade(grade);
			Enrollments[EnrolledCoursesCount] = enrollment;
		}
		else
		{
			cout << " Max Enrollments Reached For This Student !!!" << endl;
		}
	}

	void WithdrawCourseEnrollmentID(const string& enrollmentID)
	{
		for (int i = 0; i < EnrolledCoursesCount; ++i) {
			if (Enrollments[i].getEnrollmentID() == enrollmentID) {
				for (int j = i; j < EnrolledCoursesCount - 1; ++j) {
					Enrollments[j] = Enrollments[j + 1];
				}
				--EnrolledCoursesCount;
				return;
			}
			else
			{
				cout << "Not enrolled in course with ID : " << enrollmentID << endl;
			}
		}
	}

	void WithdrawCourse(const string& CourseID)
	{
		for (int k = 0; k < EnrolledCoursesCount; ++k) {
			if (EnrolledCourses[k]->CID == CourseID) {
				for (int j = k; j < EnrolledCoursesCount - 1; ++j) {
					EnrolledCourses[j] = EnrolledCourses[j + 1];
				}
				--EnrolledCoursesCount;
				return;
			}
		}
		cout << "No student with ID " << CourseID << " is enrolled in this course." << endl;
	}
};

void Course::EnrollStudent(Student* student)
{
	if (EnrolledStudentsCount < MaxStudent)
	{
		EnrolledStudents[EnrolledStudentsCount++] = student;
		student->EnrolledCourses[student->EnrolledCoursesCount++] = this;
	}
	else
	{
		cout << "Max Students Enrolled in This Course!!!" << endl;
	}
}

void Course::WithdrawStudentCourseClass(const string& StudentID)
{
	for (int i = 0; i < EnrolledStudentsCount; ++i) {
		if (EnrolledStudents[i]->SID == StudentID) {
			for (int j = i; j < EnrolledStudentsCount - 1; ++j) {
				EnrolledStudents[j] = EnrolledStudents[j + 1];
			}
			--EnrolledStudentsCount;
			return;
		}
	}
	cout << "No student with ID " << StudentID << " is enrolled in this course." << endl;
}

Student students[MaxStudent];
Course courses[MaxCourses];

void EditEnrollment(Student& student, const string& enrollmentID) {  //bonus function
	for (int i = 0; i < student.EnrolledCoursesCount; ++i) {
		if (student.Enrollments[i].getEnrollmentID() == enrollmentID) {
			string newEnrollmentID;
			time_t newEnrollmentDate = 0;
			string newGrade;
			cout << "Enter new Enrollment ID: ";
			cin >> newEnrollmentID;
			cout << "Enter new Grade: ";
			cin >> newGrade;
			student.Enrollments[i].setEnrollmentID(newEnrollmentID);
			student.Enrollments[i].setGrade(newGrade);
			cout << "Enrollment details updated successfully!" << endl;
			return;
		}
	}
	cout << "Enrollment with ID " << enrollmentID << " not found for the student." << endl;
}

void AddStudent()
{
	if (StudentCount >= MaxStudent)
	{
		cout << " Maximum Number Of Students !!! " << endl;
		return;
	}
	else
	{
		ofstream studenttxt;  //File Based System Bonus
		float cgpa = 0.0;
		studenttxt.open("Student Data.txt", ios::out | ios::app);
		cout << " Enter Student ID : ";
		cin >> students[StudentCount].SID;
		cout << " Enter Student Name : ";
		cin.ignore();
		getline(cin, students[StudentCount].SName);
		cout << " Enter Student Date Of Birth ( DD/MM/YYYY ) : ";
		getline(cin, students[StudentCount].DateOfBirth);
		cout << " Enter Student Phone Number : ";
		cin >> students[StudentCount].PhoneNumber;
		cout << " Enter Student CGPA : ";
		cin >> cgpa;
		students[StudentCount].setCGPA(cgpa);
		cout << " Enter Number Of Completed Courses : ";
		cin >> students[StudentCount].NumCompCourses;
		studenttxt << "\n" << " Student Name : " << students[StudentCount].SName << " ID : " << students[StudentCount].SID << " Date Of Birth : " << students[StudentCount].DateOfBirth << " Number : " << students[StudentCount].PhoneNumber << " CGPA : " << students[StudentCount].getCGPA() << " Number Of Completed Courses : " << students[StudentCount].NumCompCourses;
		studenttxt.close();
		++StudentCount;
		cout << " Added Successfully ! ";
	}
}
void DisplayStudents()
{
	if (StudentCount == 0)
	{
		cout << " No Students ! " << endl;
		return;
	}
	else
	{
		cout << " List Of Students : " << endl;
		for (int i = 0; i < StudentCount; ++i)
		{
			cout << "Name : " << students[i].SName << ", ID : " << students[i].SID << ", Date Of Birth : " << students[i].DateOfBirth << ", Phone Number : " << students[i].PhoneNumber << " , CGPA : " << students[i].getCGPA() << ", Completed Courses : " << students[i].NumCompCourses << endl;
		}
	}
}
void AddCourse()
{
	if (CourseCount >= MaxCourses)
	{
		cout << " Maximum Number Of Courses !!! ";
		return;
	}
	else
	{
		ofstream coursetxt;   //File Based System Bonus
		coursetxt.open("Course Data.txt", ios::out | ios::app);
		cout << " Enter Course ID : ";
		cin >> courses[CourseCount].CID;
		cout << " Enter Course Name : ";
		cin.ignore();
		getline(cin, courses[CourseCount].CName);
		cout << " Enter Instructor Name : ";
		getline(cin, courses[CourseCount].InstName);
		cout << " Enter Credit Hours : ";
		cin >> courses[CourseCount].CreditHours;
		coursetxt << "\n " << " Course Name : " << courses[CourseCount].CName << " ID : " << courses[CourseCount].CID << " Instructor Name : " << courses[CourseCount].InstName << " Credit Hourse : " << courses[CourseCount].CreditHours;
		coursetxt.close();
		++CourseCount;
		cout << " Course Added ! ";
	}
}
void DisplayCourses()
{
	if (CourseCount == 0)
	{
		cout << " No Courses Found ! " << endl;
		return;
	}
	else
	{
		cout << " List Of Courses : " << endl;
		for (int i = 0; i < CourseCount; ++i)
		{
			cout << " Name : " << courses[i].CName << " , ID : " << courses[i].CID << " , Instractor : " << courses[i].InstName << " , Credit Hours : " << courses[i].CreditHours << endl;
		}
	}
}
void SearchStudentByID(const string& StudentID)
{
	bool found = false;
	for (int i = 0; i < StudentCount; ++i)
	{
		if (students[i].SID == StudentID)
		{
			cout << " Student Name : " << students[i].SName << " , ID : " << students[i].SID << " , Date Of Birth : " << students[i].DateOfBirth << " , Phone Number : " << students[i].PhoneNumber << " , CGPA : " << students[i].getCGPA() << " , Completed Courses : " << students[i].NumCompCourses << endl;
			cout << " Enrollrd Courses : \n";
			for (int j = 0; j < students[i].EnrolledCoursesCount; ++j)
			{
				cout << " Course Name : " << students[i].EnrolledCourses[j]->CName;
			}
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << " Student With ID : " << StudentID << " Is Not Found " << endl;
	}
}
void SearchStudentByName(const string& StudentName)  //bonus function
{
	bool found = false;
	for (int i = 0; i < StudentCount; ++i)
	{
		if (students[i].SName == StudentName)
		{
			cout << " Student Name : " << students[i].SName << " , ID : " << students[i].SID << " , Date Of Birth : " << students[i].DateOfBirth << " , Phone Number : " << students[i].PhoneNumber << " , CGPA : " << students[i].getCGPA() << " , Completed Courses : " << students[i].NumCompCourses << endl;
			cout << " Enrollrd Courses : \n";
			for (int j = 0; j < students[i].EnrolledCoursesCount; ++j)
			{
				cout << " Course Name : " << students[i].EnrolledCourses[j]->CName;
			}
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << " Student With ID : " << StudentName << " Is Not Found " << endl;
	}
}
void SearchCourseByID(const string& CourseID)
{
	bool found = false;
	for (int i = 0; i < CourseCount; ++i)
	{
		if (courses[i].CID == CourseID)
		{
			cout << " Course Name : " << courses[i].CName << " , ID : " << courses[i].CID << " , Instractor : " << courses[i].InstName << " , Credit Hours : " << courses[i].CreditHours << "\nEnrolled Students : " << endl;
			cout << " Enrolled Students : " << endl;
			for (int j = 0; j < courses[i].EnrolledStudentsCount; ++j)
			{
				char buffer[26];
				ctime_s(buffer, sizeof(buffer), &(courses[i].EnrolledStudents[j]->Enrollments->EnrollmentDate));//ctime library fix !
				cout << " Student Name : " << courses[i].EnrolledStudents[j]->SName << ", ID : " << courses[i].EnrolledStudents[j]->SID << ", Grade : " << courses[i].EnrolledStudents[j]->Enrollments->getGrade() << ", Enrolled in : " << buffer << endl;
			}
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << " Course With ID : " << CourseID << " Not Found " << endl;
	}
}
void SearchCourseByName(const string& CourseName)  //bonus function
{
	bool found = false;
	for (int i = 0; i < CourseCount; ++i)
	{
		if (courses[i].CName == CourseName)
		{
			cout << " Course Name : " << courses[i].CName << " , ID : " << courses[i].CID << " , Instractor : " << courses[i].InstName << " , Credit Hours : " << courses[i].CreditHours << "\nEnrolled Students : " << endl;
			for (int j = 0; j < courses[i].EnrolledStudentsCount; ++j)
			{
				char buffer[26];
				ctime_s(buffer, sizeof(buffer), &(courses[i].EnrolledStudents[j]->Enrollments->EnrollmentDate));//ctime library fix !
				cout << " Student Name : " << courses[i].EnrolledStudents[j]->SName << ", ID : " << courses[i].EnrolledStudents[j]->SID << ", Grade : " << courses[i].EnrolledStudents[j]->Enrollments->getGrade() << ", Enrolled in : " << buffer << endl;
			}
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << " Course With ID : " << CourseName << " Not Found " << endl;
	}
}

void DeleteStudent(const string& StudentID);
void DeleteCourse(const string& CourseID);

void EditStudent(const string& StudentID)
{
	bool found = false;
	for (int i = 0; i < StudentCount; ++i)
	{
		if (students[i].SID == StudentID)
		{
			float cgpa = 0.0;
			cout << " Enter Student New ID : ";
			cin >> students[StudentCount].SID;
			cout << " Enter Student New Name : ";
			cin.ignore();
			getline(cin, students[StudentCount].SName);
			cout << " Enter Student New Date Of Birth ( DD/MM/YYYY ) : ";
			getline(cin, students[StudentCount].DateOfBirth);
			cout << " Enter Student New Phone Number : ";
			cin >> students[StudentCount].PhoneNumber;
			cout << " Enter Student New CGPA : ";
			cin >> cgpa;
			students[StudentCount].setCGPA(cgpa);
			cout << " Enter New Number Of Completed Courses : ";
			cin >> students[StudentCount].NumCompCourses;
			++StudentCount;
			cout << " Edited Successfully ! ";
			DeleteStudent(StudentID);
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << " Student With ID : " << StudentID << " Is Not Found " << endl;
	}
}
void EditCourse(const string& CourseID)
{
	bool found = false;
	for (int i = 0; i < CourseCount; ++i)
	{
		if (courses[i].CID == CourseID)
		{
			cout << " Enter Course New ID : ";
			cin >> courses[CourseCount].CID;
			cout << " Enter Course New Name : ";
			cin.ignore();
			getline(cin, courses[CourseCount].CName);
			cout << " Enter Instructor New Name : ";
			getline(cin, courses[CourseCount].InstName);
			cout << " Enter New Credit Hours : ";
			cin >> courses[CourseCount].CreditHours;
			++CourseCount;
			cout << " Course Edited ! ";
			found = true;
			DeleteCourse(CourseID);
			break;
		}
	}
	if (!found)
	{
		cout << " Course With ID : " << CourseID << " Not Found " << endl;
	}
}
void DeleteArrStudent(Student arr[], int& size, int index) {
	if (index < 0 || index >= size) {
		return;
	}
	for (int i = index; i < size - 1; ++i) {
		arr[i] = arr[i + 1];
	}
	--size;
}
void DeleteArrCourse(Course arr[], int& size, int index) {
	if (index < 0 || index >= size) {
		return;
	}
	for (int i = index; i < size - 1; ++i) {
		arr[i] = arr[i + 1];
	}
	--size;
}
void DeleteStudent(const string& StudentID)
{
	bool found = false;
	for (int i = 0; i <= StudentCount; ++i)
	{
		if (students[i].SID == StudentID)
		{
			DeleteArrStudent(students, StudentCount, i);
			cout << " Student Deleted !!! ";
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << " Student With ID : " << StudentID << " Is Not Found " << endl;
	}
}

void DeleteCourse(const string& CourseID)
{
	bool found = false;
	for (int i = 0; i <= CourseCount; ++i)
	{
		if (courses[i].CID == CourseID)
		{
			DeleteArrCourse(courses, CourseCount, i);
			cout << " Course Deleted !!! ";
			found = true;
		}
	}
	if (!found)
	{
		cout << " Course With ID : " << CourseID << " Is Not Found " << endl;
	}
}

int main()
{
	int choice;
	do {
		cout << "\n======= Student Management System Menu by C++ PROs =======\n";
		cout << "1. Add Student\n";
		cout << "2. Display All Students\n";
		cout << "3. Add Course\n";
		cout << "4. Display All Courses\n";
		cout << "5. Search Student\n";
		cout << "6. Search Course\n";
		cout << "7. Delete Student\n";
		cout << "8. Delete Course\n";
		cout << "9. Edit Student\n";
		cout << "10. Edit Course\n";
		cout << "11. Enroll Student in Course\n";
		cout << "12. Withdraw Student from Course\n";
		cout << "13. Edit Enrollment\n";
		cout << "14. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			AddStudent();
			break;
		case 2:
			DisplayStudents();
			break;
		case 3:
			AddCourse();
			break;
		case 4:
			DisplayCourses();
			break;
		case 5:
		{
			int searchchoice;
			cout << " How To Search ( Name : 1 or ID : 2 ) : ";
			cin >> searchchoice;
			if (searchchoice == 2)
			{
				string studentID;
				cout << "Enter Student ID to search : ";
				cin >> studentID;
				SearchStudentByID(studentID);
				break;
			}
			else if (searchchoice == 1)
			{
				string studentName;
				cout << "Enter Student Name to search : ";
				cin.ignore();
				getline(cin, studentName);
				SearchStudentByName(studentName);
				break;
			}
			else
			{
				cout << "Invalid Choice !";
				break;
			}
			break;
		}
		case 6:
		{
			int searchchoice;
			cout << " How To Search ( Name : 1 or ID : 2 ) : ";
			cin >> searchchoice;
			if (searchchoice == 2)
			{
				string courseID;
				cout << "Enter Course ID to search: ";
				cin >> courseID;
				SearchCourseByID(courseID);
				break;
			}
			else if (searchchoice == 1)
			{
				string courseName;
				cout << "Enter Course Name to search: ";
				cin.ignore();
				getline(cin, courseName);
				SearchCourseByName(courseName);
				break;
			}
			else
			{
				cout << "Invalid Choice !";
				break;
			}
			break;
		}
		case 7:
		{
			string StudentID;
			cout << "Enter The ID Of The Student You Want To Delete : ";
			cin >> StudentID;
			DeleteStudent(StudentID);
			break;
		}
		case 8:
		{
			string CourseID;
			cout << "Enter The ID Of The Course You Want To Delete : ";
			cin >> CourseID;
			DeleteCourse(CourseID);
			break;
		}
		case 9:
		{
			string StudentID;
			cout << "Enter The ID Of The Student You Want To Edit : ";
			cin.ignore();
			getline(cin, StudentID);
			EditStudent(StudentID);
			break;
		}
		case 10:
		{
			string CourseID;
			cout << "Enter The ID Of The Course You Want To Edit : ";
			cin.ignore();
			getline(cin, CourseID);
			EditCourse(CourseID);
			break;
		}
		case 11: {
			string studentID, courseID, enrollmentID, grade;
			time_t enrollmentDate = time(0);
			cout << "Enter Student ID: ";
			cin >> studentID;
			cout << "Enter Course ID: ";
			cin >> courseID;
			cout << "Enter Enrollment ID: ";
			cin >> enrollmentID;
			cout << "Enter Grade: ";
			cin >> grade;
			Student* student = nullptr;
			for (int i = 0; i < StudentCount; ++i) {
				if (students[i].SID == studentID) {
					student = &students[i];
					break;
				}
			}

			Course* course = nullptr;
			for (int i = 0; i < CourseCount; ++i) {
				if (courses[i].CID == courseID) {
					course = &courses[i];
					break;
				}
			}
			if (student && course) {
				student->EnrollInCourse(enrollmentID, enrollmentDate, grade);
				course->EnrollStudent(student);
				cout << "Student enrolled in course successfully!" << endl;
			}
			else {
				cout << "Student or course not found." << endl;
			}
			break;
		}
		case 12: {
			string studentID, courseID;
			cout << "Enter Student ID: ";
			cin >> studentID;
			cout << "Enter Course ID: ";
			cin >> courseID;
			Course* course = nullptr;
			Student* student = nullptr;
			for (int i = 0; i < CourseCount; ++i) {
				if (courses[i].CID == courseID) {
					course = &courses[i];
					break;
				}
			}
			for (int j = 0; j < StudentCount; ++j)
			{
				if (students[j].SID == studentID)
				{
					student = &students[j];
					break;
				}
			}
			if (course && student) {
				course->WithdrawStudentCourseClass(studentID);
				student->WithdrawCourse(courseID);
				cout << "Student withdrawn from course successfully!" << endl;
			}
			else {
				cout << "Course or Student not found." << endl;
			}
			break;
		}
		case 13:
		{
			string studentID, enrollmentID;
			cout << "Enter the ID of the student: ";
			cin >> studentID;
			cout << "Enter the ID of the enrollment you want to edit: ";
			cin >> enrollmentID;
			Student* student = nullptr;
			for (int i = 0; i < StudentCount; ++i) {
				if (students[i].SID == studentID) {
					student = &students[i];
					break;
				}
			}
			if (student) {
				EditEnrollment(*student, enrollmentID);
			}
			else {
				cout << "Student with ID " << studentID << " not found." << endl;
			}
			break;
		}

		case 14:
			cout << "Exiting program. Goodbye!" << endl;
			break;

		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 14);
	return 0;
}
