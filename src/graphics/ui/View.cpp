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
    printf("[GUI] Added a subview count: %i\n", this->subViews.size());

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


View::~View() {

    for (auto subView : subViews) {
        delete subView;
    }

}
