#include <string>
#include <algorithm>  // std::min

#include "test_runner.h"

class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor() = default;
  void Left()  { shift(left, right); }
  void Right() { shift(right, left); }
  void Insert(char token) {
    left.push_back(token);
  }
  void Cut(size_t tokens = 1) {
    for (size_t i = 0; i < tokens; ++i)
      shift(right, buffer);
  }
  void Copy(size_t tokens = 1) {
      for (size_t i = 0; i < std::min(tokens, right.size()); ++i)
        buffer.push_back(right[right.size() - i - 1]);
  }
  void Paste() {
    for (const char el : buffer)
        left.push_back(el);
  }
  std::string GetText() const {
    return left + std::string(right.rbegin(), right.rend());
  }

 private:
  void shift(std::string& source, std::string& dest) {
    if (!source.empty()) {
      char temp = source.back();
      source.pop_back();
      dest.push_back(temp);
    }
  }

 private:
  // left  right
  // ----> <------
  // abcde|qwerty
  std::string left;
  std::string right;
  std::string buffer;
};


void TypeText(Editor& editor, const std::string& text) {
  for (char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for (size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for (size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const std::string text = "esreveR";
  for (char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}

/*
#include <list>
#include <std::string>

using namespace std;

class Editor {
 public:
  Editor() : pos(text.end()) {}

  void Left() { pos = Advance(pos, -1); }
  void Right() { pos = Advance(pos, 1); }

  void Insert(char token) { text.insert(pos, token); }

  void Cut(size_t tokens = 1) {
    auto pos2 = Advance(pos, tokens);
    buffer.assign(pos, pos2);
    pos = text.erase(pos, pos2);
  }

  void Copy(size_t tokens = 1) {
    auto pos2 = Advance(pos, tokens);
    buffer.assign(pos, pos2);
  }

  void Paste() {
    text.insert(pos, buffer.begin(), buffer.end());
  }

  std::string GetText() const {
    return {text.begin(), text.end()};

  }

 private:
  using Iterator = list<char>::iterator;
  list<char> text;
  list<char> buffer;
  Iterator pos;

  Iterator Advance(Iterator it, int steps) const {
    while (steps > 0 && it != text.end()) {
      ++it;
      --steps;
    }
    while (steps < 0 && it != text.begin()) {
      --it;
      ++steps;
    }
    return it;
  }
};
*/
