#include <iostream>
#include "OpenGL.hpp"

OpenGL::OpenGL (void) : size(0, 0)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    throw std::runtime_error(std::string("Can't init SDL") + SDL_GetError());
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1)
    throw std::runtime_error(std::string("Can't init IMG") + SDL_GetError());
    if (TTF_Init() == -1)
    throw std::runtime_error(std::string("Can't init TTF") + SDL_GetError());
}

OpenGL::~OpenGL ()
{
    this->destroy();
    for (std::map<std::string, TTF_Font*>::iterator it = this->fonts.begin(); it != this->fonts.end(); ++it) {
        TTF_CloseFont(it->second);
    }
    for (std::map<std::string, SDL_Texture*>::iterator it = this->tex.begin(); it != this->tex.end(); ++it) {
        SDL_DestroyTexture(it->second);
    }
    TTF_Quit();
    SDL_Quit();
}

void  OpenGL::init(const std::string &name, Vector2 size, std::stack<AComponent*> cache)
{
    std::cout << "StartInit => Lib OpenGL" << std::endl;
    this->size = size;
    if (!(this->win = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, size.x * STEP, size.y * STEP, SDL_WINDOW_OPENGL)))
    throw std::runtime_error(std::string("Can't create Window") + SDL_GetError());
    this->gl = SDL_GL_CreateContext(this->win);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetSwapInterval(1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double)((size.x * STEP) / (double)(size.y * STEP)), 1, 1000);
    glEnable(GL_DEPTH_TEST);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    this->display(cache);
}

void    OpenGL::destroy()
{
    SDL_GL_DeleteContext(this->gl);
    SDL_DestroyWindow(this->win);
}

int OpenGL::eventManagment()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.key.type != SDL_KEYDOWN)
    return (-1);
    return (this->keyMap[event.key.keysym.scancode]);
}

void    OpenGL::drawCube(Vector2 pos, Vector2 size, Vector2 rot)
{
    glPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    glScalef((double)size.x / 2.0, (double)size.y / 2.0, 0.5);
    glRotatef(rot.x, 1, 0, 0);
    glRotatef(rot.y, 0, 1, 0);
    glBegin(GL_QUADS);
    glColor3ub(255,0,0); //face rouge
    glVertex3d(1,1,1);
    glVertex3d(1,1,-1);
    glVertex3d(-1,1,-1);
    glVertex3d(-1,1,1);
    glColor3ub(0,255,0); //face verte
    glVertex3d(1,-1,1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,1,-1);
    glVertex3d(1,1,1);
    glColor3ub(0,0,255); //face bleue
    glVertex3d(-1,-1,1);
    glVertex3d(-1,-1,-1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,-1,1);
    glColor3ub(255,255,0); //face jaune
    glVertex3d(-1,1,1);
    glVertex3d(-1,1,-1);
    glVertex3d(-1,-1,-1);
    glVertex3d(-1,-1,1);
    glColor3ub(0,255,255); //face cyan
    glVertex3d(1,1,-1);
    glVertex3d(1,-1,-1);
    glVertex3d(-1,-1,-1);
    glVertex3d(-1,1,-1);
    glColor3ub(255,0,255); //face magenta
    glVertex3d(1,-1,1);
    glVertex3d(1,1,1);
    glVertex3d(-1,1,1);
    glVertex3d(-1,-1,1);
    glEnd();
    glPopMatrix();
}

void OpenGL::display(std::stack<AComponent*> components)
{
    AComponent      *obj;
    GameComponent   *Gobj;
    UIComponent     *Uobj;
    BackgroundComponent   *Bobj;

    // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(50, 0, 20, 0, 0, 0, 0, 0, 1);
    glRotatef(-90, 0, 0, 1);
    glRotatef(180, 0, 1, 0);
    glTranslatef(-size.x / 2, -size.y / 2, -10);
    glRotatef(45, 1, 0, 0);

    while (!components.empty()) {
        obj = components.top();
        components.pop();
        if ((Gobj = dynamic_cast<GameComponent*>(obj))) {
            this->displayGame(*Gobj);
        } else if ((Uobj = dynamic_cast<UIComponent*>(obj))) {
            this->displayUI(*Uobj);
        } else if ((Bobj = dynamic_cast<BackgroundComponent*>(obj))) {
            this->displayBackground(*Bobj);
        } else {
            this->drawCube(obj->getPos(), obj->getSize(), Vector2(0, 0));
        }
    }
    SDL_GL_SwapWindow(this->win);
}

void    OpenGL::displayGame(const GameComponent &game)
{
    this->drawCube(game.getPos(), game.getSize(), Vector2(0, 0));
}

void    OpenGL::displayBackground(const BackgroundComponent &background)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(size.x / 2, size.y / 2 - 1, 1);
    glScalef((double)size.x / 2.0, (double)size.y / 2.0, 1);
    glBegin(GL_QUADS);
    glColor3ub(255, 180, 0);
    glVertex3d(1,-1,1);
    glVertex3d(1,1,1);
    glVertex3d(-1,1,1);
    glVertex3d(-1,-1,1);
    glEnd();
    glPopMatrix();
    for (int i = 0; i <= size.x; i++) {
        this->drawCube(Vector2(i, 0), Vector2(1, 1), Vector2(0, 0));
    }
    for (int i = 1; i < size.y; i++) {
        this->drawCube(Vector2(0, i), Vector2(1, 1), Vector2(0, 0));
        this->drawCube(Vector2(size.x, i), Vector2(1, 1), Vector2(0, 0));
    }
    for (int i = 0; i <= size.x; i++) {
        this->drawCube(Vector2(i, size.y), Vector2(1, 1), Vector2(0, 0));
    }
}

void    OpenGL::displayUI(const UIComponent &ui)
{
    // std::string     fontName;
    // unsigned int    colorInt;
    // SDL_Color       color;
    // SDL_Surface     *surface;
    // SDL_Texture     *texture;
    //
    // colorInt = this->colors[ui.getColor()];
    // color.r = ((colorInt) & 255);
    // color.g = ((colorInt >> 8) & 255);
    // color.b = ((colorInt >> 16) & 255);
    // color.a = ((colorInt >> 24) & 255);
    // fontName = ui.getFontName();
    // if (this->fonts[fontName] == 0) {
    //     this->fonts[fontName] = TTF_OpenFont(std::string("./assets/fonts/" + fontName + ".ttf").c_str(), ui.getFontSize());
    // }
    // surface = TTF_RenderText_Blended(fonts[fontName], ui.getText().c_str(), color);
    // texture = SDL_CreateTextureFromSurface(this->render, surface);
    // SDL_FreeSurface(surface);
    // if (ui.getPos().x < 0 || ui.getPos().y < 0)
    // {
    //   rect->x = this->size.x * STEP / 2 - ui.getFontSize() * ui.getText().length() / 4;
    //   rect->y = STEP;
    // }
    // SDL_QueryTexture(texture, NULL, NULL, &(rect->w), &(rect->h));
    // SDL_RenderCopy(this->render, texture, NULL, rect);
    // SDL_DestroyTexture(texture);
}

void sound()
{

}
