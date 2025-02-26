#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> v1(15, 2);
	v1[5] = 120;
	v1[3] = -36;
	v1[12] = 54;
	TVector<int> v2(v1);
	EXPECT_EQ(v1, v2);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> v1(15, 2);
	v1[7] = 45;
	v1[13] = -10;
	TVector<int> v2(v1);
	v2[7] = 19;
	v2[13] = 100;
	EXPECT_NE(v1, v2);
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> v(5, 1);
	
	ASSERT_ANY_THROW(v[-1] = 10);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(5, 1);
	ASSERT_ANY_THROW(v[MAX_VECTOR_SIZE + 1] = 10);
}

TEST(TVector, can_assign_vector_to_itself) // ????
{
	TVector<int> v(5, 1);
	v[1] = 15;
	EXPECT_EQ(v, v = v);
}

TEST(TVector, can_assign_vectors_of_equal_size) // ????
{
	const int size = 5;
	TVector<int> v1(size, 1), v2(size, 2);
	for (int i = 2; i < size; i++)
		v1[i] = i;

	v2 = v1;

	EXPECT_NE(0, v2[size - 1]);
	//EXPECT_EQ(v2, v1);
}

TEST(TVector, assign_operator_change_vector_size)
{
	const int size1 = 5, size2 = 10;
	TVector<int> v1(size1, 1), v2(size2, 2);

	v2 = v1;
	EXPECT_EQ(size1, v2.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	const int size1 = 5, size2 = 10;
	TVector<int> v1(size1, 1), v2(size2, 2);

	v1[3] = 20;

	v2 = v1;

	EXPECT_EQ(20, v2[3]);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	const int size = 10;
	TVector<int> v1(size, 1), v2(size, 2);
	
	for (int i = 2; i < size; i++)
		v1[i] = v2[i] = i;

	EXPECT_TRUE(v1 == v2);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	const int size = 10;
	TVector<int> v1(size, 1), v2(size, 2);

	for (int i = 2; i < size; i++)
		v1[i] = i;

	EXPECT_TRUE(v1 == v1);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	const int size1 = 10, size2 = 15;
	TVector<int> v1(size1, 1), v2(size2, 2);

	EXPECT_FALSE(v1 == v2);
}

TEST(TVector, can_add_scalar_to_vector)
{
	const int size = 10;
	TVector<double> v1(size, 1), v2(size, 0);

	v2[0] = -20.5;
	v2[1] = -20.5;

	for (int i = 2; i < size; i++)
		v2[i] = (v1[i] = i) + -20.5;

	EXPECT_EQ(v1 + -20.5, v2);
	
	/*const int size = 10;
	TVector<double> v1(size, 1);
	v1[5] = 2.5;
	v1[9] = 100.0;

	TVector<double> v2 = v1 + 3;

	EXPECT_EQ(5.5, v2[5]);
	*/
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	const int size = 10;
	TVector<double> v1(size, 1), v2(size, 0);

	v2[0] = -15.5;
	v2[1] = -15.5;

	for (int i = 2; i < size; i++)
		v2[i] = (v1[i] = i) - 15.5;

	EXPECT_EQ(v1 - 15.5, v2);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	const int size = 10;
	TVector<double> v1(size, 1), v2(size, 0);

	for (int i = 2; i < size; i++)
		v2[i] = (v1[i] = i) * 7.3;

	EXPECT_EQ(v1 * 7.3, v2);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	const int size = 10;
	TVector<double> v1(size, 1), v2(size, 3), v3(size, 1);

	for (int i = 3; i < size; i++)
		v3[i] = (v1[i] = i) + (v2[i] = i*2.3);
	v3[1] = v1[1];
	v3[2] = v1[2];

	TVector<double> sum = v1 + v2;

	EXPECT_EQ(sum, v3);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	const int size1 = 10, size2 = 15;
	TVector<int> v1(size1, 1), v2(size2, 2);

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	const int size = 10;
	TVector<double> v1(size, 1), v2(size, 3), v3(size, 1);

	for (int i = 3; i < size; i++)
		v3[i] = (v1[i] = i) - (v2[i] = i * 2.3);
	v3[1] = -v1[1];
	v3[2] = -v1[2];

	TVector<double> sum = v1 - v2;

	EXPECT_EQ(sum, v3);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	const int size1 = 10, size2 = 15;
	TVector<int> v1(size1, 1), v2(size2, 2);

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	const int size = 10;
	TVector<double> v1(size, 1), v2(size, 3);
	double ActSum = 0.0;

	for (int i = 3; i < size; i++)
		ActSum += (v1[i] = i) * (v2[i] = i * 2.3);

	double sum = v1 * v2;

	EXPECT_EQ(sum, ActSum);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	const int size1 = 10, size2 = 15;
	TVector<int> v1(size1, 1), v2(size2, 2);

	ASSERT_ANY_THROW(v1 * v2);
}

