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
 Model
 Handles connections to data store that stores information on each game

 Model will be called by a controller on an interval that is arbitrary

 @class      Model
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
#ifndef DEBUG
#define DEBUG
#include "Debug.h"
#endif
enum ControllerType { ERRORTYPE, DBType, GameType, AWSType, ActionType };
#include <iostream>
class Model{
private:
  //Database db;
  bool insertNewGame(){
    Debug::Log("Inserting Game", debug);
    return true;
  }
public:
    ControllerType type;
    Model(){
      Debug::Log("Model Constructor", debug);
    }
    void update(ControllerType type){
      const void * selfAddress = static_cast<const void*>(this);
      stringstream ssSelf;
      ssSelf << selfAddress;
      string selfStringAddress = ssSelf.str();
      Debug::LogImportant("Update Model Here, for the associated controller", todo);
      switch(type){
        case ERRORTYPE:
          Debug::Log("Inside Model Update, ERRORTYPE, Not Set - "+selfStringAddress, todo);
          break;
        case DBType:
          Debug::Log("Inside Model Update, DBType - "+selfStringAddress, todo);

          break;
        case GameType:
          Debug::Log("Inside Model Update, GameType - "+selfStringAddress, todo);
          break;
        case AWSType:
          Debug::Log("Inside Model Update, AWSType - "+selfStringAddress, todo);
          break;
        case ActionType:
          Debug::Log("Inside Model Update, ActionType - "+selfStringAddress, todo);
          break;
        default:
          Debug::Log("Default Controller Type - "+selfStringAddress, todo);
          break;
      }
    }
    bool createNewGame(){
      Debug::Log("Creating New Game", debug);
      this->insertNewGame();
      return true;
    }
    string getConfigFile(){
      std::ifstream ifs("../config/config.json");
      std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );
      return content;
    }
};
