#pragma once
#include <stdio.h>
#include <cstring>

class Car {
protected:
    int speed=0;
    // 속도 (private)
    char name[40] = { 0, };
public:
    int gear=0 ;
    Car() {}
    ~Car() {}
    Car(int s, const char* n, int g) // 매개변수가 있는 생성자
        : speed(s), gear(g) { // 멤버 초기화 리스트 (멤버변수 초기화)
            strcpy_s(name, n); // 생성자 함수 몸체 (name 멤버 초기화)
    }
    void changeGear(int g = 3) {  // 기어 단수를 변경하는 멤버 함수
        gear = g;
    }
    void speedUp() {
        // 속도를 5씩 증가 멤버 함수
        speed += 5;
    }
    void display() {
            printf("[%s] : 기어=%d단 속도=%dkmph\n", name, gear, speed);
    }
    void whereAmI() { printf("객체 주소 = %p\n", this); }
};