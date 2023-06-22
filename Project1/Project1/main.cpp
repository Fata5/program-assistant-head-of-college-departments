#include<Windows.h>
#include<fstream>
#include<string>
#include<sstream>
#include"FunctionsPrototypes.h"
#include"Event.h"


const char* DataBaseGroups = "groupsAndStudentsDataBase.txt";
const char* DataBaseEvents = "eventsDataBase.txt";

int countOfEvents = 0;
int countOfGroups = 0;

Event* pEvents = nullptr;
Group* pGroups = nullptr;
int main() {
	UpdateDataInformation();
	UpdateEventsInformation();



	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	
	while(true)
	menu();

}



void menu() {


	std::cout << "1. ������ ���� �� �������� (Groups and students lists)" << std::endl;
	std::cout << "2. ������� ������ �� ������� (Event charts at the department)" << std::endl;
	std::cout << "3. ��������� �������� �� ����� ����� (Performance and knowledge quality indicators)" << std::endl;
	std::cout << "4. �������� ���� ����� (Update the database)" << std::endl;

	int answer;
	std::cin >> answer;

	switch (answer)
	{
	case 1: {
		WorkWithGroups();
		break;
	}
	case 2: {
		MakingSchedules();
		break;
	}
	case 3: {
		CalculateQualityAndSuccessOfGroups();
		break;

	}
	case 4: {
		UpdateDataBase();
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
	groupsData.open(DataBaseGroups, std::ios::in);
	if (groupsData.is_open() == false)
		return;
	std::string currLine;
	Student tempStudent;

	while (getline(groupsData, currLine)) {
		std::stringstream ss(currLine);
		if (currLine[0] == 'C')
		{
			ss.ignore(2);
			std::getline(ss, pGroups[countOfGroups - 1].curator.name);
		}
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
		if (currLine[0] != 'G' && currLine[0] != ' ' && currLine[0] != 'C')
		{
			std::getline(ss, tempStudent.name, '|');
			ss >> tempStudent.age;
			ss.ignore(2);
			ss >> tempStudent.avgGrade;

			pGroups[countOfGroups - 1].addStudent(tempStudent);

		}
	}
}
void UpdateDataBase() {
	system("cls");
	std::ofstream groupsData;
	groupsData.open(DataBaseGroups, std::ios::out);
	if (groupsData.is_open() == false)
		return;

	
	for (int i = 0; i < countOfGroups; i++) {
		if (pGroups[i].deleted == false) {
			groupsData << "G " << pGroups[i].name << std::endl;
			for (int j = 0; j < pGroups[i].numbersOfStudents; j++) {
				if (pGroups[i].array[j].deleted == false)
					groupsData << pGroups[i].array[j].name << "|" << pGroups[i].array[j].age << " | " << pGroups[i].array[j].avgGrade << "\n";
			}
			groupsData <<"C " << pGroups[i].curator.name << "\n";
		}
	}

	groupsData.close();

}
void WorkWithGroups() {
	system("cls");
	
	int vidpovid;

	std::cout << "1. ���������� ����� (View groups)" << std::endl;
	std::cout << "2. ���������� ����� �� �������� (Edit groups and students)" << std::endl;
	std::cout << "3. �������� ���� ����� (Create a new group)" << std::endl;
	std::cout << "4. �������� ����� (Delete a group)" << std::endl;

	std::cin >> vidpovid;
	int groupForChanging = -1;

	switch (vidpovid) 
	{

	case 1: 
	{
		for (int i = 0; i < countOfGroups; i++) {
			if (pGroups[i].deleted == false) {
				std::cout << std::endl;
				std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||| " << std::endl;
				std::cout << "����� (Group):" << pGroups[i].name << std::endl;

				for (int x = 0; x < pGroups[i].numbersOfStudents; x++) {
					if (pGroups[i].array[x].deleted == false) {
						std::cout << "==================================================== " << std::endl;
						std::cout << "��'� (Name): " << pGroups[i].array[x].name << std::endl;
						std::cout << "³� (Age): " << pGroups[i].array[x].age << std::endl;
						std::cout << "������� ������ (Average grade): " << pGroups[i].array[x].avgGrade << std::endl;
						std::cout << "==================================================== " << std::endl;
					}
				}
				std::cout << "������� (Curator):" << pGroups[i].curator.name << std::endl;
				std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||| " << std::endl;
			}
		}
		break;

	}

	case 2:
	{
		for (int i = 0; i < countOfGroups; i++) {
			if(pGroups[i].deleted == false)
			std::cout << i << "." <<pGroups[i].name << std::endl;
		}
		
		
		int desiredGroupNumber;
		std::cout << "������ ����� ����� � ��� ������ ������� ����������� (Enter the group number you want to edit):" << std::endl;
		std::cin >> desiredGroupNumber;

		if (desiredGroupNumber > countOfGroups) {
			std::cout << "���� ����� � ����� ������� (There is no group with that number)" << std::endl;
			break;
		}
			
		groupForChanging = desiredGroupNumber;

	
		std::cout << "�� �� ������ �������? (What would you like to do?)" << std::endl;
		std::cout << "1.������ ��'� ����� (Change group name)" << std::endl;
		std::cout << "2.������ ���� �������� (Modify student details)" << std::endl;
		std::cout << "3.�������� �������� �� ������ (Remove a student from the list)" << std::endl;
		std::cout << "4.������ �������� �� ������ (Add a student to the list)" << std::endl;
		std::cout << "5.������ ��'� �������� (Change curator's name)" << std::endl;

		int input;
		std::cin >> input;
		switch (input)
		{

			case 1:
			{
				std::string newName;
				std::cout << "������ ���� ����� ����� (Enter the new group name):";
				std::cin.ignore();
				std::getline(std::cin, newName);
				pGroups[groupForChanging].name = newName;
				break;

			}
			case 2:
			{
				ShowStudentsOfGroupByNumber(groupForChanging);
				int studentNum;
				std::cout << "������ ����� �������� ���� ����� ������ ������ (Enter the number of the student whose fields you want to modify):";
				std::cin >> studentNum;
				int input;

				while (true) {
					std::cout << "��� ���� �� ������ ������ (Which field do you want to modify ? )" << std::endl;
					std::cout << "1. ��'� (Name)" << std::endl;
					std::cout << "2. ³� (Age)" << std::endl;
					std::cout << "3. ������� ������ (Average grade)" << std::endl;

					std::cin >> input;

					std::cin.ignore();

					int input2 = 1;
					if (input2 == 1)
					ChangeStudentsFields(input, groupForChanging, studentNum);
					


					std::cout << "1. ������ ���� ���� (Modify other fields)" << std::endl;
					std::cout << "2. �������� (Finish)" << std::endl;
					std::cin >> input2;

					if (input2 == 2)
						break;
				}


				break;


			}
			case 3:
			{
				ShowStudentsOfGroupByNumber(groupForChanging);
				int studentNum;
				std::cout << "������ ����� �������� ����� ������ �������� (Enter the number of the student you want to delete):";
				std::cin >> studentNum;

				if(pGroups[groupForChanging].numbersOfStudents > studentNum)
					pGroups[groupForChanging].array[studentNum].deleted = true;
				else {
					std::cout << "���� �������� �� ����� ������� (There is no student with that number)" << std::endl;
				}
				break;

			}

			case 4:
			{
				Student tempStudent;
				std::cout << "������ ��'� (Name): ";
				std::cin.ignore();
				std::getline(std::cin, tempStudent.name);

				std::cout << "������ ³� (Age): ";
				std::cin >> tempStudent.age;

				std::cout << "������ ������� ������ (Average grade): ";
				std::cin >> tempStudent.avgGrade;

				pGroups[groupForChanging].addStudent(tempStudent);
				break;
			}

			case 5:
			{
				std::cout << "������ ��'� �������� (Curator's name): ";
				std::cin.ignore();
				std::getline(std::cin, pGroups[groupForChanging].curator.name);
			}

			default:
				break;
		}

		break;


	 }

	case 3: 
	{
		Group TempGroup;
		std::cout << "������ ��'� ����� (Group name):" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, TempGroup.name);

		for (int i = 0; i < countOfGroups; i++) {
			if (TempGroup.name == pGroups[i].name) {
				std::cout << "����� � ����� ��'�� ��� ���� (Group with that name already exists)." << std::endl;
				break;
			}
		}

		std::cout << "������ ��'� �������� ����� (Curator's name):";
		std::cin.ignore();
		std::getline(std::cin, TempGroup.curator.name);

		AddNewGroup(TempGroup);
		break;
	}

	case 4:
	{
		for (int i = 0; i < countOfGroups; i++) {
			std::cout << i << ". ����� (Group): " << pGroups[i].name << std::endl;
		}

		int input;
		std::cout << "������ ����� �����, ��� ������ �������� (Enter the number of the group you want to delete): ";
		std::cin >> input;

		if (input < countOfGroups)
			pGroups[input].deleted = true;

		break;
		
	}

	default:
		break;


	}
}
void AddNewGroup(Group tempGroup) {
	countOfGroups++;
	Group* pTempGroups = new Group[countOfGroups];
	for (int i = 0; i < countOfGroups - 1; i++) {
		if (countOfGroups > 1)
			pTempGroups[i] = pGroups[i];
	}
	delete[] pGroups;
	pGroups = pTempGroups;
	pGroups[countOfGroups - 1] = tempGroup;
	


}
void ChangeStudentsFields(int input, int groupForChanging, int studentNum) {
	system("cls");
	switch (input) {
	case 1: {
		std::string newName;
		std::cout << "������ ���� ��'� (Enter the new name):" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, newName);
		pGroups[groupForChanging].array[studentNum].name = newName;
		break;
	}
	case 2: {
		int newAge;
		std::cout << "������ ����� �� (Enter the new age):" << std::endl;
		std::cin >> newAge;
		pGroups[groupForChanging].array[studentNum].age = newAge;
		break;
	}
	case 3: {
		int newAvgGrade;
		std::cout << "������ ���� ������� ������ (Enter the new average grade):" << std::endl;
		std::cin >> newAvgGrade;
		pGroups[groupForChanging].array[studentNum].avgGrade = newAvgGrade;
		break;
	}
	}
}
void ShowStudentsOfGroupByNumber(int index) {
	for (int i = 0; i < pGroups[index].numbersOfStudents; i++) {
		std::cout << "===================================" << std::endl;
		std::cout << i << ". ��'� (Name): " << pGroups[index].array[i].name << std::endl;
		std::cout << "³� (Age): " << pGroups[index].array[i].age << std::endl;
		std::cout << "������� ������ (Average grade): " << pGroups[index].array[i].avgGrade << std::endl;
		std::cout << "===================================" << std::endl;
	}
}

