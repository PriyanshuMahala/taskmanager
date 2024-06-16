#include "tasks.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace tasks {
	task::task(std::string t, std::string dd, int pl, std::string l)
		: text_s(t), dueDate(dd), priorityLvl(pl), label(l) {}

	Folder::~Folder() {
		for (task* t : pTasks) {
			delete t;
		}
	}

	void Folder::addTask(std::string t, std::string dd, std::string l, int pl) {
		pTasks.push_back(new task(t, dd, pl, l));
	}

	void Folder::removeTask(std::string taskName) {
		for (auto it = pTasks.begin(); it != pTasks.end(); ++it) {
			if ((*it)->getTask() == taskName) {
				delete* it;
				pTasks.erase(it);
				return;
			}
		}
	}

	void load(std::vector<Folder*>& folders, const std::string& filename) {
		std::ifstream file(filename);

		if (!file.is_open()) {
			std::cerr << "Error opening file: " << filename << std::endl;
			return;
		}

		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string folderName, text, dueDate, label;
			int priorityLvl;

			if (std::getline(iss, folderName, ',') &&
				std::getline(iss, text, ',') &&
				std::getline(iss, dueDate, ',') &&
				std::getline(iss, label, ',') &&
				iss >> priorityLvl) {
				Folder* currentFolder = nullptr;
				for (auto& folder : folders) {
					if (folder->getLabel() == folderName) {
						currentFolder = folder;
						break;
					}
				}

				if (!currentFolder) {
					currentFolder = new Folder(folderName, "");
					folders.push_back(currentFolder);
				}

				currentFolder->addTask(text, dueDate, label, priorityLvl);
			}
		}

		file.close();
	}

	void unload(const std::vector<Folder*>& folders, const std::string& filename) {
		std::ofstream file(filename);

		if (!file.is_open()) {
			std::cerr << "Error opening file: " << filename << std::endl;
			return;
		}

		for (const auto& folder : folders) {
			for (const auto& t : folder->getTaskVector()) {
				file << folder->getLabel() << ","
					<< t->getTask() << ","
					<< t->getDueDate() << ","
					<< t->getLabel() << ","
					<< t->getPriorityLvl() << "\n";
				delete t;
			}
		}

		file.close();
	}

	void transfer(const std::vector<Folder*>& folders, const std::string& filename) {
		std::ofstream file(filename);

		if (!file.is_open()) {
			std::cerr << "Error opening file: " << filename << std::endl;
			return;
		}

		for (const auto& folder : folders) {
			for (const auto& t : folder->getTaskVector()) {
				file << folder->getLabel() << ","
					<< t->getTask() << ","
					<< t->getDueDate() << ","
					<< t->getLabel() << ","
					<< t->getPriorityLvl() << "\n";
			}
		}

		file.close();
	}

	void Folder::PrintTasks(bool toLoad) {
		if (toLoad) {
			std::vector<Folder*> folders;
			load(folders, FILENAME);
			for (auto& folder : folders) {
				if (folder->getLabel() == label) {
					pTasks = folder->getTaskVector();
					break;
				}
			}
		}

		for (task* t : pTasks) {
			std::cout << "Task: " << t->getTask() << '\n';
			std::cout << "Due date: " << t->getDueDate() << '\n';
			std::cout << "Label: " << t->getLabel() << '\n';
			std::cout << "Priority level: " << t->getPriorityLvl() << '\n';
		}
	}

	bool isInt(int& val) {
		if (!std::cin >> val) {
			std::cin.clear();
			return false;
		}
		return true;
	}
}