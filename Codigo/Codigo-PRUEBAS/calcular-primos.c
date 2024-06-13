
/* BENCHMARKS TEST REQUIRED */
#include "benchmarks_deploy.h"
extern char *arm_cortex_pmu_events[];
extern int benchmark_num_trials;
extern int n_events;
int do_miller_rabin_primes_benchmark();

// Función para calcular a^b mod m
uint64_t power(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t result = 1;
    a = a % m;
    while (b > 0) {
        if (b & 1) {
            result = (result * a) % m;
        }
        b = b >> 1;
        a = (a * a) % m;
    }
    return result;
}

// Test de primalidad de Miller-Rabin
bool isPrimeMillerRabin(uint64_t n, int k) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    // Encontrar r y d tal que n - 1 = 2^r * d
    uint64_t d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    // Realizar el test de Miller-Rabin k veces
    for (int i = 0; i < k; i++) {
        uint64_t a = 2 + rand() % (n - 4);
        uint64_t x = power(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool prime = false;
        while (d != n - 1) {
            x = (x * x) % n;
            d *= 2;
            if (x == 1) return false;
            if (x == n - 1) {
                prime = true;
                break;
            }
        }
        if (!prime) return false;
    }
    return true;
}

int do_miller_rabin_primes_benchmark() {
    
    int count = 0;
    int LOOP = benchmark_num_trials;

    /* BENCHMARK START */

    for (uint64_t num = 2; count < LOOP; num++) {
        if (isPrimeMillerRabin(num, 10)) {
            count++;
        }
    }

    /* BENCHMARK END */
    return 0;
}