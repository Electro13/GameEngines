#include "Particle.h"

Particle::Particle(GLuint shaderProgram_, GLuint textureID_) {

}

Particle::~Particle() {

}

void Particle::Render(Camera* camera_) {
    
    glUniform1d(textureLoc, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glm::mat4 model;
    glm::vec4 distance = camera_->GetView() * model * glm::vec4(position, 1.0f);
    glm::vec4 attenuation = distance * glm::inversesqrt(0.1f);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0));
    model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(size * attenuation));
    glUniform4fv(colourLoc, 1, glm::value_ptr(glm::vec4(colour.r, colour.g, colour.b, 1.0f)));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, particleList.size());
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void Particle::SetDistance() {
    
}

void Particle::GenerateBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, particleList.size() * sizeof(ParticleVertex), &particleList[0], GL_STATIC_DRAW);

    //Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (GLvoid*)0);

    //Texture Coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (GLvoid*)offsetof(ParticleVertex, particleTextureCoords));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    modelLoc = glGetUniformLocation(particleShader, "model");
    projLoc = glGetUniformLocation(particleShader, "proj");
    textureLoc = glGetUniformLocation(particleShader, "inputTexture");
    colourLoc = glGetUniformLocation(particleShader, "tintColour");
}