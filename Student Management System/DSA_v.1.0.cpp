#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <conio.h>

using namespace std;

struct Course* searchCourseById(int);
struct Student* searchStudentById(int);
bool checkDuplicates(int, int);

struct Course {
	
	int courseID, creditHour;
	string courseName, grade;
	Course *next;
	
	void DisplayCourseInfo() {
		cout << "________\t____________\n";
		cout << courseID << "\t" << courseName << "\t" << creditHour << endl;
		cout << "________\t____________\n";
	}

};

struct Student {
	
	int Sid, age;
	Course *first=NULL, *top;
	string Fname, Lname, gender;
	Student *next;
	

	Course* getCourses() {
		
		ifstream st_course("student_course.txt");
		
		int cid, sid;
		string grade;
		
		
		while(st_course >> sid >> cid >> grade) {
			
			if(sid != this->Sid)
				continue;
			
			if (first == NULL) {
				first = searchCourseById(cid);
				
				//this read the grade and store it in it's grade attribute
				first->grade = grade;
				top = first;
			} else {
				Course *temp = searchCourseById(cid);
				
				//this read the grade and store it in it's grade attribute
				temp->grade = grade;
				
				top->next = temp;
				top = top->next;
			} 
			top->next = NULL;
		}
		return first;
	}
	
	//this checks wether the course already exists or not
	bool checkCourse(int cid) {
		Course* curr = getCourses();
		while(curr != NULL) {
			if (curr->courseID == cid){
				return true;
			}
			curr = curr->next;
		}
		return false;
	}
	
	void registerCourse(int CId) {
		if (searchCourseById(CId) == NULL){
			cout << "There is no course with this ID!";
			return;
		}
		if(checkCourse(CId)) {
			cout << "This student has already been registered to this course";
			return;
		}
		
		if (first == NULL) {
			first = searchCourseById(CId);
			top = first;
		} else {
			Course *temp = searchCourseById(CId);
			top->next = temp;
			top = top->next;
		}
		top->next = NULL;
	}
};

void addNewCourse() {
		
	fstream courseLog("CourseLog.txt", ios::out | ios::app);
	char cont;
	do{
		
		Course *newCourse = new Course();
		
		cout << "Course id: ";
        cin >> newCourse->courseID;
        
        if(searchCourseById(newCourse->courseID) != NULL) {
			cout << "This course already exists\n";
			return;
		}
        cout << "\nCourse name: ";
        cin >> newCourse->courseName;
        cout << "\nCredit Hour: ";
        cin >> newCourse->creditHour;
        
		courseLog << newCourse->courseID << '\t' << newCourse->courseName << '\t' << newCourse->creditHour << "\n";
        
		cout << "Press x to abort or any key to continue: ";
        cont = getch();
        
		system("cls");

	} while(cont != 'x' && cont !='X');
}

Course* readCourseLog() {
	ifstream courseLog("CourseLog.txt");
	Course *last = new Course();
	Course *head = NULL;
	while(courseLog.good()) {
		
		Course *course = new Course();
		courseLog >> course->courseID >> course->courseName >> course->creditHour;
		
		if (head == NULL) {
			head = course;
			last = course;
		} else {
			last->next = course;
			last = last->next;
		} 	

		last->next = NULL;
	}
	return head;
}

Course* searchCourseById(int CId) {
	Course *head = readCourseLog();
	while (head != NULL) {
		if (head->courseID == CId)
			return head;
		head = head->next; 
	}
	return NULL;
}

void registerStudent() {
	
	fstream studentLog("studentLog.txt", ios::out | ios::app);
	
	char cont;//termination
	do{
		
		Student *newStudent = new Student();
				
		cout << "Student id: ";
        cin >> newStudent->Sid;
        cout << "\nStudent first name: ";
        cin >> newStudent->Fname;
        cout << "\nStudent Father name: ";
        cin >> newStudent->Lname;
        cout << "\nStudent Age: ";
        cin >> newStudent->age;
        cout << "\nStudent Gender: ";
        cin >> newStudent->gender;

        if(searchStudentById(newStudent->Sid) != NULL) {
			cout << "This student already exists\n";
			return;
		}
        
        studentLog << newStudent->Sid << '\t' << newStudent->Fname << '\t' << newStudent->Lname << '\t'
        << newStudent->age << '\t' << newStudent->gender << endl;
        
		cout << "Enter x to abort or any other key to continue: ";
        cont = getch();
        
		system("cls");

	} while(cont != 'x' && cont !='X');
}

