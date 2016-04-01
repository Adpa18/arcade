#include <iostream>
#include "OpenGL.hpp"

OpenGL::OpenGL (void) : size(ArcadeSystem::winWidth, ArcadeSystem::winHeight)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("Can't init SDL") + SDL_GetError());
    }
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1) {
        throw std::runtime_error(std::string("Can't init IMG") + SDL_GetError());
    }
    if (TTF_Init() == -1) {
        throw std::runtime_error(std::string("Can't init TTF") + SDL_GetError());
    }
    if (!(this->win = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x * STEP, size.y * STEP, SDL_WINDOW_OPENGL))) {
        throw std::runtime_error(std::string("Can't create Window") + SDL_GetError());
    }
    if (!(this->fonts["default"] = TTF_OpenFont("/usr/share/fonts/truetype/DejaVuSans.ttf", STEP))) {
        this->fonts["default"] = TTF_OpenFont("/usr/share/fonts/dejavu/DejaVuSans.ttf", STEP);
    }
    this->gl = SDL_GL_CreateContext(this->win);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetSwapInterval(1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gluPerspective(70, (double)((size.x * STEP) / (double)(size.y * STEP)), 1, 1000);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

OpenGL::~OpenGL ()
{
    for (std::map<std::string, TTF_Font*>::iterator it = this->fonts.begin(); it != this->fonts.end(); ++it) {
        TTF_CloseFont(it->second);
    }
    for (std::map<std::string, SDL_Surface*>::iterator it = this->tex.begin(); it != this->tex.end(); ++it) {
        SDL_FreeSurface(it->second);
    }
    fonts.clear();
    tex.clear();
    SDL_GL_DeleteContext(this->gl);
    SDL_DestroyWindow(this->win);
    TTF_Quit();
    SDL_Quit();
}

// void  OpenGL::init(const std::string &name, std::stack<AComponent*> cache)
// {
//     this->setTitle(name);
//     this->display(cache);
// }
//
// void  OpenGL::init(const std::string &name)
// {
//     this->setTitle(name);
// }

void    OpenGL::setTitle(const std::string &title)
{
    SDL_SetWindowTitle(this->win, title.c_str());
}

int OpenGL::eventManagment()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.key.type != SDL_KEYDOWN)
        return (-1);
    if (this->keyMap[event.key.keysym.scancode])
        return (this->keyMap[event.key.keysym.scancode]);
    return (event.key.keysym.sym);
}

void    OpenGL::drawCube(Vector2<double> pos, Vector2<double> size, Vector2<double> rot, const std::string &texName)
{
    bool    isTextured = loadTexture(texName);
    glPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    glScalef((double)size.x / 2.0, (double)size.y / 2.0, 0.5);
    glRotatef(rot.x, 1, 0, 0);
    glRotatef(rot.y, 0, 1, 0);
    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    if (!isTextured) {
        glColor3ub(255,0,0); //face rouge
    }
    glTexCoord2i(0,1); glVertex3i(1,1,1);
    glTexCoord2i(0,0); glVertex3i(1,1,-1);
    glTexCoord2i(1,0); glVertex3i(-1,1,-1);
    glTexCoord2i(1,1); glVertex3i(-1,1,1);
    if (!isTextured) {
        glColor3ub(0,255,0); //face verte
    }
    glTexCoord2i(0,1); glVertex3i(1,-1,1);
    glTexCoord2i(0,0); glVertex3i(1,-1,-1);
    glTexCoord2i(1,0); glVertex3i(1,1,-1);
    glTexCoord2i(1,1); glVertex3i(1,1,1);
    if (!isTextured) {
        glColor3ub(0,0,255); //face bleue
    }
    glTexCoord2i(0,1); glVertex3i(-1,-1,1);
    glTexCoord2i(0,0); glVertex3i(-1,-1,-1);
    glTexCoord2i(1,0); glVertex3i(1,-1,-1);
    glTexCoord2i(1,1); glVertex3i(1,-1,1);
    if (!isTextured) {
        glColor3ub(255,255,0); //face jaune
    }
    glTexCoord2i(0,1); glVertex3i(-1,1,1);
    glTexCoord2i(0,0); glVertex3i(-1,1,-1);
    glTexCoord2i(1,0); glVertex3i(-1,-1,-1);
    glTexCoord2i(1,1); glVertex3i(-1,-1,1);
    if (!isTextured) {
        glColor3ub(0,255,255); //face cyan
    }
    glTexCoord2i(0,1); glVertex3i(1,1,-1);
    glTexCoord2i(0,0); glVertex3i(1,-1,-1);
    glTexCoord2i(1,0); glVertex3i(-1,-1,-1);
    glTexCoord2i(1,1); glVertex3i(-1,1,-1);
    if (!isTextured) {
        glColor3ub(255,0,255); //face magenta
    }
    glTexCoord2i(0,1); glVertex3i(1,-1,1);
    glTexCoord2i(0,0); glVertex3i(1,1,1);
    glTexCoord2i(1,0); glVertex3i(-1,1,1);
    glTexCoord2i(1,1); glVertex3i(-1,-1,1);
    glEnd();
    glPopMatrix();
    if (isTextured)
        glDeleteTextures(1, &texture);
}

