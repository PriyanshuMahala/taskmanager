#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "tasks.h"

void LOOP() {
	std::vector<tasks::Folder*> folders;
	tasks::load(folders, tasks::FILENAME);// Will display error when run for the first time
	while (true) {
		int option;
		std::cout << "1. Add folder" << '\n';
		std::cout << "2. Add task" << '\n';
		std::cout << "3. Remove folder" << '\n';
		std::cout << "4. Remove task" << '\n';
		std::cout << "5. Change " << '\n';
		std::cout << "6. Display All " << '\n';
		std::cout << "7. Clear" << '\n';
		std::cout << "8. Save and Exit " << '\n';
		std::cout << "Enter your option: ";

		// Read option input and validate it
		if (!(std::cin >> option) || option < 1 || option > 8) {
			std::cout << "Invalid option! Please enter a valid int between 1 and 8.\n";
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
		else if (option == 3) {
			std::string FolderName;
			bool isFound = false;
			tasks::Folder* currentFolder = nullptr;
			std::vector<tasks::Folder*>::iterator it;

			std::cout << "Enter Folder name: ";
			std::getline(std::cin, FolderName);

			for (it = folders.begin(); it != folders.end(); ++it) {
				if ((*it)->getLabel() == FolderName) {
					isFound = true;
					currentFolder = *it;
					break;
				}
			}

			if (!isFound) {
				std::cout << "Could not find a folder named " << FolderName << '\n';
				continue;
			}

			// Delete the folder and remove it from the vector
			delete currentFolder;
			folders.erase(it);
			std::cout << "Deleted folder " << FolderName << '\n';
		}

		else if (option == 4) {
			std::string FolderName;
			bool isFound = false;
			tasks::Folder* currentFolder = nullptr;
			tasks::task* currentTask = nullptr;
			std::string taskName;

			std::cout << "Enter Folder name: ";
			std::getline(std::cin, FolderName);

			for (tasks::Folder* fold : folders) {
				if (fold->getLabel() == FolderName) { isFound = true; currentFolder = fold; break; }
			}
			if (!isFound) { std::cout << "Could not find a folder named " << FolderName << '\n'; }
			isFound = false;

			std::cout << "Enter task name: ";
			std::getline(std::cin, taskName);

			currentFolder->removeTask(taskName);
			
		}

		else if (option == 5) {
			char option;
			bool isFound = false;
			std::string folderName;
			std::string taskName;
			tasks::Folder* currentFolder = nullptr;
			tasks::task* currentTask = nullptr;
			std::string newString;
			int newInt = 0;

			std::cout << "Choose what to change: ";
			std::cout << "a. Task's dueDate" << '\n';
			std::cout << "b. Task's priority level" << '\n';
			std::cout << "c. Folder's name" << '\n';
			std::cout << "d. Folder's description" << '\n';

			std::cout << "Choose: ";
			std::cin >> option;

			switch (option) {
			case 'a':

				std::cout << "Enter folder name: ";
				std::getline(std::cin, folderName);
				for (tasks::Folder* fold : folders) {
					if (fold->getLabel() == folderName) { isFound = true; currentFolder = fold; break; }
				}
				if (!isFound) { std::cout << "Could not find folder named" << folderName << '\n'; continue; }
				isFound = false;
				std::cout << "Enter task name: ";
				std::getline(std::cin, taskName);
				for (tasks::task* t : currentFolder->getTaskVector()) {
					if (t->getTask() == taskName) { isFound = true; currentTask = t; break; }
				}
				if (!isFound) { std::cout << "Could not find task: " << taskName << " in folder " << currentFolder << '\n'; }
				std::cout << "Enter new task dueDate: ";
				std::cin >> newString;

				currentTask->setDueDate(newString);
				break;
			case 'b':
				std::cout << "Enter folder name: ";
				std::getline(std::cin, folderName);
				for (tasks::Folder* fold : folders) {
					if (fold->getLabel() == folderName) { isFound = true; currentFolder = fold; break; }
				}
				if (!isFound) { std::cout << "Could not find folder named" << folderName << '\n'; continue; }
				isFound = false;
				std::cout << "Enter task name: ";
				std::getline(std::cin, taskName);
				for (tasks::task* t : currentFolder->getTaskVector()) {
					if (t->getTask() == taskName) { isFound = true; currentTask = t; break; }
				}
				if (!isFound) { std::cout << "Could not find task: " << taskName << " in folder " << currentFolder << '\n'; }
				std::cout << "Enter new task priority level: ";
				std::cin >> newInt;

				currentTask->setPriorityLvl(newInt);
				break;

			case 'c':
				std::cout << "Enter folder name: ";
				std::getline(std::cin, folderName);
				for (tasks::Folder* fold : folders) {
					if (fold->getLabel() == folderName) { isFound = true; currentFolder = fold; break; }
				}
				if (!isFound) { std::cout << "Could not find folder named" << folderName << '\n'; continue; }

				std::cout << "Enter new folder name: ";
				std::getline(std::cin, newString);

				currentFolder->setLabel(newString);
				break;

			case 'd':
				std::cout << "Enter folder name: ";
				std::getline(std::cin, folderName);
				for (tasks::Folder* fold : folders) {
					if (fold->getLabel() == folderName) { isFound = true; currentFolder = fold; break; }
				}
				if (!isFound) { std::cout << "Could not find folder named" << folderName << '\n'; continue; }

				std::cout << "Enter new folder description: ";
				std::getline(std::cin, newString);

				currentFolder->setDescription(newString);
				break;

			default:
				break;
			}
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
			currentFolder->PrintTasks(false);
		}
		else if (option == 7) {
			system("cls");
		}
		else if (option == 8) {
			tasks::unload(folders, tasks::FILENAME);
			std::cout << "Saved all tasks..." << '\n';
			return;
		}
	}

	// Clean up dynamically allocated folders
	for (tasks::Folder* folder : folders) {
		delete folder;
	}
}