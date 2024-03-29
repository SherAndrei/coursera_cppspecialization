# Пул объектов
На практике часто возникают объекты, создание которых занимает значительное время, например, потоки (threads), TCP-соединения или подключения к базе данных. Поэтому, когда такой объект становится не нужен, его не разрушают, а откладывают в сторону, чтобы потом переиспользовать. В этой задаче вам предстоит реализовать такую схему — вам надо написать шаблон класса ObjectPool: 

```c++
template <class T>
class ObjectPool {
public:
  T* Allocate();
  T* TryAllocate();

  void Deallocate(T* object);

  ~ObjectPool();

private:
  ...
};
```

Объект класса ObjectPool должен поддерживать два набора объектов: выделенные и освобождённые, — изначально оба набора пусты.
* Метод Allocate должен работать так:
    1. если есть хотя бы один освобождённый объект, то его надо перенести в множество выделенных и вернуть указатель на него в качестве результата функции
    2. если же освобождённых объектов нет, то создаётся новый объект, помещается в множество выделенных, и указатель на него возвращается в качестве результата функции
* Метод TryAllocate работает аналогично, однако если освобождённых объектов нет, он должен просто возвращать nullptr.
* Метод Deallocate переносит объект из множества выделенных в множество освобождённых; если переданный объект не содержится в множестве выделенных, метод Deallocate должен бросать исключение invalid_argument.
* Методы Allocate и TryAllocate должны возвращать объекты в порядке FIFO, т.е. множество освобождённых объектов должно представлять собой очередь: методы [Try]Allocate должны извлекать объекты из её начала, а метод Deallocate должен помещать освобождаемый объект в её конец.
* Деструктор объекта ObjectPool должен уничтожать все объекты пула, как выделенные, так и освобождённые.

## Решение
    object_pool.cpp

# Swap, SortPointers, ReversedCopy

В этой задаче вам нужно реализовать три шаблонных функции:

* template <typename T> void Swap(T* first, T* second) — обменивает местами значения, на которые указывают указатели first и second
* template <typename T> void SortPointers(vector<T*>& pointers) — сортирует указатели по значениям, на которые они указывают
* template <typename T> void ReversedCopy(T* src, size_t count, T* dst) — копирует в обратном порядке count элементов, начиная с адреса в указателе src, в область памяти, начинающуюся по адресу dst. При этом
* каждый объект из диапазона [src; src + count) должен быть скопирован не более одного раза;
* диапазоны [src; src + count) и [dst; dst + count) могут пересекаться;
* элементы в части диапазона [src; src + count), которая не пересекается с [dst; dst + count), должны остаться неизменными.

## Решение
    swap_sort_copy.cpp

# Пишем свой вектор

## Условие 
В лекциях мы уже начали реализовывать свой вектор. В этой задаче вам надо его развить: добавить методы Size, Capacity и PushBack. Пришлите на проверку заголовочный файл simple_vector.h, содержащий объявление и определение шаблона класса SimpleVector:  
```c++
template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size);
  ~SimpleVector();

  T& operator[](size_t index);

  T* begin();
  T* end();

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);

private:
  ...
};
```

Требования:
* метод Capacity должен возвращать текущую ёмкость вектора — количество элементов, которое помещается в блок памяти, выделенный вектором в данный момент
* метод Size должен возвращать количество элементов в векторе
* метод PushBack добавляет новый элемент в конец вектора; если в текущем выделенном блоке памяти не осталось свободного места (т.е. Size() == Capacity()), вектор должен выделить блок размера 2 * Capacity(), скопировать в него все элементы и удалить старый.
* первый вызов метода PushBack для вновь созданного объекта должен делать ёмкость, равной единице
* метод PushBack должен иметь амортизированную константную сложность
* методы begin и end должны возвращать итераторы текущие начало и конец вектора
* в деструкторе должен освобождаться текущий блок памяти, выделенный вектором
* также см. дополнительные требования к работе SimpleVector в юнит-тестах в приложенном шаблоне решения

## Решение
    simple_vector.h

# Односвязный список

Односвязный список — классический пример структуры данных, для реализации которой нужно пользоваться памятью в куче. В этой задаче вам нужно реализовать шаблон класса LinkedList, который представляет собой односвязный список и обладает следующим интерфейсом:

```c++
template <typename T>
class LinkedList {
public:
  struct Node {
    T value;
    Node* next = nullptr;
  };

  ~LinkedList();

  void PushFront(const T& value);
  void InsertAfter(Node* node, const T& value);
  void RemoveAfter(Node* node);
  void PopFront();

  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
};
```

* Метод GetHead возвращает указатель на голову списка, он используется для перебора элементов списка (см. шаблон ToVector в заготовке решения)
* Метод PushFront добавляет новый элемент в голову списка.
* Метод InsertAfter вставляет новый элемент в список так, чтобы он шёл после узла node. Если node == nullptr, метод эквивалентен PushFront
* Метод PopFront удаляет элемент из головы списка и освобождает выделенную под него память. Если список пуст, метод завершается корректно. Если после выполнения метода список стал пустым, метод GetHead должен возвращать nullptr
* Метод RemoveAfter должен удалять из списка элемент, который следует за узлом node, и освобождать выделенную под него память. Если node == nullptr, метод эквивалентен PopFront. Если node->next == nullptr, то метод должен корректно завершаться.
* Все методы, перечисленные выше, должны работать за O(1)
* Деструктор класса LinkedList освобождает всю память, выделенную для хранения элементов списка.
