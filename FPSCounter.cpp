#include <cmath>
#include <cstdint>
#include <iostream>
#include "FPSCounter.h"

const std::size_t FPSCounter::sm_sample_count = 51;

void FPSCounter::query_update(double& mean, double& stddev)
{
    m_samples.push_back(std::chrono::high_resolution_clock::now());
    if(m_samples.size() <= 2)
    {
        stddev = mean = std::nan("");
    }
    else
    {
        for(; m_samples.size() > sm_sample_count; m_samples.pop_front());
        std::int64_t sum_nanoseconds = 0;
        double sum_fps{0.0};
        Samples::const_iterator sample_it{m_samples.cbegin()};
        Samples::const_iterator prev_sample_it{sample_it};
        ++sample_it;
        std::int64_t delta_nanoseconds;
        double fps;
        for(; sample_it != m_samples.cend(); ++sample_it)
        {
            auto f = *sample_it - *prev_sample_it;
            delta_nanoseconds = std::chrono::nanoseconds(f).count();
            sum_nanoseconds += delta_nanoseconds;
            fps = 1e9 / static_cast<double>(delta_nanoseconds);
            sum_fps += fps * fps;
            prev_sample_it = sample_it;
        }
        mean = ((sm_sample_count - 1) / static_cast<double>(sum_nanoseconds) * 1e9);
        stddev = std::sqrt(sum_fps / (sm_sample_count - 1) - mean * mean);
    }
}

QString FPSCounter::qstring_query_update()
{
    QString ret;
    double mean, stddev;
    query_update(mean, stddev);
    if(std::isnan(mean))
        ret = QString("need %1 more samples").arg(2 - m_samples.size());
    else
        ret = QString(u8"FPS: mean=%1 σ=%2 n=%3").arg(mean, 8, 'f').arg(stddev, 8, 'f').arg(m_samples.size()-1);
    return ret;
}
