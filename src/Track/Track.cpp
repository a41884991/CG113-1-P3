/* --- Track.cpp --- */

/* ------------------------------------------
author: User
date: 11/19/2024
------------------------------------------ */

#include "Track.h"
#include "ControlPoint/ControlPoint.h"
#include "ShaderProgram/ShaderProgram.h"

#define NODES_PER_LINE 10

Track::Track()
{
    // Constructor
    m_controlPoints.push_back(ControlPoint(glm::vec3(0.0, 2.0, 2.0), 0));
    m_controlPoints.push_back(ControlPoint(glm::vec3(2.0, 2.0, 0.0), 1));
    m_controlPoints.push_back(ControlPoint(glm::vec3(0.0, 2.0, -2.0), 2));
    m_controlPoints.push_back(ControlPoint(glm::vec3(-2.0, 2.0, 0.0), 3));

    trackMode = TrackMode::LINEAR;
}

Track::~Track()
{
    // Destructor
}

void Track::Render(ShaderProgram *program)
{
    for (auto &point : m_controlPoints)
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
    m_nodes.clear();

    ControlPoint startPoint = *m_controlPoints.end();
    ControlPoint endPoint;

    const float PERCENT = 1.0f / NODES_PER_LINE;

    for (auto &point : m_controlPoints)
    {
        endPoint = point;

        auto p1_pos = startPoint.getPosition();
        auto p2_pos = endPoint.getPosition();
        auto p1_rot = startPoint.getRotation();
        auto p2_rot = endPoint.getRotation();

        for (int i = 0; i < NODES_PER_LINE; ++i)
        {
            TrackNode currentNode;

            float t = i * PERCENT;

            currentNode.position = (1 - t) * p1_pos + t * p2_pos;
            currentNode.rotation = (1 - t) * p1_rot + t * p2_rot;

            m_nodes.push_back(currentNode);
        }

        startPoint = point;
    }
}