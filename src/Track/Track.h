/* --- Track.h --- */

/* ------------------------------------------
Author: User
Date: 11/19/2024
------------------------------------------ */

#ifndef TRACK_H
#define TRACK_H

#include <glm.hpp>
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
    void createTrackObject();

private:
    struct TrackNode{
        glm::vec3 position;
        glm::vec3 rotation;
    };

    struct TrackObject{
        GLuint VAO;
        GLuint VBO;
        glm::mat4 model;
    };

    std::vector<TrackNode> m_nodes;
    std::vector<TrackObject> m_trackObjects;
    std::vector<ControlPoint> m_controlPoints;
    TrackMode trackMode;
};

#endif // TRACK_H
