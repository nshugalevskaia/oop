#include <iostream>
#include <string>
#include <vector>
#include "object.h"
#include "container.h"

size_t Object::sm_objectCount = 0;

Object::Object() {
	++sm_objectCount;
};

Object::~Object()
{
	--sm_objectCount;
}

size_t Object::GetObjectCount() const {
		return sm_objectCount;
};


Task::Task()
		:executed(false)
{};

TaskWithResult::TaskWithResult()
	:m_result(0)
{};

Named::Named(std::string name)
	:m_name(name) 
{};
	
std::string Named::toString() const {
	return m_name;
};


AddTask::AddTask(Container<Task&> store, Task& task, std::string name)
	:Named(name)
	,m_task(task)
	,m_store(store)
{};

void AddTask::Execute(){
	m_store.PushBack(m_task);
	executed = true;
};

std::string AddTask::toString() const{
		if (executed)
		{
			return m_name + " Task is added";
		}
		else {
			return m_name + " Task wasn't executed";
		}
};



void ObjectCounter::Execute() {
	m_result = GetObjectCount();
	executed = true;
};

std::string ObjectCounter::toString() const {
	if (executed)
	{
		return " There are " + std::to_string(m_result) + " objects now";
	}
	else {
		return " Task wasn't executed";
	}
};


std::string ListLength::toString() const {
	if (executed)
	{
		return m_name + " List contains " + std::to_string(m_result) + " elements";
	}
	else {
		return m_name + " Task wasn't executed";
	}
};

ListLength::ListLength(Container<Object&>& store, std::string name)
		:Named(name)
		,m_store(store)
{};



void ListLength::Execute(){
		m_store.Clear();
		executed = true;
	}

ListCleaner::ListCleaner(Container<Object&> &store)
	:m_store(store)
{};

std::string ListCleaner::toString() const{
	if (executed)
	{
		return "List is cleaned";
	}
	else {
		return "Task wasn't executed";
	}
};


 void ListCleaner::Execute() {
		m_store.Clear();
		executed = true;
};

BinaryExpression::BinaryExpression(double first, double second, std::string name, std::string operatorSign)
	:Named(name)
	, m_first(first)
	, m_second(second)
	, m_operatorSign(operatorSign)
{};

std::string BinaryExpression::toString() const{

		if (executed)
		{
			return m_name + " "+std::to_string(m_first) + m_operatorSign + std::to_string(m_second) + " = " + std::to_string(m_result);
		}
		else {
			return m_name + " Task wasn't executed";
		}

};


BinarySum::BinarySum(double first, double second, std::string name)
	:BinaryExpression(first, second, name," + ")
{};

void BinarySum::Execute()  {
		m_result = m_first + m_second;
		executed = true;
};


BinarySub::BinarySub(double first, double second, std::string name)
	:BinaryExpression(first, second, name," - ")
{};

void BinarySub::Execute(){
	m_result = m_first - m_second;
	executed = true;
};

BinaryMul::BinaryMul(double first, double second, std::string name)
	:BinaryExpression(first, second, name," * ")
{};

void BinaryMul::Execute(){
		m_result = m_first * m_second;
		executed = true;
	};

BinaryDiv::BinaryDiv(double first, double second, std::string name)
	:BinaryExpression(first, second, name," / ")
{};

void BinaryDiv::Execute(){
	m_result = m_first / m_second;
	executed = true;
};

Task* RandomTask(size_t randCoeff){
	Task *newTask;
	Container<Object&> taskList;
	srand(randCoeff);
	size_t type = rand() % BoundType;
	switch(type){
		
	case(objectcounter): {

		newTask=new ObjectCounter();
		}
	case(lenList): {
		std::string name = "Task " + std::to_string(type) + ": ListLength";
		newTask = new ListLength(taskList,name);

		}

	case(createTask): {
		std::string name = "Task " + std::to_string(type) + ": CreateTask";
		//newTask = new AddTask(taskList,,name);
		}
	default: return nullptr;
	}

	return newTask;
}
