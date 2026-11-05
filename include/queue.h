#pragma once
#include <exception>
const double factor = 2.0;
const int MAX_SIZE = 1000000;//миллион
template<class T>
class Queue {
private:
	int size = 0;
	int capacity = 1;
	T* data;
	T* tail;//Указывает на первый элемент очереди.
	T* head;//Указывает на последний элемент очереди.
	//Считаем, что хвост изначально слева, голова - справа.
	//Нетрудно заметить, что и при единичном размере, и при нулевом tail и head будут указывать на один и тот же
	//элемент. Было решено поступить так: отдельно рассматривать нулевой размер.
public:
	Queue(int len = 1) :size(0), capacity(len) {
		if (len > MAX_SIZE) {
			throw(std::length_error("Queue will become too large!"));
		}
		if (len <= 0) {
			throw(std::length_error("Length cannot be unpositive!"));
		}
		data = new T[len];
		tail = data;
		head = tail;
	}
	int len()const {
		return(size);
	}
	~Queue() {
		delete[](data);
	}
	bool empty()const {
		return(size == 0);
	}
	Queue(const Queue& q) :size(q.size), capacity(q.capacity) {
		if (q.empty()) {
			data = new T[capacity];
			tail = data;
			head = data;
			return;
		}
		data = new T[q.capacity];
		int i = q.tail - q.data;
		tail = data + (q.tail - q.data);
		head = data + (q.head - q.data);
		do {
			data[i] = q.data[i];
			if (i == capacity - 1) {
				i = 0;
			}
			else {
				i++;
			}

		} while (i != (int)(q.head - q.data));
	}
	Queue& operator=(const Queue& q) {
	if (&q == this) {
		return(*this);
	}
	if (q.empty()) {
		T* tmp = new T[q.capacity];
		delete[](data);
		data = tmp;
		tail = tmp;
		head = tmp;
		size = 0;
		capacity = q.capacity;
		return(*this);
	}
	T* tmp = new T[q.capacity];
	size = q.size;
	capacity = q.capacity;
	int i = q.tail - q.data;
	do{
		tmp[i] = q.data[i];
		if (i == capacity - 1) {
			i = 0;
		}
		else {
			i++;
		}

	}while (i != (int)(q.head - q.data));
	delete[](data);
	data = tmp;
	tail = data + (q.tail - q.data);
	head = data + (q.head - q.data);
	return(*this);
	}
	Queue(Queue&& q): size(q.size), capacity(q.capacity) {
		data = q.data;
		tail = q.tail;
		head = q.head;
		q.data = nullptr;
		q.tail = nullptr;
		q.head = nullptr;
		q.size = 0;
		q.capacity = 0;
	}
	Queue& operator=(Queue&& q) {
		if (&q == this) {
			return(*this);
		}
		size = q.size;
		capacity = q.capacity;
		delete[](data);
		data = q.data;
		tail = q.tail;
		head = q.head;
		q.data = nullptr;
		q.tail = nullptr;
		q.head = nullptr;
		q.size = 0;
		q.capacity = 0;
		return(*this);
	}
	void resize(int new_capacity) {
		if (capacity >= new_capacity) {
			return;
		}
		int tmp_cap = capacity;
		while (tmp_cap< new_capacity) {
			tmp_cap = tmp_cap * factor;
		}
		if ((*this).empty()) {
			T* tmp = new T[tmp_cap];
			capacity = tmp_cap;
			delete[](data);
			data = tmp;
			tail = data;
			head = data;
			return;
		}
		T* tmp = new T[tmp_cap];
		int j = (int)(tail - data);
		for (int i = 0; i < size; i++) {
			tmp[i] = data[j];
			if (j == capacity - 1) {
				j=0;
			}
			else {
				j++;
			}
		}
		capacity = tmp_cap;
		delete[](data);
		data = tmp;
		tail = data;
		head = data+size-1;
	}
	bool operator==(const Queue& q)const {
		if (size != q.size) {
			return(false);
		}
		if (q.empty() && (*this).empty()) {
			return(true);
		}
		int j = (int)(q.tail - q.data);
		int i = (int)(tail - data);
		for (int k = 0; k < size; k++) {
			if (data[i] != q.data[j]) {
				return(false);
			}
			if (j == q.capacity - 1) {
				j = 0;
			}
			else {
				j++;
			}
			if (i == capacity - 1) {
				i = 0;
			}
			else {
				i++;
			}
		}
		return(true);
	}
	bool operator!=(const Queue& q)const {
		return(!((*this) == q));
	}
	T& bottom(){
		if ((*this).empty()) {
			throw(std::logic_error("Empty queue has no top!"));
		}
		return(*tail);
	}
	const T& bottom()const {
		if ((*this).empty()) {
			throw(std::logic_error("Empty queue has no top!"));
		}
		return(*tail);
	}
	void pop() {
		if ((*this).empty()) {
			throw(std::logic_error("Nothing to pop: queue is empty!"));
		}
		size--;
		if ((int)(tail - data) == capacity - 1) {
			tail = data;
		}
		else {
			tail++;
		}
	}
	void push(const T& elem) {
		if (size == MAX_SIZE) {
			throw(std::length_error("Queue will become too large!"));
		}
		if ((*this).empty()) {
			*tail = elem;
			size++;
			return;
		}
		if (size == capacity) {
			resize(size + 1);
		}
		if ((int)(head - data) == capacity - 1) {
			head = data;
		}
		else {
			head++;
		}
		*head = elem;
		size++;
	}
};