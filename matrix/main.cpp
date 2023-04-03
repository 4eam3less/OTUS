#include <iostream>

template<std::size_t Dimensional, typename Type>
class Matrix{
public:
    explicit Matrix(Type default_value) : default_value_(default_value) {}
    Matrix() = default;
    Matrix(Matrix &) = default;
    Matrix(Matrix &&) = default;
    ~Matrix() = default;

private:

    Type default_value_ = 0;
    size_t size_ = 0;
};


int main(){

    std::cout << "test";
    return 0;
}