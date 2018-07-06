#include "gtest/gtest.h"

#include "test_utils.h"

#include "../src/munkres.h"

TEST(munkres_sub_min_row, Correct)
{
  const int n = 3;
  const int m = 4;
  float a[n * m] = {
    1, 2, 3, 2,
    2, 1, 3, 1,
    3, 4, 2, 3
  };
  float a_true[n * m] = {
    0, 1, 2, 1,
    1, 0, 2, 0,
    1, 2, 0, 1,
  };

  munkres_sub_min_row(a, n, m);
  assert_all_equal(a_true, a, n * m);
}

TEST(munkres_sub_min_col, Correct)
{
  const int n = 3;
  const int m = 4;
  float a[n * m] = {
    1, 2, 3, 2,
    2, 1, 3, 1,
    3, 4, 2, 3
  };
  float a_true[n * m] = {
    0, 1, 1, 1,
    1, 0, 1, 0,
    2, 3, 0, 2,
  };

  munkres_sub_min_col(a, n, m);
  assert_all_equal(a_true, a, n * m);
}

TEST(munkres_step_1, Correct)
{
  const int n = 3;
  const int m = 4;

  float a[n * m] = {
    0, 1, 1, 1,
    1, 0, 1, 0,
    2, 3, 0, 2,
  };

  bool s[n * m] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
  };

  bool s_true[n * m] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
  };

  munkres_step_1(a, s, n, m);
  assert_all_equal(s_true, s, n * m);
}

TEST(munkres_step_1, ShouldReturnTrue)
{
  const int n = 3;
  const int m = 4;

  bool s[n * m] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
  };
  bool c1[m] = { 
    0, 0, 0, 0
  };

  bool done = munkres_step_2(s, c1, n, m);
  ASSERT_EQ(true, done);
}

TEST(munkres_step_1, ShouldReturnFalse)
{
  const int n = 3;
  const int m = 4;

  bool s[n * m] = {
    1, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 1, 0,
  };
  bool c1[m] = { 
    0, 0, 0, 0
  };

  bool done = munkres_step_2(s, c1, n, m);
  ASSERT_EQ(false, done);
}

#ifndef EXCLUDE_MAIN
int main(int argc, char *argv[]) 
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif