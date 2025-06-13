#include <iostream>
#include <string>
#include <array>
#include <typeinfo>

// this is a generic package class, template for any type T
template<typename T>
class Package {
private:
    T item; // stores item of type T
public:
    Package(T i) : item(i) {}
    // outputs the type of item stored
    void label() {
        std::cout << "Generic package containing: " << typeid(T).name() << "\n";
    }
};

//specialization of package for string
template<>
class Package<std::string> {
private:
    std::string item; // stores the string item
public:
    Package(std::string i) : item(i) {}
    void label() {
        // outputs label for book packages
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

//template that holds a fixed number of items
template<typename T, int Size>
class Box {
private:
    std::array<T, Size> items;
    int count = 0;  //tracks number of items added
public:
//adds an item to the box if there is space
    bool addItem(const T& item) {
        if (count < Size) {
            items[count++] = item;
            std::cout << "Added item to box: \"" << item << "\"\n";
            return true;
        }
        //box if full
        return false;
    }
    //prints all items that are in the box
    void printItems() const {
        std::cout << "Box contents:\n";
        for (int i = 0; i < count; ++i) {
            std::cout << " - " << items[i] << "\n";
        }
    }
};

//shipping function for any item type
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
    //makes a package with an integer
    Package<int> p1(42);
    p1.label();

    // creates specialzied book package(string)
    Package<std::string> p2("C++ Primer");
    p2.label();

    //fragile package for pointer or double
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

    //ships various items/demonstrates functions
    shipItem(7); //regular item
    shipItem(std::string("Package Label")); //string item
    shipItem(22.5); //temp-sens item

    return 0;
}
