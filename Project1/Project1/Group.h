
#include<iostream>
#include"Student.h"
#include"Curator.h"

class Group {
public:
	std::string name = "NoName";
	int numbersOfStudents = 0;
	Student* array = nullptr;
	bool deleted = false;
	Curator curator;

	void addStudent(Student temp) {
		this->numbersOfStudents++;
		Student* pTemp = new Student[numbersOfStudents + 1];
		for (int i = 0; i < numbersOfStudents; i++) {
			if (numbersOfStudents > 1)
				pTemp[i] = array[i];
		}

		pTemp[numbersOfStudents - 1] = temp;

		delete[] array;
		array = pTemp;

	}
};