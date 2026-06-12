#pragma once
#include <vector>
#include <string>
#include "../model/Sample.h"

class SampleController {
public:
    void addSample(const Sample& sample);
    const std::vector<Sample>& getAll() const;
    std::vector<Sample>& getAll();
    Sample* findById(const std::string& id);
    std::vector<const Sample*> searchByName(const std::string& keyword) const;
    int getTotalStock() const;
    int getSampleCount() const;

private:
    std::vector<Sample> samples_;
};
