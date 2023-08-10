#include "mbed.h"
#include <iostream>
#include <chrono>

// Objeto para establecer la comunicación serial con el Pc
UnbufferedSerial serial(USBTX, USBRX, 9600);
using namespace std;

int tiempoR;
int tiempoG;
int tiempoB;

// MCD dos numeros

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// MCD tres numeros

int gcd_three(int a, int b, int c) {
    int result = gcd(a, b);
    result = gcd(result, c);
    return result;
}

int main() {
    // Initialise the digital pin LED1 as an output
    DigitalOut ledR(LED1, 1);
    DigitalOut ledG(LED2, 1);
    DigitalOut ledB(LED3, 1);

    cout << "Ingrese el tiempo para el LED rojo (ms): ";
    cin >> tiempoR;

    cout << "Ingrese el tiempo para el LED verde: (ms)";
    cin >> tiempoG;

    cout << "Ingrese el tiempo para el LED azul: (ms)";
    cin >> tiempoB;

    // Variable contador - periodos del mcm de los LEDs
    int count = 0;
    const int MCD = gcd_three(tiempoR, tiempoG, tiempoB);

    // Periodo de cada LED
    int periodoR = tiempoR/MCD;
    int periodoG = tiempoG/MCD;
    int periodoB = tiempoB/MCD;

    while (true) {
        if(count % periodoR == 0) {
            ledR = !ledR;
            cout << "LedR = " << count*MCD << "ms" << endl;
        }
        if(count % periodoG == 0) {
            ledG = !ledG;
            cout << "LedG = " << count*MCD << "ms"  << endl;
        }
        if(count % periodoB == 0) {
            ledB = !ledB;
            cout << "LedB = " << count*MCD << "ms"  << endl;
        }
        ThisThread::sleep_for(MCD);
        count += 1;
    }
}
