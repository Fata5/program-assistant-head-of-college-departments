#include<iostream>
#include<Windows.h>
#include<fstream>
#include<string>
#include<sstream>

void menu();

void listAndWorkWithGroups();
void UpdateDataInformation();
void ShowStudentsOfGroupByNumber(int index);
void ChangeStudentsFields(int input, int groupForChanging, int studentNum);

#pragma region Classes

class Student {
public:
	std::string name = "NoName";
	int avgGrade = 0;
	int age = 0;

};


class Group {
public:
	std::string name = "NoName";
	int numbersOfStudents = 0;
	int indicatorOfSuccess = 0;
	Student* array = nullptr;


	void addStudent(Student temp) {
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
#pragma endregion

int countOfGroups = 0;

Group* pGroups = nullptr;
int main() {




	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);



	while (true)
		menu();

}



void menu() {
	std::cout << "1.������ ���� �� ��������" << std::endl;
	std::cout << "2.������� ������ �� �������" << std::endl;
	std::cout << "3.��������� �������� �� ����� �����" << std::endl;
	std::cout << "4.�������� ���� ������" << std::endl;

	int answer;
	std::cin >> answer;

	switch (answer)
	{
	case 1: {
		listAndWorkWithGroups();
		break;
	}
	case 4: {
		UpdateDataInformation();
		break;
	}
	default:
		break;
	}

}

void UpdateDataInformation() {
	countOfGroups = 0;
	std::fstream groupsData;
	groupsData.open("groupsAndStudentDataBase.txt", std::ios::in);
	if (groupsData.is_open() == false)
		return;

	std::string currLine;


	Student tempStudent;

	while (getline(groupsData, currLine)) {

		std::stringstream ss(currLine);
		if (currLine[0] == 'G')
		{
			countOfGroups++;


			Group* pTempGroups = new Group[countOfGroups];
			for (int i = 0; i < countOfGroups - 1; i++) {
				if (countOfGroups > 1)
					pTempGroups[i] = pGroups[i];
			}
			delete[] pGroups;
			pGroups = pTempGroups;
			ss.ignore(2);
			std::getline(ss, pGroups[countOfGroups - 1].name);

		}
		if (currLine[0] != 'G' && currLine[0] != ' ')
		{
			pGroups[countOfGroups - 1].numbersOfStudents++;



			std::getline(ss, tempStudent.name, '|');
			ss >> tempStudent.age;
			ss.ignore(2);
			ss >> tempStudent.avgGrade;

			pGroups[countOfGroups - 1].addStudent(tempStudent);



		}
	}
}

void listAndWorkWithGroups() {


	int vidpovid;
	std::cout << "1.���������� �����" << std::endl;
	std::cout << "2.���������� ����� �� ��������" << std::endl;
	std::cin >> vidpovid;
	int groupForChanging = -1;
	switch (vidpovid)
	{

	case 1: {
		for (int i = 0; i < countOfGroups; i++) {
			std::cout << std::endl;
			std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||| " << std::endl;
			std::cout << "�����:" << pGroups[i].name << std::endl;

			for (int x = 0; x < pGroups[i].numbersOfStudents; x++) {
				std::cout << "==================================================== " << std::endl;
				std::cout << "��'�: " << pGroups[i].array[x].name << std::endl;
				std::cout << "³�: " << pGroups[i].array[x].age << std::endl;
				std::cout << "������� ������: " << pGroups[i].array[x].avgGrade << std::endl;
				std::cout << "==================================================== " << std::endl;

			}
			std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||| " << std::endl;
		}
		break;

	}

	case 2:
	{

		std::string desiredGroupName;
		std::cout << "������ ����� ����� � ��� ������ ������� �����������:" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, desiredGroupName);

		for (int i = 0; i < countOfGroups; i++) {
			std::cout << pGroups[i].name << std::endl;
			if (pGroups[i].name == desiredGroupName) {
				groupForChanging = i;

			}

		}

		if (groupForChanging == -1) {
			std::cout << "���� ����� � ����� ��'�� ��������� �� ���" << std::endl;
			break;
		}

		std::cout << "�� �� ������ �������?:" << std::endl;
		std::cout << "1.������ ��'� �����:" << std::endl;
		std::cout << "2.������ ���� ��������:" << std::endl;
		std::cout << "3.�������� �������� �� ������" << std::endl;

		int input;
		std::cin >> input;
		switch (input)
		{

		case 1:
		{
			std::string newName;
			std::cout << "������ ���� ����� �����:";
			std::cin >> newName;
			pGroups[groupForChanging].name = newName;
			break;

		}
		case 2:
		{
			ShowStudentsOfGroupByNumber(groupForChanging);
			int studentNum;
			std::cout << "�������� ���������� ����� �������� :";
			std::cin >> studentNum;
			int input;
			std::cout << "��� ���� �� ������ ������" << std::endl;
			std::cout << "1.��'�" << std::endl;
			std::cout << "2.³�" << std::endl;
			std::cout << "3.������� ������" << std::endl;
			std::cin >> input;

			std::cin.ignore();

			int input2 = 1;
			while (true) {

				if (input2 == 1)
					ChangeStudentsFields(input, groupForChanging, studentNum);
				//input2 = 0;

				std::cout << "1.������ ���� ����" << std::endl;
				std::cout << "2.��������" << std::endl;
				std::cin >> input2;

				if (input2 == 2)
					break;
			}


			break;


		}


		}



	}



	}
}

void ChangeStudentsFields(int input, int groupForChanging, int studentNum) {
	//std::cin.ignore();
	switch (input) {
	case 1: {
		std::string newName;
		std::cout << "������ ���� ��'�" << std::endl;
		std::getline(std::cin, newName);
		pGroups[groupForChanging].array[studentNum].name = newName;
		break;
	}
	case 2: {
		int newAge;
		std::cout << "������ ����� ��" << std::endl;
		std::cin >> newAge;
		pGroups[groupForChanging].array[studentNum].age = newAge;
		break;
	}
	case 3: {
		int newAvgGrade;
		std::cout << "������ ���� ������� ������" << std::endl;
		std::cin >> newAvgGrade;
		pGroups[groupForChanging].array[studentNum].avgGrade = newAvgGrade;
		break;
	}



	}
}

void ShowStudentsOfGroupByNumber(int index) {
	for (int i = 0; i < pGroups[index].numbersOfStudents; i++) {
		std::cout << "===================================" << std::endl;
		std::cout << i << ".��'�:" << pGroups[index].array[i].name << std::endl;
		std::cout << "³�:" << pGroups[index].array[i].age << std::endl;
		std::cout << "������� ������:" << pGroups[index].array[i].avgGrade << std::endl;
		std::cout << "===================================" << std::endl;
	}

}

