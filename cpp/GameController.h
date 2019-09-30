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
 GameController
 To control manipilation of games

 GameController will be used by Game to create/control games

 @class   GameController
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
#ifndef CONTROLLER
#define CONTROLLER
#include "Controller.h"
#endif
#ifndef DEBUG
#define DEBUG
#include "Debug.h"
#endif
#ifndef AWS_CONTROLLER
#define AWS_CONTROLLER
#include "AWSController.h"
#endif
#ifndef ACTION_CONTROLLER
#define ACTION_CONTROLLER
#include "ActionController.h"
#endif
#include <iostream>
using namespace std;
class GameController : public Controller{
	private:
		const string ID = GameController::GenerateID(25);
	public:
		AWSController aws;
		ActionController ac;
	GameController(){
		this->model.type = GameType;
		const void * selfAddress = static_cast<const void*>(this);
		stringstream ssSelf;
		ssSelf << selfAddress;
		string selfStringAddress = ssSelf.str();
		Debug::Log("creating GAMEController, With AWSController and With ID "+this->ID+" - "+selfStringAddress, debug);
	}

	/*
	  * @desc opens a modal window to display a message
	  * @param string $msg - the message to be displayed
	  * @return bool - success or failure
	*/
	void initiate(){
		Debug::LogImportant("GameController, Initiating Game, Insert Player to DB & fetching", todo);
		//string playerInserted = execute("../go/bin/service insertPlayer");
		string playerInserted = this->db.callDB("insertPlayer");
		string playerInsertedResult = this->db.parseForRealJSON(playerInserted);
		string playerID = this->db.parse(playerInsertedResult, "PlayerID").asString();
		Debug::LogImportant("[PlayerID]"+playerID+"[PlayerID]", verbose);
		try{
			this->aws.createCredentials(playerID);
		} catch(runtime_error &ex){
			Debug::Log("GameController, Initiate, Error in Creating AWS Credentials", verbose);
		}
		//initiate MQTT connection with pairing broker to keep player/game info in persistent/realtime?
		try{
			Debug::LogImportant("Initiate MQTT connection with pairing broker?", question);
			//call MQTT pair
		}catch(runtime_error &ex){
			Debug::Log("GameController, Initiate, Error in Pairing with MQTT", verbose);
		}

		//create a new instance using the credentials for this player
		try{
			this->aws.create(playerID);
		} catch(runtime_error &ex){
			Debug::Log("GameController, initiate Error in Creating AWS Server", verbose);
		}

	}
	/*
		* @desc opens a modal window to display a message
		* @param string $msg - the message to be displayed
		* @return bool - success or failure
	*/
	void PairPlayers(){
		Debug::Log("GameController, Pairing Players ", debug);
	}
	/*
		* @desc opens a modal window to display a message
		* @param string $msg - the message to be displayed
		* @return bool - success or failure
	*/
	static string GenerateID(const int len){
		char *s;
		static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
		string returnString(s);
		return returnString;
	}
	/*
		* @desc opens a modal window to display a message
		* @param string $msg - the message to be displayed
		* @return bool - success or failure
	*/
	int getIDLength(){
		return this->ID.length();
	}
	/*
		* @desc opens a modal window to display a message
		* @param string $msg - the message to be displayed
		* @return bool - success or failure
	*/
	void start(){
		try{
			Debug::Log("GameController, Starting Game ", debug);
			this->aws.start();
		} catch(runtime_error &ex){
				Debug::LogImportant("Runtime Error GameController", verbose);
		}
	}
	/*
		* @desc opens a modal window to display a message
		* @param string $msg - the message to be displayed
		* @return bool - success or failure
	*/
	void stop(){
		try{
			Debug::Log("GameController, Stop Game ", debug);
			this->aws.stop();
		} catch(runtime_error &ex){

		}
	}
};
