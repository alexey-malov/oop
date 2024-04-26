#include <array>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

class Speakable {
public:
    virtual ~Speakable() = default;
    virtual void Speak() const = 0;
};

class Drawable {
public:
    virtual ~Drawable() = default;
    virtual void Draw() const = 0;
};

class Animal {
public:
    virtual ~Animal() = default;
    void Eat(string_view food) {
        cout << GetType() << " is eating "sv << food << endl;
        ++energy_;
    }
    virtual string GetType() const = 0;

private:
    int energy_ = 100;
};

class Fish : public virtual Animal, public virtual Drawable {
public:
    string GetType() const override {
        return "fish"s;
    }
    void Draw() const override {
        cout << "><(((*>"sv << endl;
    }
};

class Cat : public virtual Animal, public Speakable, public virtual Drawable {
public:
    void Speak() const override {
        cout << "Meow-meow"sv << endl;
    }
    void Draw() const override {
        cout << "(^w^)"sv << endl;
    }
    string GetType() const override {
        return "cat"s;
    }
};

class CatFish : public Cat, public Fish {
public:
    string GetType() const override {
        return "catfish"s;
    }
    void Draw() const override {
        cout << "><(((*){"sv << endl;
    }
};

void Feed(Animal& animal) {
    animal.Eat("meat"sv);
}

void Talk(Speakable& speakable) {
    speakable.Speak();
}

template <typename DrawableIterator>
void DrawPicture(DrawableIterator begin, DrawableIterator end) {
    for (; begin != end; ++begin) {
        const Drawable* drawable = *begin;
        drawable->Draw();
    }
}

int main() {
    CatFish cat_fish;

    Feed(cat_fish);
    Talk(cat_fish);
    cat_fish.Draw();
}