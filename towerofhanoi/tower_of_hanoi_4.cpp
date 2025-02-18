#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

void ToH3(int i, int j, char from_rod, char to_rod, char aux_rod)
{
   if (i > j)
      return;
   ToH3(i, j - 1, from_rod, aux_rod, to_rod);
   cout << "transfer disk " << j << " from tower " << from_rod << " to rod " << to_rod << "\n";
   ToH3(i, j - 1, aux_rod, to_rod, from_rod);
}

void ToH4small(int i, int j, char A, char B, char C, char D)
{
   if (j < i)
      return;

   if (j == i)
   {
      cout << "transfer disk " << i << " from tower " << A << " to rod " << B << "\n";
      return;
   }

   if (j == i + 1)
   {
      cout << "transfer disk " << i << " from tower " << A << " to rod " << C << "\n";
      cout << "transfer disk " << i + 1 << " from tower " << A << " to rod " << B << "\n";
      cout << "transfer disk " << i << " from tower " << C << " to rod " << B << "\n";
      return;
   }

   if (j == i + 2)
   {
      cout << "transfer disk " << i << " from tower " << A << " to rod " << D << "\n";
      cout << "transfer disk " << i + 1 << " from tower " << A << " to rod " << C << "\n";
      cout << "transfer disk " << i + 2 << " from tower " << A << " to rod " << B << "\n";
      cout << "transfer disk " << i + 1 << " from tower " << C << " to rod " << B << "\n";
      cout << "transfer disk " << i << " from tower " << D << " to rod " << B << "\n";
      return;
   }
}
void ToH43(int i, int j, char A, char B, char C, char D)
{
   int n, k;

   n = j - i + 1;
   if (n <= 3)
   {
      ToH4small(i, j, 'A', 'B', 'C', 'D');
      return;
   }

   k = (int)round(sqrt(2 * n));

   ToH43(i, j - k, 'A', 'D', 'B', 'C');
   ToH3(j - k + 1, j, 'A', 'B', 'C');
   ToH43(i, j - k, 'D', 'B', 'A', 'C');
}

int main()
{
   int n;
   cin >> n;
   ToH43(1, n, 'A', 'B', 'C', 'D');
   return 0;
}