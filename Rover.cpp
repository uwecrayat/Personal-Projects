/*
 * Rover.cpp
 *
 *  Created on: Apr 30, 2015
 *      Author: Adam
 */

#include <cmath>
//#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Rover {
private:
	string name;
	int x;
	int y;
	string dir;
	int speed;
public:
	Rover() {
		x = 0;
		y = 0;
		dir = "N";
		speed = 0;
	}
	Rover(string name, int x, int y, string dir, int speed) {
		this->name = name;
		this->x = x;
		this->y = y;
		this->dir = dir;
		this->speed = speed;
	}

	const string& getDir() const {
		return dir;
	}

	void setDir(const string& dir) {
		this->dir = dir;
	}

	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}

	int getSpeed() const {
		return speed;
	}

	void setSpeed(int speed) {
		this->speed = speed;
	}

	int getX() const {
		return x;
	}

	void setX(int x) {
		this->x = x;
	}

	int getY() const {
		return y;
	}

	void setY(int y) {
		this->y = y;
	}

	string getRoverData() const {
		ostringstream data;
		data << "Rover name: " << name << "\n" << "X-position: " << x << "\n"
				<< "Y-position: " << y << "\n" << "Direction: " << dir << "\n"
				<< "Speed: " << speed << endl;
		return data.str();
	}
};

// variables
int arr_size;
vector<Rover> rovers;
// functions

void updatePosition(int elapsedTime);

double distance(double x1, double y1, double x2, double y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void checkIfCollision(vector<Rover> rovers) {
	for (vector<int>::size_type i = 0; i < rovers.size(); i++) {
		for (vector<int>::size_type j = 0; j < rovers.size(); j++) {
			if (i != j) {
				double dist = distance(rovers[i].getX(), rovers[i].getY(),
						rovers[j].getX(), rovers[j].getY());
				if (dist == 0) {
					cout << "DISASTER ALERT! " << rovers[i].getName()
							<< " collided with " << rovers[j].getName() << endl;
					// Eclipse tells me that using these lines to remove an element from a vector gives an error.
					// It says "required from here" and then compiles with lots of error messages.
					// A quick google search tells me this is how to remove something from a vector given an element and not using the known position. I'm confused why it wouldn't work. I have commented the two lines that would remove crashed rovers because of this.
//					rovers.erase(remove(rovers.begin(), rovers.end(), rovers[i]), rovers.end());
//					rovers.erase(remove(rovers.begin(), rovers.end(), rovers[j]), rovers.end());
				}
			}
		}
	}
}

void checkIfClose(vector<Rover> rovers) {
	checkIfCollision(rovers);
	for (vector<int>::size_type i = 0; i < rovers.size(); i++) {
		for (vector<int>::size_type j = 0; j < rovers.size(); j++) {
			if (i != j) {
				double dist = distance(rovers[i].getX(), rovers[i].getY(),
						rovers[j].getX(), rovers[j].getY());
				if (dist <= 5) {
					cout << "DANGER! Rover " << rovers[i].getName() << " is "
							<< dist << " meters away from "
							<< rovers[j].getName() << endl;
				}
			}
		}
	}
}

void displayAllRoverData(vector<Rover> rovers) {
	cout << "Rover\tX-Position\tY-Position\tDirection\tSpeed" << endl;
	for (vector<int>::size_type i = 0; i < rovers.size(); i++) {
		cout << rovers[i].getName() << "\t" << rovers[i].getX() << "\t\t"
				<< rovers[i].getY() << "\t\t" << rovers[i].getDir() << "\t\t"
				<< rovers[i].getSpeed() << endl;
	}
}

void promptUser() {
	cout << "How many rovers would you like to make? (Maximum is 5): ";
	cin >> arr_size;
	while (arr_size <= 0 || arr_size > 5) {
		cout << "Invalid number of rovers. Only 1-5 is valid." << endl;
		cout << "How many rovers would you like to make? (Maximum is 5): ";
		cin >> arr_size;
	}
	rovers.resize(arr_size);
	for (vector<int>::size_type i = 0; i < rovers.size(); i++) {
		string tmp;
		double vals;
		cout << "Name of rover " << (i + 1) << ": ";
		cin >> tmp;
		rovers[i].setName(tmp);
		cout << "X-position of rover " << (i + 1) << ": ";
		cin >> vals;
		rovers[i].setX(vals);
		cout << "Y-position of rover " << (i + 1) << ": ";
		cin >> vals;
		rovers[i].setY(vals);
		cout << "Direction of rover " << (i + 1) << " (N, S, E, or W) " << ": ";
		cin >> tmp;

		while (true) {
			if (tmp == "N" || tmp == "S" || tmp == "E" || tmp == "W") {
				rovers[i].setDir(tmp);
				break;
			} else {
				cout << "Only these four directions are allowed. Try again."
						<< endl;
				cout << "Direction of rover " << (i + 1) << " (N, S, E, or W) "
						<< ": ";
				cin >> tmp;
			}
		}

		cout << "Speed of rover " << (i + 1) << ": ";
		cin >> vals;
		while (vals < 0 || vals > 5) {
			cout << "Invalid speed. Only 0-5 is valid." << endl;
			cout << "Speed of rover " << (i + 1) << ": ";
			cin >> vals;
		}
		rovers[i].setSpeed(vals);
	}
	cout << "\nSummary" << endl;
	for (vector<int>::size_type i = 0; i < rovers.size(); i++) {
		cout << rovers[i].getRoverData() << endl;
	}
}

int main(int argc, char **argv) {
	promptUser();
	bool done = false;
	while (!done) {
		displayAllRoverData(rovers);
		checkIfClose(rovers);
		for (vector<int>::size_type i = 0; i < rovers.size(); i++) {
			cout << rovers[i].getRoverData();
		}
		cout << "\n";
		displayAllRoverData(rovers);
		cout << "\nEnter new rover direction (N, S, E, W) or q to quit" << endl;
		string res;
		cin >> res;
		if (res == "q") {
			done = true;
		}
	}

}

