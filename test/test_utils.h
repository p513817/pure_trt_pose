#pragma once

#include "gtest/gtest.h"

void AllFloatEqual(float *a, float *b, size_t N)
{
  for (size_t i = 0; i < N; i++) {
    ASSERT_FLOAT_EQ(a[i], b[i]);
  }
}

template<typename T>
void AllEqual(T *a, T *b, size_t N)
{
  for (size_t i = 0; i < N; i++) {
    ASSERT_EQ(a[i], b[i]);
  }
}

template<typename T>
void AllNear(T *a, T*b, size_t N, T abserr)
{
  for (size_t i = 0; i < N; i++) {
    ASSERT_NEAR(a[i], b[i], abserr);
  }
}