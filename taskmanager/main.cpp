#include <iostream>
#include <vector>
#include <string>
#include "tasks.h"

void LOOP();

int main() {
	LOOP();
	return 0;
}

void LOOP() {
	std::vector<tasks::Folder*> folders;
	while (true) {
		int option;
		std::cout << "1. Add folder" << '\n';
		std::cout << "2. Add task" << '\n';
		std::cout << "3. Remove folder" << '\n';
		std::cout << "4. Remove task" << '\n';
		std::cout << "5. Change " << '\n';
		std::cout << "6. Display All " << '\n';
		std::cout << "Enter your option: ";

		// Read option input and validate it
		if (!(std::cin >> option) || option < 1 || option > 6) {
			std::cout << "Invalid option! Please enter a valid int between 1 and 6.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		// Clear input buffer
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (option == 1) {
			std::string name, description;
			std::cout << "Name for folder: ";
			std::getline(std::cin, name);
			std::cout << "Description for folder: ";
			std::getline(std::cin, description);
			folders.push_back(new tasks::Folder(name, description));
		}
		else if (option == 2) {
			std::string taskNAME, label, dueDate, folderName;
			int PriorityLvl;
			bool isFound = false;

			std::cout << "Enter folder name: ";
			std::getline(std::cin, folderName);

			tasks::Folder* currentFolder = nullptr;
			for (tasks::Folder* t : folders) {
				if (t->getLabel() == folderName) {
					isFound = true;
					currentFolder = t;
					break;
				}
			}

			if (!isFound) {
				std::cout << "Folder not found, please create one!" << '\n';
				continue;
			}

			std::cout << "Enter task name: ";
			std::getline(std::cin, taskNAME);
			std::cout << "Enter label: ";
			std::getline(std::cin, label);
			std::cout << "Enter due date: ";
			std::getline(std::cin, dueDate);
			std::cout << "Enter priority level: ";

			// Read PriorityLvl and validate it
			while (!(std::cin >> PriorityLvl)) {
				std::cout << "It looks like the option you entered is not an integer! \n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Enter priority level: ";
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			currentFolder->addTask(taskNAME, dueDate, label, PriorityLvl);
			std::cout << "New task added to " << folderName << " folder" << '\n';
		}
		else if (option == 6) {
			std::string FolderName;
			tasks::Folder* currentFolder = nullptr;
			bool isFound = false;

			std::cout << "Enter folder name: ";
			std::getline(std::cin, FolderName);
			for (tasks::Folder* folder : folders) {
				if (folder->getLabel() == FolderName) { currentFolder = folder; isFound = true; break; }
			}
			if (!isFound) { std::cout << "Could not find folder " << FolderName << '\n'; continue; }
			currentFolder->PrintTasks(true);
		}
	}

	// Clean up dynamically allocated folders
	for (tasks::Folder* folder : folders) {
		delete folder;
	}
}