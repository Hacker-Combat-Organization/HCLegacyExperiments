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
 Database
 To handle all db calls for this application

 DBController

 @file   		 Database
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
// #ifndef FUNCTIONS
// #define FUNCTIONS
// #include "Functions.h"
// #endif
#ifndef CONTROLLER
#define CONTROLLER
#include "Controller.h"
#endif
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <typeinfo>
// This is the JSON header
#include <json/json.h>
using namespace std;
class Database{
  private:
  public:
    string b = "-----BEGIN RSA PRIVATE KEY-----\n";
    string e = "\n-----END RSA PRIVATE KEY-----\n";
    Database(){
      Debug::Log("Database Constructor", debug);
    }
    bool isConnected(){
      Debug::LogImportant("Database, How should we test connection to mgo?", question);
      return true;
    }
    string callDB(string call, string param1 = "n/a"){
        //inserts certificate response into db
        Debug::LogImportant("Database, CallDB", todo);
        string result;
        if( call == "insertPlayerCertificate" ){
          result = execute("../go/bin/service insertPlayerCertificate "+param1);
          result = this->parseForRealJSON(result);
          result = this->parse(result, "Result").asString();
          Debug::LogImportant("DB: "+result, demo);
          return result;
        }else if( call == "insertGame" ){
          result = execute("../go/bin/service insertGame");
          result = this->parseForRealJSON(result);
          result = this->parse(result, "Result").asString();
          Debug::LogImportant(result, demo);
          return result;
        }else if( call == "insertPlayer" ){
          result = execute("../go/bin/service insertPlayer");
          result = this->parseForRealJSON(result);
          //result = this->parse(result, "PlayerID");
          Debug::LogImportant(result, demo);
          return result;
        }else if( call == "create" ){
          result = execute("../go/bin/service create "+param1);
          result = this->parseForRealJSON(result);
          result = this->parse(result, "Result").asString();
          Debug::LogImportant(result, demo);
          return result;
        }else{
          return result;
        }
    }

    /*
      * @name   Parse
      * @desc   parses json string for specific key
      * @param  String json - the json object to parse
      * @param  String lookFor - the key that you are looking for
      * @return string - json string that is searched for
    */
    Json::Value parse(string json, string lookFor){
      Debug::LogImportant("Database, parsing JSON response? ", question);
      Json::Reader jsonReader;
      Json::Value jsonValue;
      bool parsedCorrectly;
      try{
        parsedCorrectly = jsonReader.parse(json,jsonValue,false);
        if(not parsedCorrectly){
          Debug::LogImportant("Did not Parse Correctly: "+jsonReader.getFormattedErrorMessages(), debug);
          return "no";
        }
      }catch(Json::LogicError &ex){
        Debug::LogImportant("Logic Error with trying to parse: "+jsonReader.getFormattedErrorMessages(), debug);
      }
      const Json::Value result = jsonValue[lookFor];
      //cout << typeid(result).name() << endl;
      //cout << jsonValue[0].asString() <<endl;
      return result;
      // if(not KM.isNull())
      // {
      //   cout<<"KM: "<< KM.asString() <<endl;
      // }else{
      //   cout << "IS NULL" << endl;
      // }

      //Debug::Log(KM.asString(),demo);

      ///////////

      // string json_example = "{\"test_array\": \
      //                       [\"test_item1\", \
      //                       \"test_item2\"], \
      //                       \"test_object\": \
      //                       \"test_value\" \
      //                       }";
      //
      //  // Let's parse it
      //  Json::Value root;
      //  Json::Reader reader;
      //  bool parsedSuccess = reader.parse(json_example, root, false);
      //
      //  if(not parsedSuccess){
      //    Debug::LogImportant("Failed to parse JSON"+reader.getFormatedErrorMessages(), debug);
      //  }
      //
      //  // Let's extract the array contained
      //  // in the root object
      //  const Json::Value array = root["array"];
      //
      //  // Iterate over sequence elements and
      //  // print its values
      //  for(unsigned int index=0; index<array.size();
      //      ++index)
      //  {
      //    cout<<"Element "<<index<<" in array: "<<array[index].asString()<<endl;
      //  }
      //
      //  // Lets extract the not array element
      //  // contained in the root object and
      //  // print its value
      //  const Json::Value notAnArray =
      //                root["not an array"];
      //
      //  if(not notAnArray.isNull())
      //  {
      //    cout<<"Not an array: "
      //        <<notAnArray.asString()
      //        <<endl;
      //  }
      //
      //  // If we want to print JSON is as easy as doing:
      //  cout<<"Json Example pretty print: "
      //      <<endl<<root.toStyledString()
      //      <<endl;
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
    static string trimTrailing(string str, string splitter){
      size_t endpos = str.find_last_not_of(splitter);
      if( string::npos != endpos )
      {
          str = str.substr( 0, endpos+1 );
      }
      return str;
    }
    static string trimBeginning(string str, string splitter){
      size_t startpos = str.find_first_not_of(splitter);
      if( string::npos != startpos )
      {
          str = str.substr( startpos );
      }
      return str;
    }
    static string parseForRealJSON(string json){
      string result;
      size_t startpos = json.find_first_of("{");
      if( string::npos != startpos )
      {
          result = json.substr( startpos );
      }
      size_t endpos = result.find_last_of("}");
      if( string::npos != endpos )
      {
          result = result.substr( 0, endpos+1 );
      }
      return result;
    }
    static string substituteString(string body, char occurence, char replacement){
      Debug::LogImportant("Database, substituteString, occurence: "+to_string(occurence), todo);
      // string s(body);
      // string o(occurence);
      // //std::replace( s.begin(), s.end(), "ABC", "AAA" ); // replace all 'x' to 'y'
	    // std::replace(s.begin(), s.end(), occurence, replacement); //global function
      // Debug::LogImportant("Database, substituteString, edited: "+s+" and "+o, todo);

      std::string str(body);
      std::replace(str.begin(), str.end(), occurence, replacement); //global function
      std::cout << str;
      return str;
    }
};
