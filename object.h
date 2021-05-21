#pragma once

template<typename T>
class Container;
class Object
{
public:
	Object();
	virtual std::string toString() const = 0;
	size_t GetObjectCount() const;
	virtual ~Object();

private:
	static size_t sm_objectCount;
};

class Task :public Object
{
public:

	Task();
	virtual void Execute() {};


protected:
	bool executed;
};

class TaskWithResult :public Task
{
public:
	TaskWithResult();

protected:
	double m_result;
};

class Named :public Object
{
public:
	Named(std::string name);
	virtual std::string toString() const override;

protected:
	std::string m_name;
};

class AddTask :public Task, Named
{
public:

	AddTask(Container<Task&> store, Task& task, std::string name);
	virtual void Execute() override;
	virtual std::string toString() const override;

protected:
	Container<Task&> &m_store;
	Task& m_task;

};

class ObjectCounter :public TaskWithResult {
public:
	ObjectCounter() {}
	virtual void Execute() override;
	virtual std::string toString() const override;

};

class ListLength :public TaskWithResult, Named {
public:
	ListLength(Container<Object&> &store, std::string name);
	virtual std::string toString() const override;
	virtual void Execute() override;

private:
	Container<Object&> &m_store;
};

class ListCleaner :public Task
{
public:
	ListCleaner(Container<Object&> &store);
	virtual std::string toString() const override;
	virtual void Execute() override;

private:
	Container<Object&> &m_store;
};

class BinaryExpression :public TaskWithResult, Named {
public:

	BinaryExpression(double first, double second, std::string name, std::string operatorSign);
	virtual std::string toString() const override;
protected:

	double m_first;
	double m_second;
	std::string m_operatorSign;
};

class BinarySum :public BinaryExpression {
public:
	BinarySum(double first, double second, std::string name);
	virtual void Execute() override;
};

class BinarySub :public BinaryExpression {
public:
	BinarySub(double first, double second, std::string name);
	virtual void Execute() override;
};
class BinaryMul :public BinaryExpression {
public:
	BinaryMul(double first, double second, std::string name);
	virtual void Execute() override;
};
class BinaryDiv :public BinaryExpression {
public:
	BinaryDiv(double first, double second, std::string name);
	virtual void Execute() override;
};
enum types { objectcounter, lenList, createTask, clearList, sum, subsraction, multiplication, division, BoundType };
Task* RandomTask(size_t randCoeff);