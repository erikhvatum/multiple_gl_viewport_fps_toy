#pragma once

#include <chrono>
#include <list>
#include <QString>

class FPSCounter
{
public:
    static const std::size_t sm_sample_count;

    void query_update(double& mean, double& stddev);
    QString qstring_query_update();

protected:
    typedef std::chrono::time_point<std::chrono::system_clock> Sample;
    typedef std::list<Sample> Samples;

    Samples m_samples;
};
