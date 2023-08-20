#include <iostream>
#include <memory>
#include <string>

class Human {
 public:
  virtual void say_hello() = 0;
  virtual ~Human() {}
};

class Male : public Human {
 public:
  void say_hello() override { std::cout << "Hello, I am a male\n"; }
};

class Female : public Human {
 public:
  void say_hello() override { std::cout << "Hello, I am a female\n"; }
};

class Animal {
 public:
  virtual void make_sound() = 0;
  virtual ~Animal() {}
};

class Dog : public Animal {
 public:
  void make_sound() override { std::cout << "Woof!\n"; }
};

class Cat : public Animal {
 public:
  void make_sound() override { std::cout << "Meow!\n"; }
};

class AbstractFactory {
 public:
  virtual std::unique_ptr<Human> create_human() = 0;
  virtual std::unique_ptr<Animal> create_animal() = 0;
  virtual ~AbstractFactory(){};
};

class MaleDogFactory : public AbstractFactory {
 public:
  std::unique_ptr<Human> create_human() override {
    return std::make_unique<Male>();
  }
  std::unique_ptr<Animal> create_animal() override {
    return std::make_unique<Dog>();
  }
};

class FemaleCatFactory : public AbstractFactory {
 public:
  std::unique_ptr<Human> create_human() override {
    return std::make_unique<Female>();
  }
  std::unique_ptr<Animal> create_animal() override {
    return std::make_unique<Cat>();
  }
};

int main() {
  std::unique_ptr<AbstractFactory> male_dog_factory =
      std::make_unique<MaleDogFactory>();  // Create a unique_ptr to a concrete
                                           // factory object
  std::unique_ptr<AbstractFactory> female_cat_factory =
      std::make_unique<FemaleCatFactory>();  // Create another unique_ptr to a
                                             // concrete factory object

  std::unique_ptr<Human> male =
      male_dog_factory->create_human();  // Create a unique_ptr to a concrete
                                         // product object through the factory
  male->say_hello();                     // Call the product's method

  std::unique_ptr<Animal> dog =
      male_dog_factory
          ->create_animal();  // Create another unique_ptr to a concrete product
                              // object through the factory
  dog->make_sound();          // Call the product's method

  std::unique_ptr<Human> female =
      female_cat_factory
          ->create_human();  // Create another unique_ptr to a concrete product
                             // object through the factory
  female->say_hello();       // Call the product's method

  std::unique_ptr<Animal> cat =
      female_cat_factory
          ->create_animal();  // Create another unique_ptr to a concrete product
                              // object through the factory
  cat->make_sound();          // Call the product's method

  // No need to delete anything manually, as the unique_ptr will take care of it
  // automatically

  return 0;
}