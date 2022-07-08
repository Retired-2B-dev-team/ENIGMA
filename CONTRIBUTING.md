# Wskazówki dla twórców:
W celu zapewnienia czytelności kodu oraz utrzymania porządku w repozytorium, wrzucając kod dbajmy by przestrzegał poniższych wskazówek.

### Ujednolicona konwencja formatowania kodu:
1. Używamy pojedynczej tabulacji jako wcięć.
2. Zostawiamy puste linijki, w celu oddzielenia logicznie spójnych fragmentów kodu, lub w celu poprawy czytelności.
3. Wstawiamy pojedynczą spację w następujących wyrażeniach:
  - `#include <iostream>`
  - `x = 4` / `x < 7` / `x == 0`
  - `x += 1`
  - `std::cout << "Hello, World!";`
  - `{ 0, 1, 4, 2 }`
  - `if ()`
  - `else if ()`
4. Klamry wstawiamy od nowego wiersza np.
  ```c++
  if (x == True)
  {
      std::cout << "Hello, World!";
  }
  ```
5. Znak wskaźnika `*` podczas deklaracji wskaźnika piszemy przy typie zmiennej np. `int* a;`
6. Słowa kluczowe `private` i `public` piszemy jedno wcięcie mniej niż kod danej klasy/struktury np.
  ```c++
  class Foo
  {
  
  private:
      int bar = 0;
      
  public:
      void baz()
      {
          std::cout << "Hello, World!";
      }
  };
  ```
### Zasady tworzenia nazw zmiennych, funkcji, klas itp.:
1. **Nazwy nadajemy tak aby jak najlepiej odzwierciedlały funkcję i cel danego elementu.**
2. `Zmienne`, `funkcje`, `metody` i `atrybuty` nazywamy **małymi literami**.
3. Słowa w nazwach oddzielamy pojedynczym znakiem `_` np. `int moja_zmienna`.
4. `Stałe` nazywamy **WIELKIMI LITERAMI**.
5. `Klasy`/`struktury` nazywamy poczynając od **Wielkiej Litery**, przy czym utworzone `obiekty`/`zmienne` danje klasy/struktury nazywamy **małymi literami**.
6. Nazwy zmiennych, które są `argumentami` metod klas/struktur zaczynamy od podwójnego znaku podłogi `__`, w celu odróżnienia od atrybutów danej klasy/struktury np.
  ```c++
  struct Foo
  {
  private:
    int bar = 0;
  public:
    init(int __bar)
    {
      bar = __bar;
    }
  };
  ```
### Inne konwencje:
Jeśli uważasz, że coś powinno się tu jeszcze znaleźć, to nie omieszkaj tego dopisać.
### Przykładowy fragment kodu:
```c++
#include <iostream>


struct Pair
{

private:
  int x = 0;
  int y = 0;
  
public:
  Pair(__x, __y)
  {
    x = __x;
    y = __y;
  }
  int get_x()
  {
    return x;
  }
  int get_y()
  {
    return y;
  }
};

void hello_world()
{
  std::cout << "Hello, World!";
}

void add_1(int* pointer)
{
  *pointer += 1;
}



int main()
{
  int foo = 0;
  int x = 3;
  int y = 5;
  
  Pair coordinates = Pair(x, y);
  
  
  if (coordinates.get_x() == 3)
  {
    hello_world();
  }
  else if (coordinates.get_y() < 10)
  {
    add_1(&foo);
  }
  
  return 0;
}
```
