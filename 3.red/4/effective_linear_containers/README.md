# Спортсмены

У каждого спортсмена на футболке написан уникальный номер. Спортсмены по очереди выходят из раздевалки и должны построиться на стадионе. Тренер каждому выходящему спортсмену называет номер того спортсмена, перед которым нужно встать. Если спортсмена с названным номером на поле нет, то нужно встать в конец шеренги.

В стандартном вводе сначала задано натуральное число n, не превосходящее 100000, — количество спортсменов. Далее идут n пар неотрицательных целых чисел, не превосходящих 100000. Первое число в паре — номер очередного выходящего спортсмена. Второе число в паре — номер того спортсмена, перед которым должен встать текущий.

Напечатайте в стандартный вывод номера спортсменов в порядке построения на поле.

Ограничение по времени — 0,8 с.

## Решение
    athlets.cpp

# Stack Vector

Условие 

В блоке про модель памяти мы говорили, что динамическая память нужна для хранения тех объектов, которые должны жить дольше, чем создавшая их функция. Кроме того мы говорили, что можно создать такой вектор, который не использует память из кучи, а хранит все свои объекты на стеке. В этой задаче вам предстоит это сделать. Вы совсем недавно познакомились с контейнером array, который хранит все свои данные на стеке. Реализуйте интерфейс вектора поверх него. Более формально, реализуйте шаблон класса template <typename T, size_t N> StackVector<T, N>, где T — тип элемента вектора, а N — его максимальная вместимость. Класс StackVector должен иметь следующий интерфейс:  

```c++
template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0);

  T& operator[](size_t index);
  const T& operator[](size_t index) const;

  ??? begin();
  ??? end();
  ??? begin() const;
  ??? end() const;

  size_t Size() const;
  size_t Capacity() const;

  void PushBack(const T& value);
  T PopBack();
};
```

* Метод Capacity должен возвращать вместимость вектора, то есть количество объектов, которое в него в принципе может поместиться.
* Метод Size должен возвращать текущее количество объектов в векторе
* Конструктор принимает размер вектора (по аналогии со стандартным вектором). Если аргумент конструктора оказался больше вместимости вектора, конструктор должен выбрасывать исключение invalid_argument
* Методы begin/end должны возвращать итераторы на начало и текущий конец вектора; их тип не указан, вы должны выбрать его самостоятельно
* Метод PushBack добавляет новый элемент в конец вектора. Если текущий размер вектора равен его вместимости, метод PushBack должен выбрасывать стандартное исключение overflow_error
* Метод PopBack уменьшает размер вектора на один и возвращает элемент вектора, который был последним. Если вектор пуст, метод PopBack должен выбрасывать стандартное исключение underflow_error

Интерфейс класса StackVector описан в файле stack_vector.h, приложенном к этой задаче. Часть требований к нему сформулирована в виде юнит-тестов в файле stack_vector.cpp.

Обратите внимание, как отличается поведение метода PushBack в классе StackVector от метода PushBack в классе SimpleVector, который вы реализовывали ранее в блоке про модель памяти. SimpleVector::PushBack выделял дополнительную память в куче, если размер вектора оказывался равен ёмкости. В случае с классом StackVector мы должны на этапе компиляции задать максимальную ёмкость вектора и, если она оказывается исчерпана, нам больше неоткуда взять память, и мы просто бросаем исключение. В этом состоит недостаток реализации вектора на стеке по сравнению с обычным вектором.

С другой стороны, файл stack_vector.cpp содержит бенчмарк, который демонстрирует преимущество StackVector перед обычным вектором. Этот бенчмарк моделирует ситуацию, когда мы считываем из потока количество объектов N, а затем добавляем в вектор N объектов с помощью метода push_back (тестовые данные разложены в vector<vector<int>>, чтобы исключить из бенчмарка время, необходимое на парсинг). Когда вы реализуете шаблон StackVector, сравните его производительность с вектором.

На проверку пришлите заголовочный файл с реализацией шаблона StackVector.

## Решение
    stack_vector.h

# Translator

