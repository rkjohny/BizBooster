/*
 * Author: Rezaul Karm
 * Email: rkjohny@gmail.com
 * Creation Date: 11/04/2016
 *
 * Copyright (C) 2016 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of Rezaul Karim and
 *     is not to be disclosed or used without prior written permission of Rezaul Karim.
 *     This copyright extends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 *     Please refer to License.txt file for more details.
 */

#include <iostream>
#include <gtest/gtest.h>
#include <type_traits>

using namespace std;

// running all test cases

int main( int argc, char **argv )
{
    std::cout << "Running Json testing..." << std::endl;

    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
