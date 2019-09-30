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
 Controller
 Controller will call loop methods, and updating information on the loop
 specified by the child object

 Controller will inferited from an ActionController, AWSController, or a GameController

 @class      Controller
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
#ifndef MODEL
#define MODEL
#include "Model.h"
#endif
#ifndef DEBUG
#define DEBUG
#include "Debug.h"
#endif
#ifndef DATABASE
#define DATABASE
#include "Database.h"
#endif
#include <iostream>
#include <thread>
enum LoopType { listening, notListening};
static LoopType LoopMode = notListening;
class Controller{
private:
  int gameSpeed;
public:
    Model model;
    Database db;
    Controller(){
      Debug::Log("Inside Controller Constructor, Switch, Check for child class type ", todo);
      //this->model.update(this->model.type);
      const void * selfAddress = static_cast<const void*>(this);
      stringstream ssSelf;
      ssSelf << selfAddress;
      string selfStringAddress = ssSelf.str();
      const void * modelAddress = static_cast<const void*>(&this->model);
      stringstream ssModel;
      ssModel << modelAddress;
      string selfStringModel = ssModel.str();
      Debug::Log("Controller Constructor: object: "+selfStringAddress+" | Model: " + selfStringModel, debug);
    }
    void updateModel(){
      Debug::Log("Updating Model, inside Controller", debug);
      this->model.update(this->model.type);
    }
    void createLoop(){
      Debug::Log("Controller, Creating Loop",debug);
    }
    void startLoop(){
      Debug::Log("Controller, Starting Loop",debug);
      std::thread loopThread;
      std::thread stopperThread;
      stopperThread = std::thread([=] {
        sleep(1);
        //Debug::Log("Controller, Threading for timer canceler",debug);
        LoopMode = listening;
      });
      // Sleep for 50*1000ms
      if(LoopMode == notListening){
        loopThread = std::thread([=] {
          //for(int i = 0; i <10; i++){
          int i = 0;
          while(LoopMode == notListening){
            Debug::LogImportant("Inside Controller, loop iterator in startLoop:  "+to_string(i), todo);
            string str = "figlet "+to_string(i);
            system(str.c_str());
            //cout << this->execute(str.c_str()) << endl;
            Debug::Log("Inside Controller, Start Loop called from AWSController Start(), should this only update AWS related model (e.g ~stats)?", question);
            this->updateModel();
            sleep(1);
            i++;
          }
        });
      }else{
        Debug::LogImportant("Looping and active loop mode", todo);
        //sleep(1);
      }
      stopperThread.join();
      loopThread.join();
    }
    void fetchDataFromModel(){
      Debug::Log("Controller, Fetching Data From Model",debug);
    }
    void stopLoop(){
      Debug::Log("Controller, Stopping Loop",debug);
    }
    static string execute(string cmd) {
      string data;
      FILE * stream;
      const int max_buffer = 256;
      char buffer[max_buffer];
      cmd.append(" 2>&1");
      stream = popen(cmd.c_str(), "r");
      if (stream) {
        while (!feof(stream))
          if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
          pclose(stream);
        }
      return data;
    }
};
