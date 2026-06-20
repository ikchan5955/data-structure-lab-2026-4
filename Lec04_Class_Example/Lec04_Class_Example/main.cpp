#include "Rectangle.h"
#include "Pet.h"
#include "Music.h"

using namespace std;
int main() {
	// Rectangle 클래스로 rect1 객체생성 
	Rectangle rect1(4, 6);
	cout << "Rectangle 1: " << endl;
	//printf("Rectangle 1: \n");
	cout << "Area: " << rect1.getArea() << endl;
	//printf("Area: %lf\n", rect1.getArea());
	cout << "Perimeter: " << rect1.getPerimeter() << endl;
	cout << "Is Square? " << boolalpha << rect1.isSquare() << endl;
	printf("===================================\n");

	Pet myPet("Lucky", 5, "dog");
	cout << "My pet's name is " << myPet.getName() << endl;
	Puppy myPuppy("Kong", 3, "dog", "Puddle");
	cout << "My puppy's breed is " << myPuppy.getBreed() << endl;
	printf("===================================\n");

	// Creat a new music streaming service
	MusicStreamingService myService("Melon");
	// Add some music to the service
	myService.addMusic("Jump", "Blackpink", "Jump", 2025);
	myService.addMusic("Swim", "BTS", "ARIRANG", 2026);
	myService.addMusic("BANG BANG", "IVE", "REVIVE", 2026);
	myService.addMusic("404", "KiiiKiii", "Delulu", 2026);
	myService.addMusic("DDUDU", "Blackpink", "DDUDU", 2024);
	// Search by title
	string music_title;
	cout << "Enter the Music Title: ";
	cin >> music_title;
	Music* result = myService.searchByTitle(music_title);
	if (result != NULL) {
		cout << "Found: " << result->getTitle() << endl;
	}
	else {
		cout << "Not Found" << endl;
	}
	// Search by artist
	string artist_name;
	cout << "Enter the artist name: ";
	cin >> artist_name;
	vector<Music*> artistResult = myService.searchByArtist(artist_name);
	if (artistResult.size() > 0) {
		cout << "Found " << artistResult.size() << " songs by " << artist_name << " : " << endl;
		for (int i = 0; i < artistResult.size(); i++) {
			cout << artistResult[i]->getTitle() << endl;
		}
	}
	else {
		cout << "Not Found" << endl;
	}
	return 0;
}