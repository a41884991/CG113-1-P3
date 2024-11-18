/* --- Track.h --- */

/* ------------------------------------------
Author: User
Date: 11/19/2024
------------------------------------------ */

#ifndef TRACK_H
#define TRACK_H

#include <vector>
#include "DataStructure.h"

class ControlPoint;
class ShaderProgram;

class Track
{
public:
    Track();
    ~Track();

    void Render(ShaderProgram *program);

    void setTrackMode(const TrackMode &newTrackMode);

private:
    void updateTrack();

    void createLinearTrack();

private:
    std::vector<ControlPoint> m_points;
    TrackMode trackMode;
};

#endif // TRACK_H
