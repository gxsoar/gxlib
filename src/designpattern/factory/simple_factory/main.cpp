#include <iostream>
#include <string>

class Animal {
public:
  virtual void make_sound() = 0;
  virtual ~Animal() {}
};

class Dog : public Animal {
public:
  void make_sound() override {
    std::cout << "Woof!\n";
  }
};

class Cat : public Animal {
public:
  void make_sound() override {
    std::cout << "Meow!\n";
  }
};

class AnimalFactory {
public:
  virtual Animal* create_animal(const std::string &type) = 0;
  virtual ~AnimalFactory() {}
};

class SimpleAnimalFactory : public AnimalFactory {
public:
  Animal* create_animal(const std::string &type) {
    if (type == "dog") {
      return new Dog();
    } else if (type == "cat") {
      return new Cat();
    } else return nullptr;
  }
};

int main() { 
  AnimalFactory *factory = new SimpleAnimalFactory();
  auto dog = factory->create_animal("dog");
  dog->make_sound();
  auto cat = factory->create_animal("cat");
  cat->make_sound();
  delete dog;
  delete cat;
  delete factory;
  return 0;
}