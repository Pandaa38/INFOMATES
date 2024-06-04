touch tests//.timeout
CMD="valgrind --leak-check=full /home/juan/Documentos/MyProgram/MP_KMERS_PROJECT/Kmer5/./dist/LEARN/GNU-Linux/LEARN  -K 1 -p human -o tests/output/human1.prf ../Genomes/human1.dna 1> tests//.out4 2>&1"
eval $CMD
rm tests//.timeout
