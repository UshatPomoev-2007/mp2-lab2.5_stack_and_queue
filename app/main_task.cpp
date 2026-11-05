#include <iostream>
#include <string>
#include <array>
#include "../include/stack.h"
int place(std::array<char,4>arr, char elem) {
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] == elem) {
			return(i);
		}
	}
	return(-1);
}
bool bracket_checker(std::string str) {
	Stack<char>s;
	std::array<char, 4>lefts = { '(', '[', '{', '<'};
	std::array<char, 4>rights = { ')', ']', '}', '>'};
	if (str.size() == 0) {
		return(true);
	}
	if (place(rights, str[0])>-1) {
		return(false);
	}
	s.push(str[0]);
	for (int i = 1; i < str.size(); i++) {
		if (place(rights, str[i])>-1) {
			if (s.empty()) {
				return(false);
			}
			if (place(lefts, s.top()) == place(rights, str[i])) {
				s.pop();
				continue;
			}
			else {
				return(false);
			}
		}
		else {
			s.push(str[i]);
		}
	}
	return(s.empty());
}
int main() {
	std::array<std::string, 7>arr = { "","(,}", "([])","(][)","<[{}]>","[(){}]","[<{(>])"};
	for (int i = 0; i < arr.size(); i++) {
		std::cout << bracket_checker(arr[i]) << " ";//true, false, true, false, true, true, false
	}
}