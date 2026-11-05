#pragma once
#include <stdexcept>
const double factor = 2.0;
const int MAX_SIZE = 1000000;//миллион
template<class T>
class Stack {
private:
	int size = 0;
	int capacity = 1;
	T* data;
public:
Stack(int len = 1) :size(0), capacity(len) {
	if (len > MAX_SIZE||len < 1) {
		throw(std::length_error("Cannot create stack with too large size!"));
	}
	data = new T[len];
}
~Stack() {
	delete[](data);
}
Stack(const Stack& s) :size(s.size), capacity(s.capacity) {
	data = new T[s.capacity];
	for (int i = 0; i < size; i++) {
		data[i] = s.data[i];
	}
}
Stack& operator=(const Stack& s) {
	if (&s == this) {
		return(*this);
	}
	size = s.size;
	capacity = s.capacity;
	T* tmp = new T[capacity];
	for (int i = 0; i < size; i++) {
		tmp[i] = s.data[i];
	}
	delete[](data);
	data = tmp;
	return(*this);
}
Stack(Stack&& s):size(s.size), capacity(s.capacity) {
	data = s.data;
	s.data = nullptr;
}
Stack& operator=(Stack&& s){
	if (this == &s) {
		return(*this);
	}
	capacity = s.capacity;
	size = s.size;
	delete[](data);
	data = s.data;
	s.data = nullptr;
	return(*this);
}
int len()const {//Может, пригодится, может - нет.
	return(size);
}
bool operator==(const Stack& s)const {
	if (size != s.size) {
		return(false);
	}
	for (int i = 0; i < size; i++) {
		if (s.data[i] != data[i]) {
			return(false);
		}
	}
	return(true);
}
bool operator!=(const Stack& s)const {
	if (size != s.size) {
		return(true);
	}
	for (int i = 0; i < size; i++) {
		if (s.data[i] != data[i]) {
			return(true);
		}
	}
	return(false);
}
private:
void resize(int new_capacity) {
	if (capacity >= new_capacity) {
		return;
	}
	while (capacity < new_capacity) {
		capacity = capacity * factor;
	}
	T* tmp = new T[capacity];
	for (int i = 0; i < size; i++) {
		tmp[i] = data[i];
	}
	delete[](data);
	data = tmp;
}
public:
void push(const T& elem) {
	if (size + 1 > MAX_SIZE) {
		throw(std::length_error("Stack will become too large!"));
	}
	size = size + 1;
	(*this).resize(size);
	data[size - 1] = elem;
}
void pop() {
	if ((*this).empty()) {
		throw(std::logic_error("Nothing to pop: stack is empty!"));
	}
	size = size - 1;
}
T& top() {
	if ((*this).empty()) {
		throw(std::logic_error("Empty stack has no top!"));
	}
	return(data[size - 1]);
}
T& top()const {
	if ((*this).empty()) {
		throw(std::logic_error("Empty stack has no top!"));
	}
	return(data[size - 1]);
}
bool empty()const {
	return(size == 0);
}
};