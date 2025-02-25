// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "marl/containers.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <cstddef>
#include <string>

class ContainersVectorTest : public testing::Test {};

TEST(ContainersVectorTest, Empty)
{
    marl::containers::vector<std::string, 4> vector;
    ASSERT_EQ(vector.size(), size_t(0));
}

TEST(ContainersVectorTest, WithinFixedCapIndex)
{
    marl::containers::vector<std::string, 4> vector;
    vector.resize(4);
    vector[0] = "A";
    vector[1] = "B";
    vector[2] = "C";
    vector[3] = "D";

    ASSERT_EQ(vector[0], "A");
    ASSERT_EQ(vector[1], "B");
    ASSERT_EQ(vector[2], "C");
    ASSERT_EQ(vector[3], "D");
}

TEST(ContainersVectorTest, BeyondFixedCapIndex)
{
    marl::containers::vector<std::string, 1> vector;
    vector.resize(4);
    vector[0] = "A";
    vector[1] = "B";
    vector[2] = "C";
    vector[3] = "D";

    ASSERT_EQ(vector[0], "A");
    ASSERT_EQ(vector[1], "B");
    ASSERT_EQ(vector[2], "C");
    ASSERT_EQ(vector[3], "D");
}

TEST(ContainersVectorTest, WithinFixedCapPushPop)
{
    marl::containers::vector<std::string, 4> vector;
    vector.push_back("A");
    vector.push_back("B");
    vector.push_back("C");
    vector.push_back("D");

    ASSERT_EQ(vector.size(), size_t(4));
    ASSERT_EQ(vector.end() - vector.begin(), ptrdiff_t(4));

    ASSERT_EQ(vector.front(), "A");
    ASSERT_EQ(vector.back(), "D");
    vector.pop_back();
    ASSERT_EQ(vector.size(), size_t(3));
    ASSERT_EQ(vector.end() - vector.begin(), ptrdiff_t(3));

    ASSERT_EQ(vector.front(), "A");
    ASSERT_EQ(vector.back(), "C");
    vector.pop_back();
    ASSERT_EQ(vector.size(), size_t(2));
    ASSERT_EQ(vector.end() - vector.begin(), ptrdiff_t(2));

    ASSERT_EQ(vector.front(), "A");
    ASSERT_EQ(vector.back(), "B");
    vector.pop_back();
    ASSERT_EQ(vector.size(), size_t(1));
    ASSERT_EQ(vector.end() - vector.begin(), ptrdiff_t(1));

    ASSERT_EQ(vector.front(), "A");
    ASSERT_EQ(vector.back(), "A");
    vector.pop_back();
    ASSERT_EQ(vector.size(), size_t(0));
}

TEST(ContainersVectorTest, BeyondFixedCapPushPop)
{
    marl::containers::vector<std::string, 2> vector;
    vector.push_back("A");
    vector.push_back("B");
    vector.push_back("C");
    vector.push_back("D");

    ASSERT_EQ(vector.size(), size_t(4));
    ASSERT_EQ(vector.end() - vector.begin(), ptrdiff_t(4));

    ASSERT_EQ(vector.front(), "A");
    ASSERT_EQ(vector.back(), "D");
    vector.pop_back();
    ASSERT_EQ(vector.size(), size_t(3));
    ASSERT_EQ(vector.end() - vector.begin(), ptrdiff_t(3));

    ASSERT_EQ(vector.front(), "A");
    ASSERT_EQ(vector.back(), "C");
    vector.pop_back();
    ASSERT_EQ(vector.size(), size_t(2));
    ASSERT_EQ(vector.end() - vector.begin(), ptrdiff_t(2));

    ASSERT_EQ(vector.front(), "A");
    ASSERT_EQ(vector.back(), "B");
    vector.pop_back();
    ASSERT_EQ(vector.size(), size_t(1));
    ASSERT_EQ(vector.end() - vector.begin(), ptrdiff_t(1));

    ASSERT_EQ(vector.front(), "A");
    ASSERT_EQ(vector.back(), "A");
    vector.pop_back();
    ASSERT_EQ(vector.size(), size_t(0));
}

TEST(ContainersVectorTest, CopyConstruct)
{
    marl::containers::vector<std::string, 4> vectorA;

    vectorA.resize(3);
    vectorA[0] = "A";
    vectorA[1] = "B";
    vectorA[2] = "C";

    marl::containers::vector<std::string, 2> vectorB(vectorA);
    ASSERT_EQ(vectorB.size(), size_t(3));
    ASSERT_EQ(vectorB[0], "A");
    ASSERT_EQ(vectorB[1], "B");
    ASSERT_EQ(vectorB[2], "C");
}

TEST(ContainersVectorTest, MoveConstruct)
{
    marl::containers::vector<std::string, 4> vectorA;

    vectorA.resize(3);
    vectorA[0] = "A";
    vectorA[1] = "B";
    vectorA[2] = "C";

    marl::containers::vector<std::string, 2> vectorB(std::move(vectorA));
    ASSERT_EQ(vectorB.size(), size_t(3));
    ASSERT_EQ(vectorB[0], "A");
    ASSERT_EQ(vectorB[1], "B");
    ASSERT_EQ(vectorB[2], "C");
}

TEST(ContainersVectorTest, Copy)
{
    marl::containers::vector<std::string, 4> vectorA;
    marl::containers::vector<std::string, 2> vectorB;

    vectorA.resize(3);
    vectorA[0] = "A";
    vectorA[1] = "B";
    vectorA[2] = "C";

    vectorB.resize(1);
    vectorB[0] = "Z";

    vectorB = vectorA;
    ASSERT_EQ(vectorB.size(), size_t(3));
    ASSERT_EQ(vectorB[0], "A");
    ASSERT_EQ(vectorB[1], "B");
    ASSERT_EQ(vectorB[2], "C");
}

TEST(ContainersVectorTest, Move)
{
    marl::containers::vector<std::string, 4> vectorA;
    marl::containers::vector<std::string, 2> vectorB;

    vectorA.resize(3);
    vectorA[0] = "A";
    vectorA[1] = "B";
    vectorA[2] = "C";

    vectorB.resize(1);
    vectorB[0] = "Z";

    vectorB = std::move(vectorA);
    ASSERT_EQ(vectorA.size(), size_t(0));
    ASSERT_EQ(vectorB.size(), size_t(3));
    ASSERT_EQ(vectorB[0], "A");
    ASSERT_EQ(vectorB[1], "B");
    ASSERT_EQ(vectorB[2], "C");
}
