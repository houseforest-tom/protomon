#include "NBase.h"
#include "NRenderer.h"
#include "NKeyboard.h"
#include "NMouse.h"
#include "NTextureManager.h"
#include "NFontManager.h"
#include "NField.h"
#include "NTransform2D.h"
#include "NGameObject.h"

//NGine v0.3 Testbed Implementation

void renderStats (NRenderer &gfx, const NFontManager &fmgr, const NMouse &mouse);
void renderCursor(NRenderer &gfx, const NMouse &mouse);

int main(int argc, char *argv[]) {


    float     deltaTime  = 0;
    uint64_t  lastTime   = 0;


	//Initialize Window & Renderer
	NRenderer gfx;
	gfx.init(1280, 720, false);


    //Load Texture(s)
    NTextureManager texmgr;
    texmgr.loadAsset("stuff", "res/stuff.png");
    texmgr.loadAsset("crate", "res/crate.png");
    if(!texmgr.containsAsset("stuff")) crash("Error Texture could not be loaded");
    texmgr.setErrorKey("stuff");


    //Load Font(s)
    NFontManager fontmgr;
    fontmgr.loadAsset("default", "res/landt.ttf");



    //Initialize Input Devices
	NKeyboard kb;
	kb.init();
	NMouse mouse;
	mouse.init(gfx.getWindowWidth(), gfx.getWindowHeight());


    uint objCnt = 5000;
    NGameObject objects[objCnt];
    ubyte colors[objCnt][3];
    for(uint i=0; i<objCnt; ++i){

        NTransform2D &objTr = objects[i].getTransform();

        objTr.x  = rand() % gfx.getWindowWidth();
        objTr.y  = rand() % gfx.getWindowWidth();
        objTr.vx = -50.f + (rand() % 1000) / 10.f;  //[-5....+5]
        objTr.vy = -50.f + (rand() % 1000) / 10.f;
        objTr.ax = -5 + (rand() % 100) / 10.f; //[-.5..+.5]
        objTr.ay = -5 + (rand() % 100) / 10.f;
        objTr.rotation = rand() % 360;

        for(uint j=0; j<3; ++j)
            colors[i][j] = rand() % 255;
    }

	while(!gfx.wasWindowClosed() && !kb.wasKeyPressed(sf::Keyboard::Escape)) {

        /*******************************************************************************************************************************************************/
        /* UPDATE **********************************************************************************************************************************************/
        /*******************************************************************************************************************************************************/

		kb.update();
		mouse.update(gfx);

        /*******************************************************************************************************************************************************/



        /*******************************************************************************************************************************************************/
        /* RENDER **********************************************************************************************************************************************/
        /*******************************************************************************************************************************************************/

		gfx.clearScreen(0, 0, 0);
		glColor4f(1, 1, 1, 1);
		float r = 8;

        for(uint i=0; i<objCnt; ++i){

            NTransform2D &objTr = objects[i].getTransform();

            if(objTr.x < r || objTr.x > gfx.getWindowWidth() - r){ objTr.vx *= -1; }
            if(objTr.y < r || objTr.y > gfx.getWindowHeight() - r){ objTr.vy *= -1; }

            glColor3ubv(colors[i]);

            gfx.renderRegular(objTr.x, objTr.y, r, 5);

            objTr.update(deltaTime);
        }

        renderStats(gfx, fontmgr, mouse);
        renderCursor(gfx, mouse);

		gfx.present();

		/*******************************************************************************************************************************************************/

		deltaTime = (gfx.getElapsedTime() - lastTime) / 1000000.f;
		lastTime = gfx.getElapsedTime();

		if( deltaTime == 0 ) deltaTime = 1 / 1000000.f;
	}

	//Fix unused Variable Bullshit
	return (0 * argc * (int)argv);
}
/*******************************************************************************************************************************************************/


/*******************************************************************************************************************************************************/
void renderStats(NRenderer &gfx, const NFontManager &fmgr, const NMouse &mouse){

    NTextBuffer<128> buf;
    const NFont &font   = fmgr.getAsset("default");
    uint  textColor     = gfx.packRGB(3, 254, 49);

    sprintf(buf, "FPS: %03u", gfx.getFPS());
    gfx.renderString(font, 14, 10, 10, textColor, buf);

    sprintf(buf, "Resolution");
    gfx.renderString(font, 14, gfx.getWindowWidth() - 250, 10, textColor, buf);
    sprintf(buf, "Engine: %ux%u", gfx.getWindowWidth(), gfx.getWindowHeight());
    gfx.renderString(font, 14, gfx.getWindowWidth() - 200, 36, textColor, buf);
    sprintf(buf, "Client:   %ux%u", gfx.getWindowWidth(), gfx.getWindowHeight());
    gfx.renderString(font, 14, gfx.getWindowWidth() - 200, 62, textColor, buf);

    sprintf(buf, "Mouse: {%04u|%04u}", mouse.getX(), mouse.getY());
    gfx.renderString(font, 16, gfx.getWindowWidth() - 200, gfx.getWindowHeight() - 100, textColor, buf);
}
/*******************************************************************************************************************************************************/


/*******************************************************************************************************************************************************/
void renderCursor(NRenderer &gfx, const NMouse &mouse){

    glColor4f(1, 1, 1, 1);
    gfx.renderRegular(mouse.getX(), mouse.getY(), 5, 8);
}
/*******************************************************************************************************************************************************/
