/////////knihovny
#include <iostream>
#include <vector>
#include <cmath>
#include <sndfile.h>


///////////hlavní část programu
int main() {

///////////určení vstupu a výstupu
    std::string inputName = "input.wav";
    std::string outputName = "output.wav";

///////////ukládaní a jak budou vypadat dle knihovny
    SF_INFO info;
    SNDFILE* infile = sf_open(inputName.c_str(), SFM_READ, &info);

//////////////kontrola otevření
    if (!infile) { std::cerr << "Nelze otevřít input.wav\n"; return 1; }

/////////////vektor se vzorky
    std::vector<float> samples(info.frames * info.channels);
    sf_read_float(infile, samples.data(), samples.size());
    sf_close(infile);

/////////////vektor do kterého uložím výsledek
    std::vector<float> filtered(samples.size());

////////////přepínač mezi vysokofrekvenčním a nízkofrekvenčním
    bool lowPass = false;   // true = LPF, false = HPF

////////////zadání mezní frekvence
    float cutoff;
    std::cout << "Zadej mezni frekvenci (Hz): ";
    std::cin >> cutoff;

///////////Q faktor metoda Butterworth(prý se používá nejčastěji pro nejhladší průběh)
    float Q = 0.707f;

///////////výpočet úhlové frekvence
    float omega = 2.0f * M_PI * cutoff / info.samplerate;
    float sin_ = sin(omega);
    float cos_ = cos(omega);
    float alpha = sin_ / (2.0f * Q);

//////////koeficienty biquadu
    float b0, b1, b2, a0, a1, a2;

//////////koeficienty dle typu filtru
    if (lowPass) {
        b0 = (1 - cos_) / 2;
        b1 = 1 - cos_;
        b2 = (1 - cos_) / 2;
    }
    else {
        b0 = (1 + cos_) / 2;
        b1 = -(1 + cos_);
        b2 = (1 + cos_) / 2;
    }

//////////společné koeficienty
    a0 = 1 + alpha;
    a1 = -2 * cos_;
    a2 = 1 - alpha;

//////////normalizace koeficientů
    b0 /= a0;  b1 /= a0;  b2 /= a0;
    a1 /= a0;  a2 /= a0;

//////////stavové proměnné pro každý kanál zvlášť
    std::vector<float> x1(info.channels, 0.0f);
    std::vector<float> x2(info.channels, 0.0f);
    std::vector<float> y1(info.channels, 0.0f);
    std::vector<float> y2(info.channels, 0.0f);

//////////for cyklus filtrující vzorky
    for (size_t i = 0; i < samples.size(); i++) {

        int ch = i % info.channels;
        float x = samples[i];

//////////diferenční rovnice 2. řádu
        float y = b0 * x
                + b1 * x1[ch]
                + b2 * x2[ch]
                - a1 * y1[ch]
                - a2 * y2[ch];

//////////posun historie vzorků
        x2[ch] = x1[ch];
        x1[ch] = x;

        y2[ch] = y1[ch];
        y1[ch] = y;

//////////ochrana proti přetečení
        if (y > 1.0f) y = 1.0f;
        if (y < -1.0f) y = -1.0f;

        filtered[i] = y;
    }

////////////uložení vystupu
    SNDFILE* outfile = sf_open(outputName.c_str(), SFM_WRITE, &info);
    if (!outfile) { std::cerr << "Nelze vytvořit output.wav\n"; return 1; }

    sf_write_float(outfile, filtered.data(), filtered.size());
    sf_close(outfile);

////////////////dokončení a výpis uložení:
    std::cout << "Výsledek uložení: " << outputName << "\n";
    return 0;
}
