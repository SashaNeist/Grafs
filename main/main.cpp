#include <iostream> // Для ввода/вывода
#include <string>   // Для работы со строками
#include <vector>   // Для использования вектора (динамический массив)
#include <list>     // Для использования списка (двусвязный список)
#include <fstream>  // Для работы с файлами
#include <sstream>  // Для работы с потоками строк
#include <queue>    // Для работы с очередью (используется в BFS)

#define VERCOUNT 8 // Устанавливаем количество вершин
#define STARTVERTEX 6 // Устанавливаем начальную вершину для обхода

// Функция для загрузки графа из файла
void getFromFile(std::vector<std::list<int>> &adjacencyList)
{
  std::string line;       // Строка для чтения из файла
  std::ifstream file;     // Объект для работы с файлом
  file.open("edges.txt"); // Открываем файл "edges.txt"

  // Проверяем, удалось ли открыть файл
  if (!file.is_open())
  {
    std::cerr << "Error: couldn`t open file\n"; // Выводим сообщение об ошибке, если файл не открылся
    return;                                     // Выходим из функции
  }
  else
  {
    adjacencyList.clear();              // Очищаем список смежности, если в нем что-то было
    adjacencyList.resize(VERCOUNT + 1); // Устанавливаем размер списка смежности (предполагаем, что у нас до 8 вершин)
    while (std::getline(file, line))    // Читаем файл построчно
    {
      std::stringstream ss(line);       // Создаем поток из строки
      int ver1, ver2;                   // Объявляем переменные для хранения вершин
      int weight;                       // Объявляем переменную для хранения веса (не используем)
      if (ss >> ver1 >> ver2 >> weight) // Пытаемся считать из строки 3 числа: вершина1, вершина2, вес
      {
        if (ver1 > 0 && ver1 <= 8 && ver2 > 0 && ver2 <= 8) // Проверяем, что вершины находятся в пределах [1, 8]
          adjacencyList[ver1].push_back(ver2);              // Добавляем вершину2 в список смежности вершины1
        else
        {
          std::cerr << "Error: incorrect ver id in file:" << line << "\n"; // Выводим ошибку, если id вершины неверный
          return;                                                          // Выходим из функции
        }
      }
      else
      {
        std::cerr << "Error: incorrect file format in line:" << line << "\n"; // Выводим ошибку, если формат строки неверный
        return;                                                               // Выходим из функции
      }
    }
  }
  file.close(); // Закрываем файл
  // Проверяем, закрылся ли файл
  if (file.is_open())
    std::cerr << "Error: couldn`t close file\n";
  else
    std::cout << "File was read successfully\n"; // Сообщаем об успешном чтении файла
  return;
}

// Функция для обхода графа в ширину (BFS)
void bfs(const std::vector<std::list<int>> &adjacencyList, int startVertex)
{
  int n = adjacencyList.size();        // Получаем количество вершин
  std::queue<int> queue;               // Создаем очередь для хранения вершин
  std::vector<bool> visited(n, false); // Создаем вектор для отметки посещенных вершин, изначально все false
  visited[startVertex] = true;         // Помечаем начальную вершину как посещенную
  queue.push(startVertex);             // Добавляем начальную вершину в очередь
  std::cout << "BFS path: ";           // Выводим заголовок для BFS

  // Пока очередь не пуста
  while (!queue.empty())
  {
    int currentVertex = queue.front(); // Получаем вершину из начала очереди
    queue.pop();                       // Удаляем вершину из начала очереди
    std::cout << currentVertex << " "; // Выводим текущую вершину
    // Перебираем соседей текущей вершины
    for (int neighbor : adjacencyList[currentVertex])
    {
      // Если соседняя вершина не посещена
      if (!visited[neighbor])
      {
        visited[neighbor] = true; // Помечаем соседа как посещенного
        queue.push(neighbor);     // Добавляем соседа в очередь
      }
    }
  }
  std::cout << std::endl; // Перевод строки после вывода обхода
}

// Рекурсивная функция для обхода графа в глубину (DFS)
void dfsRecursive(const std::vector<std::list<int>> &adjacencyList, int u, std::vector<bool> &visited)
{
  visited[u] = true;     // Помечаем текущую вершину как посещенную
  std::cout << u << " "; // Выводим текущую вершину
  // Перебираем соседей текущей вершины
  for (int neighbor : adjacencyList[u])
  {
    // Если соседняя вершина не посещена
    if (!visited[neighbor])
    {
      dfsRecursive(adjacencyList, neighbor, visited); // Рекурсивный вызов для соседа
    }
  }
}

// Функция для обхода графа в глубину (DFS)
void dfs(const std::vector<std::list<int>> &adjacencyList, int startVertex)
{
  int n = adjacencyList.size();                      // Получаем количество вершин
  std::vector<bool> visited(n, false);               // Создаем вектор для отметки посещенных вершин
  std::cout << "DFS path: ";                         // Выводим заголовок для DFS
  dfsRecursive(adjacencyList, startVertex, visited); // Вызываем рекурсивную функцию
  std::cout << std::endl;                            // Перевод строки после вывода обхода
}

int main()
{
  std::vector<std::list<int>> adjacencyList; // Объявляем список смежности
                      
  getFromFile(adjacencyList);                // Загружаем граф из файла

  // Выводим список смежности для проверки
  for (int i = 1; i < adjacencyList.size(); i++)
  {
    std::cout << "Vertices near " << i << ": ";
    for (auto j = adjacencyList[i].begin(); j != adjacencyList[i].end(); ++j)
      std::cout << *j << " ";
    std::cout << "\n";
  }
  std::cout << "\n";

  bfs(adjacencyList, STARTVERTEX); // Запускаем BFS с начальной вершины
  dfs(adjacencyList, STARTVERTEX); // Запускаем DFS с начальной вершины
  return 0;                        // Выходим из программы
}