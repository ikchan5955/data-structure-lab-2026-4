#include "Complex.h"

void main() {
	Complex a, b, c;
	a.read("A =");
	b.read("B =");
	c.set(1.0, 2.4);
	c.add(a, b);
	a.print("A = ");
	b.print("B = ");
	c.print("A + B = ");
}