void CalculateQualityAndSuccessOfGroups() {
	system("cls");
	std::cout << "============================================" << std::endl;
	for (int i = 0; i < countOfGroups; i++) {

		int goodStudentGrade=0;
		int badStudentGrade=0;

		float sum = 0;
		float maxSum = pGroups[i].numbersOfStudents * 12;

		for (int x = 0; x < pGroups[i].numbersOfStudents; x++) {
			sum += pGroups[i].array[x].avgGrade;

			if (pGroups[i].array[x].avgGrade < 4)
				badStudentGrade++;
			else if(pGroups[i].array[x].avgGrade > 7) 
				goodStudentGrade++;
		}
		float resultQuality = goodStudentGrade / pGroups[i].numbersOfStudents * 100;
		float resultSuccess = sum  / maxSum * 100;
		

		std::cout << pGroups[i].name << " �� (has):" << std::endl;
		std::cout << "\t ����� ����� � (Quality of knowledge) :" << resultQuality <<'%' <<std::endl;
		std::cout << "\t �������� ������ � (Success rate):" << resultSuccess << '%'<< std::endl;
		std::cout << std::endl;
	}
	std::cout << "============================================" << std::endl;


}
void AddNewEvent(Event tempEvent) {
	countOfEvents++;
	Event* pTempEvents = new Event[countOfEvents];
	for (int i = 0; i < countOfEvents - 1; i++) {
		if (countOfEvents > 1)
			pTempEvents[i] = pEvents[i];
	}
	delete[] pEvents;
	pEvents = pTempEvents;
	pEvents[countOfEvents - 1] = tempEvent;



}
void UpdateEventsInformation() {
	countOfEvents = 0;

	std::fstream eventsData;
	eventsData.open(DataBaseEvents, std::ios::in);
	if (eventsData.is_open() == false)
		return;

	std::string currLine;

	Event tempEvent;
	
	while (std::getline(eventsData, currLine)) {
		std::stringstream ss(currLine);
		if (currLine[0] == 'E')
		{
			countOfEvents++;
			ss.ignore(2);
			std::getline(ss, tempEvent.name);
		}

		if (currLine[0] != 'E' && currLine[0] != 'D') {
			tempEvent.text.append(currLine);
			tempEvent.text.append("\n");
		}
		
		
			
		

		if (currLine[0] == 'D') {
			tempEvent.text.pop_back();
			ss.ignore(2);
			std::getline(ss, tempEvent.data);

			Event* pTempEvent = new Event[countOfEvents];

			for (int i = 0; i < countOfEvents - 1; i++) {
				if (countOfEvents > 1)
					pTempEvent[i] = pEvents[i];
			}
			delete[] pEvents;
			pEvents = pTempEvent;

			pEvents[countOfEvents - 1].name = tempEvent.name;
			pEvents[countOfEvents - 1].text = tempEvent.text;
			pEvents[countOfEvents - 1].data = tempEvent.data;
			tempEvent.text.erase();
		}
	}
	eventsData.close();
	
}
void UpdateEventsDataBase() {
	system("cls");

	std::ofstream groupsData;
	groupsData.open(DataBaseEvents, std::ios::out);
	if (groupsData.is_open() == false)
		return;


	for (int i = 0; i < countOfEvents; i++) {
		if (pEvents[i].deleted == false) {
			groupsData << "E " << pEvents[i].name << std::endl;

			groupsData << pEvents[i].text << std::endl;

			groupsData << "D " << pEvents[i].data << "\n";
		}
	}

	groupsData.close();
	  
}
void ShowEvents() {
	system("cls");
	for (int i = 0; i < countOfEvents; i++) {

		std::cout << "\t\t\t\t" << pEvents[i].name << std::endl;
		std::cout << pEvents[i].text << std::endl;

		std::cout << "���� ����������� (Date of the event): ";
		std::cout << pEvents[i].data << std::endl;
		std::cout << std::endl;

	}

}
void ChangingFieldsOfEvent(int input, int eventForChanging) {
	
	switch (input) {
	case 1: {
		std::string newName;
		std::cout << "������ ���� ��'� (Enter the new name):" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, newName);
		pEvents[eventForChanging].name = newName;
		break;
	}
	case 2: {
		std::string newData;
		std::cout << "������ ���� ���� (Enter the new date):" << std::endl;
		std::cin >> newData;
		pEvents[eventForChanging].data = newData;
		break;
	}
	case 3: {
		std::string newText;
		std::cout << "������ ����� ���� (Enter the new description):" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, newText);
		pEvents[eventForChanging].text = newText;
		break;
	}
	}
}
void MakingSchedules() {
	system("cls");
	int vidpovid;
	std::cout << "1. ���������� ������ (View events)" << std::endl;
	std::cout << "2. ���������� ������ (Edit events)" << std::endl;
	std::cout << "3. �������� ����� ����� (Create a new event)" << std::endl;
	std::cout << "4. ������� ���� ����� (Update the database)" << std::endl;
	std::cin >> vidpovid;
	switch (vidpovid) {
	case 1:{

		ShowEvents();
		break;
	}
	case 2:{
		int eventForChanging = -1;

		for (int i = 0; i < countOfEvents; i++) {
			if (pEvents[i].deleted == false)
				std::cout << i << "." << pEvents[i].name << std::endl;
		}


		int desiredEventNumber;
		std::cout << "������ ����� ������ � ����� ������ ������� ����������� (Enter the number of the event you want to edit):";
		std::cin >> desiredEventNumber;

		if (desiredEventNumber > countOfEvents) {
			std::cout << "���� ������ � ����� ������� (There is no event with that number)" << std::endl;
			break;
		}

		eventForChanging = desiredEventNumber;

		int vidpovid;
		std::cout << "1.���������� ����� (Edit event)" << std::endl;
		std::cout << "2.�������� ����� (Delete event)" << std::endl;
		
		std::cin >> vidpovid;

		switch (vidpovid) {
		case 1:
		{
			while (true) {
				int input;
				std::cout << "��� ���� �� ������ ������ (Which field do you want to change)" << std::endl;
				std::cout << "1.����� ������ (Event name)" << std::endl;
				std::cout << "2.���� ����������� (Event date)" << std::endl;
				std::cout << "3.���� ������ (Event description)" << std::endl;

				std::cin >> input;

				std::cin.ignore();

				int input2 = 1;
				if (input2 == 1)
				ChangingFieldsOfEvent(input, eventForChanging);



				std::cout << "1.������ ���� ���� (Change other fields)" << std::endl;
				std::cout << "2.�������� (Finish)" << std::endl;
				std::cin >> input2;

				if (input2 == 2)
					break;
			}
			break;
		}
		case 2:
		{
			pEvents[eventForChanging].deleted = true;
			break;
		}
		
		default:
			break;

		}
		break;
	}
	case 3:{
		std::cin.ignore();
		Event TempEvent;
		std::cout << "������ ����� ������ (Enter event name):" << std::endl;
		std::getline(std::cin, TempEvent.name);

		for (int i = 0; i < countOfEvents; i++) {
			if (TempEvent.name == pEvents[i].name) {
				std::cout << "����� � ����� ��'�� ��� ���� (An event with this name already exists)";
				break;
			}
		}

		std::cout << "������ ���� �� ������ (Enter event description):";
		std::getline(std::cin, TempEvent.text);


		std::cout << "������ ���� ����������� ������ (Enter event date):";

		std::getline(std::cin, TempEvent.data);

		AddNewEvent(TempEvent);
		break;
	}
	case 4:{
		UpdateEventsDataBase();
		UpdateEventsInformation();
		break;

	}
	default:
		break;


	}
}

