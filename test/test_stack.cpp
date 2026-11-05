#include <gtest/gtest.h>
#include <utility>
#include <array>
#include "stack.h"
TEST(test_stack, can_create_stack_with_positive_size) {
	EXPECT_NO_THROW(Stack<int>(10));
}
TEST(test_stack, cannot_create_stack_with_too_large_size) {
	EXPECT_ANY_THROW(Stack<int>(10000000));
}
TEST(test_stack, cannot_create_stack_with_negative_size) {
	EXPECT_ANY_THROW(Stack<int>(-1));
}
TEST(test_stack, can_create_copied_stack) {
	Stack<int>s(5);
	s.push(1);
	Stack<int>s1(s);
	EXPECT_EQ(s, s1);
}
TEST(test_stack, can_assign_stack_to_other) {
	Stack<int>s(5);
	Stack<int>s1(4);
	s = s1;
	EXPECT_EQ(s, Stack<int>(4));
}
TEST(test_stack, can_assign_stack_to_itself) {
	Stack<int>s(5);
	Stack<int>s1(s);
	s = s;
	EXPECT_EQ(s, s1);
}
TEST(test_stack, can_move_stack) {
	Stack<int>s(5);
	Stack<int>s1(s);//С чем-то же надо сравнивать результат перемещения
	Stack<int>s2(std::move(s));
	EXPECT_EQ(s1, s2);
}
TEST(test_stack, can_do_move_assignment) {
	Stack<int>s(5);
	Stack<int>s1(s);
	Stack<int>s2=std::move(s);
	EXPECT_EQ(s1, s2);
}
TEST(test_stack, can_get_size) {
	Stack<int>s(5);
	s.push(1);
	EXPECT_EQ(s.len(), 1);
}
TEST(test_stack, can_compare_stacks_correctly) {
	Stack<int>s(5);
	Stack<int>s1(5);
	Stack<int>s2(s1);
	s.push(1);
	std::array<bool,4> arr = { s == s1, s1 == s2, s != s1, s1 != s2 };
	std::array<bool,4> arr1 = { false, true, true, false };
	EXPECT_EQ(arr, arr1);
}
TEST(test_stack, can_push_an_element_to_stack) {
	Stack<int>s(5);
	s.push(2);
	std::array<bool, 2> arr = { s.top() == 2,s.len() == 1 };
	std::array<bool, 2> arr1 = { true, true };
	EXPECT_EQ(arr, arr1);
}
TEST(test_stack, DISABLED_cannot_push_to_large_stack) {
	Stack<int>s(MAX_SIZE);
	for (int i = 0; i < MAX_SIZE; i++) {
		s.push(1);
	}
	EXPECT_ANY_THROW(s.push(1));
}
TEST(test_stack, pushing_an_element_changes_size) {
	Stack<int>s(5);
	s.push(1);
	EXPECT_EQ(s.len(), 1);
}
TEST(test_stack, resize_is_not_a_problem_for_push) {
	Stack<int>s(5);
	s.push(2);
	s.push(3);
	std::array<int, 2>arr;
	arr[0] = s.top();
	s.pop();
	arr[1] = s.top();
	std::array<int, 2>arr2 = { 3,2 };
	EXPECT_EQ(arr, arr2);
}
TEST(test_stack, can_pop_an_element_from_stack) {
	Stack<int>s(5);
	s.push(2);
	s.pop();
	std::array<bool, 2> arr = { s.empty(),s.len() == 0};
	std::array<bool, 2> arr1 = { true, true };
	EXPECT_EQ(arr, arr1);
}
TEST(test_stack, popping_an_element_changes_size) {
	Stack<int>s(5);
	s.push(1);
	s.pop();
	EXPECT_EQ(s.len(), 0);
}
TEST(test_stack, cannot_pop_from_empty_stack) {
	Stack<int>s(5);
	EXPECT_ANY_THROW(s.pop());
}
TEST(test_stack, can_get_top_of_the_stack) {
	Stack<int>s(5);
	s.push(2);
	EXPECT_EQ(s.top(), 2);
}
TEST(test_stack, cannot_get_top_of_the_empty_stack) {
	Stack<int>s(5);
	EXPECT_ANY_THROW(s.top());
}
TEST(test_stack, can_check_stack_is_empty) {
	Stack<int>s(5);
	std::array<bool, 2> arr = {s.empty()};
	s.push(1);
	arr[1] = s.empty();
	std::array<bool, 2> arr1 = { true, false };
	EXPECT_EQ(arr, arr1);
}
