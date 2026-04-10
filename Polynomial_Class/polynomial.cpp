#include "polynomial.h"
#include <iostream>
void main() {
	Polynomial a, b, c;
	a.read("A"); // 다항식 a를 읽음 (키보드로 입력)
	b.read("B"); // 다항식 b를 읽음 (키보드로 입력)
	c.add(a, b); // c = a + b
	a.display("A = "); // 다항식 a를 화면에 출력
	b.display("B = "); // 다항식 b를 화면에 출력
	c.display("A+B="); // 다항식 c=a+b를 화면에 출력
}