#include <iostream>
#include "vec3.h"
using namespace std;

int main() {

	ivec3* uwu01 = new ivec3(5,8,9);
	ivec3* uwu02 = new ivec3(1,1,1);

	ivec3* sum = new ivec3();

	
	uwu01->Normalize();
	cout << uwu01->x << "," << uwu01->y << "," << uwu01->z << endl;

	int distance = uwu01->DistanceTo(*uwu02);
	cout << distance << endl;

	uwu01->SetToZero();
	cout << uwu01->x << "," << uwu01->y << "," << uwu01->z << endl;

}