#include "car.h" // 자동차 클래스 헤더파일 포함

int main() {

	// 스포츠카 클래스 (자식 클래스) : 자동차 클래스에 터보 기능 추가
	class SportsCar : public Car
	{
	public:
		bool bTurbo;
		// 터보 장치 ON?
		void setTurbo(bool bTur) { bTurbo = bTur; }
		void speedUp() {   // 터보가 ON이 되어 있으면 가속이 빨리됨
			if (bTurbo) speed += 20;
			else Car::speedUp();
		}
	};
	Car myCar(0, "Morning", 1);

	// 2. 현재 상태 출력
	myCar.display();
	// 3. 속도 올리기 (5씩 증가)
	myCar.speedUp();
	myCar.speedUp();

	// 4. 기어 변경 (기본값 4단으로 변경됨)
	myCar.changeGear();
	// 5. 변경된 상태 출력
	myCar.display();
		// 6. 주소 확인

	myCar.whereAmI();
	return 0;
}