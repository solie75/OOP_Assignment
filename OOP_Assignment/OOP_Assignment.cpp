// OOP_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

// 동물 종류
enum class EAnimal
{
    Dog,
    Cat,
    Cow,
    End,
};

// 각 종류별 동물의 개체 수
int arrAnimalNum[(int)EAnimal::End]{0};
int IncreaseAnimalNum(EAnimal _type)
{
    arrAnimalNum[(int)_type]++;
    return arrAnimalNum[(int)_type];
}

int DecreaseAnimalNum(EAnimal _type)
{
    arrAnimalNum[(int)_type]--;
    return arrAnimalNum[(int)_type];
}


class Animal
{
public:
    virtual void makeSound() = 0; // 울음소리를 순수가상함수로 구현

    EAnimal GetType() { return type; }
    void SetType(EAnimal _type) { type = _type; }
    void SetIndex(int _i) { index = _i; }
    int GetIndex() { return index; }

    Animal()
    {};
    ~Animal() {};

private:
    EAnimal type = EAnimal::End;
    unsigned int index = 0;
};

class Dog : public Animal
{
public:
    virtual void makeSound() override
    {
        cout << "Dog " << to_string(GetIndex()) << " : Woof !" << "\n";
    }

    Dog(int _index)
        : Animal()
    {
        SetType(EAnimal::Dog);
        SetIndex(_index);
    }
};

class Cat : public Animal
{
public:
    virtual void makeSound() override
    {
        cout << "Cat " << to_string(GetIndex()) << " : Meow !" << "\n";
    }

    Cat(int _index)
        : Animal()
    {
        SetType(EAnimal::Cat);
        SetIndex(_index);
    }
};

class Cow : public Animal
{
public:
    virtual void makeSound() override
    {
        cout << "Cow " << to_string(GetIndex()) << " : Moo !" << "\n";
    }

    Cow(int _index)
        : Animal()
    {
        SetType(EAnimal::Cow);
        SetIndex(_index);
    }
};

class Zoo
{
private:
    // 동물 배열
    vector<Animal*> vecAnimals;

public:
    // 동물원에 동물 추가.
    void AddAnimal(Animal* _animal)
    {
        vecAnimals.push_back(_animal);
    }

    // 현재 동물원의 모든 동물들의 울음소리 출력.
    void performActions()
    {
        for (Animal* animal : vecAnimals)
        {
            animal->makeSound();
        }
    }

    ~Zoo()
    {
        // 동물원 소멸시 추가된 모든 동물을 해제
        for (Animal* animal : vecAnimals)
        {
            delete animal;
            animal = nullptr;
        }
    }
};

Animal* CreateRandomAnimal()
{
    Animal* animal = nullptr;

    // 정해진 동물 종류 수에서 무작위로 한 종류를 선별
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, (int)EAnimal::End);
    int randomNum = dis(gen);

    switch (randomNum)
    {
    case 1:
        animal = new Dog(IncreaseAnimalNum(EAnimal::Dog));
        break;
    case 2:
        animal = new Cat(IncreaseAnimalNum(EAnimal::Cat));
        break;
    case 3:
        animal = new Cow(IncreaseAnimalNum(EAnimal::Cow));
        break;
    }

    return animal;
}

int main()
{
    Zoo zoo;

    cout << "Enter tha total numver of animals in your zoo." << "\n";
    cout << "Animals Will be Randomly generated within that number" << "\n";

    int AnimalNum = 0;
    cin >> AnimalNum;

    while (AnimalNum--)
    {
        zoo.AddAnimal(CreateRandomAnimal());
    }

    cout << "All the animals in the zoo are making sounds" << "\n";

    zoo.performActions();
}