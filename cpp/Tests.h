/*
Copyright 2014-Present Hacker Combat Authors
This file is part of the Hacker Combat library.
The Hacker Combat Protocol is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
The Hacker Combat Protocol is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public License
along with the Hacker Combat Protocol library. If not, see <http://www.gnu.org/licenses/>.
*/
/*
 Tests
 To handle unit testing

 Tests will be used to control all unit testing

 @class      Tests
 @package    GameFoundation
 @author     Jovonni L. Pharr <jpharr2@student.gsu.edu>
 @copyright  2014-2016 The Hacker Combat Organization
 @version    1.0.1
 @link       http://www.hackercombat.org
 @see        http://www.hackercombat.org/help
 @since      File available since Release 1.0.1
 @deprecated N/A


//==================================

function documentation


  * @desc opens a modal window to display a message
  * @param string $msg - the message to be displayed
  * @return bool - success or failure
*


*/

#ifndef MAIN_GAME_TESTS_H
#define MAIN_GAME_TESTS_H

#include <tut/tut.hpp>
#include <tut/tut_console_reporter.hpp>
#include <tut/tut_main.hpp>


#endif


#ifndef MAIN_GAME_i
#define MAIN_GAME_i

#include "MainGame.h"

#endif


#ifndef AWS_CONTROLLER
#define AWS_CONTROLLER
#include "AWSController.h"
#endif

#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER
#include "GameController.h"
#endif

#ifndef GAME
#define GAME
#include "Game.h"
#endif

#ifndef DEBUG
#define DEBUG
#include "Debug.h"
#endif

#ifndef DATABASE
#define DATABASE
#include "Database.h"
#endif


#include <string>
#include <cstdio>
#include <cstring>

// This is the JSON header
#include <json/json.h>

// #ifndef FUNCTIONS
// #define FUNCTIONS
// #include "Functions.h"
// #endif


void runTests();
