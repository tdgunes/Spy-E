//
// Created by Taha Doğan Güneş on 02/04/15.
//

#include "graphics/ui/View.h"

View::View() {
    hidden = false;
}

void View::addSubview(View* view) {
    this->subViews.push_back(view);
    this->setSystem(this->system);
    printf("[GUI] Added a subview count: %lu\n", this->subViews.size());
    std::string viewTag = view->getTag();
    if (!viewTag.empty()) {
        this->viewMap[viewTag] = view;
    }
}

View* View::viewWithTag(std::string tag){
    std::map<std::string, View*>::iterator iterator = this->viewMap.find(tag);
    View* view = NULL;

    if (iterator != this->viewMap.end()) {
        view = iterator->second;
    }
    else {
        printf("[GUI][View] Does not have a view with tag: %s \n", tag.c_str());
    }

    return view;
}

void View::setTag(std::string tag) {
    this->tag = tag;
}

std::string View::getTag(){
    return this->tag;
}

void View::draw() {
    if (!hidden) {
        for (auto subView : subViews) {
            subView->draw();
        }
    }
}

void View::setSystem(GUI *system) {
    this->system = system;
    for (auto subView : subViews) {
        subView->setSystem(system);
    }
}

GUI *View::getSystem() {
    return this->system;
}

void View::setFrame(Rect frame) {
    this->frame = frame;
}


void View::setFrame(float x, float y, float w, float h) {
    this->setFrame(Rect(x,y,w,h));
}


bool View::isMouseInside() {
    float mouseX = this->getSystem()->getInput()->getMouse()->mouseX;
    float mouseY = this->getSystem()->getInput()->getMouse()->mouseY;
    bool inside = this->frame.x < mouseX &&
                   this->frame.y < mouseY &&
                   this->frame.x + this->frame.w > mouseX &&
                   this->frame.y + this->frame.h > mouseY;
    return inside;
}

void View::handleEvents() {
    if(this->isMouseInside()) {
        for (auto subView : subViews)
            subView->handleEvents();
    }
}


View::~View() {
    for (auto subView : subViews) {
        delete subView;
    }
}

Rect View::getFrame() {
    return this->frame;
}
