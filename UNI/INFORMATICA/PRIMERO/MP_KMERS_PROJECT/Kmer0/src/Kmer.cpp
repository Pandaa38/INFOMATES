/*
 * Metodología de la Programación: Kmer0
 * Curso 2023/2024
 */

/** 
 * @file Kmer.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Javier Martínez Baena <jbaena@ugr.es>
 * 
 * Created on 24 October 2023, 14:00
 */


#include<iostream>
#include<cctype>
#include"Kmer.h"

using namespace std;

Kmer::Kmer(int k){
    
    if(k <= 0) throw std::invalid_argument( string("Kmer(int k): ") 
                                            + "K is less or equal than zero ");
    
    _text = string(k, MISSING_NUCLEOTIDE);
}

Kmer::Kmer(const std::string& text){
    
    if(text.length() == 0) 
        throw std::invalid_argument(string(" Kmer(const std::string& text): ")
                                    + "text is empty");
    
    _text = text;
}

int Kmer::getK() const{
    
    return _text.length();
}

int Kmer::size() const{
    
    return _text.length();
}

string Kmer::toString() const{
    
    return _text;
}

const char& Kmer::at(int index) const{
    
    if(index < 0 || index >= getK())
        throw std::out_of_range(
                string("const char& Kmer::at(int index) const: ") + 
                "invalid position" + to_string(index));
    
    
    return _text.at(index);
}

char& Kmer::at(int index){
    
    if(index < 0 || index >= getK())
        throw std::out_of_range( string("char& Kmer::at(int index): ") + 
                                "invalid position" + to_string(index));
    
    return _text.at(index);
}

void Kmer::normalize(const std::string& validNucleotides){
    
    Kmer normalize(_text);
    ToUpper(normalize);
    _text = normalize.toString();
    
    for(int i = 0; i < _text.length(); i++){
        
        if(!IsValidNucleotide( toupper(_text[i]), validNucleotides)){
            _text[i] = MISSING_NUCLEOTIDE;
        }
    }
}

Kmer Kmer::complementary(const std::string& nucleotides, 
         const std::string& complementaryNucleotides) const{
    
    if(nucleotides.size() != complementaryNucleotides.size())
        throw std::invalid_argument(
                string( "Kmer Kmer::complementary(const std::string& nucleotides,"
                "const std::string& complementaryNucleotides) const: ") +
                "the sizes of nucleotides and complementaryNucleotides "
                "are not the same");
    
    string complemented_nucleotides = _text;
    
    for(int i = 0; i < size(); i++){
        
        if(IsValidNucleotide(_text[i], nucleotides)){
            int pos = nucleotides.find(_text[i]);
            complemented_nucleotides[i] = complementaryNucleotides[pos];
        }
    }
    
    return Kmer(complemented_nucleotides);
}

bool IsValidNucleotide(char nucleotide,const std::string& validNucleotides){
    
    bool valid = true;
    if(validNucleotides.find_first_of(nucleotide) == -1)
        valid = false;
    
    return valid;
}

void ToLower(Kmer& kmer){
    
    for(int i = 0; i < kmer.getK(); i++){
        
        kmer.at(i) = tolower(kmer.at(i));
    }
}

void ToUpper(Kmer& kmer){
    
    for(int i = 0; i < kmer.getK(); i++){
        
        kmer.at(i) = toupper(kmer.at(i));
    }
}





