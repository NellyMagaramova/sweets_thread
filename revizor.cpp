#include "revizor.h"

#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <mutex>
#include <queue>
#include <windows.h>
using namespace std;

void Sweets::readFile(std::string &filepath) 
{
	
	std::ifstream stream(filepath);
	char ff;
	string file_buffer;
	
	if (!stream.is_open()) std::cout << "error openning\n";

	else
	{
		std::unique_lock<std::mutex>lk(this->mut);  //для записи

		while (!stream.eof())
		
		{
			ff = stream.get();
		
			if (ff>0)
			{
			
				file_buffer += ff;
			
				if (ff == '\n')
				{
					
					this->buf.push(file_buffer);
					file_buffer.erase();
			
					lk.unlock();
					
				}
			}
		}
	}
	std::cout << "Halva" << "  " << m_halva <<endl;
	std::cout << "Jujube" << "  " << m_marmelad << endl;
	std::cout << "Zefir" << "  " << m_zefir << endl;
	std::cout << "Condensed milk" << "  " << m_condensedMilk << endl;
	std::cout << "Pastila" << "  " << m_pastila << endl;
	std::cout << "Waffle" << "  " << m_waffle << endl;
	std::cout << "Cookie" << "  " << m_pechenie << endl;
	std::cout << "Jam" << "  " << m_jam << endl;
	std::cout << "Eclair" << "  " << m_eclair << endl;
	std::cout << "Sweets" << "  " << m_sweets << endl;
	std::cout << "Pie" << "  " << m_pie << endl;
		
	
}

Sweets::Sweets() : m_halva(0), m_marmelad(0), m_zefir(0),m_condensedMilk(0), m_pastila(0), m_pechenie(0), m_waffle(0), m_jam(0), m_eclair(0), m_pie(0), m_sweets(0) {}
Sweets::~Sweets() {
	

}
void Sweets::revizor() {
	

	while (!this->buf.empty()) 
	{
		m_z = false;
		string dataToCount;
		std::unique_lock<std::mutex>lk(this->mut);

	

		dataToCount = buf.front();

		cout <<"revizor  "<<dataToCount;
	
		
		if (dataToCount.find("Halva") != std::string::npos) m_halva = m_halva + 1;
		
		if (dataToCount.find("Jujube") != std::string::npos)this->m_marmelad = m_marmelad + 1;
		if (dataToCount.find("Zefir") != std::string::npos)m_zefir = m_zefir + 1;
		if (dataToCount.find("Condensed milk") != std::string::npos)m_condensedMilk =m_condensedMilk + 1;
		if (dataToCount.find("Pastila") != std::string::npos) m_pastila = m_pastila + 1;
		if (dataToCount.find("Waffle") != std::string::npos) m_waffle =m_waffle + 1;
		if (dataToCount.find("Cookie") != std::string::npos) m_pechenie = m_pechenie + 1;
		if (dataToCount.find("Jam") != std::string::npos) m_jam = m_jam + 1;
		if (dataToCount.find("Eclair") != std::string::npos) m_eclair = m_eclair + 1;
		if (dataToCount.find("Sweets") != std::string::npos) m_sweets = m_sweets + 1;
		if (dataToCount.find("Pie") != std::string::npos)m_pie = m_pie + 1;

		if (dataToCount.find("Jujube") != std::string::npos)
		{
			
			buf.pop();
			buf.push("Zefir");
			dataToCount.erase();
			dataToCount = buf.front();
		
		}
	


		dataToCount.erase();
		lk.unlock();
	}

	
};

void Sweets::writeToFile(std::string& filepath) 
{
	ofstream result(filepath);
	
	while (!this->buf.empty())
	{
		
		std::string dataToFile;
		std::unique_lock<std::mutex>lk(this->mut);

		

		dataToFile = this->buf.front();
		

		if (result.is_open())
		{
			if ((dataToFile.find("Sweets") != std::string::npos) || (dataToFile.find("Jujube") != std::string::npos) || (dataToFile.find("Zefir") != std::string::npos) || (dataToFile.find("Condensed milk") != std::string::npos) || (dataToFile.find("Cookie") != std::string::npos))
			{
				
				result << dataToFile;
			}

		}

		this->buf.pop();
		dataToFile.erase();
		lk.unlock();

	}
	

};
