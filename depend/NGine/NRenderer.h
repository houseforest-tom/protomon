#ifndef NGINE_RENDERER_HDR
#define NGINE_RENDERER_HDR

/***************************************************************************************************************/
#include "NBase.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include "NTexture.h"
#include "NFont.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

/***************************************************************************************************************/

///Provides several Functions concerning Graphics
///Only usable on SFML & OpenGL2.1+ compatible Hardware
class NRenderer {
    friend class NMouse;

private:

	///Target Window Dimensions
	ushort m_windowWidth = 0, m_windowHeight = 0;

	///Viewport Ratio
	float m_ratio = 16.0f / 9.0f;

	///Bits per Pixel Rate
	ubyte m_bpp = 32;

	///Fullscreen Flag
	bool m_fullscreen = false;

	///SFML Window Interface
	sf::RenderWindow m_window;

	///Elapsed Game Time
	sf::Clock m_clock;

	///Window Event Buffer
	sf::Event m_event;

	///Was Window Close Message dispatched
	bool m_closeInvoked = false;

    ///Frames per Second Calculation
	ularge m_frameBeginTime = 0, m_frameCnt = 0, m_frameDur = 0;
	ushort m_framesPerSecond = 0;

public:

	///Vertices renderered last Frame
	static ularge dbg_verticesRendered, dbg_avoidedTextureBinds;

	///Initialize a new 32-Bit RGBA Format SFML OpenGL Renderer
	void init(ushort width, ushort height, bool full);

	///Initialize a new SFML OpenGL Renderer with given BPP Rate
	void init(ushort width, ushort height, ubyte bpp, bool full);

	///Dispatch Window Messages
	void handleEvents(void);

	///Clear the Screen Surface
	void clearScreen(ubyte r, ubyte g, ubyte b);

	///Update the Back Buffer
	void present(void);

	///Render a Quad
	void renderQuad(float left, float top, float width, float height) const;
	void renderQuad(float left, float top, float width, float height, float angle) const;

	///Render an Oval
	void renderOval(float left, float top, float width, float height) const;
	void renderOval(float left, float top, float width, float height, float angle) const;

	///Render a Circle
	void renderCircle(float x, float y, float radius) const;

	///Render a regular Polygon
	void renderRegular(float x, float y, float radius, ubyte edges, bool pointy = false) const;

	///Render a textured Quad
	void renderTexQuad(const NTexture &tex, float left, float top, float width, float height) const;
	void renderTexQuad(const NTexture &tex, float left, float top, float width, float height, float angle) const;
	void renderSubtexQuad(const NTexture &tex, float left, float top, float width, float height, float u1, float v1, float u2, float v2) const;
	void renderSubtexQuad(const NTexture &tex, float left, float top, float width, float height, float u1, float v1, float u2, float v2, float angle) const;

	///Render a String
	void renderString(const NFont &font, float size, float left, float top, uint color, const string &text);

	///Return Window Dimensions
	inline ushort getWindowWidth(void) const { return m_windowWidth; }
	inline ushort getWindowHeight(void) const { return m_windowHeight; }

	//Return a Reference to the Window
	inline sf::RenderWindow &getWindow(void) { return m_window; }

	//Pack & Unpack Color Values
	inline uint packRGBA(ubyte r, ubyte g, ubyte b, ubyte a) const { return r << 24 | g << 16 | b << 8 | a; }
	inline uint packRGBAf(float r, float g, float b, float a) const { return ((ubyte)(r * 255)) << 24 | ((ubyte)(g * 255)) << 16 | ((ubyte)(b * 255)) << 8 | (ubyte)(a * 255); }
	inline void unpackRGBA(uint rgba, ubyte *r, ubyte *g, ubyte *b, ubyte *a) const { *r = (rgba >> 24) & 0xff; *g = (rgba >> 16) & 0xff; *b = (rgba >> 8) & 0xff; *a = (rgba) & 0xff; }
	inline void unpackRGBAf(uint rgba, float *r, float *g, float *b, float *a) const { *r = ((rgba >> 24) & 0xff) / 255.f; *g = ((rgba >> 16) & 0xff) / 255.f; *b = ((rgba >> 8) & 0xff) / 255.f; *a = ((rgba) & 0xff) / 255.f; }
	inline uint packRGB(ubyte r, ubyte g, ubyte b) const { return r << 24 | g << 16 | b << 8 | 255; }
	inline uint packRGBf(float r, float g, float b) const { return ((ubyte)(r * 255)) << 24 | ((ubyte)(g * 255)) << 16 | ((ubyte)(b * 255)) << 8 | 255; }
	inline void unpackRGB(uint rgb, ubyte *r, ubyte *g, ubyte *b) const { *r = (rgb >> 24) & 0xff; *g = (rgb >> 16) & 0xff; *b = (rgb >> 8) & 0xff; }
	inline void unpackRGBf(uint rgb, float *r, float *g, float *b) const { *r = ((rgb >> 24) & 0xff) / 255.f; *g = ((rgb >> 16) & 0xff) / 255.f; *b = ((rgb >> 8) & 0xff) / 255.f; }

	///Return Amount of FPS rendered
	inline ushort getFPS(void) { return m_framesPerSecond; }

	///Return Time elapsed
	inline uint64_t getElapsedTime(void) const { return static_cast<uint64_t>(m_clock.getElapsedTime().asMicroseconds()); }

	///Return whether Close Message was dispatched
	inline bool wasWindowClosed(void) const { return m_closeInvoked; }
};

#endif // NGINE_RENDERER_HDR
