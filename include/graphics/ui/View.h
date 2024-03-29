
#ifndef SPYE_VIEW_H
#define SPYE_VIEW_H

#include "graphics/ui/Primitives.h"
#include "graphics/ui/GUI.h"
#include "input/Mouse.h"
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <string>

class Image;

class View {

protected:
    Rect frame = Rect(0, 0, 0, 0);

private:
    GUI *system;
    std::map<std::string, View*> viewMap;
    std::string tag;

public:
    bool hidden;
    View();
    ~View();
    std::vector<View *> subViews;
    Color color = Color(0, 0, 0);
    Image *backgroundImage;
    GUI *getSystem();

    virtual bool isMouseInside();
    virtual void addSubview(View *view);
    virtual void setSystem(GUI *system);
    virtual void setFrame(Rect frame);
    virtual void setFrame(float x, float y, float w, float h);
    virtual Rect getFrame();
    virtual void draw();
    virtual void setTag(std::string tag);
    virtual std::string getTag();
    virtual View *viewWithTag(std::string tag);

    void handleEvents();
};


#endif //SPYE_VIEW_H
