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
		for (task* t : pTasks) {
			if (t->getTask() == taskName) { delete t; return; }
		}
	}

	void load(std::vector<task*>& taskPointers, const std::string& filename) {
		std::ifstream file(filename);

		if (!file.is_open()) {
			std::cerr << "Error opening file: " << filename << std::endl;
			return;
		}

		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string text, dueDate, label;
			int priorityLvl;

			if (std::getline(iss, text, ',') &&
				std::getline(iss, dueDate, ',') &&
				std::getline(iss, label, ',') &&
				iss >> priorityLvl) {
				taskPointers.push_back(new task(text, dueDate, priorityLvl, label));
			}
		}

		file.close();
	}

	void unload(std::vector<task*>& taskPointers, const std::string& filename) {
		std::ofstream file(filename);

		if (!file.is_open()) {
			std::cerr << "Error opening file: " << filename << std::endl;
			return;
		}

		for (const auto& t : taskPointers) {
			file << t->getTask() << ","
				<< t->getDueDate() << ","
				<< t->getLabel() << ","
				<< t->getPriorityLvl() << "\n";
			delete t;
		}

		taskPointers.clear();
		file.close();
	}
	void transfer(std::vector<task*>& taskPointers, const std::string& filename) {
		std::ofstream file(filename);

		if (!file.is_open()) {
			std::cerr << "Error opening file: " << filename << std::endl;
			return;
		}

		for (const auto& t : taskPointers) {
			file << t->getTask() << ","
				<< t->getDueDate() << ","
				<< t->getLabel() << ","
				<< t->getPriorityLvl() << "\n";
			delete t;
		}

		file.close();
	}

	void Folder::PrintTasks(bool toLoad) {
		if (toLoad)load(pTasks, FILENAME);
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