//
// Created on 7/15/20.
//

#ifndef PACPAC_TIMEDEFFECT_H
#define PACPAC_TIMEDEFFECT_H

#include <chrono>
using namespace std::chrono_literals;

struct TimedEffect {
    enum Effect {
        CHANGE_DIRECTION,       // Change directions when the remaining time hits 0
    };

    std::chrono::microseconds total_duration = 1s;
    std::chrono::microseconds time_remaining = 1s;
    Effect effect;

    TimedEffect() : effect( CHANGE_DIRECTION ) {}
    explicit TimedEffect( const std::chrono::microseconds& time, Effect effect = CHANGE_DIRECTION ) : total_duration( time ), time_remaining( time ), effect( effect ) {}

    TimedEffect( const TimedEffect& ) = default;
    TimedEffect& operator =( const TimedEffect& ) = default;

    TimedEffect operator -=( const std::chrono::microseconds& time ) {
        time_remaining -= time;
        return *this;
    }

    operator std::chrono::microseconds() const {
        return time_remaining;
    }
};

#endif // PACPAC_TIMEDEFFECT_H