Student* readStudentLog() {
	ifstream studentLog("studentLog.txt");
	Student *last = new Student();
	Student *head = NULL;
	while(studentLog.good()) {
		
		Student *student = new Student();
		studentLog >> student->Sid >> student->Fname >> student->Lname >> student->age >> student->gender;
		
		if (head == NULL) {
			head = student;
			last = student;
		} else {
			last->next = student;
			last = last->next;
		} 			
		last->next = NULL;
	}
	studentLog.close();
	return head;
}

Student* searchStudentById(int studentId) {
	
	Student *head = readStudentLog();
	while(head != NULL) {
		if (head->Sid == studentId) 
			return head;
		head = head->next; 
	}
	return NULL;
	
}

void registerCoursesForStudent(){
	
	int studentID;
	cout << "Enter Student ID: ";
	cin >> studentID;

	Student *student = searchStudentById(studentID);
	
	if (student == NULL){
		cout << "There is no student with this ID!\n";
		return;
	}
	
	int courseID;
	char cont;
	do {
		cout << "Enter the courseIDs: ";
		cin >> courseID;
		student->registerCourse(courseID);
		cout << "\nEnter x to abort or any other key to continue:_ ";
		cont = getch();
		cout << endl;
		
	} while(cont != 'x' && cont !='X');

	fstream studentCourseLog("student_course.txt", ios::out | ios::app);
	Course *curr = student->first;
	while(curr != NULL) {
		studentCourseLog << student->Sid << "\t" << curr->courseID << "\t" << "not_assigned" << endl;
		curr = curr->next;
	}	
	cout << "Course added to student successfully!\n";
}

void gradeStudents() {
	int studentID;
	cout << "Enter Student ID: ";
	cin >> studentID;
	
	Student *student = searchStudentById(studentID);
	
	if (student == NULL) {
		cout << "There is no student with this ID!";
		return ;
	}
	
	Course *curr = student->getCourses();
	
	//This will display the courses of a student	
	while (curr != NULL) {
		cout << curr->courseID << "\t" << curr->courseName << "\t" << curr->creditHour << endl;
		curr = curr->next;
	}
	
	fstream temp("temp.txt", ios::out);
	fstream student_course("student_course.txt", ios::out|ios::in);
	
	int cid, sid, newcid;
	
	string newGrade, grade;
	
	char cont;//Termination controller
	
	//this will store the course id as key and the grade s a value
	map<int, string> courseGrade; 

	do{
		cout << "Enter the course id: ";
		cin >> newcid;
		cout << "Enter the grade: ";
		cin >> newGrade;
	
		//check the entered course belongs to the student and populate the course_grade map for a student
		if (student->checkCourse(newcid)) {
			courseGrade[newcid] = newGrade;
		};
		
		cout << "Insert any key to continue or x to abort:_";
		cont = getch();
	
	} while(cont != 'x' & cont != 'X');
		
	while(student_course >> sid >> cid >> grade ) {
		if(student->Sid == sid && courseGrade.find(cid) != courseGrade.end()) {
			temp << sid << "\t" << cid << "\t" << courseGrade[cid] << endl;
		} else {
			temp << sid << "\t" << cid << "\t" << grade << endl;
		}
	}
	cout << "Grade assigned succesfully !!\n";
	student_course.close();
	temp.close();
    remove("student_course.txt");
	rename("temp.txt", "student_course.txt");
}

void deleteStudent() {
	int id;
	cout << "Please insert the id of the student to be deleted: ";
	cin >> id;
	
	Student *curr = readStudentLog();
	
	Student *dummy = new Student();
	dummy->next = curr;
	
	Student *prev =  dummy;
	Student *student = searchStudentById(id);
	
	if(student == NULL) {
		cout << "The above student doesn't exist!\n";
		return;
	}
	while(curr != NULL) {
		
		if(curr->Sid == student->Sid) {
			prev->next = curr->next;
			delete curr;
			break;			
		}
		prev = curr;
		curr = curr->next;
	}
	//dummy->next is our new head 
	ofstream studentLog("studentLog.txt");
	Student *temp = dummy->next;
	//regsiter the updated linked list to the file
	while(temp->next != NULL) {
		studentLog << temp->Sid << '\t' << temp->Fname << '\t' << temp->Lname << '\t'
        << temp->age << '\t' << temp->gender << endl;
		temp = temp->next;
	}
	cout << "Student deleted successfully!!!\n";
} 

void deleteCourse() {
	int id;
	cout << "Please insert the id of the course to be deleted: ";
	cin >> id;
	
	Course *curr = readCourseLog();
	
	Course *dummy = new Course();
	dummy->next = curr;
	
	Course *prev =  dummy;
	Course *course = searchCourseById(id);
	
	if(course == NULL) {
		cout << "The above course doesn't exist!\n";
		return;
	}
	while(curr != NULL) {
		
		if(curr->courseID == course->courseID) {
			prev->next = curr->next;
			delete curr;
			break;			
		}
		prev = curr;
		curr = curr->next;
	}
	//dummy->next is our new head 
	ofstream courseLog("CourseLog.txt");
	Course *temp = dummy->next;
	//regsiter the updated linked list to the file
	while(temp->next != NULL) {
		courseLog << temp->courseID <<"\t" << temp->courseName << "\t" << temp->creditHour << endl;
		temp = temp->next;
	}
	cout << "Course deleted successfully!!!\n";
}

