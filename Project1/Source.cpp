#include <iostream>
#include <thread>
#include <memory>
#include <vector>
using namespace std::literals::chrono_literals;

class Entity
{
public:
	int value;
public:
	Entity(const int& p_Value = 0)
	: value(p_Value)
	{
	}
};

std::vector<std::shared_ptr<Entity>> entitys;

void DoWork(int &count)
{
	entitys.reserve(10);
	while (count --> 0)
	{
		std::shared_ptr<Entity> entity = std::make_shared<Entity>(count);
		entitys.emplace_back(entity);
		std::this_thread::sleep_for(1s);
	}
}

int main()
{
	bool makeThread = false;
	int count = 10;
	while (count >= 0)
	{
		std::thread worker;
		if (!makeThread)
		{
			worker = std::thread( DoWork, std::ref(count) );
			makeThread = true;
		}
		std::cout << "Main thread...\n";

		if (worker.joinable())
		{
			worker.detach();
		}
		std::this_thread::sleep_for(1s);
	}
	std::cout << "Finished!\n";
	for (auto entity : entitys)
	{
		std::cout << entity->value << std::endl;
	}
	return 0;
}