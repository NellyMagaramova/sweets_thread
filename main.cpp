#include "revizor.h"
#include <thread>
using namespace std;

int main(int argc, char* argv[]) {

	string fileclose;
	string fileopen;

	if (argc == 1)
	{
		cout << "Expected two arguments : path to file with data and path to save file. Example:  .\threads.exe C:\\Users\\..\\text1.txt" "C:\\Users\\..\\result.txt  \n";
		cin >> fileopen;
		cin >> fileclose;
		
	}

	if (argc == 2) {fileopen = string(argv[1]);  fileclose = string("result.txt"); }
	if (argc == 3) {fileopen = string(argv[1]);  fileclose = string(argv[2]);}

	Sweets obj;
	std::thread func_read(&Sweets::readFile,&obj,std::ref(fileopen));
	std::thread func_write(&Sweets::writeToFile, &obj, std::ref(fileclose));
	std::thread func_rev(&Sweets::revizor, &obj);

	
	func_write.join();
	func_rev.join();
	func_read.join();
	std::cout << "open file with results" << std::endl;

	system("pause");
	return 0;

}