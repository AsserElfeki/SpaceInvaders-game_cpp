export module Module_A;
export import std.core;

export class Player {
private: 
	int position_x;
	double position_y;
	std::string ID;

public:
	Player(int _a, double _b, std::string _c) : 
		position_x(_a), position_y(_b), ID(_c) {
		/*std::cout << "construction\n";*/
	};

	void print_player() {
		std::cout << "Player info:\n";
		std::cout << "Name: " << ID << std::endl;
		std::cout << "Position (X , Y) = (" << position_x << " , " << position_y << ")\n";
		std::cout << std::endl; 
	}
};

export int test_int{ 100 };