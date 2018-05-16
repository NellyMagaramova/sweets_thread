#pragma once
#include <iostream>
#include <string>
#include <mutex>
#include <queue>



class Sweets{
public:
	Sweets();
	void readFile(std::string &filepath);
	void revizor() ;
	void writeToFile(std::string& filepath) ;
	~Sweets();

private:
	std::queue<std::string>buf;

	

		int m_halva;
		int m_marmelad;
		int m_zefir;
		int m_condensedMilk;
		int m_pastila;
		int m_pechenie;
		int m_waffle;
		int m_jam;
		int m_eclair;
		int m_pie;
		int m_sweets;

		bool m_z;


	
	std::mutex mut;
	std::condition_variable data_cond;
	

};