Разработайте класс Translator, позволяющий сохранять двуязычные пары слов и затем переводить слова с одного языка на другой с использованием уже добавленных пар:
```c++
class Translator {
public:
  void Add(string_view source, string_view target);
  string_view TranslateForward(string_view source) const;
  string_view TranslateBackward(string_view target) const;

private:
  // ...
};
```

Более конкретно, объект t типа Translator должен допускать следующие действия:

* Создание с помощью конструктора по умолчанию. В этом случае база переводов пуста.
* Добавление двуязычной пары: t.Add(source, target). После такого вызова считается, что слово source на языке 1 соответствует слову target на языке 2. Переданные в метод Add строки могут быть уничтожены раньше объекта t.
* Перевод с языка 1 на язык 2: t.TranslateForward(source). Если ранее уже был вызов t.Add(source_copy, target)для некоторой строки target и строки source_copy, равной source (или являющейся ей), нужно вернуть target. Если такого вызова не было, нужно вернуть пустую строку. Если таких вызовов было несколько, нужно вернуть target для последнего из них.
* Перевод с языка 2 на язык 1: t.TranslateBackward(target). Если ранее уже был вызов t.Add(source, target_copy)для некоторой строки source и строки target_copy, равной target (или являющейся ей), нужно вернуть source. Если такого вызова не было, нужно вернуть пустую строку. Если таких вызовов было несколько, нужно вернуть source для последнего из них.

## Ограничения
Каждая строка должна храниться в экземпляре класса Translator не более одного раза. При нарушении этого ограничения вы получите ошибку «Memory limit exceeded».

## Решение
    translator.h

# AirportCounter

## Условие
Вам необходимо разработать простейшую систему сбора статистики вылетов для небольших авиакомпаний. Высокоуровневые требования выглядят следующим образом:
* Система сбора статистики должна представлять собой класс AirportCounter, умеющий в произвольный момент времени для заданного аэропорта вернуть текущее количество вылетов из него.
* Набор возможных аэропортов фиксирован в виде enum и потому не может изменяться в рамках одного сеанса работы системы статистики, то есть в рамках одного экземпляра AirportCounter. Таким образом, класс AirportCounter необходимо шаблонизировать типом этого enum: если назвать такой enum TAirport, получим шаблонный класс AirportCounter<TAirport>.
* Гарантируется (по крайней мере, обещано заказчиком), что по enum аэропортов можно будет легко определить количество элементов в нём, а также перебрать сами элементы. А именно, любой используемый enum будет иметь вид enum class SomeCityAirport { Airport1, Airport2, ..., AirportN, Last_ };, то есть будет содержать некоторое количество элементов-аэропортов и элемент Last_ в качестве последнего. Поскольку в этом enum не будут заданы числовые значения для элементов, можно полагаться на то, что они будут пронумерованы подряд от 0 до N-1, а выражение static_cast<uint32_t>(SomeCityAirport::Last_) будет содержать количество аэропортов (N).
* Класс должен уметь конструироваться по списку аэропортов вылета, а также позволять обновлять этот список: добавить вылет из какого-то аэропорта, удалить один вылет (например, ошибочно добавленный) или удалить из истории все вылеты из некоторого аэропорта.

## Тестирование
Прежде чем перейти к более детальному описанию интерфейса класса, опишем процесс тестирования задачи.

Вам будут даны все тесты, на которых будет проверяться шаблонный класс AirportCounter. Ваша задача — добиться не только корректной работы на этих тестах, но и уложиться на них в 2 секунды. (Считайте, что заказчик предоставил вам подробнейшие сценарии использования вашего класса, которые затем были преобразованы в конкретные бенчмарки.)

Таким образом, вы должны выбрать способ реализации класса, ориентируясь лишь на конкретные бенчмарки.

Отметим, что данные бенчмарки составлены на основе реального примера из высоконагруженного сервиса, замедление которого даже на десятки процентов недопустимо. Именно поэтому в этой задаче важно не только спроектировать решение с приемлемой асимптотической сложностью, но и «разогнать» его на конкретных примерах.

