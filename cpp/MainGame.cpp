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
 MainGame
 To initiate

 MainGame

 @file   		 MainGame
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
#ifndef MAIN_GAME_i
#define MAIN_GAME_i
#include "MainGame.h"
#endif
#include <time.h>
int main(int argc, char* argv[]){
	clock_t tStart = clock();
	if(argc > 1){
			//string mode = (string(argv[1]));
			//bool testing = (mode == "test") ? true : false;
			//if(testing){
			string cmd = string(argv[1]);
			if(cmd == "test"){
				runTests();
			}else if(cmd == "play"){
				//system("mongo --eval 'b.serverStatus()' > TEST.TXT");
				//string query = "mongo --eval 'db.test.find()' > TEST.TXT ";
				// string query = "aws iam list-users";
				// system(query.c_str());
				//
				// std::ifstream t("TEST.TXT");
				// std::string str((std::istreambuf_iterator<char>(t)),
        // std::istreambuf_iterator<char>());
		    // str.erase(0, str.find("\n") + 1);
				// str.erase(0, str.find("\n") + 1);
		    // std::cout << str << endl;
				//
				//string str2 = "echo '" + myString + "' > TEST.TXT ";
				//system(str2.c_str());

				// Game game = Game::Game();
				// game.StartGame();
				// Debug::Log("In Between Start Game, and End Game Actions with arg count > ", debug);
				// game.StopGame();
			}
	}else{
		Game game = Game::Game();
		Debug::Log("Inside Main Game, Need to start game loop, or event driven design?", question);
		game.StartGame();
		//Debug::Log("In Between Start Game, and End Game Actions", debug);
		//game.StopGame();
	}
	//cout << Debug.Mode << endl;
	printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	return 0;
}
