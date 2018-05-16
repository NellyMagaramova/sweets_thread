#include "revizor.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>

#include <mutex>
#include <queue>
#include <windows.h>
using namespace std;

void Sweets::readFile(std::string &filepath) 
{
	//cout << "download file    " << filepath << std::endl;
	std::ifstream stream(filepath);
	char ff;
	string file_buffer;

	if (!stream.is_open()) std::cout << "error openning";

	else
	{
		std::lock_guard<std::mutex>lk(this->mut);

		while (!stream.eof())
		{
			ff = stream.get();  
			file_buffer += ff;

			if (ff == '\n')
			{
				this->buf.push(file_buffer);
				file_buffer.clear();
				this->data_cond.notify_one();
			}
		}
	}
	std::cout << "\n Halva" << "  " <<m_halva << endl;
	std::cout << "\n Jujube" << "  " << m_marmelad << endl;
	std::cout << "\n Zefir" << "  " << m_zefir << endl;
	std::cout << "\n Condensed Milk" << "  " << m_condensedMilk << endl;
	std::cout << "\n Pastila" << "  " << m_pastila << endl;
	std::cout << "\n Waffle" << "  " << m_waffle << endl;
	std::cout << "\n Cookie" << "  " << m_pechenie << endl;
	std::cout << "\n Jam" << "  " << m_jam << endl;
	std::cout << "\n Eclair" << "  " << m_eclair << endl;
	std::cout << "\n Sweets" << "  " << m_sweets << endl;
	std::cout << "\n Pie" << "  " << m_pie << endl;
}

Sweets::Sweets() : m_halva(0), m_marmelad(0), m_zefir(0),m_condensedMilk(0), m_pastila(0), m_pechenie(0), m_waffle(0), m_jam(0), m_eclair(0), m_pie(0), m_sweets(0) {}
Sweets::~Sweets() {
	//delete m_halva;delete m_halva; delete m_marmelad; delete m_zefir; delete m_condensedMilk; delete m_pastila; delete m_pechenie; delete m_waffle; delete m_jam, delete m_eclair; delete m_pie; delete m_sweets;

}
void Sweets::revizor() {
	

	while (!this->buf.empty()) 
	{
		m_z = false;
		string dataToCount;
		std::unique_lock<std::mutex>lk(this->mut);

		while (this->buf.empty())
		{
			data_cond.wait(lk);
		}

		dataToCount = buf.front();

		
		
		
		if (dataToCount.find("Halva") != std::string::npos)m_halva = m_halva + 1;
		if (dataToCount.find("Jujube") != std::string::npos)m_marmelad = m_marmelad + 1;
		if (dataToCount.find("Zefir") != std::string::npos)m_zefir = m_zefir + 1;
		if (dataToCount.find("Condensed Milk") != std::string::npos)m_condensedMilk =m_condensedMilk + 1;
		if (dataToCount.find("Pastila") != std::string::npos) m_pastila = m_pastila + 1;
		if (dataToCount.find("Waffle") != std::string::npos) m_waffle =m_waffle + 1;
		if (dataToCount.find("Cookie") != std::string::npos) m_pechenie = m_pechenie + 1;
		if (dataToCount.find("Jam") != std::string::npos) m_jam = m_jam + 1;
		if (dataToCount.find("Eclair") != std::string::npos) m_eclair = m_eclair + 1;
		if (dataToCount.find("Sweets") != std::string::npos) m_sweets = m_sweets + 1;
		if (dataToCount.find("Pie") != std::string::npos)m_pie = m_pie + 1;

		if (dataToCount.find("Jujube") != std::string::npos)
		{
			m_z = true;
		}else m_z = false;

		dataToCount.erase();
		lk.unlock();
	}
	std::cout << this->buf.front();
	
};

void Sweets::writeToFile(std::string& filepath) 
{
	ofstream result(filepath);
	
	while (!this->buf.empty())
	{
		
		std::string dataToFile;
		std::unique_lock<std::mutex>lk(this->mut);

		while (this->buf.empty())
		{
			data_cond.wait(lk);

		}

		dataToFile = this->buf.front();
		//cout <<"dataToFile  "<<dataToFile;

		if (result.is_open())
		{
			if ((dataToFile.find("Sweets") != std::string::npos) || (dataToFile.find("Jujube") != std::string::npos) || (dataToFile.find("Zefir") != std::string::npos) || (dataToFile.find("Condensed milk") != std::string::npos) || (dataToFile.find("Cookie") != std::string::npos))
			{
				if (m_z==true)
				{
					dataToFile.replace(dataToFile.begin(), dataToFile.end() - 1, "Zefir");
				}
				result << dataToFile;
			}

		}

		
	
		
		this->buf.pop();


		dataToFile.erase();
		lk.unlock();
		data_cond.notify_one();
		

	}
	result.close();

	//std::cout << this->buf.front();


	//cout << "open file with results  " << filepath << std::endl;
	
};