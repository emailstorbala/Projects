#include <iostream>
#include <fmt/format.h>

using std::cout;
using std::endl;
using fmt::format;

class Sample {
    public:
        Sample(void) = default;
        Sample(int x);
        //void IncrementSampleByOne(void) = delete;
        void IncrementSampleByOne(void);

        int sampleId = 0;
};

Sample::Sample(int x) {
    this->sampleId = x;
}

void Sample::IncrementSampleByOne(void) {
    this->sampleId++;
}


int main() {
    Sample sample;
    sample.IncrementSampleByOne();
    cout << format("Sample id is {}", sample.sampleId) << endl;

    return EXIT_SUCCESS;
}
