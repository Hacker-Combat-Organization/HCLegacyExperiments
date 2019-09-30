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
 Debug
 Helper class for managing logs

 Debug

 @file   		 Debug
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
#include <iostream>
#include <string.h>
#include <ctime>
using namespace std;
enum ModeType { verbose, debug, demo, testing, todo, question };
static const ModeType Mode = todo;
class Debug{
  private:
  public:
    Debug(){

    }
    /*
      * @name Log
      * @desc Logs any output to the console for developer
      * @param string for the message, and a ModeType for category of log
      * @return void - void
    */
    static void Log(string message, ModeType category){
      switch(category)
      {
          case verbose:
            if(Mode == 0){
              //cout << "Verbose: " << message << endl;
              cout << "\033[1;31mVerbose C++: "<<Debug::GetTime()<<" | \033[0m" << "\033[1;37m"<<message<<"\033[0m\n";
            }
            break;
          case debug:
            if(Mode == 1){
              //cout << "Debug: " << message << endl;
              cout << "\033[1;34mDebug C++: "<<Debug::GetTime()<<" | \033[0m" << "\033[1;37m"<<message<<"\033[0m\n";
            }
            break;
          case demo:
            if(Mode == 2){
              //cout << "Demo: " << message << endl;
              cout << "\033[1;37Demo C++: "<<Debug::GetTime()<<" | \033[0m" << "\033[1;37m"<<message<<"\033[0m\n";
            }
          break;
          case testing:
              //cout << "Debug: " << message << endl;
              cout << "\033[1;33mTesting C++: "<<Debug::GetTime()<<" | \033[0m" << "\033[1;37m"<<message<<"\033[0m\n";
          break;
          case todo:
              //cout << "Debug: " << message << endl;
              cout << "\033[1;36mTODO C++: "<<Debug::GetTime()<<" | \033[0m" << "\033[1;37m"<<message<<"\033[0m\n";
          break;
          case question:
              //cout << "Debug: " << message << endl;
              cout << "\033[1;31mQuestion C++: "<<Debug::GetTime()<<" | \033[0m" << "\033[1;37m"<<message<<"\033[0m\n";
          break;
      }
    }
    static void LogImportant(string message, ModeType category){
        switch(category)
        {
            case verbose:
                cout << "\033[1;31mVerbose C++: "<<Debug::GetTime()<<" | \033[0m" << "\033[1;37m"<<message<<"\033[0m\n";
              break;
            case debug:
                cout << "\033[1;31mDebug C++: "<<Debug::GetTime()<<" | \033[0m" << "\033[1;37m"<<message<<"\033[0m\n";
              break;
            case demo:
                cout << "\033[1;31mDemo C++: "<<Debug::GetTime()<<" | \033[0m" << "\033[1;37m"<<message<<"\033[0m\n";
            break;
            case testing:
                cout << "\033[1;31mTesting C++: "<<Debug::GetTime()<<" | \033[0m" << "\033[1;37m"<<message<<"\033[0m\n";
            break;
            case todo:
                cout << "\033[1;35mTODO C++: "<<Debug::GetTime()<<" | \033[0m" << "\033[1;37m"<<message<<"\033[0m\n";
            break;
            case question:
                //cout << "Debug: " << message << endl;
                cout << "\033[1;35mQuestion C++: "<<Debug::GetTime()<<" | \033[0m" << "\033[1;37m"<<message<<"\033[0m\n";
            break;
        }
    }
    static string GetTime(){
      time_t rawtime;
      struct tm * timeinfo;
      char buffer[80];
      time (&rawtime);
      timeinfo = localtime(&rawtime);
      strftime(buffer,80,"%d-%m-%Y %I:%M:%S:%s",timeinfo);
      std::string str(buffer);
      return str;
    }
};
