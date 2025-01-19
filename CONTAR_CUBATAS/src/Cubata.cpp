//
// Created by juan on 27/12/24.
//

#include "Cubata.h"

#include <algorithm>
#include <iostream>
#include <istream>
#include <ostream>

Cubatas::Cubatas() {}
Cubatas::~Cubatas() {}

void Cubatas::add_persona(const std::string &name, const std::map<std::string, int> &attributes, int num) {

	persona nuevo = persona(name, attributes, num);
	bebedor.push_back(nuevo);
}

void Cubatas::add_persona(const persona &persona) {
	bebedor.push_back(persona);
}

void Cubatas::remove_persona(const std::string &name) {

	std::vector<persona>::iterator it = find_persona(name);
	bebedor.erase(it);
}

void Cubatas::remove_persona(const persona &persona) {
	remove_persona(persona.name);
}

//ERRORRRRRRR ESTA MAL NO SE PORQUE
std::map<std::string, int> Cubatas::get_cubatas_persona(const std::string &name) const{

	//std::vector<persona>::iterator
	std::vector<persona>::const_iterator it = find_persona(name);

	std::map<std::string, int> cubatas_ = it->cubatas;
	return cubatas_;
}

Cubatas::persona Cubatas::get_persona(const std::string &name) const{
	return (*find_persona(name));
}

std::vector<Cubatas::persona>::iterator Cubatas::find_persona(const std::string &name) {

	std::vector<persona>::iterator it = bebedor.begin();
	bool found = false;
	while (it != bebedor.end() && !found) {
		if ((*it).name == name) found = true;
		else ++it;
	}
	return it;
}
std::vector<Cubatas::persona>::const_iterator Cubatas::find_persona(const std::string &name) const {
	std::vector<persona>::const_iterator it = bebedor.begin();
	bool found = false;
	while (it != bebedor.end() && !found) {
		if ((*it).name == name) found = true;
		else ++it;
	}
	return it;
}

int Cubatas::num_personas() const{
	return bebedor.size();
}

int Cubatas::total_cubatas() const {

	int total = 0;
	for (auto it : bebedor) {
		total += it.num_cubatas;
	}
	return total;
}


std::string Cubatas::get_persona_name(int pos) const {
	std::vector<persona>::const_iterator it = bebedor.begin();
	it += pos;
	return it->name;
}
int Cubatas::get_num_cubatas(int pos) const {
	return bebedor[pos].num_cubatas;
}


void Cubatas::leer_personas(std::istream &is){

	std::string line;

	while (getline(is, line)) {

		line = normalizar(line);
		int sepadaror = line.find_last_of(":");

		std::string name = line.substr(0, sepadaror);
		std::string drink = line.substr(sepadaror + 1);

		//std::cout << name << " " << drink << std::endl;

		std::vector<persona>::iterator it = find_persona(name);
		if (it != bebedor.end()) {
			it->cubatas[drink]++;
			it->num_cubatas++;
		}
		else {
			persona p;
			p.name = name;
			p.cubatas[drink] = 1;
			p.num_cubatas = 1;
			this->add_persona(p);
		}
	}

}


std::ostream& operator<<(std::ostream& os, const Cubatas& cubatas) {
	for (int i = 0; i < cubatas.num_personas(); i++) {
		os << "El bebedor \"" << cubatas.get_persona_name(i) << "\" ha bebido este año:" << std::endl;

		auto map = cubatas.get_cubatas_persona(cubatas.get_persona_name(i));

		for(auto j : map) {
			os << '\t' << j.first << ": " << j.second << std::endl;
		}
		os << "Eso hace un total de " << cubatas.get_num_cubatas(i) << " cubatas " << std::endl;
		os << std::endl;
	}

	os << std::endl;
	os << "El total final de cubatas es: " << cubatas.total_cubatas() << std::endl;
	return os;
}

std::string normalizar(const std::string &line) {
	std::string new_line;
	//new_line.reserve(line.size());

	for (auto c : line) {
		if (!isspace(c)) {
			new_line += tolower(c);
		}
	}
	size_t pos_last_dash = new_line.find("-");
	size_t pos_less_than = new_line.find("<");

	// Ajustar la longitud de substr
	if (pos_less_than != std::string::npos && pos_less_than > pos_last_dash)
		new_line = new_line.substr(pos_last_dash + 1, pos_less_than - pos_last_dash - 1);
	else
		new_line = new_line.substr(pos_last_dash + 1);

	return new_line;
}