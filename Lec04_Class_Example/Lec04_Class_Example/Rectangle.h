#pragma once
#include <iostream>
class Rectangle {
private:
	double width;
	double height;

public:
	Rectangle(double w, double h) {
		width = w;
		height = h;
	}
	// 면적 구하기
	double getArea() {
		return width * height;
	}
	// 둘레길이 구하기
	double getPerimeter() {
		return 2 * (width + height);
	}
	// 정사각형 판별 함수
	bool isSquare() {
		return (width == height);
	}
};