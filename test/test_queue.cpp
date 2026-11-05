#include <gtest/gtest.h>
#include <array>
#include <utility>
#include "queue.h"
TEST(test_queue, can_create_queue) {
	EXPECT_NO_THROW(Queue<int>(5));
}
TEST(test_queue, cannot_create_too_large_queue) {
	EXPECT_ANY_THROW(Queue<int>(MAX_SIZE+1));
}
TEST(test_queue, cannot_create_queue_with_unpositive_size) {
	EXPECT_ANY_THROW(Queue<int>(0));
}
TEST(test_queue, can_get_size_of_queue) {
	Queue<int>q(5);
	q.push(1);
	EXPECT_EQ(q.len(), 1);
}
TEST(test_queue, can_create_if_queue_is_empty) {
	Queue<int>q(5);
	std::array<bool, 2>arr = { q.empty() };
	q.push(1);
	arr[1] = q.empty();
	std::array<bool, 2>arr2 = { true, false };
	EXPECT_EQ(arr, arr2);
}
TEST(test_queue, can_create_copied_queue) {
	Queue<int>q(5);
	q.push(1);
	Queue<int>q1(q);
	EXPECT_EQ(q, q1);
}
TEST(test_queue, can_create_copied_queue_by_empty_queue) {
	Queue<int>q(5);
	Queue<int>q1(q);
	EXPECT_EQ(q, q1);
}
TEST(test_queue, can_assign_queue_to_itself) {
	Queue<int>q(5); 
	Queue<int>q1(q);
	q = q;
	EXPECT_EQ(q, q1);
}
TEST(test_queue, can_assign_queue_to_other) {
	Queue<int>q(5);
	Queue<int>q1(4);
	q1.push(1);
	q = q1;
	EXPECT_EQ(q, q1);
}
TEST(test_queue, can_assign_empty_queue) {
	Queue<int>q(5);
	q.push(1);
	Queue<int>q1(4);
	q = q1;
	EXPECT_EQ(q, q1);
}
TEST(test_queue, can_move_queue) {
	Queue<int>q(5);
	Queue<int>q1(q);
	Queue<int>q2(std::move(q));
	EXPECT_EQ(q1, q2);
}
TEST(test_queue, can_do_move_assignment) {
	Queue<int>q(5);
	Queue<int>q1(q);
	Queue<int>q2=(std::move(q));
	EXPECT_EQ(q1, q2);
}
TEST(test_queue, can_compare_queues) {
	Queue<int>q(5);
	Queue<int>q1(5);
	Queue<int>q2(4);
	Queue<int>q3(q);
	q.push(1);
	std::array<bool, 6>arr = { q3 == q3, q3 == q, q3 == q2, q3 == q1, q3!=q,q3!=q3  };//Проверяем: на равенство с собой,
	//на неравенство при изменении очереди, на равенство равных очередей с разными capacity, на равенство очередей 
	//с нулевыми размерами, 2 проверки на неравенство.
	std::array<bool, 6> arr2 = { true, false, true, true, true, false };
	EXPECT_EQ(arr, arr2);
}
TEST(test_queue, different_accomodation_of_elements_inside_of_memory_is_not_important_if_queues_must_be_equal) {
	//Не сумел придумать адекватного названия для теста, поэтому поясню так. Благодаря работе с памятью
	//очередь может изменить расположение в памяти, но не измениться для пользователя. Это надо отследить отдельно.
	Queue<int>q(1);
	q.push(1);
	q.push(2);
	Queue<int>q1(1);
	q1.push(1);
	q1.push(1);
	q1.pop();
	q1.push(2);
	EXPECT_EQ(q, q1);
}
TEST(test_queue, can_get_the_bottom_of_the_queue) {
	Queue<int>q(5);
	q.push(1);
	q.push(2);
	EXPECT_EQ(q.bottom(), 1);
}
TEST(test_queue, cannot_get_bottom_from_the_empty_queue) {
	Queue<int>q(5);
	EXPECT_ANY_THROW(q.bottom());
}
TEST(test_queue, get_pop_an_element_from_a_queue) {
	Queue<int>q(5);
	Queue<int>q1(q);
	q.push(1);
	q.pop();
	EXPECT_EQ(q, q1);
}
TEST(test_queue, popping_an_element_changes_a_queue) {
	Queue<int>q(5);
	q.push(1);
	q.pop();
	EXPECT_EQ(q.len(), 0);
}
TEST(test_queue, can_push_an_element_to_queue) {
	Queue<int>q(5);
	q.push(1);
	EXPECT_EQ(q.bottom(), 1);
}
TEST(test_queue, pushing_changes_size) {
	Queue<int>q(5);
	q.push(1);
	EXPECT_EQ(q.len(), 1);
}
TEST(test_queue, DISABLED_cannot_push_to_large_queue) {
	Queue<int>q(MAX_SIZE);
	for (int i = 0; i < MAX_SIZE; i++) {
		q.push(1);
	}
	EXPECT_ANY_THROW(q.push(1));
}