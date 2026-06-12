#include "SampleController.h"

void SampleController::addSample(const Sample& sample) {
    samples_.push_back(sample);
}

const std::vector<Sample>& SampleController::getAll() const {
    return samples_;
}

std::vector<Sample>& SampleController::getAll() {
    return samples_;
}

Sample* SampleController::findById(const std::string& id) {
    for (auto& s : samples_) {
        if (s.id == id) return &s;
    }
    return nullptr;
}

std::vector<const Sample*> SampleController::searchByName(const std::string& keyword) const {
    std::vector<const Sample*> result;
    for (const auto& s : samples_) {
        if (s.name.find(keyword) != std::string::npos)
            result.push_back(&s);
    }
    return result;
}

int SampleController::getTotalStock() const {
    int total = 0;
    for (const auto& s : samples_) total += s.stock;
    return total;
}

int SampleController::getSampleCount() const {
    return static_cast<int>(samples_.size());
}
