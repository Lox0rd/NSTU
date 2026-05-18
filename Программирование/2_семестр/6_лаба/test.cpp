// #include <iostream>
// // struct Person{
// //     int age;
// // }
// class Person {
//     private:
//         int age;
//     public:
//         void setAge(){
//             std::cout << "age:";
//             std::cin >> this->age;
//         }
//         int getAge() {
//             return age;
//         }
// };



// int main() {
//     Person p;
//     // p.age = 20;
//     p.setAge();
//     std::cout << p.getAge() << " - age";    
// }

#include<iostream>
// #include<string>

class Passport {
    private:
        std::string series;
        std::string number;
    public:
        Passport() = default;
        Passport(std::string series, std::string number)
        : series((series.length() == 4) ? series : series), 
          number((number.length() == 6) ? number : number ) 
         {        }
        void Print() {
            std::cout << "Passport:\nSeries: " << series << std::endl;
            std::cout << "Number: " << number << std::endl;
        }
};

int main() {
    Passport p1, p2("1234", "123456");
    p1.Print();
    p2.Print();
    return 0;
}