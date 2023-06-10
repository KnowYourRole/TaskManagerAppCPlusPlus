#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 

class Task {
public:
	std::string title;
	std::string description;
	bool isDone;

	Task(const std::string& _title, const std::string& _description)
		: title(_title), description(_description), isDone(false) {}
};

class TaskManager {
private:
	std::vector<Task> tasks;
	const std::string filename = "tasks.txt";

public:
	void addTask(const std::string& title, const std::string& description) {
		tasks.emplace_back(title, description);
	}

	void deleteTask(int index) {
		if (index >= 0 && index < tasks.size()) {
			tasks.erase(tasks.begin() + index);
		}
	}

	void markTaskAsDone(int index) {
		if (index >= 0 && index < tasks.size()) {
			tasks[index].isDone = true;
		}
	}

	void exportTasks() {
		std::ofstream file(filename);
		if (file.is_open()) {
			for (const auto& task : tasks) {
				file << task.title << ',' << task.description << ',' << task.isDone << '\n';
			}
			file.close();
			std::cout << "Tasks exported successfully.\n";
		}
		else {
			std::cerr << "Failed to export tasks.\n";
		}
	}

	void importTasks() {
		tasks.clear();
		std::ifstream file(filename);
		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				std::stringstream ss(line);
				std::string title, description, isDoneStr;
				std::getline(ss, title, ',');
				std::getline(ss, description, ',');
				std::getline(ss, isDoneStr, ',');
				bool isDone = (isDoneStr == "1");
				tasks.emplace_back(title, description);
				tasks.back().isDone = isDone;
			}
			file.close();
			std::cout << "Tasks imported successfully.\n";
		}
		else {
			std::cerr << "Failed to import tasks.\n";
		}
	}

	void listTasks() {
		int index = 0;
		for (const auto& task : tasks) {
			std::cout << index << ". ";
			std::cout << "Title: " << task.title << ", ";
			std::cout << "Description: " << task.description << ", ";
			std::cout << "Status: " << (task.isDone ? "Done" : "Not Done") << '\n';
			index++;
		}
	}
};

int main() {
	TaskManager taskManager;

	// Load existing tasks
	taskManager.importTasks();

	int choice;
	std::string title, description;
	do {
		std::cout << "Task Management Application\n";
		std::cout << "1. Add Task\n";
		std::cout << "2. Delete Task\n";
		std::cout << "3. Mark Task as Done\n";
		std::cout << "4. List Tasks\n";
		std::cout << "5. Export Tasks\n";
		std::cout << "6. Exit\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			std::cout << "Enter task title: ";
			std::cin.ignore();
			std::getline(std::cin, title);
			std::cout << "Enter task description: ";
			std::getline(std::cin, description);
			taskManager.addTask(title, description);
			break;
		case 2:
			std::cout << "Enter the task index to delete: ";
			int deleteIndex;
			std::cin >> deleteIndex;
			taskManager.deleteTask(deleteIndex);
			break;
		case 3:
			std::cout << "Enter the task index to mark as done: ";
			int doneIndex;
			std::cin >> doneIndex;
			taskManager.markTaskAsDone(doneIndex);
			break;
		case 4:
			taskManager.listTasks();
			break;
		case 5:
			taskManager.exportTasks();
			break;
		case 6:
			// Save tasks before exiting
			taskManager.exportTasks();
			std::cout << "Exiting the application.\n";
			break;
		default:
			std::cout << "Invalid choice. Please try again.\n";
			break;
		}

	} while (choice != 6);

	return 0;
}