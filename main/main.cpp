#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>

void getFromFile(std::vector<std::list<int>> &adjacensyList)
{
  std::string line;
  std::ifstream file;
  file.open("edges.txt");

  if (!file.is_open())
  {
    std::cerr << "Error: couldn`t open file\n";
    return;
  }
  else
  {
    adjacensyList.resize(9);
    while (std::getline(file, line))
    {
      std::stringstream ss(line);
      int ver1, ver2, weight;
      if (ss >> ver1 >> ver2 >> weight)
      {
        if (ver1 > 0 && ver1 <= 8 && ver2 > 0 && ver2 <= 8) // Проверка что вершины лежат в пределах 1-8
          adjacensyList[ver1].push_back(ver2);              // Добавляем ver2 в список смежности для ver1
        else
          std::cerr << "Error: incorrect ver id in file:" << line << "\n";
      }
      else
        std::cerr << "Error: incorrect file format in line:" << line << "\n";
    }
  }
  file.close();
  if (file.is_open())
    std::cerr << "Error: couldn`t close file\n";
  else
    std::cout << "File was read successfully\n";
  return;
}

int main()
{
  std::vector<std::list<int>> adjacencyList;
  getFromFile(adjacencyList);

  // Здесь вы можете вывести adjacencyList для проверки
  for (int i = 1; i < adjacencyList.size(); i++)
  {
    std::cout << "Vertices near " << i << ": ";
    for (auto j = adjacencyList[i].begin(); j != adjacencyList[i].end(); ++j)
      std::cout << *j << " ";
    std::cout << "\n";
  }
  return 0;
}