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
 AWSController
 To Handle AWS connections for each AWSController

 AWSController will manage creating servers, stopping servers

 @class   AWSController
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

creating new server:
aws ec2 run-instances --image-id ami-8a8c81e0 --count 1 --instance-type t2.micro --key-name swarm-ubuntu --security-group-ids sg-00c05278 --subnet-id subnet-1ba0c66d



AWS create instance of server from image:
"aws ec2 run-instances --image-id ami-8a8c81e0 --count 1
--instance-type t2.micro --key-name swarm-ubuntu
--security-group-ids sg-00c05278 --subnet-id subnet-1ba0c66d"

THIS IS THE ONLY ASPECT THAT SHOULD MAKE ANY DIRECT AWS CALLS

//optional flags
//--dry-run | --no-dry-run (boolean)
//--tag Name=my-new-instance
system("aws ec2 run-instances --image-id ami-8a8c81e0 --count 1 --instance-type t2.micro --key-name swarm-ubuntu --security-group-ids sg-00c05278 --subnet-id subnet-1ba0c66d --tag Name=HAM --dry-run=true");
//exe_cmd("aws iam list-users", wg)
//exe_cmd("aws ec2 create-key-pair --key-name MyKeyPair", wg)
//exe_cmd("aws ec2 run-instances --image-id ami-8a8c81e0 --count 1 --instance-type t2.micro --key-name mkp --security-group-ids sg-00c05278 --subnet-id subnet-1ba0c66d --debug", wg)

chmod 400 7pnvnj2bf0.pem
ssh -i "root.pem" ec2-user@52.23.199.106

TODO:: CPP should always call Go service for any AWS call, or any MongoDB call.
This way, the cpp segments can just parse the JSON that returns, and This
abstracts the AWS and MONGO details

