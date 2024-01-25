#include <iostream>
#include <memory>

// Базовий клас Component, який визначає інтерфейс для конкретних компонентів
class Component {
public:
    virtual void operation() const = 0;
    virtual ~Component() = default;
};

// Конкретний компонент
class ConcreteComponent : public Component {
public:
    void operation() const override {
        std::cout << "Concrete Component operation\n";
    }
};

// Абстрактний клас Decorator, який також реалізує інтерфейс Component
class Decorator : public Component {
public:
    Decorator(std::unique_ptr<Component> component) : component_(std::move(component)) {}

    void operation() const override {
        if (component_) {
            component_->operation();
        }
    }

private:
    std::unique_ptr<Component> component_;
};

// Конкретний декоратор A
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(std::unique_ptr<Component> component) : Decorator(std::move(component)) {}

    void operation() const override {
        Decorator::operation();
        addAdditionalOperation();
    }

private:
    void addAdditionalOperation() const {
        std::cout << "Concrete Decorator A additional operation\n";
    }
};

// Конкретний декоратор B
class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(std::unique_ptr<Component> component) : Decorator(std::move(component)) {}

    void operation() const override {
        Decorator::operation();
        addExtraFunctionality();
    }

private:
    void addExtraFunctionality() const {
        std::cout << "Concrete Decorator B extra functionality\n";
    }
};

int main() {
    // Використання паттерна "Декоратор"
    std::unique_ptr<Component> component = std::make_unique<ConcreteComponent>();
    component->operation();

    std::unique_ptr<Component> decoratedComponentA = std::make_unique<ConcreteDecoratorA>(std::move(component));
    decoratedComponentA->operation();

    std::unique_ptr<Component> decoratedComponentB = std::make_unique<ConcreteDecoratorB>(std::move(decoratedComponentA));
    decoratedComponentB->operation();

    return 0;
}