## Нитерфейс класса
```c++
template <typename TAirport>
class AirportCounter {
public:
  // конструктор по умолчанию: список элементов пока пуст
  AirportCounter();

  // конструктор от диапазона элементов типа TAirport
  template <typename TIterator>
  AirportCounter(TIterator begin, TIterator end);

  // получить количество элементов, равных данному
  size_t Get(TAirport airport) const;

  // добавить данный элемент
  void Insert(TAirport airport);

  // удалить одно вхождение данного элемента
  void EraseOne(TAirport airport);

  // удалить все вхождения данного элемента
  void EraseAll(TAirport airport);

  using Item = pair<TAirport, size_t>;

  // получить некоторый объект, по которому можно проитерироваться,
  // получив набор объектов типа Item - пар (аэропорт, количество),
  // упорядоченных по аэропорту
  ??? GetItems() const;

private:
  // ???
};
```
## Решение
    airport_counter.cpp

# Текстовый редактор
Рассмотрим упрощённый текстовый редактор, поддерживающий следующий набор команд:
* Перемещение курсора влево (Left) и вправо (Right) на одну позицию.
* Ввод символа в текущую позицию курсора (Insert).
* Копирование фрагмента текста, начинающегося в текущей позиции курсора, в буфер обмена (Copy).
* Вырезание фрагмента текста аналогично копированию с последующим удалением скопированных символов из текста (Cut).
* Вставка содержимого буфера обмена в текущую позицию курсора (Paste).

Эти команды действительно поддерживаются практически любым текстовым редактором. Также для команд действуют стандартные правила, определяющие их эффект:
* Если редактор содержит текст длиной n символов, то курсор может находиться в одной из (n + 1) возможных позиций. Например, обозначим курсор вертикальной чертой | (это обозначение мы будем использовать в дальнейшем), тогда в тексте abc курсор может располагаться в 4 позициях: |abc, a|bc, ab|c, abc|. Поэтому команда Left не имеет эффекта, когда курсор расположен в начале текста, а Right не имеет эффекта, когда курсор находится в конце. В частности, ни Left, ни Right не имеют эффекта, когда редактор не содержит текста.
* Введённый символ располагается в позиции курсора, сдвигая курсор и весь текст справа от него на одну позицию вправо. Аналогично, при вставке фрагмента длиной n курсор и текст справа от него смещаются на n позиций вправо.
* Буфер обмена изначально пуст. Вставка пустого фрагмента не имеет эффекта. Содержимое буфера не сбрасывается после вставки, а остается неизменным до следующей команды Copy или Cut. Копирование или вырезание фрагмента нулевой длины не оказывает влияния на текст, но опустошает буфер обмена. Курсор не смещается ни при копировании, ни при вырезании текста. Например, после вырезания из текста ab|cdef фрагмента из трёх символов, получим текст ab|f.

Вам предстоит реализовать «ядро» текстового редактора, поддерживающего все описанные операции, в виде класса Editor, имеющего следующий интерфейс:
```c++
class Editor {
public:
  Editor();
  void Left();   // сдвинуть курсор влево
  void Right();  // сдвинуть курсор вправо
  void Insert(char token);   // вставить символ token
  void Copy(size_t tokens);  // cкопировать
                             // не более tokens символов,
                             // начиная с текущей позиции курсора
  void Cut(size_t tokens);  // вырезать не более tokens символов,
                            // начиная с текущей позиции курсора
  void Paste();  // вставить содержимое буфера
                 // в текущую позицию курсора
  string GetText() const;  // получить текущее содержимое
                           // текстового редактора
};
```

Как можно заметить, каждой описанной команде сопоставлен метод класса Editor. Также введён метод GetText(), позволяющий получить текущее содержимое редактора в виде строки. В комментариях к методам Cut(size_t tokens) и Copy(size_t tokens) указано, что в буфер обмена попадает фрагмент длиной не более tokens символов — это означает, что, если справа от курсора располагается менее, чем tokens символов, методы Cut() и Copy() должны вырезать/скопировать все символы справа.  

## Ограничения
Реализация класса Editor должна обрабатывать 10^6 запросов не более чем за 1 секунду. При этом гарантируется, что:
* длина текста никогда не превышает 10^6 символов;
* методы Copy() и Cut() суммарно копируют/вырезают не более 10^6 символов;
* метод GetText() вызывается один раз в каждом из тестов.

