#include <iostream>
#include <string>
#include <memory>

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
  virtual std::unique_ptr<Animal> create_animal() = 0;
  virtual ~AnimalFactory() {}
};

class CatFactory : public AnimalFactory {
public:
  std::unique_ptr<Animal> create_animal() override {
    return std::make_unique<Cat>();
  }
};

class DogFactory : public AnimalFactory {
public:
  std::unique_ptr<Animal> create_animal() override {
    return std::make_unique<Dog>();
  }
};

int main() { 
  std::unique_ptr<AnimalFactory> dog_factory = std::make_unique<DogFactory>();
  std::unique_ptr<AnimalFactory> cat_factory = std::make_unique<CatFactory>();
  std::unique_ptr<Animal> cat = cat_factory->create_animal();
  std::unique_ptr<Animal> dog = dog_factory->create_animal();
  cat->make_sound();
  dog->make_sound();
  return 0;
}