#version 460

out uint outID;

uniform int ID;

void main(void) {
    outID = ID;
}