void OpenGL::display(std::stack<AComponent*> components)
{
    SDL_Rect            rect;
    AComponent          *obj;
    GameComponent       *Gobj;
    UIComponent         *Uobj;
    UIAdvanceComponent  *UAobj;
    BackgroundComponent *Bobj;
    HighScoreComponent  *Hobj;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(30, 0, 10, 0, 0, 0, 0, 0, 1);
    glRotatef(-90, 0, 0, 1);
    glRotatef(180, 0, 1, 0);
    glTranslatef(-size.x / 2, -size.y / 2, -10);
    glRotatef(30, 1, 0, 0);

    while (!components.empty()) {
        obj = components.top();
        components.pop();
        rect.x = obj->getPos().x;
        rect.y = obj->getPos().y;
        if ((Gobj = dynamic_cast<GameComponent*>(obj))) {
            this->displayGame(*Gobj);
        } else if ((Uobj = dynamic_cast<UIComponent*>(obj))) {
            this->displayUI(*Uobj, &rect);
        } else if ((UAobj = dynamic_cast<UIAdvanceComponent*>(obj))) {
            this->displayAdvanceUI(*UAobj, &rect);
        } else if ((Hobj = dynamic_cast<HighScoreComponent*>(obj))) {
            this->displayHighScore(Hobj->getComponentsToDisplay());
        } else if ((Bobj = dynamic_cast<BackgroundComponent*>(obj))) {
            this->displayBackground(*Bobj);
        } else {
            this->drawCube(obj->getPos(), Vector2<double>(1, 1), Vector2<double>(0, 0), "");
        }
    }
    SDL_GL_SwapWindow(this->win);
}

void    OpenGL::displayHighScore(UIComponent const * const *uiComponents)
{
    SDL_Rect    rect;

    for (size_t i = 0; i < HighScoreComponent::componentNb && uiComponents[i] != NULL; i++) {
        rect.x = uiComponents[i]->getPos().x;
        rect.y = uiComponents[i]->getPos().y;
        displayUI(*uiComponents[i], &rect);
    }
}

void    OpenGL::displayUI(const UIComponent &ui, SDL_Rect *rect)
{
    unsigned int    colorInt;
    SDL_Color       color;
    SDL_Surface     *surface;

    colorInt = this->colors[ui.getColor()];
    color.r = ((colorInt) & 255);
    color.g = ((colorInt >> 8) & 255);
    color.b = ((colorInt >> 16) & 255);
    color.a = ((colorInt >> 24) & 255);
    if (ui.getText().empty() || !this->fonts["default"]) {
        return;
    }
    surface = TTF_RenderText_Blended(this->fonts["default"], ui.getText().c_str(), color);
    this->loadSurface(surface);
    SDL_FreeSurface(surface);
    glPushMatrix();
    rect->w = ui.getText().length();
    rect->h = 2;
    glRotatef(45, 1, 0, 0);
    glTranslatef(this->size.x / 2, -this->size.y / 2 + rect->y, 0);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex3i(-rect->w, -rect->h, 1);
    glTexCoord2i(1, 0);
    glVertex3i(rect->w, -rect->h, 1);
    glTexCoord2i(1, 1);
    glVertex3i(rect->w, rect->h, 1);
    glTexCoord2i(0, 1);
    glVertex3i(-rect->w, rect->h, 1);
    glEnd();
    glPopMatrix();
    glDeleteTextures(1, &texture);
}

void    OpenGL::displayAdvanceUI(const UIAdvanceComponent &ui, SDL_Rect *rect)
{
    std::string     fontName;
    unsigned int    colorInt;
    SDL_Color       color;
    SDL_Surface     *surface;

    colorInt = this->colors[ui.getColor()];
    color.r = ((colorInt) & 255);
    color.g = ((colorInt >> 8) & 255);
    color.b = ((colorInt >> 16) & 255);
    color.a = ((colorInt >> 24) & 255);
    fontName = ui.getFontName();
    if (this->fonts[fontName] == 0) {
        this->fonts[fontName] = TTF_OpenFont(std::string("./assets/fonts/" + fontName + ".ttf").c_str(), ui.getFontSize());
    }
    surface = TTF_RenderText_Blended(fonts[fontName], ui.getText().c_str(), color);
    this->loadSurface(surface);
    SDL_FreeSurface(surface);
}

void    OpenGL::displayGame(const GameComponent &game)
{
    this->drawCube(game.getPos(), game.getDim(), Vector2<double>(0, 0), game.getSprite2D());
}

void    OpenGL::displayBackground(const BackgroundComponent &background)
{
    glPushMatrix();
    loadTexture(background.getSprite2D());
    glTranslatef(size.x / 2, size.y / 2 - 1, 0);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex3i(-size.x / 2, -size.y / 2, 1);
    glTexCoord2i(size.x / 2, 0);
    glVertex3i(size.x / 2, -size.y / 2, 1);
    glTexCoord2i(size.x / 2, size.y / 2);
    glVertex3i(size.x / 2, size.y / 2, 1);
    glTexCoord2i(0, size.y / 2);
    glVertex3i(-size.x / 2, size.y / 2, 1);
    glEnd();
    glPopMatrix();
    glDeleteTextures(1, &texture);
}

void sound()
{

}

bool           OpenGL::loadTexture(const std::string &sprite2D)
{
    if (sprite2D.empty()) {
        return (false);
    }
    if (this->tex[sprite2D] == 0) {
        this->tex[sprite2D] = IMG_Load(std::string("./assets/sprites2D/" + sprite2D).c_str());
    }
    return (this->loadSurface(this->tex[sprite2D]));
}

bool           OpenGL::loadSurface(SDL_Surface *surface)
{
    GLenum      format;

    if (!surface) {
        return (false);
    }
    if (surface->format->BytesPerPixel == 4) {
        format = (surface->format->Rmask == 0x000000ff) ? GL_RGBA : GL_BGRA;
    } else if (surface->format->BytesPerPixel == 3) {
        format = (surface->format->Rmask == 0x000000ff) ? GL_RGB : GL_BGR;
    } else {
        return (false);
    }
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, surface->format->BytesPerPixel,surface->w,
            surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
    return (true);
}
