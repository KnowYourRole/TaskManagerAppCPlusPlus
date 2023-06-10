#include "pch.h"
#include "CppUnitTest.h"
#include "..\..\TaskManagerMain\TaskManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(TaskManagerTests)
	{
	public:

		TEST_METHOD(TestAddTask)
		{
			TaskManager taskManager;
			taskManager.addTask("Task 1", "Description 1");
			taskManager.addTask("Task 2", "Description 2");

			Assert::AreEqual(2, taskManager.listTasks());
		}

		TEST_METHOD(TestDeleteTask)
		{
			TaskManager taskManager;
			taskManager.addTask("Task 1", "Description 1");
			taskManager.addTask("Task 2", "Description 2");

			taskManager.deleteTask(0);
			Assert::AreEqual(1, taskManager.listTasks());
		}

		TEST_METHOD(TestMarkTaskAsDone)
		{
			TaskManager taskManager;
			taskManager.addTask("Task 1", "Description 1");
			taskManager.addTask("Task 2", "Description 2");

			taskManager.markTaskAsDone(1);
			Assert::IsTrue(taskManager.getTaskStatus(1));
		}

		TEST_METHOD(TestExportTasks)
		{
			TaskManager taskManager;
			taskManager.addTask("Task 1", "Description 1");
			taskManager.addTask("Task 2", "Description 2");

			taskManager.exportTasks();
			// Add assertions to check the exported file or other relevant expectations
		}

		TEST_METHOD(TestImportTasks)
		{
			TaskManager taskManager;
			taskManager.importTasks();

			Assert::AreEqual(2, taskManager.listTasks());
			// Add assertions to verify the imported tasks or other relevant expectations
		}
	};
}
