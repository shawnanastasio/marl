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

#include "osfiber.h"

#include "marl_test.h"

TEST(WithoutBoundScheduler, OSFiber)
{
    std::string str;
    auto constexpr fiberStackSize = 8 * 1024;
    auto main = std::unique_ptr<marl::OSFiber>(marl::OSFiber::createFiberFromCurrentThread());
    std::unique_ptr<marl::OSFiber> fiberA, fiberB, fiberC;
    fiberC = std::unique_ptr<marl::OSFiber>(marl::OSFiber::createFiber(fiberStackSize, [&]
    {
        str += "C";
        fiberC->switchTo(fiberB.get());
    }));
    fiberB = std::unique_ptr<marl::OSFiber>(marl::OSFiber::createFiber(fiberStackSize, [&]
    {
        str += "B";
        fiberB->switchTo(fiberA.get());
    }));
    fiberA = std::unique_ptr<marl::OSFiber>(marl::OSFiber::createFiber(fiberStackSize, [&]
    {
        str += "A";
        fiberA->switchTo(main.get());
    }));

    main->switchTo(fiberC.get());

    ASSERT_EQ(str, "CBA");
}
