#include <iostream>
#include <windows.h>
#include <bitset>
#include <cstring>
using namespace std;

struct WashingMachine {
    char brand[50];
    char color[30];
    double width;
    double length;
    double height;
    int power;
    int spinSpeed;
    int temp;
};

struct Iron {
    char brand[50];
    char model[30];
    char color[30];
    int minTemp;
    int maxTemp;
    bool steam;
    int power;
};

struct Boiler {
    char brand[50];
    char color[30];
    int power;
    double volume;
    int temp;
};

struct Animal {
    char name[30];
    char className[30];
    char nickname[30];
};

union IntBytes {
    int number;
    char bytes[sizeof(int)];
};

union IntUnsignedInt {
    int signedValue;
    unsigned int unsignedValue;
};

union IntBoolBytes {
    int number;
    bool bytes[sizeof(int) * 8];
};

void showWashingMachine(WashingMachine wm);
void showIron(Iron i);
void showBoiler(Boiler b);
void fillAnimal(Animal& a);
void showAnimal(Animal a);
void makeSound(Animal a);
void inputInt(IntBytes& ib);
void showAllBytes(IntBytes ib);
void showByte(IntBytes ib, int index);
void showByteBinary(IntBytes ib, int index);
int countZeroBytes(IntBoolBytes ib);
void showByteInfo(IntBoolBytes ib);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // 1
    WashingMachine wm{ "Samsung", "Білий", 60, 55, 85, 2000, 1200, 90 };
    showWashingMachine(wm);

    // 2
    Iron i{ "Philips", "GC3920", "Синій", 100, 220, true, 2400 };
    showIron(i);

    // 3
    Boiler b{ "Ariston", "Сріблястий", 1500, 50, 75 };
    showBoiler(b);

    // 4
    Animal a;
    fillAnimal(a);
    showAnimal(a);
    makeSound(a);

    // 5
    IntBytes ib;
    inputInt(ib);
    showAllBytes(ib);
    showByte(ib, 0);
    showByteBinary(ib, 0);

    // 6
    IntUnsignedInt iu;
    iu.signedValue = -12345;
    cout << "Значення як signed: " << iu.signedValue << endl;
    cout << "Значення як unsigned: " << iu.unsignedValue << endl;

    // 7
    IntBoolBytes ibool;
    ibool.number = 0x00FF00FF;
    cout << "Кількість нульових байтів: " << countZeroBytes(ibool) << endl;
    showByteInfo(ibool);
}

void showWashingMachine(WashingMachine wm)
{
    cout << "\nПральна машинка:\n";
    cout << "Фірма: " << wm.brand << "\nКолір: " << wm.color
        << "\nРозміри (ШxДxВ): " << wm.width << "x" << wm.length << "x" << wm.height
        << "\nПотужність: " << wm.power << " Вт"
        << "\nШвидкість віджиму: " << wm.spinSpeed << " об/хв"
        << "\nТемпература нагріву: " << wm.temp << "°C" << endl;
}

void showIron(Iron i)
{
    cout << "\nПраска:\n";
    cout << "Фірма: " << i.brand << "\nМодель: " << i.model
        << "\nКолір: " << i.color
        << "\nТемпература: " << i.minTemp << "-" << i.maxTemp << "°C"
        << "\nПодача пари: " << (i.steam ? "так" : "ні")
        << "\nПотужність: " << i.power << " Вт" << endl;
}

void showBoiler(Boiler b)
{
    cout << "\nБойлер:\n";
    cout << "Фірма: " << b.brand
        << "\nКолір: " << b.color
        << "\nПотужність: " << b.power << " Вт"
        << "\nОбсяг: " << b.volume << " л"
        << "\nТемпература нагріву: " << b.temp << "°C" << endl;
}

void fillAnimal(Animal& a)
{
    cout << "\nВведіть назву тварини: ";
    cin >> a.name;
    cout << "Введіть клас тварини: ";
    cin >> a.className;
    cout << "Введіть кличку: ";
    cin >> a.nickname;
}

void showAnimal(Animal a)
{
    cout << "\nТварина:\nНазва: " << a.name
        << "\nКлас: " << a.className
        << "\nКличка: " << a.nickname << endl;
}

void makeSound(Animal a)
{
    cout << a.nickname << " подає голос: ";
    if (strcmp(a.name, "Кіт") == 0)
        cout << "Мяу!\n";
    else if (strcmp(a.name, "Собака") == 0)
        cout << "Гав!\n";
    else
        cout << "Невідомий звук!\n";
}

void inputInt(IntBytes& ib)
{
    cout << "Введіть ціле число: ";
    cin >> ib.number;
}

void showAllBytes(IntBytes ib)
{
    cout << "Байти числа (hex): ";
    for (int i = 0; i < sizeof(int); i++)
        cout << hex << (0xFF & (int)ib.bytes[i]) << " ";
    cout << dec << endl;
}

void showByte(IntBytes ib, int index)
{
    if (index >= 0 && index < sizeof(int))
        cout << "Байт[" << index << "]: " << hex << (0xFF & (int)ib.bytes[index]) << dec << endl;
    else
        cout << "Неправильний індекс байта!" << endl;
}

void showByteBinary(IntBytes ib, int index)
{
    if (index >= 0 && index < sizeof(int))
        cout << "Бітовий вигляд байта[" << index << "]: " << bitset<8>(ib.bytes[index]) << endl;
    else
        cout << "Неправильний індекс байта!" << endl;
}

int countZeroBytes(IntBoolBytes ib)
{
    int count = 0;
    for (int i = 0; i < sizeof(int); i++)
        if (((ib.number >> (i * 8)) & 0xFF) == 0)
            count++;
    return count;
}

void showByteInfo(IntBoolBytes ib)
{
    cout << "Інформація про байти числа:\n";
    for (int i = 0; i < sizeof(int); i++)
    {
        int val = (ib.number >> (i * 8)) & 0xFF;
        cout << "Байт[" << i << "]: " << (val == 0 ? "нульовий" : "не нульовий") << endl;
    }
}
