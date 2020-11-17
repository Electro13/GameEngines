#include "Particle.h"

Particle::Particle(GLuint shaderProgram_, GLuint textureID_) {
    particleShader = shaderProgram_;
    size = 5;
    velocity = glm::vec3(1.5f);
    colour = glm::vec3(1, 0, 0);
    GenerateBuffers();
}

Particle::~Particle() {

}

void Particle::Render(Camera* camera_) {
    glEnable(GL_PROGRAM_POINT_SIZE);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
    //glUniform1d(textureLoc, 0);
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, textureID);
    glm::mat4 model;
    //glm::vec4 distance = camera_->GetView() * model * glm::vec4(position, 1.0f);
    //glm::vec4 attenuation = distance * glm::inversesqrt(0.1f);
    model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
    //model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
    //model = glm::scale(model, glm::vec3(size * attenuation));
    glUniform3fv(colourLoc, 1, glm::value_ptr(colour));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
    glUniform1f(pointSize, size);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
    glDisable(GL_PROGRAM_POINT_SIZE);
    //glBindTexture(GL_TEXTURE_2D, 0);

}

void Particle::Update(const float deltaTime_) {
    lifeTime -= deltaTime_;
    position = deltaTime_ * velocity;
}

void Particle::GenerateBuffers() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    ////Texture Coordinates
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (GLvoid*)offsetof(ParticleVertex, particleTextureCoords));

    glBindVertexArray(0);

    modelLoc = glGetUniformLocation(particleShader, "model");
    projLoc = glGetUniformLocation(particleShader, "proj");
    viewLoc = glGetUniformLocation(particleShader, "view");
    /*textureLoc = glGetUniformLocation(particleShader, "inputTexture");*/
    colourLoc = glGetUniformLocation(particleShader, "tintColour");
    pointSize = glGetUniformLocation(particleShader, "Size");
}