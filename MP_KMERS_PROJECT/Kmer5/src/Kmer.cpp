/*
 * Metodología de la Programación: Kmer0
 * Curso 2023/2024
 */

/** 
 * @file Kmer.cpp
 * @author Juan Reche Aguilar
 * 
 * Created on 24 October 2023, 14:00
 */

#include<iostream>
#include<cctype>
#include"Kmer.h"


Kmer::Kmer(int k){
    
    if(k <= 0) throw std::invalid_argument( std::string("Kmer(int k): ") 
                                            + "K is less or equal than zero ");
    
    _text = std::string(k, MISSING_NUCLEOTIDE);
}

Kmer::Kmer(const std::string& text){
    
    if(text.empty()) 
        throw std::invalid_argument(std::string("Kmer(const std::string& ")
                                    + "text): text is empty");
    
    _text = text;
}

int Kmer::getK() const{
    
    return _text.length();
}

int Kmer::size() const{
    
    return _text.length();
}

std::string Kmer::toString() const{
    
    return _text;
}

const char& Kmer::at(int index) const{
    
    if(index < 0 || index >= getK())
        throw std::out_of_range(
                std::string("const char& Kmer::at(int index) const: ") + 
                "invalid position" + std::to_string(index));
    
    return _text.at(index);
}

char& Kmer::at(int index){
    
    if(index < 0 || index >= getK())
        throw std::out_of_range( std::string("char& Kmer::at(int index): ") + 
                                "invalid position" + std::to_string(index));
    
    return _text.at(index);
}

void Kmer::toLower(){
    
    for(int i = 0; i < getK(); i++){
        
        _text[i] = tolower(_text[i]);
    }
}

void Kmer::toUpper(){
    
    for(int i = 0; i < getK(); i++){
        
        _text[i] = toupper(_text[i]);
    }
}

void Kmer::normalize(const std::string& validNucleotides){
    
    toUpper();
    
    for(int i = 0; i < (int)_text.length(); i++){
        
        if(!IsValidNucleotide( toupper(_text[i]), validNucleotides)){
            _text[i] = MISSING_NUCLEOTIDE;
        }
    }
}

Kmer Kmer::complementary(const std::string& nucleotides, 
         const std::string& complementaryNucleotides) const{
    
    if(nucleotides.size() != complementaryNucleotides.size())
        throw std::invalid_argument(
         std::string( "Kmer Kmer::complementary(const std::string& nucleotides,"
                "const std::string& complementaryNucleotides) const: ") +
                "the sizes of nucleotides and complementaryNucleotides "
                "are not the same");
    
    std::string complemented_nucleotides = _text;
    
    for(int i = 0; i < size(); i++){
        
        if(IsValidNucleotide(_text[i], nucleotides)){
            int pos = nucleotides.find(_text[i]);
            complemented_nucleotides[i] = complementaryNucleotides[pos];
        }
    }
    
    return Kmer(complemented_nucleotides);
}

void Kmer::write(std::ostream& outputStream) const{
    
    outputStream.write(_text.c_str(), size() + 1);
}

void Kmer::read(std::istream& inputStream){
    
    //hacer bucle leer caracter a caracter
    std::string kmero;
    char caracter;
    
    do{
        inputStream.read(reinterpret_cast<char*>(&caracter), sizeof(char));
        if(caracter != '\0'){
            kmero += caracter;
        }
    }while(caracter != '\0');
    
    _text = kmero;
}

bool Kmer::thereIsMissingNucleotide() const{
    
    bool missing = false;
    int miss = _text.find(MISSING_NUCLEOTIDE);
   
    if(miss != -1) missing = true;
    
    return missing;
}

bool Kmer::thereIsInvalidNucleotide(const std::string& validNucleotides) const{
    
    bool invalid = false;
    
    for(int i = 0; i < size() && !invalid; i++){
        if(!IsValidNucleotide(at(i), validNucleotides))
            invalid = true;
    }
    
    return invalid;
}

bool IsValidNucleotide(char nucleotide,const std::string& validNucleotides){
    
    bool valid = true;
    if((int)validNucleotides.find_first_of(nucleotide) == -1)
        valid = false;
    
    return valid;
}

void ToLower(Kmer& kmer){
    
    kmer.toLower();
}

void ToUpper(Kmer& kmer){
    
    kmer.toUpper();
}

std::ostream& operator<<(std::ostream& os, const Kmer& kmer){
    
    os << kmer.toString();
    
    return os;
}

std::istream& operator>>(std::istream& is, Kmer& kmer){
    
    std::string kmer_text;
     
    is >> kmer_text;
    
    kmer = Kmer(kmer_text);
    
    return is;
}
