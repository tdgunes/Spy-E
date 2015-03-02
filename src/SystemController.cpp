#include "SystemController.h"
#include "System.h"

SystemController::SystemController() {
    currentState = NULL;
}

SystemController::~SystemController() {
}

void SystemController::update(float dt) {
    for (auto system: coreSystems) {
        system->update(dt);
    }

    if (currentState != NULL) {
        for (auto system: *currentState) {
            system->update(dt);
        }
    }
}

void SystemController::draw() {
    for (auto system: coreSystems) {
        system->draw();
    }

    if (currentState != NULL) {
        for (auto system: *currentState) {
            system->draw();
        }
    }
}

void SystemController::setState(std::string name) {
    std::map<std::string, std::vector<System*>>::iterator state = gameStates.find(name);
    if (state != gameStates.end()) {
        currentState = &state->second;
    }
}

void SystemController::addCoreSystem(System *s) {
    coreSystems.push_back(s);
}

