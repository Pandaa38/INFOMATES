/*
 * Metodología de la Programación: Kmer1
 * Curso 2023/2024
 */

/** 
 * @file KmerFreq.cpp
 * @author Juan Reche Aguilar
 * 
 * Created on 27 de octubre de 2023, 11:03
 */

#include "KmerFreq.h"

#include <iostream>
#include <string>


KmerFreq::KmerFreq(): _kmer(Kmer()), _frequency(0){}

const Kmer& KmerFreq::getKmer() const{
    
    return _kmer;
}

int KmerFreq::getFrequency() const{
    
    return _frequency;
}

void KmerFreq::setKmer(const Kmer& kmer){
    
    _kmer = kmer;
}

void KmerFreq::setFrequency(int frequency){
    
    if(frequency < 0)
        throw std::out_of_range("setFrequency: frequency is negative");
    
    _frequency = frequency;
}

std::string KmerFreq::toString() const{
    
    return std::string(_kmer.toString()) + " " + std::to_string(_frequency);
}

void KmerFreq::write(std::ostream& outputStream) const{
    
    _kmer.write(outputStream);
    outputStream.write(reinterpret_cast<char*>(_frequency), sizeof(int));
    
}

void KmerFreq::read(std::istream& inputStream){
    
    Kmer aux;
    aux.read(inputStream);
    
    this->setKmer(aux);
    
    inputStream.read(reinterpret_cast<char*>(&_frequency), sizeof(int));
}

void copy_kmer(const KmerFreq *origen, KmerFreq *destino, int size){
    
    for(int i = 0; i < size; i++){
        destino[i] = origen[i];
    }    
}

std::ostream& operator<<(std::ostream& os, KmerFreq kmerFreq){
    
    os << kmerFreq.toString();
    return os;
}

std::istream& operator>>(std::istream& is, KmerFreq kmerFreq){
    
    int number;
    Kmer nucleotide;
    
    is >> number >> nucleotide;
    
    kmerFreq.setFrequency(number);
    kmerFreq.setKmer(nucleotide);
    
    return is;
}

bool operator>(const KmerFreq& kmerFreq1, const KmerFreq& kmerFreq2){
    
    bool bigger = false;
    
    if(kmerFreq1.getFrequency() > kmerFreq2.getFrequency())
        bigger = true;
    else if(kmerFreq1.getFrequency() == kmerFreq2.getFrequency()){
        
        if(kmerFreq1.getKmer().toString() < kmerFreq2.getKmer().toString())
            bigger = true;
    }
    return bigger;
}

bool operator<(const KmerFreq& kmerFreq1, const KmerFreq& kmerFreq2){
    return kmerFreq2 > kmerFreq1;
}

bool operator==(const KmerFreq& kmerFreq1, const KmerFreq& kmerFreq2){
    
    return (kmerFreq1.getKmer().toString() == kmerFreq2.getKmer().toString() && 
            kmerFreq1.getFrequency() == kmerFreq2.getFrequency());
}

bool operator!=(const KmerFreq& kmerFreq1, const KmerFreq& kmerFreq2){
    
    return !(kmerFreq1 == kmerFreq2);
}

bool operator<=(const KmerFreq& kmerFreq1, const KmerFreq& kmerFreq2){
    
    return (kmerFreq1 < kmerFreq2 || kmerFreq1 == kmerFreq2);
}

bool operator>=(const KmerFreq& kmerFreq1, const KmerFreq& kmerFreq2){
    
    return (kmerFreq1 > kmerFreq2 || kmerFreq1 == kmerFreq2);
}