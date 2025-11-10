#include <iostream>

class Kruh
{
   private:

      float radius;
      const float pi = 3.14159265;
      public:

    setRadius =(float r)
    radius = r;
    void print()
    std:cout <<"rádius je " << radius << std::endl;
       float spocitejObvod() {
   return 2 * pi * radius
   }
   float spocitejPlochu() {
   return pi * radius * radius
}

int main()
{
  float prvniRadius = 2;
   Kruh prvniKruh;
   prvniKruh.setRadius( prvniRadius );

   float druhyRadius = 4;
   Kruh druhyKruh( druhyRadius );

   }
   std::cout << "Plocha kruhu:" << prvniKruh.spocitejPlochu() << std::endl;
   std::cout << "Obvod kruhu:" << prvniKruh.spocitejObvod() << std::endl;

   druhyKruh.vypisUdaje();

   // BONUS: radius kruhu bude sablonovy parametr, a udela pole kruhu a pro kazdy kruh spocita vse

   return 0;
}