char* getFullNameArray(string fName, string lName) {
    string fullName = fName + lName;
    char* fullNameArray = new char[fullName.length() + 1];
    strcpy(fullNameArray, fullName.c_str());
    return fullNameArray;
}


Student* iSort(Student* head) {
    Student* dummy = new Student();
    dummy->next = head;
    Student* prev = dummy;
    Student* curr = head;
    Student* next = curr->next;

    while (next != NULL) {
        char* currFullNameArray = getFullNameArray(curr->Fname, curr->Lname);
        char* nextFullNameArray = getFullNameArray(next->Fname, next->Lname);
        char* prevNextFullNameArray = getFullNameArray(prev->next->Fname, prev->next->Lname);

        if (strcmp(currFullNameArray, nextFullNameArray) > 0) {
            while (prev->next != NULL && strcmp(prevNextFullNameArray, nextFullNameArray) < 0) {
                prev = prev->next;
                if (prev->next != NULL) {
                    prevNextFullNameArray = getFullNameArray(prev->next->Fname, prev->next->Lname);
                }
            }

            curr->next = next->next;
            next->next = prev->next;
            prev->next = next;

            prev = dummy;
        } else {
            curr = next;
        }

        next = curr->next;
    }

    return dummy->next;
}

void displayStudent() {
	int sid;
	cout << "Please insert the studets ID:_";
	cin >> sid;
	
	Student* student = searchStudentById(sid);
	if(student == NULL) {
		cout << "There is no student with the above id!!!";
		return;
	} 
	
	cout << student->Sid << "\t" <<  student->Fname << "\t" << student->Lname << "\t" << student->age << "\t" << student->gender << endl;
    Course *courses = student->getCourses();
    while(courses != NULL) {
    	cout << "________\t____________\n";
    	cout << endl << courses->courseID << "   " << courses->courseName << "   " << courses->creditHour << "   " << courses->grade << endl;
    	courses = courses->next;
	}
	cout << "________\t____________\n";
}
void displayCourse() {
	int cid;
	cout << "Please insert the studets ID:_";
	cin >> cid;
	searchCourseById(cid)->DisplayCourseInfo();
}
void displayAllStudents() {
	Student* head = readStudentLog();
	while(head->next != NULL) {
		cout << head->Sid << "\t" <<  head->Fname << "\t" << head->Lname << "\t" << head->age << "\t" << head->gender << endl;
		head = head->next;
	}
}


int main() {
	int c;
	
	while (true){
		
		cout << "\t Wellcome to our Student course management System!!! \n1. Add new student\n2. Add new course \n3. Register students to courses\n";
		cout << "4. Give grade to students \n5. Search a student \n6. Search a course\n7. Sort student\n8. Display students\n9. Delete Students\n10. Delete Course\n0. TO EXIT.\n_";
		
		cin >> c;
		
		//this will store the head of the sorted student record
		Student* curr;
		
		system ("cls");
		
		switch(c){
		
		case 1:
			registerStudent();
			system("pause");
			system("cls");
			break;
		
		case 2: 
			addNewCourse();
			system("pause");
			system("cls");
			break;
		
		case 3:
		    registerCoursesForStudent();
			system("pause");
			system("cls");
		    break;
		
		case 4:
			gradeStudents();
			system("pause");
			system("cls");
			break;
		
		case 5:
			displayStudent();
			system("pause");
			system("cls");
			break;
		
		case 6:
			displayCourse();
			system("pause");
			system("cls");
			break;
		
		case 7:
			curr = iSort(readStudentLog());
			while (curr->next != NULL) {
        		cout << curr->next->Sid << "\t" <<  curr->next->Fname << "\t" << curr->next->Lname << "\t" << curr->next->age << "\t" << curr->next->gender << endl;
        		curr = curr->next;
			}
			system("pause");
			system("cls");
			break;	
		
		case 8:
			displayAllStudents();
			system("pause");
			system("cls");
			break;
		
		case 9:
			deleteStudent();
			system("pause");
			system("cls");
			break;
		
		case 10:
			deleteCourse();
			system("pause");
			system("cls");
			break;
		
		case 0:
			return -1;
			
		default:
			cout << "Please Enter a valid input!\n";
			system("pause");
			system("cls");
			break;			
		}
	}	
	return 0;
}
