#pragma once

#define ERROR_INDEX -10001
#define ERROR_INDEX -10001
#include <cstdlib>

typedef unsigned long long uint64;

template <typename T>
struct DoubleListUnit
{
	T *value;
	DoubleListUnit *prev;
	DoubleListUnit *next;
};

template <typename T>
class DoubleList
{
	DoubleListUnit<T> last = nullptr;
	uint64 lenght = 0;
public:
	DoubleList<T>();
	int Insert<T>(uint64 pos, T value);
	int Remove<T>(uint64 pos);
	uint64 GetLength<T>();
	void Sort<T>();

	~DoubleList<T>();
};

template <typename T>
DoubleList<T>::DoubleList()
{
}

template <typename T>
int DoubleList<T>::Insert(uint64 pos, T value)
{
	if (pos > lenght + 1)
		return ERROR_INDEX;
	
	DoubleListUnit<T> u = last;
	while (u.prev)
	{
		u = u.prev;
	}

	for (uint64 i = 0; i < pos && u.next != nullptr; i++)
	{
		u = u.next;
	}

	// Inserting
	DoubleListUnit<T> unit = new DoubleListUnit<T>;
	DoubleListUnit<T> *next = u.next;	
	u.next = &unit;
	unit.prev = u;
	unit.next = u.next;
	next->next->prev = &unit;

	lenght++;
	return 0;
}

template <typename T>
int DoubleList<T>::Remove(uint64 pos)
{
	if (lenght <= 0)
	{
		lenght = 0;
		return ERROR
	}
	// TODO
	DoubleListUnit<T> u = last;
	while (u.prev)
		u = u.prev;

	for (uint64 i = 0; i < pos && u.next != NULL; i++)
	{
		u = u.next;
	}
	

	if (u.prev)
		u.prev->next = u.next;
	if (u.next)
		u.next->prev = u.prev;
	lenght--;
	return 0;
}