## Решение
    text_editor.cpp

# Статистика Web-сервера
## Условие
Представим, что у нас есть web-сервер, который обслуживает запросы к интернет-магазину. Он поддерживает следующий набор запросов по протоколу HTTP:
* GET / HTTP/1.1 — получить главную страницу магазина
* POST /order HTTP/1.1 — разместить новый заказ
* POST /product HTTP/1.1 — добавить новый товар в магазин (команда админки)
* GET /order HTTP/1.1 — получить детали заказа
* PUT /product HTTP/1.1 — то же самое, что и POST /order HTTP/1.1
* GET /basket HTTP/1.1 — получить состав текущей корзины клиента
* DELETE /product HTTP/1.1 — удалить товар из интернет-магазина (команда админки)
* GET /help HTTP/1.1 — получить страницу о том, как пользоваться интернет-магазином

С точки зрения протокола HTTP, первые части приведённых выше запросов («GET», «POST», «PUT», «DELETE») называются методами. Вторые части называются URI (Uniform Resource Identifier). Третья часть — это версия протокола. Таким образом, наш web-сервер поддерживает 4 метода: GET, POST, PUT, DELETE и 5 URI: «/», «/order», «/product», «/basket», «/help».

Главный системный администратор нашего сервера озаботился его масштабированием и для начала он решил изучить статистику использования. Он хочет для каждого метода и каждого URI посчитать, сколько раз он встречался в запросах к серверу за последний месяц. Он попросил вас помочь с этим.

У вас уже есть какая-то кодовая база для изучения запросов к серверу, и вы хотите воспользоваться ею, чтобы сэкономить время. У вас есть заголовочный файл http_request.h, содержащий структуру HttpRequest:
```c++
#pragma once

#include <string_view>

using namespace std;

struct HttpRequest {
  string_view method, uri, protocol;
};
```
Кроме того, есть заголовочный файл stats.h, содержащий объявления класса Stats и функции ParseRequest:
```c++
#pragma once

#include "http_request.h"

#include <string_view>
#include <map>

using namespace std;

class Stats {
public:
  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
};

HttpRequest ParseRequest(string_view line);
```
Наконец, у вас есть готовая функция ServeRequests:
```c++
Stats ServeRequests(istream& input) {
  Stats result;
  for (string line; getline(input, line); ) {
    const HttpRequest req = ParseRequest(line);
    result.AddUri(req.uri);
    result.AddMethod(req.method);
  }
  return result;
}
```
Вам нужно, основываясь на реализации функции ServeRequests, реализовать класс Stats и функцию ParseRequest.

Дополнительные требования к классу Stats:
* метод GetMethodStats возвращает словарь, в котором для каждого метода хранится, сколько раз он встретился в качестве аргумента метода AddMethod;
* метод GetUriStats работает аналогично для URI;
* если метод, переданный в метод AddMethod, не поддерживается нашим сервером (список поддерживаемых методов приведён выше), то нужно на единицу увеличить счётчик для метода "UNKNOWN" (подробнее см. юнит-тесты в заготовке решения);
* если URI, переданный в метод AddUri, не поддерживается нашим сервером, то нужно на единицу увеличить счётчик для URI "unknown".

Дополнительные сведения о функции ParseRequest:
* функция ParseRequest разбивает исходный запрос на три соответствующих части (метод, URI, версия протокола), возвращая результат в полях соответствующей структуры HttpRequest;
* при разборе исходного запроса, каждую часть запроса необходимо выделять и сохранять в результирующую структуру без каких-либо дополнительных изменений. Например, для запроса "UNDEFINED /something HTTP/1.1++", в поля метода, URI и протокола структуры HttpRequest необходимо записать "UNDEFINED", "/something" и "HTTP/1.1++", соответственно.

На проверку пришлите архив, состоящий из файлов stats.h и stats.cpp (а также любых других файлов, которые вы посчитаете нужным добавить в свой проект). При этом ваши файлы не должны содержать реализацию функции ServeRequests (если ваша посылка будет содержать функцию ServeRequests, вы получите ошибку компиляции).

## Решение
    stat/
