#include "benchmarks_deploy_gem5.h"

int do_miller_rabin_primes_benchmark();
// Función para calcular a^b mod m
uint64_t power(uint64_t a, uint64_t b, uint64_t m);
// Test de primalidad de Miller-Rabin
bool isPrimeMillerRabin(uint64_t n, int k);
