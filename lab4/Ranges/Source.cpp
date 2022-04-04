#include <ranges>
#include <iostream> 
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

int main() {

    std::vector<int> numbers = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 };
    std::vector<int> output; 

	/*for (int i : std::views::iota(1) | std::views::take(100))
		std::cout << i << " , ";
    std::cout << std::endl; */

    auto prime = [](int i)
    {
        if (i <= 1)
            return false;
        for (int j = 2; j * j <= i; ++j)
        {
            if (i % j == 0) 
                return false;
        }
        return true;

    };

    //Using ranges create a vector with only prime numbers from another vector
    std::cout << " Task 1 :\n";
    for (int i : numbers | std::views::filter(prime))
    {
        std::cout << i << " , ";
        output.push_back(i);
    }
    std::cout << std::endl;
    std::cout << std::endl;

    //Try to use range factory as input(iota)
    std::cout << " Task 1.1 :\n";
    for (int i : std::views::iota(1) | std::views::take(100) | std::views::filter(prime))
        std::cout << i << " , ";
    std::cout << std::endl;
    std::cout << std::endl;

    //Display this vector in reverse order
    std::cout << " Task 2 :\n";
    auto reverse = std::ranges::reverse_view{ output };
    for (auto n : reverse)
        std::cout << n << " , ";
    std::cout << std::endl;
    std::cout << std::endl;

    //Display all found prime numbers which are greater than 10(don't use filter view)
    std::cout << "Task 3 :\n";
    auto bigger_10 = [](int i) { return i <= 10; };
    auto skip_10 = std::views::drop_while(bigger_10); 
    for (int i : output | skip_10)
        std::cout << i << " , ";
    std::cout << std::endl;
    std::cout << std::endl;

    //Display three first prime numbers
    std::cout << "Task 4 :\n";
    for (int i : output | std::views::take(3))
        std::cout << i << " , ";
    std::cout << std::endl;
    std::cout << std::endl;

    //Display every but three first prime numbers
    std::cout << "Task 5 :\n";
    for (int i : output | std::views::drop(3))
        std::cout << i << " , ";
    std::cout << std::endl;
    std::cout << std::endl;

    //Calculate and display squares of numbers 2-4 from task 5
    std::cout << "Task 6 :\n";
    for (int i : output | std::views::drop(5) | std::views::take(3) | std::views::transform([](int i) {return i * i; }))
        std::cout << i << " , ";
    std::cout << std::endl;
    std::cout << std::endl;

    //Read contents of points.csv file into a string, split it by commas, and display in triples, as points in space 
    //(there are 20 points)
    std::cout << "Task 7 :\n";
    
    std::ifstream inFile("points.csv");
    std::vector<int> points;
    if (inFile) {
        std::string line;
        std::string point{};
        std::string separator{ "," };
        std::getline(inFile, line);
        for (const auto& word : std::views::split(line, separator)) 
        {
            for (const auto& c : word) 
                point += c;
            point += "\n";
            points.push_back(std::stoi(point));
            point = {};
        }
        for (int i = 0; i < points.size(); i += 3) {
            std::cout << "(" << points[i] << "; " << points[i + 1] << "; "
                << points[i + 2] << ")" << std::endl;
        }
        inFile.close();
    }

    std::cout << std::endl;
    std::cout << std::endl;
}




    
    
