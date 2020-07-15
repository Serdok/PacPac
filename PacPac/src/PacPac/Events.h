//
// Created on 7/15/20.
//

#ifndef PACPAC_EVENTS_H
#define PACPAC_EVENTS_H

/**
 * Basic event interface
 */
class IEvent {
protected:
    IEvent() = default;
};

/**
 * Game ended
 */
class GameEnd : public IEvent {
public:
    GameEnd() = default;
};

/**
 * Update directions
 */
class UpdateDirection : public IEvent {
public:
    UpdateDirection() = default;
};

#endif // PACPAC_EVENTS_H
