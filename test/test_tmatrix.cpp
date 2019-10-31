#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
	try
	{
		TMatrix<int> m(5);
	}
	catch (char* err)
	{
		cout << err;
	}
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	/*TMatrix<int> m(5);

	m[1][2] = 17;
	m[4][2] = -10;

	TMatrix<int> m1(m);

	EXPECT_EQ(m1, m);*/
	ADD_FAILURE();
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
  ADD_FAILURE();
}

TEST(TMatrix, can_get_size)
{
  ADD_FAILURE();
}

TEST(TMatrix, can_set_and_get_element)
{
  ADD_FAILURE();
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
  ADD_FAILURE();
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
  ADD_FAILURE();
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
  ADD_FAILURE();
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
  ADD_FAILURE();
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
  ADD_FAILURE();
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
  ADD_FAILURE();
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
  ADD_FAILURE();
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
  ADD_FAILURE();
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
  ADD_FAILURE();
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m1(5), m2(5);

	m1[1][4] = 7;
	m1[2][3] = -5;

	m2[1][4] = 5;
	m2[2][3] = -5;

	TMatrix<int> sum = m1 + m2;

	EXPECT_EQ(sum[1][4], m1[1][4] + m2[1][4]);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	const int size1 = 5, size2 = 10;
	TMatrix<int> m1(size1), m2(size2);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
  ADD_FAILURE();
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	const int size1 = 5, size2 = 10;
	TMatrix<int> m1(size1), m2(size2);
	ASSERT_ANY_THROW(m1 - m2);
}

