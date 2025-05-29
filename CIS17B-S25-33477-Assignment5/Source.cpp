#include <iostream>
#include <string>
#include <array>
#include <typeinfo>

// this is a generic package class
template<typename T>
class Package {
private:
    T item;
public:
    Package(T i) : item(i) {}
    void label() {
        std::cout << "Generic package containing: " << typeid(T).name() << "\n";
    }
};

//case for strings
template<>
class Package<std::string> {
private:
    std::string item;
public:
    Package(std::string i) : item(i) {}
    void label() {
        //prints the type
        std::cout << "Book package: \"" << item << "\"\n";
    }
};

//handles pointer types and for fragile stuff
template<typename T>
class Package<T*> {
private:
    T* item;
public:
    Package(T* i) : item(i) {}
    void label() {
        std::cout << "Fragile package for pointer to type: " << typeid(T).name() << "\n";
    }
};

//box that has a fixed size
template<typename T, int Size>
class Box {
private:
    std::array<T, Size> items;
    int count = 0;
public:
    bool addItem(const T& item) {
        if (count < Size) {
            items[count++] = item;
            std::cout << "Added item to box: \"" << item << "\"\n";
            return true;
        }
        //box if full
        return false;
    }

    void printItems() const {
        std::cout << "Box contents:\n";
        for (int i = 0; i < count; ++i) {
            std::cout << " - " << items[i] << "\n";
        }
    }
};

//shipping func
template<typename T>
void shipItem(const T& item) {
    std::cout << "Shipping item of type: " << typeid(T).name() << "\n";
}

//for doubles, temperature as controlled shipment
template<>
void shipItem(const double& item) {
    std::cout << "Shipping temperature-controlled item: " << item << "°C\n";
}
//cleans up the string output to resemble sample code, otherwise it looks messy
template<>
void shipItem(const std::string& item) {
    std::cout << "Shipping item of type: std::string\n";
}

int main() {
    //makes a package with int
    Package<int> p1(42);
    p1.label();

    // book package
    Package<std::string> p2("C++ Primer");
    p2.label();

    //fragile package
    double temp = 98.6;
    Package<double*> p3(&temp);
    p3.label();

    std::cout << "\n";

    //tests the box class
    Box<std::string, 3> bookBox;
    bookBox.addItem("The Pragmatic Programmer");
    bookBox.addItem("Clean Code");
    bookBox.printItems();

    std::cout << "\n";

    //ships various items
    shipItem(7); //regular item
    shipItem(std::string("Package Label")); //string item
    shipItem(22.5); //temp-sens item

    return 0;
}
