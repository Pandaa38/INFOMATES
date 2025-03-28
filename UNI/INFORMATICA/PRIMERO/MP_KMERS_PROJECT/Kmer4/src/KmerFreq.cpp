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

void copy_kmer(const KmerFreq *origen, KmerFreq *destino, int size){
    
    for(int i = 0; i < size; i++){
        destino[i] = origen[i];
    }
    
}