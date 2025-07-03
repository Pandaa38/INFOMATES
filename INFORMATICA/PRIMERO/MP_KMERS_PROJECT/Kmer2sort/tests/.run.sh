touch tests//.timeout
CMD="valgrind --leak-check=full /home/juan/Documentos/MyProgram/MP_KMERS_PROJECT/Kmer2sort/dist/Debug/GNU-Linux/kmer2sort  tests/output/4pairs_5pairsDNA.prf ../Genomes/4pairsDNA.prf ../Genomes/5pairsDNA.prf 1> tests//.out12 2>&1"
eval $CMD
rm tests//.timeout
