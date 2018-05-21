#include "revizor.h"
#include <thread>
#include <windows.h>
//#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "");


	string fileclose;
	string fileopen;

	if (argc == 1)
	{
		cout << "Expected two arguments : path to file with data and path to save file. Example:  .\threads.exe C:\\Users\\..\\text1.txt"    "C:\\Users\\..\\result.txt  \n";
		cout << "Enter a path to download file"<<std::endl;
		cin >> fileopen;
		cout << "Enter a path to save file"<<std::endl;
		cin >>fileclose;
		
	}

	if (argc == 2) {fileopen = string(argv[1]);  fileclose = string("result.txt"); }
	if (argc == 3) {fileopen = string(argv[1]);  fileclose = string(argv[2]);}


	//std::ifstream stream(fileopen);
	

	//while(!stream.is_open()) {
	//	std::cout << "\n \n the path:" << std::endl;
	//	cout <<fileopen;
	//	cout << "\n is not correct \n";

	//	fileopen.erase();

	//	cout << "Enter a new path to download file \n";
	//	
	//	cin >> fileopen;

	//	stream.open(fileopen);
	//	cout << std::endl;
	//}
	//stream.close();


	Sweets obj;
	std::thread func_read(&Sweets::readFile,&obj,std::ref(fileopen));

	

	std::thread func_rev(&Sweets::revizor, &obj);

	std::thread func_write(&Sweets::writeToFile, &obj, std::ref(fileclose));
	
	func_read.join();
	func_rev.join();
	
	func_write.join();
	

	std::cout << "open file with results" << std::endl;

	system("pause");
	return 0;

}
