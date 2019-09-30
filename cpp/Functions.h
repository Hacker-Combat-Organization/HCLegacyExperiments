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
string trimTrailing(string str){
  size_t endpos = str.find_last_not_of("\t");
  if( string::npos != endpos )
  {
      str = str.substr( 0, endpos+1 );
  }
  return str;
}
string trimBeginning(string str){
  size_t startpos = str.find_first_not_of(" \t");
  if( string::npos != startpos )
  {
      str = str.substr( startpos );
  }
  return str;
}
void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   cout << "Hello World! Thread ID, " << tid << endl;
   pthread_exit(NULL);
}

// string execute(string cmd) {
//   string data;
//   FILE * stream;
//   const int max_buffer = 256;
//   char buffer[max_buffer];
//   cmd.append(" 2>&1");
//
//   stream = popen(cmd.c_str(), "r");
//   if (stream) {
//     while (!feof(stream))
//       if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
//       pclose(stream);
//     }
//   return data;
// }
