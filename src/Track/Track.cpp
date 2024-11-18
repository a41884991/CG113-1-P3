/* --- Track.cpp --- */

/* ------------------------------------------
author: User
date: 11/19/2024
------------------------------------------ */

#include "Track.h"
#include "ControlPoint/ControlPoint.h"
#include "ShaderProgram/ShaderProgram.h"

Track::Track()
{
    // Constructor
    m_points.push_back(ControlPoint(glm::vec3(0.0, 2.0, 2.0), 0));
    m_points.push_back(ControlPoint(glm::vec3(2.0, 2.0, 0.0), 1));
    m_points.push_back(ControlPoint(glm::vec3(0.0, 2.0, -2.0), 2));
    m_points.push_back(ControlPoint(glm::vec3(-2.0, 2.0, 0.0), 3));

    trackMode = TrackMode::LINEAR;
}

Track::~Track()
{
    // Destructor
}

void Track::Render(ShaderProgram *program)
{
    for (auto &point : m_points)
    {
        point.Render(program);
    }
}

void Track::setTrackMode(const TrackMode &newTrackMode)
{
    trackMode = newTrackMode;
}

void Track::updateTrack()
{
    switch (trackMode)
    {
    case TrackMode::LINEAR: // linear
        createLinearTrack();
        break;

    default:
        break;
    }
}

void Track::createLinearTrack()
{
    ControlPoint startPoint = *m_points.end();
    ControlPoint endPoint;

    for (auto &point : m_points)
    {
        endPoint = point;
    }
}