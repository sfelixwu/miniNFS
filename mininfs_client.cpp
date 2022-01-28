
// ecs251 miniNFS

#include <iostream>
#include "Shadow_Directory.h"

using namespace std;

int
main()
{
  Shadow_Directory dir_mount 
  { "http://127.0.0.1:8384", "1234567890", "Directory", "00000002" };

  Json::Value result_000;

  result_000 = dir_mount.LookUp("00000002", "my_first_file");

  result_000 = dir_mount.Create("00000001", "my_first_file", "sattr dummy");

  result_000 = dir_mount.Create("00000002", "my_first_file", "sattr dummy");

  result_000 = dir_mount.LookUp("00000002", "my_first_file");

  result_000 = dir_mount.Create("00000002", "my_first_file", "sattr dummy");

  result_000 = dir_mount.dumpJ();

  std::cout << result_000.toStyledString() << std::endl;

  return 0;
}
