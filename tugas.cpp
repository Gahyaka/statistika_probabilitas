#include <iostream>
#include <vector>
#include <numeric> // Untuk std::accumulate
#include <algorithm> // Untuk std::max_element
#include <utility> // Untuk std::pair

// Fungsi untuk menghitung median dari sebuah vektor (sub-vektor)
// Prasyarat: vektor harus sudah terurut
double calculateMedian(const std::vector<int>& sorted_vec) {
    size_t n = sorted_vec.size();
    if (n == 0) {
        return 0; // Menghindari pembagian dengan nol jika vektor kosong
    }
    if (n % 2 != 0) {
        // Jika jumlah data ganjil, median adalah nilai tengah
        return sorted_vec[n / 2];
    } else {
        // Jika jumlah data genap, median adalah rata-rata dua nilai tengah
        return (static_cast<double>(sorted_vec[n / 2 - 1]) + sorted_vec[n / 2]) / 2.0;
    }
}


int main() {
    // 1. Representasi Data: Pasangan {nilai, frekuensi}
    std::vector<std::pair<int, int>> freq_data = {
        {1, 5}, {7, 7}, {13, 8}, {19, 9}, {25, 10},
        {31, 3}, {37, 6}, {42, 7}
    };

    // 2. Membuat Dataset Lengkap dan Menghitung Total
    std::vector<int> dataset;
    double total_sum = 0;
    int total_freq = 0;

    for (const auto& pair : freq_data) {
        int value = pair.first;
        int freq = pair.second;

        // Menambahkan nilai ke dataset sebanyak frekuensinya
        for (int i = 0; i < freq; ++i) {
            dataset.push_back(value);
        }

        // Akumulasi untuk perhitungan mean
        total_sum += static_cast<double>(value) * freq;
        total_freq += freq;
    }
    
    // Karena data input sudah urut, 'dataset' yang dihasilkan juga otomatis terurut.
    // Kita tidak perlu memanggil std::sort(dataset.begin(), dataset.end());

    std::cout << "--- Analisis Statistik Data Tunggal ---" << std::endl;
    std::cout << "Total data (N): " << total_freq << std::endl << std::endl;

    // 3. Menghitung Mean
    double mean = total_sum / total_freq;
    std::cout << ">> Mean (Rata-rata)" << std::endl;
    std::cout << "   Hasil: " << mean << std::endl << std::endl;

    // 4. Menghitung Modus
    int max_freq = 0;
    for (const auto& pair : freq_data) {
        if (pair.second > max_freq) {
            max_freq = pair.second;
        }
    }

    std::vector<int> modes;
    for (const auto& pair : freq_data) {
        if (pair.second == max_freq) {
            modes.push_back(pair.first);
        }
    }
    
    std::cout << ">> Modus (Nilai Paling Sering Muncul)" << std::endl;
    std::cout << "   Frekuensi tertinggi: " << max_freq << std::endl;
    std::cout << "   Hasil: ";
    for (size_t i = 0; i < modes.size(); ++i) {
        std::cout << modes[i] << (i == modes.size() - 1 ? "" : ", ");
    }
    std::cout << std::endl << std::endl;

    // 5. Menghitung Median dan Kuartil
    // Q2 adalah median dari keseluruhan data
    double q2 = calculateMedian(dataset);

    // Menentukan titik potong untuk Q1 dan Q3
    size_t mid_index = dataset.size() / 2;

    // Vektor untuk separuh bawah data (untuk Q1)
    std::vector<int> lower_half(dataset.begin(), dataset.begin() + mid_index);

    // Vektor untuk separuh atas data (untuk Q3)
    // Jika N ganjil, kita lewati elemen tengah
    std::vector<int> upper_half(dataset.begin() + (dataset.size() % 2 == 0 ? mid_index : mid_index + 1), dataset.end());
    
    double q1 = calculateMedian(lower_half);
    double q3 = calculateMedian(upper_half);

    std::cout << ">> Median dan Kuartil" << std::endl;
    std::cout << "   Q1 (Kuartil Bawah): " << q1 << std::endl;
    std::cout << "   Q2 (Median): " << q2 << std::endl;
    std::cout << "   Q3 (Kuartil Atas): " << q3 << std::endl;


    return 0;
}