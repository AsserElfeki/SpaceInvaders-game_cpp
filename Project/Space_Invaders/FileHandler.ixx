//module;
//#include <fstream>
//#include <iostream>
//#include <vector>
//#include <map>
//
//export module FileHandler;
//
//export class file_handler
//{
//private : 
//
//
//public:
//
//	void read()
//	{
//		int score;
//		std::string name;
//	
//		std::ifstream InFile("Scores.txt");
//		if (InFile)
//		{
//			while (getline(InFile, pesel_line))
//			{
//				if (!pesel_line.empty() && pesel_line.length() < 13) {
//					for (int i = 0; i < 11; i++) {
//						auto b = pesel_line[i];
//						auto a = pesel_line[i] - '0';
//						pesel.push_back((pesel_line[i]) - '0'); //transform to int
//					}
//					fh_pesels.push_back(pesel);
//					pesel = {};
//				}
//			}
//		}
//
//		file.close();
//	}
//
//	void write(std::vector<PESEL_base*>) {
//		std::ofstream file(this->OutputFile);
//		if (file) {
//			for (auto element : pesels) {
//				file << *element << std::endl;
//			}
//			file.close();
//		}
//	}
//
//	std::ostream& operator<<(std::ostream& os, PESEL_base& obj)
//	{
//		os << "PESEL number: ";
//		for (auto a : obj.get_pesel_num()) {
//			os << a;
//		}
//		os << std::endl;
//
//		os << "Date of birth: " << obj.getBirthDay() << '/' << obj.getBirthMonth() << '/' << obj.CalcBirthYear() << std::endl;
//		os << "Gender: " << obj.getGender() << std::endl;
//		return os;
//	}
//};
