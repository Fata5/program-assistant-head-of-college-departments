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


	std::cout << "1. Списки груп та студентів (Groups and students lists)" << std::endl;
	std::cout << "2. Графіки заходів на відділенні (Event charts at the department)" << std::endl;
	std::cout << "3. Показники успішності та якості знань (Performance and knowledge quality indicators)" << std::endl;
	std::cout << "4. Обновити базу даних (Update the database)" << std::endl;

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

	std::cout << "1. Подивитися групи (View groups)" << std::endl;
	std::cout << "2. Редагувати групи та студентів (Edit groups and students)" << std::endl;
	std::cout << "3. Створити нову групу (Create a new group)" << std::endl;
	std::cout << "4. Видалити групу (Delete a group)" << std::endl;

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
				std::cout << "Група (Group):" << pGroups[i].name << std::endl;

				for (int x = 0; x < pGroups[i].numbersOfStudents; x++) {
					if (pGroups[i].array[x].deleted == false) {
						std::cout << "==================================================== " << std::endl;
						std::cout << "Ім'я (Name): " << pGroups[i].array[x].name << std::endl;
						std::cout << "Вік (Age): " << pGroups[i].array[x].age << std::endl;
						std::cout << "Середня оцінка (Average grade): " << pGroups[i].array[x].avgGrade << std::endl;
						std::cout << "==================================================== " << std::endl;
					}
				}
				std::cout << "Куратор (Curator):" << pGroups[i].curator.name << std::endl;
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
		std::cout << "Введіть номер групи в якій хочете зробити редагування (Enter the group number you want to edit):" << std::endl;
		std::cin >> desiredGroupNumber;

		if (desiredGroupNumber > countOfGroups) {
			std::cout << "Немає групи з таким номером (There is no group with that number)" << std::endl;
			break;
		}
			
		groupForChanging = desiredGroupNumber;

	
		std::cout << "Що ви хочете зробити? (What would you like to do?)" << std::endl;
		std::cout << "1.Змінити ім'я групи (Change group name)" << std::endl;
		std::cout << "2.Змінити поля студента (Modify student details)" << std::endl;
		std::cout << "3.Видалити студента із списку (Remove a student from the list)" << std::endl;
		std::cout << "4.Додати студента до списку (Add a student to the list)" << std::endl;
		std::cout << "5.Змінити ім'я куратора (Change curator's name)" << std::endl;

		int input;
		std::cin >> input;
		switch (input)
		{

			case 1:
			{
				std::string newName;
				std::cout << "Введіть нову назву групи (Enter the new group name):";
				std::cin.ignore();
				std::getline(std::cin, newName);
				pGroups[groupForChanging].name = newName;
				break;

			}
			case 2:
			{
				ShowStudentsOfGroupByNumber(groupForChanging);
				int studentNum;
				std::cout << "Введіть номер студента поля якого хочете змінити (Enter the number of the student whose fields you want to modify):";
				std::cin >> studentNum;
				int input;

				while (true) {
					std::cout << "Яке поле ви хочете змінити (Which field do you want to modify ? )" << std::endl;
					std::cout << "1. Ім'я (Name)" << std::endl;
					std::cout << "2. Вік (Age)" << std::endl;
					std::cout << "3. Середня оцінка (Average grade)" << std::endl;

					std::cin >> input;

					std::cin.ignore();

					int input2 = 1;
					if (input2 == 1)
					ChangeStudentsFields(input, groupForChanging, studentNum);
					


					std::cout << "1. Змінити інші поля (Modify other fields)" << std::endl;
					std::cout << "2. Закінчити (Finish)" << std::endl;
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
				std::cout << "Введіть номер студента якого хочете видалити (Enter the number of the student you want to delete):";
				std::cin >> studentNum;

				if(pGroups[groupForChanging].numbersOfStudents > studentNum)
					pGroups[groupForChanging].array[studentNum].deleted = true;
				else {
					std::cout << "Немає студента під таким номером (There is no student with that number)" << std::endl;
				}
				break;

			}

			case 4:
			{
				Student tempStudent;
				std::cout << "Введіть Ім'я (Name): ";
				std::cin.ignore();
				std::getline(std::cin, tempStudent.name);

				std::cout << "Введіть Вік (Age): ";
				std::cin >> tempStudent.age;

				std::cout << "Введіть середню оцінку (Average grade): ";
				std::cin >> tempStudent.avgGrade;

				pGroups[groupForChanging].addStudent(tempStudent);
				break;
			}

			case 5:
			{
				std::cout << "Введіть ім'я куратора (Curator's name): ";
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
		std::cout << "Введіть ім'я групи (Group name):" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, TempGroup.name);

		for (int i = 0; i < countOfGroups; i++) {
			if (TempGroup.name == pGroups[i].name) {
				std::cout << "Група з таким ім'ям вже існує (Group with that name already exists)." << std::endl;
				break;
			}
		}

		std::cout << "Введіть ім'я куратора групи (Curator's name):";
		std::cin.ignore();
		std::getline(std::cin, TempGroup.curator.name);

		AddNewGroup(TempGroup);
		break;
	}

	case 4:
	{
		for (int i = 0; i < countOfGroups; i++) {
			std::cout << i << ". Група (Group): " << pGroups[i].name << std::endl;
		}

		int input;
		std::cout << "Введіть номер групи, яку хочете видалити (Enter the number of the group you want to delete): ";
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
		std::cout << "Введіть нове ім'я (Enter the new name):" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, newName);
		pGroups[groupForChanging].array[studentNum].name = newName;
		break;
	}
	case 2: {
		int newAge;
		std::cout << "Введіть новий вік (Enter the new age):" << std::endl;
		std::cin >> newAge;
		pGroups[groupForChanging].array[studentNum].age = newAge;
		break;
	}
	case 3: {
		int newAvgGrade;
		std::cout << "Введіть нову середню оцінку (Enter the new average grade):" << std::endl;
		std::cin >> newAvgGrade;
		pGroups[groupForChanging].array[studentNum].avgGrade = newAvgGrade;
		break;
	}
	}
}
void ShowStudentsOfGroupByNumber(int index) {
	for (int i = 0; i < pGroups[index].numbersOfStudents; i++) {
		std::cout << "===================================" << std::endl;
		std::cout << i << ". Ім'я (Name): " << pGroups[index].array[i].name << std::endl;
		std::cout << "Вік (Age): " << pGroups[index].array[i].age << std::endl;
		std::cout << "Середня оцінка (Average grade): " << pGroups[index].array[i].avgGrade << std::endl;
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
		

		std::cout << pGroups[i].name << " має (has):" << std::endl;
		std::cout << "\t якість знань у (Quality of knowledge) :" << resultQuality <<'%' <<std::endl;
		std::cout << "\t успішність занань у (Success rate):" << resultSuccess << '%'<< std::endl;
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

		std::cout << "Дата проходження (Date of the event): ";
		std::cout << pEvents[i].data << std::endl;
		std::cout << std::endl;

	}

}
void ChangingFieldsOfEvent(int input, int eventForChanging) {
	
	switch (input) {
	case 1: {
		std::string newName;
		std::cout << "Введіть нове ім'я (Enter the new name):" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, newName);
		pEvents[eventForChanging].name = newName;
		break;
	}
	case 2: {
		std::string newData;
		std::cout << "Введіть нову дату (Enter the new date):" << std::endl;
		std::cin >> newData;
		pEvents[eventForChanging].data = newData;
		break;
	}
	case 3: {
		std::string newText;
		std::cout << "Введіть новий опис (Enter the new description):" << std::endl;
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
	std::cout << "1. Подивитися заходи (View events)" << std::endl;
	std::cout << "2. Редагувати заходи (Edit events)" << std::endl;
	std::cout << "3. Створити новий захід (Create a new event)" << std::endl;
	std::cout << "4. Оновити базу даних (Update the database)" << std::endl;
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
		std::cout << "Введіть номер заходу в якому хочете зробити редагування (Enter the number of the event you want to edit):";
		std::cin >> desiredEventNumber;

		if (desiredEventNumber > countOfEvents) {
			std::cout << "Немає заходу з таким номером (There is no event with that number)" << std::endl;
			break;
		}

		eventForChanging = desiredEventNumber;

		int vidpovid;
		std::cout << "1.Редагувати захід (Edit event)" << std::endl;
		std::cout << "2.Видалити захід (Delete event)" << std::endl;
		
		std::cin >> vidpovid;

		switch (vidpovid) {
		case 1:
		{
			while (true) {
				int input;
				std::cout << "Яке поле ви хочете змінити (Which field do you want to change)" << std::endl;
				std::cout << "1.Назва заходу (Event name)" << std::endl;
				std::cout << "2.Дата проходження (Event date)" << std::endl;
				std::cout << "3.Опис заходу (Event description)" << std::endl;

				std::cin >> input;

				std::cin.ignore();

				int input2 = 1;
				if (input2 == 1)
				ChangingFieldsOfEvent(input, eventForChanging);



				std::cout << "1.Змінити інші поля (Change other fields)" << std::endl;
				std::cout << "2.Закінчити (Finish)" << std::endl;
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
		std::cout << "Введіть назву заходу (Enter event name):" << std::endl;
		std::getline(std::cin, TempEvent.name);

		for (int i = 0; i < countOfEvents; i++) {
			if (TempEvent.name == pEvents[i].name) {
				std::cout << "Захід з таким ім'ям вже існує (An event with this name already exists)";
				break;
			}
		}

		std::cout << "Введіть опис до заходу (Enter event description):";
		std::getline(std::cin, TempEvent.text);


		std::cout << "Введіть дату проходження заходу (Enter event date):";

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

