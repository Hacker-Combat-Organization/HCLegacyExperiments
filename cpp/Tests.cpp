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
#ifndef TESTS
#define TESTS
#include "Tests.h"
#endif
#include <unordered_set>
class TestListenerBase
{
protected:
    void AddMethodCall(std::string methodName)
    {
        Debug::Log("Mock Base Class - AddMethodCall", todo);
        _methodsCalled.insert(methodName);
    }

    bool WasCalled(std::string methodName)
    {
        Debug::Log("Mock Method was called - Inside WasCalled", todo);
        return _methodsCalled.count(methodName) > 0;
    }
private:
    unordered_set<string> _methodsCalled;
};

#define REGISTER_METHOD(METHODNAME) \
    void METHODNAME () \
    { \
        AddMethodCall(#METHODNAME); \
    } \
    bool METHODNAME##WasCalled() \
    { \
        return WasCalled(#METHODNAME); \
    }
using namespace std;
#ifndef __MY_CLASS_MOCK__
#define __MY_CLASS_MOCK__
  //#include "TestListenerBase.h"
  //#include "MyClass.h"
  //a mock for game object
  class MyClassMock : public Game, public TestListenerBase
  {
  public:
      REGISTER_METHOD(DoSomething);
  };
  //->
#endif

namespace tut
{
    struct GameControllerTest{};
    typedef test_group<GameControllerTest> GameControllerTests;
    typedef GameControllerTests::object GameControllerTestObject;
    struct AWSControllerTest{};
    typedef test_group<AWSControllerTest> AWSControllerTests;
    typedef AWSControllerTests::object AWSControllerTestObject;
    struct ActionControllerTest{};
    typedef test_group<ActionControllerTest> ActionControllerTests;
    typedef ActionControllerTests::object ActionControllerTestObject;
    struct GameTest{};
    typedef test_group<GameTest> GameTests;
    typedef GameTests::object GameTestObject;
    struct ModelTest{};
    typedef test_group<ModelTest> ModelTests;
    typedef ModelTests::object ModelTestObject;
    struct ActionTest{};
    typedef test_group<ActionTest> ActionTests;
    typedef ActionTests::object ActionTestObject;
    struct ControllerTest{};
    typedef test_group<ControllerTest> ControllerTests;
    typedef ControllerTests::object ControllerTestObject;
    struct DatabaseTest{};
    typedef test_group<DatabaseTest> DatabaseTests;
    typedef DatabaseTests::object DatabaseTestObject;
}

namespace
{
    tut::GameControllerTests ServerTest("GameController Tests");
    tut::AWSControllerTests AWSTest("AWSController Tests");
    tut::ActionControllerTests ActionControllerTest("ActionController Tests");
    tut::GameTests GameTest("Game Tests");
    tut::ModelTests ModelTest("Model Tests");
    tut::ActionTests ActionTest("Action Tests");
    tut::ControllerTests ControllerTest("Controller Tests");
    tut::DatabaseTests DatabaseTest("Database Tests");
}


namespace tut{ //GameController tests
  template<>
  template<>
  void GameControllerTestObject::test<1>()
  {
    set_test_name("Check if object is created by checking string size");
    GameController gc;
    bool created = (gc.getIDLength() > 0) ? true : false;
    ensure(created);
  }
}

namespace tut{ //AWSController tests
  template<>
  template<>
  void AWSControllerTestObject::test<1>()
  {
    set_test_name("Check if Execute Command Works As Expected");
    AWSController aws = AWSController::AWSController();
    string command = "echo g";
    string expected = "g";
    string result = aws.execute(command);
    size_t startpos = result.find_first_not_of("\n");
    if( string::npos != startpos )
    {
        result = result.substr( startpos );
    }
    size_t endpos = result.find_last_not_of("\n");
    if( string::npos != endpos )
    {
        result = result.substr( 0, endpos+1 );
    }
    ensure_equals(expected,result);
  }
  template<>
  template<>
  void AWSControllerTestObject::test<2>()
  {
    set_test_name("Write a file");
    AWSController aws = AWSController::AWSController();
    string textToWrite = "A";
    string location = "../cert/";
    string fileName = "testing.txt";
    aws.writeFile(textToWrite,location,fileName);
    string result = aws.readFile(location+fileName);
    ensure_equals(result, textToWrite);
  }
}

namespace tut{ //ActionController tests
  template<>
  template<>
  void ActionControllerTestObject::test<1>()
  {
    set_test_name("Main ActionController Test");
  }
}

namespace tut{ //Game tests
  template<>
  template<>
  void GameTestObject::test<1>()
  {
    set_test_name("Show Scores");
    MyClassMock mock;
    bool result = mock.DoSomethingWasCalled(); // return false
    mock.DoSomething();
    result = mock.DoSomethingWasCalled(); // result true
    //ensure(GameShowScores());
    //Game game = Game::Game();
    //bool gameStarted = game.StartGame();
    //ensure(gameStarted);
  }
}

namespace tut{ //Model tests
  template<>
  template<>
  void ModelTestObject::test<1>()
  {
    set_test_name("Main Model Test");
  }
}

namespace tut{ //Action tests
  template<>
  template<>
  void ActionTestObject::test<1>()
  {
    set_test_name("Main Action Test");
  }
}

namespace tut{ //Controller tests
  template<>
  template<>
  void ControllerTestObject::test<1>()
  {
    set_test_name("Main Controller Test");
  }
}

namespace tut{ //Database tests
  template<>
  template<>
  void DatabaseTestObject::test<1>()
  {
    set_test_name("Database, check if parses json currectly");
    string json = "{\"test_array\": \
                          [\"test_item1\", \
                          \"test_item2\"], \
                          \"test_object\": \
                          \"test_value\" \
                          }";
    Database db;
    string expectedResult = "test_value";
    string result = db.parse(json, "test_object").asString();
    ensure_equals(result, expectedResult);
  }
  template<>
  template<>
  void DatabaseTestObject::test<2>()
  {
    set_test_name("Database, check if parses json currectly #2");
    string json = "{\"KeyName\": \"MyKeyPair\"}";
    Database db;
    string expectedResult = "MyKeyPair";
    string result = db.parse(json, "KeyName").asString();
    ensure_equals(result, expectedResult);
  }
  template<>
  template<>
  void DatabaseTestObject::test<3>()
  {
    set_test_name("check if string substring is removed correctly");
    string original("abc");
    string expected("axc");
    string result = Database::substituteString(original,'b','x');
    cout << result << endl;
    ensure_equals(result,expected);
  }
}


void runTests()
{
    Debug::Log("---------------------- ",testing);
    Debug::Log("Running All Tests:",testing);
    tut::console_reporter reporter;
    tut::runner.get().set_callback(&reporter);
    tut::runner.get().run_tests();
    Debug::Log("Tests Completed",testing);
    Debug::Log("---------------------- ",testing);
}
