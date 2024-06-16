#pragma once

#include <string>
#include <vector>

namespace tasks {
	enum { low = 1, medium, high };
	const std::string FILENAME = "TaskInfo.txt";

	class task {
	private:
		std::string text_s;
		std::string dueDate;
		int priorityLvl;
		std::string label;

	public:
		task(std::string t, std::string dd, int pl, std::string l);

		std::string getTask()const { return text_s; }
		std::string getDueDate()const { return dueDate; }
		std::string getLabel()const { return label; }
		int getPriorityLvl() const { return priorityLvl; }

		void setPriorityLvl(int lvl) { priorityLvl = lvl; }
		void setDueDate(std::string d) { dueDate = d; }
	};

	class Folder {
	private:
		std::string label;
		std::string description;
		std::vector<task*> pTasks;

	public:
		Folder(std::string l, std::string description) : label(l), description(description) {}
		~Folder();

		std::string getLabel()const { return label; }

		std::vector<task*>& getTaskVector() { return pTasks; }
		void addTask(std::string t, std::string dd, std::string l, int pl);
		void removeTask(std::string taskName);
		void PrintTasks(bool toLoad);
	};

	//global
	void load(std::vector<Folder*>& folders, const std::string& filename);
	void unload(const std::vector<Folder*>& folders, const std::string& filename);
	void transfer(const std::vector<Folder*>& folders, const std::string& filename);

	//Functionality
	bool isInt(int& val);
}
