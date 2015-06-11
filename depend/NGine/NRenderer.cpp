#include "NRenderer.h"

/***************************************************************************************************************/
ularge NRenderer::dbg_verticesRendered = 0ul;
ularge NRenderer::dbg_avoidedTextureBinds = 0ul;
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::init(ushort width, ushort height, bool full) {

	init(width, height, 32, full);
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::init(ushort width, ushort height, ubyte bpp, bool full) {

	//Check for Validity of Input Parameters
	if(width == 0 || height == 0 || bpp < 8 || bpp % 8 != 0) {
		crash("Invalid Parameters for Renderer Initialization");
	}

	//Locally store Parameters
	m_windowWidth = width;
	m_windowHeight = height;
	m_bpp = bpp;
	m_fullscreen = full;

	//Create Window using OpenGL 2.1 Standard
    m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), string("Powered by NGine v").append(NGINE_VER), (full ? sf::Style::Fullscreen : sf::Style::Default), sf::ContextSettings(32, 0, 4, 2, 1));
	m_window.setVerticalSyncEnabled(false);
	m_window.setMouseCursorVisible(false);

    glEnable(GL_BLEND);
    glEnable(GL_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Initialize OpenGL
	glShadeModel(GL_SMOOTH);
	glClearDepth(1);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, m_windowWidth, m_windowHeight);
	glOrtho(0, m_windowWidth, m_windowHeight, 0, -1, 100);


	cout << "Successfully initialized OpenGL-2.1 Renderer with Parameters:" << endl;
	cout << "\t- Window Dimensions: " << m_windowWidth << "x" << m_windowHeight << endl;
	cout << "\t- Color Depth: " << (ushort)bpp << endl;
	cout << "\t- Full Screen: " << (m_fullscreen ? "YES" : "NO") << endl << endl;
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::handleEvents(void){

    while(m_window.pollEvent(m_event)){

        switch(m_event.type){

        case sf::Event::Closed:
            m_closeInvoked = true;
        break;

        default:
        break;

        }
    }
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::clearScreen(ubyte r, ubyte g, ubyte b) {

	glClearColor((float)r / 255.f, (float)g / 255.f, (float)b / 255.f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);

	NRenderer::dbg_verticesRendered = 0;
	NRenderer::dbg_avoidedTextureBinds = 0;
	m_frameBeginTime = m_clock.getElapsedTime().asMicroseconds();
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::present() {

	m_window.display();
	m_frameDur += m_clock.getElapsedTime().asMicroseconds() - m_frameBeginTime;
	m_frameCnt++;
	if(m_frameDur >= 1000000){
        m_framesPerSecond = (ushort)(roundf(1000000.f * (float)m_frameCnt / (float)m_frameDur));
        m_frameDur = m_frameCnt = 0;
	}
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::renderQuad(float left, float top, float width, float height)  const{

    glDisable(GL_TEXTURE_2D);
	glTranslatef(left + width / 2, top + height / 2, 0);

	glBegin(GL_QUADS);
	glVertex2f(-width / 2, -height / 2);
	glVertex2f(width / 2, -height / 2);
	glVertex2f(width / 2, height / 2);
	glVertex2f(-width / 2, height / 2);
	glEnd();

	NRenderer::dbg_verticesRendered += 4;

	glTranslatef(-left - width / 2, -top - height / 2, 0);
	glEnable(GL_TEXTURE_2D);
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::renderQuad(float left, float top, float width, float height, float angle) const {

    glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(left + width / 2, top + height / 2, 0);

	glRotatef(angle, 0, 0, 1);

	glBegin(GL_QUADS);
	glVertex2f(-width / 2, -height / 2);
	glVertex2f(width / 2, -height / 2);
	glVertex2f(width / 2, height / 2);
	glVertex2f(-width / 2, height / 2);
	glEnd();

	NRenderer::dbg_verticesRendered += 4;

	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::renderOval(float left, float top, float width, float height)  const{

    glDisable(GL_TEXTURE_2D);
	glTranslatef(left + width / 2, top + height / 2, 0);

	//Higher Step = Lower Precision = Less GPU Power required
	float step = 1.0f;

	//Percentage of Screen Space taken up by this Oval
	float screenPct = (PI * SQR((width + height) / 2)) / (m_windowWidth * m_windowHeight);
	if(screenPct > .5f) step = .5f;
	if(screenPct < .25f) step = 2.0f;
	if(screenPct < .1f) step = 4.0f;
	if(screenPct < .05f) step = 6.0f;
	if(screenPct < .025f) step = 12.0f; //Base Rendering Precision on visible Size of the Object

	glBegin(GL_TRIANGLE_FAN);
	for(float i=0; i<360; i+=step) {
		glVertex2f( cos(i / 180.0 * PI) * width / 2, sin(i / 180.0 * PI) * height / 2);
	}
	glEnd();

	NRenderer::dbg_verticesRendered += 360.0 / step;

	glTranslatef(-left - width / 2, -top - height / 2, 0);
	glEnable(GL_TEXTURE_2D);
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::renderOval(float left, float top, float width, float height, float angle) const{

    glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(left + width / 2, top + height / 2, 0);

	glRotatef(angle, 0, 0, 1);

	//Higher Step = Lower Precision = Less GPU Power required
	float step = 1.0f;

	//Percentage of Screen Space taken up by this Oval
	float screenPct = (PI * SQR((width + height) / 2)) / (m_windowWidth *m_windowHeight);
	if(screenPct > .5f) step = .5f;
	if(screenPct < .25f) step = 2.0f;
	if(screenPct < .1f) step = 4.0f;
	if(screenPct < .05f) step = 6.0f;
	if(screenPct < .025f) step = 12.0f; //Base Rendering Precision on visible Size of the Object

	glBegin(GL_TRIANGLE_FAN);
	for(float i=0.0f; i<360.0f; i+=step) {
		glVertex2f( cos(i / 180.0 * PI) * width / 2, sin(i / 180.0 * PI) * height / 2);
	}
	glEnd();

	NRenderer::dbg_verticesRendered += 360.0 / step;

	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::renderCircle(float x, float y, float radius) const{

    glDisable(GL_TEXTURE_2D);
	register float x_radius = radius, y_radius = radius;

	//Higher Step = Lower Precision = Less GPU Power required
	float step = 1.0f;

	//Percentage of Screen Space taken up by this Oval
	float screenPct = PI * SQR(radius) / (m_windowWidth * m_windowHeight);
	if(screenPct > .5f) step = .5f;
	if(screenPct < .25f) step = 2.0f;
	if(screenPct < .1f) step = 4.0f;
	if(screenPct < .05f) step = 6.0f;
	if(screenPct < .025f) step = 12.0f; //Base Rendering Precision on visible Size of the Object

	glBegin(GL_TRIANGLE_FAN);
	for(float i=0; i<360; i+=step) {
		glVertex2f(x + cos(i / 180.0 * PI) * x_radius, y + sin(i / 180.0 * PI) * y_radius);
	}
	glEnd();

	NRenderer::dbg_verticesRendered += 360.0 / step;
	glEnable(GL_TEXTURE_2D);
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::renderRegular(float x, float y, float radius, ubyte edges, bool pointy) const{

    glDisable(GL_TEXTURE_2D);
	register float x_radius = radius, y_radius = radius;

    //Amount of Partialization (~Shape Edge Count)
	float step = 360.f / edges;
    float start = pointy ? 0 : step / 2;

	glBegin(GL_TRIANGLE_FAN);
	for(float i = start; i < 360 + start; i += step) {
		glVertex2f(x + cos(i / 180.0 * PI) * x_radius, y + sin(i / 180.0 * PI) * y_radius);
	}
	glEnd();

	NRenderer::dbg_verticesRendered += edges;
	glEnable(GL_TEXTURE_2D);
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::renderTexQuad(const NTexture &tex, float left, float top, float width, float height) const{

    dbg_avoidedTextureBinds += (!tex.bind());

	glTranslatef(left + width / 2, top + height / 2, 0);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(-width / 2, -height / 2);

		glTexCoord2f(1, 0);
		glVertex2f(width / 2, -height / 2);

		glTexCoord2f(1, 1);
		glVertex2f(width / 2, height / 2);

		glTexCoord2f(0, 1);
		glVertex2f(-width / 2, height / 2);
	glEnd();

	glTranslatef(- left - width / 2, - top - height / 2, 0);

	NRenderer::dbg_verticesRendered += 4;
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::renderTexQuad(const NTexture &tex, float left, float top, float width, float height, float angle) const{

    dbg_avoidedTextureBinds += (!tex.bind());

	//Transform
	glTranslatef(left + width / 2, top + height / 2, 0);
	glRotatef(angle, 0, 0, 1);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(-width / 2, -height / 2);

		glTexCoord2f(1, 0);
		glVertex2f(width / 2, -height / 2);

		glTexCoord2f(1, 1);
		glVertex2f(width / 2, height / 2);

		glTexCoord2f(0, 1);
		glVertex2f(-width / 2, height / 2);
	glEnd();

    //Retransform
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-left - width / 2, -top - height / 2, 0);

    NRenderer::dbg_verticesRendered += 4;
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::renderSubtexQuad(const NTexture &tex, float left, float top, float width, float height, float u1, float v1, float u2, float v2) const{

    dbg_avoidedTextureBinds += (!tex.bind());

	glTranslatef(left + width / 2, top + height / 2, 0);

	glBegin(GL_QUADS);
		glTexCoord2f(u1, v1);
		glVertex2f(-width / 2, -height / 2);

		glTexCoord2f(u2, v1);
		glVertex2f(width / 2, -height / 2);

		glTexCoord2f(u2, v2);
		glVertex2f(width / 2, height / 2);

		glTexCoord2f(u1, v2);
		glVertex2f(-width / 2, height / 2);
	glEnd();

	glTranslatef(- left - width / 2, - top - height / 2, 0);

	NRenderer::dbg_verticesRendered += 4;
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::renderSubtexQuad(const NTexture &tex, float left, float top, float width, float height, float u1, float v1, float u2, float v2, float angle) const{

    dbg_avoidedTextureBinds += (!tex.bind());

    //Transform
	glTranslatef(left + width / 2, top + height / 2, 0);
	glRotatef(angle, 0, 0, 1);

	glBegin(GL_QUADS);
		glTexCoord2f(u1, v1);
		glVertex2f(-width / 2, -height / 2);

		glTexCoord2f(u2, v1);
		glVertex2f(width / 2, -height / 2);

		glTexCoord2f(u2, v2);
		glVertex2f(width / 2, height / 2);

		glTexCoord2f(u1, v2);
		glVertex2f(-width / 2, height / 2);
	glEnd();

	//Retransform
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-left - width / 2, -top - height / 2, 0);

    NRenderer::dbg_verticesRendered += 4;
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NRenderer::renderString(const NFont &font, float size, float left, float top, uint color, const string &text) {

    //Prepare Text Object
    sf::Text txt;
    txt.setString(text);
    txt.setPosition(left, top);
    txt.setFont(*(font.m_font));
    txt.setCharacterSize(size);
    sf::Color col;

    ubyte r, g, b, a;
    unpackRGBA(color, &r, &g, &b, &a);
    col.r = r; col.g = g; col.b = b; col.a = a;
    txt.setColor(col);

    m_window.pushGLStates();
    m_window.draw(txt);
    m_window.popGLStates();

    NRenderer::dbg_verticesRendered += 4;
}
/***************************************************************************************************************/
