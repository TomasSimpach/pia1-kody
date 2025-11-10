#include <iostream>
#include <cmath>

class Kruh
{
private:
    float radius;
    const float pi = 3.14159265f;

public:
    Kruh() {
        radius = 0;
    }
    Kruh(float r) {
        radius = r;
    }

    void setRadius(float r) {
        radius = r;
    }

    float spocitejObvod() {
        return 2 * pi * radius;
    }

    float spocitejPlochu() {
        return pi * radius * radius;
    }
};

int main()
{
    float prvniRadius = 2;
    Kruh prvniKruh;
    prvniKruh.setRadius(prvniRadius);

    float druhyRadius = 4;
    Kruh druhyKruh(druhyRadius);

    std::cout << "Plocha kruhu1: " << prvniKruh.spocitejPlochu() << std::endl;
    std::cout << "Obvod kruhu1: " << prvniKruh.spocitejObvod() << std::endl;
    std::cout << "Plocha kruhu2: " << druhyKruh.spocitejPlochu() << std::endl;
    std::cout << "Obvod kruhu2: " << druhyKruh.spocitejObvod() << std::endl;
    

// BONUS: radius kruhu bude sablonovy parametr, a udela pole kruhu a pro kazdy kruh spocita vse

    return 0;
}
