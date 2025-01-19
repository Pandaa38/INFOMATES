//
// Created by juan on 27/12/24.
//

#ifndef CUBATA_H
#define CUBATA_H

#include <map>
#include <string>
#include <vector>

//puedo hacer un array dinamico de cubatas para que cada persona tenga un map distinto
//mejor vector mas rapido y facil


//debo hacer metodos constantes para hacer bien << y >>
class Cubatas {

	private:
	//std::pmr::map<std::string, int> cubata;
	//std::string persona;
	//std::pair<string, std::pmr::map<std::string, int>> personas;

	struct persona {
		std::string name;
		std::map<std::string, int> cubatas;
		int num_cubatas;
	};

	std::vector< persona > bebedor;

	/******************************************************************************************/
	public:

	//CONSTRUCTOR Y DESTRUCTOR
	Cubatas();
	~Cubatas();

	//MODIFICADORES
	void add_persona(const std::string &name, const std::map<std::string, int> &attributes, int num=0);
	void add_persona(const persona &persona);

	void remove_persona(const std::string &name);
	void remove_persona(const persona &persona);

	//INFORMACION
	std::map<std::string, int> get_cubatas_persona(const std::string &name) const;
	persona get_persona(const std::string &name) const;

	std::string get_persona_name(int pos) const;
	int get_num_cubatas(int pos) const;

	int num_personas() const;
	int total_cubatas() const;

	//ITERADORES
	std::vector<persona>::iterator find_persona(const std::string &name);
	std::vector<persona>::const_iterator find_persona(const std::string &name) const;
	//void read_cubatas(std::ifstream &file);

	void leer_personas(std::istream &is);

	//friend std::istream& operator>>(std::ostream& is, Cubatas& cubatas);
};

std::ostream& operator<<(std::ostream& os, const Cubatas& cubatas);
//std::istream& operator>>(std::istream& is, Cubatas& cubatas, const std::string & nombres_validos);

std::string normalizar(const std::string &line);


#endif //CUBATA_H