*/
#ifndef CONTROLLER
#define CONTROLLER
#include "Controller.h"
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
#include <string.h>
#include <fstream>
using namespace std;
class AWSController : public Controller{
        private:
          /*
            * @name createNewCertificate
            * @desc calls AWSCLI to create new certificate for a player
            * @param void
            * @return void, but should return a boolean based on success
          */
          void createNewCertificate(string playerID){
            //creates new certificate
            Debug::LogImportant("AWSController, createNewCertificate for player, AWSCLI", todo);
            //create new certificate
            string certificateCreated = execute("../go/bin/service create "+playerID);
            Debug::LogImportant("AWSController, CreateNewCert Response: "+certificateCreated, verbose);
            //string certificateCreated = this->db.callDB("create", playerID);
            string certificateCreatedResult = this->db.parseForRealJSON(certificateCreated);
            Debug::LogImportant(certificateCreatedResult, verbose);
            //parse for certificate
            string certificate = this->db.parse(certificateCreatedResult, "KeyMaterial").asString();
            Debug::LogImportant("[CERT]"+certificate+"[CERT]", verbose);
            //inserts certificate response into db
            Debug::LogImportant("AWSController, createNewCertificate, Insert Into DB", todo);
            // string success = this->db.callDB("insertPlayerCertificate", '"' + this->db.substituteString(certificate, "\n") + '"');
            certificate = this->db.trimBeginning(certificate, this->db.b);
            certificate = this->db.trimTrailing(certificate, this->db.e);
            string success = this->db.callDB("insertPlayerCertificate", '"' + certificate + '"');
            Debug::LogImportant("AWSController, createNewCertificate, write certificate to file", todo);
            this->writeFile(certificate, "../cert/", playerID+".pem",this->db.b,this->db.e,true);
            // string sshIn = execute("ssh -i '../swarm.pem' ec2-user@54.164.79.248");
            //
            // Debug::LogImportant("AWSController, createNewCertificate, SSH'ing, "+sshIn, todo);
            //cout << certificateStored << endl;
          }
          /*
            * @name addNewServer
            * @desc calls AWSCLI to add a new server using a specific certs
            * @param void
            * @return void, but should return a boolean based on success
          */
          void addNewServer(string playerID){
            //todo
            Debug::LogImportant("AWSController, addNewServer Server using player credentials created", todo);
            //command
            string serverAdded = execute("../go/bin/service launch "+playerID);
            Debug::LogImportant(serverAdded, verbose);
            string serverAddedResult = this->db.parseForRealJSON(serverAdded);
            Debug::LogImportant(serverAddedResult, verbose);
            execute("chmod 400 ../cert/"+playerID+".pem");
            //parse for certificate
            string ownerID(this->db.parse(serverAddedResult, "OwnerId").asString());
            Debug::LogImportant("[OWNERID]"+ownerID+"[OWNERID]", debug);
            Json::Value instances = this->db.parse(serverAddedResult, "Instances");
            //Json::Value IP = this->db.parse(instances, "PrivateIpAddress");
            cout << instances[0] << endl;
            cout << instances[0]["PrivateIpAddress"] << endl;
            //Json::Value IP = this->db.parse(instances[0].asString(), "PrivateIpAddress");
            Debug::LogImportant("[PRIVATEIPADDRESS] "+instances[0]["PrivateIpAddress"].asString()+" [PRIVATEIPADDRESS]", todo);
            //aws ec2 describe-instances --instance-ids i-1234567890abcdef0
            cout << instances[0]["InstanceId"]  << endl;
            string description = execute("aws ec2 describe-instances --instance-ids "+instances[0]["InstanceId"].asString());
            Debug::LogImportant("[INSTANCEID] "+description+" [INSTANCEID]", todo);
            Json::Value reservations = this->db.parse(description,"Reservations");
            //cout << reservations[0] << endl;
            cout << reservations[0]["Instances"] << endl;
            //Json::Value server = this->db.parse(reservations[0], "Instances");
            string IPAddress(reservations[0]["Instances"][0]["PublicIpAddress"].asString());
            Debug::LogImportant("[PUBLICIPADDRESS] "+IPAddress+" [PUBLICIPADDRESS]", todo);
            //cout << server[0]["PublicIpAddress"] << endl;
            //string publicIP(server[0]["PublicIpAddress"].asString());
            //ssh -i "root.pem" ec2-user@52.23.199.106,54.175.179.122
            Debug::LogImportant("ssh -i '../cert/"+playerID+".pem' ubuntu@"+IPAddress, verbose);
          }
        public:
          /**
            * @desc constructor
            * @param void, maybe could pass credentials?
            * @return an instance of AWSController
          */
          AWSController(){
            //AWSController aws = this;
            this->model.type = AWSType;
            const void * selfAddress = static_cast<const void*>(this);
            stringstream ssSelf;
            ssSelf << selfAddress;
            string selfStringAddress = ssSelf.str();
            Debug::Log("Creating AWSController Controller - "+selfStringAddress, debug);
          }
          /*
            * @name createCredentials
            * @desc creates certificate for this player
            * Note: In go, createLoginCert actually creates cert via
            ** exe_cmd("aws ec2 create-key-pair --key-name MyKeyPair", wg)
            * @param void, should pass a playerID?
            * @return void, but should return a boolean based on success?
          */
          void createCredentials(string playerID){
            Debug::Log("AWSController credential is being created", debug);
            this->createNewCertificate(playerID);
          }
          /*
            * @name Create
            * @desc Creates a new server for player, calls addNewServer
            * @param void, maybe should pass in playerID string?
            * @return void, but should return a boolean based on success?
          */
          void create(string playerID){
            Debug::Log("AWSController Server is being created", debug);
            this->addNewServer(playerID);
          }
          /*
            * @name start
            * @desc start player server on AWS
            * @param void, should pass a serverID, or playerID?
            * @return void, but should return a boolean based on success?
          */
          void start(){
            Debug::LogImportant("AWSController, Start AWS Server", todo);
            //this->startLoop();
          }
          /*
            * @name stop
            * @desc stops player server on AWS
            * @param void, should pass a serverID, or playerID?
            * @return void, but should return a boolean based on success?
          */
          void stop(){
            Debug::LogImportant("AWSController, Stop AWS Server", todo);
            this->stopLoop();
          }
          /*
            * @name retire
            * @desc terminates a player server on AWS
            * @param void, should pass a serverID, or playerID?
            * @return void, but should return a boolean based on success?
          */
          void retire(){
            Debug::LogImportant("AWSController, Retire AWS Server", todo);
          }
          /*
            * @name execute
            * @desc Logs any output to the console for developer
            * @param string for the message, and a ModeType for category of log
            * @return void, but should return a boolean based on success?
          */
          string execute(string cmd) {
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
          /*
            * @name readFile
            * @desc Read a designated file
            * @param void
            * @return void, but should return a boolean based on success
          */
          string readFile(string file){
            Debug::LogImportant("AWSController, readFile", todo);
            // string line;
            // ifstream myfile (file);
            // if (myfile.is_open())
            // {
            //   while ( getline (myfile,line) )
            //   {
            //     cout << line << '\n';
            //   }
            //   myfile.close();
            // }else cout << "Unable to open file";
            // return true;
                std::ifstream ifs(file);
                string test = string((std::istreambuf_iterator<char>(ifs)),
                              (std::istreambuf_iterator<char>()));
                return test;
          }
          /*
            * @name writeFile
            * @desc write to a specific file
            * @param void
            * @return bool - whether it worked
          */
          bool writeFile(string textToWrite, string location, string fileName, string prefix = "", string suffix = "", bool endLine = false){
            Debug::LogImportant("AWSController, writeFile, "+textToWrite, todo);
            ofstream myfile (location+fileName);
              if (myfile.is_open())
              {
                myfile << prefix;
                myfile << textToWrite;
                myfile << suffix;
                myfile.close();
              }else cout << "Unable to open file";
              return true;
          }
};
