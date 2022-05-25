#include <iostream>
#include <SDL.h>
#include <fstream>
#include <string>
#include "drawingOOP.h"
using namespace std;

SDL_Renderer* renderer;
void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}
void RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
	int offsetx, offsety, d;
	int status;

	offsetx = 0;
	offsety = radius;
	d = radius - 1;
	status = 0;

	while (offsety >= offsetx) {

		status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
			x + offsety, y + offsetx);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
			x + offsetx, y + offsety);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
			x + offsetx, y - offsety);
		status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
			x + offsety, y - offsetx);

		if (status < 0) {
			status = -1;
			break;
		}

		if (d >= 2 * offsetx) {
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}
}
void Circle::Draw()
{
    cout << "Drawing " << m_name << endl;
	SDL_SetRenderDrawColor(renderer, m_color.red, m_color.green, m_color.blue, m_color.alpha);
	DrawCircle(renderer, m_x, m_y, m_radius);
	RenderFillCircle(renderer, m_x, m_y, m_radius);
}

void Rectangle::Draw()
{
    cout << "Drawing " << m_name << endl;
    SDL_Rect r;
    r.x = m_x;
    r.y = m_y;
    r.w = m_width;
    r.h = m_height;
    SDL_SetRenderDrawColor(renderer, m_color.red, m_color.green, m_color.blue, m_color.alpha);
    SDL_RenderFillRect(renderer, &r);

}

void Triangle::Draw() {
    cout << "Drawing" << m_name << endl;
    SDL_SetRenderDrawColor(renderer, m_color.red, m_color.green, m_color.blue, m_color.alpha);

    for (int i = 0; i <= m_width/2; i++) {
        SDL_RenderDrawLine(renderer, m_x+i, m_y-i, m_x + m_width - i, m_y - i);
        SDL_RenderDrawLine(renderer, m_x + m_width - i, m_y - i, m_x + (m_width / 2), m_y - m_height + i);
        SDL_RenderDrawLine(renderer, m_x + (m_width / 2), m_y - m_height + i, m_x + i, m_y - i);
    }
}


int main(int argc, char** argv)
{
    bool leftMouseButtonDown = false;
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL2 Pixel Drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1366, 768, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    SDL_Texture* texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 800, 600);
    Uint32* pixels = new Uint32[800 * 600];
    memset(pixels, 0xff000000, 800 * 600 * sizeof(Uint32));
    
    
    
    
    
    while (!quit)
    {
        
        SDL_UpdateTexture(texture, NULL, pixels, 800 * sizeof(Uint32));

        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
                leftMouseButtonDown = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
                leftMouseButtonDown = true;
        case SDL_MOUSEMOTION:
            if (leftMouseButtonDown)
            {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                //pixels[mouseY * 640 + mouseX] = 0;
            }
            break;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Clear winow
        SDL_RenderClear(renderer);
        Color color = Color{ 1,2,3,4 };
        vector<Shape*> items;
        Rectangle* rect1 = new Rectangle("First Rectangle", 100, 100, 100, 100, Color{123,123,123,255});
        Rectangle* rect2 = new Rectangle("Second Rectangle", 230, 100, 100, 100, Color{ 123,123,123,255 });
        Rectangle* rect3 = new Rectangle("Third Rectangle", 360, 100, 100, 100, Color{ 123,123,123,255 });
        Rectangle* rect4 = new Rectangle("Fourth Rectangle", 490, 100, 100, 100, Color{ 123,123,123,255 });
		Circle* circle1 = new Circle("Fst Circle", 700, 150, 50, Color{ 123,123,123,255 });
        
        items.push_back(rect1);
        items.push_back(rect2);
        items.push_back(rect3);
        items.push_back(rect4);
        items.push_back(circle1);
		
		Triangle* tri1 = new Triangle("First Triangle", 0, 100, 100, 100, Color{ 242,22,145,255 });
        Triangle* tri2 = new Triangle("Second Triangle", 100, 100, 200, 100, Color{ 87,4,252,255 });
        Triangle* tri3 = new Triangle("Third Triangle", 0, 350, 100, 250, Color{ 255,0,0,128 });

        items.push_back(tri1);
        items.push_back(tri2);
        items.push_back(tri3);



		//domek
		Rectangle* rect5 = new Rectangle("podstawa domku", 800, 350, 250, 250, Color{ 239,228,175,255 });
		Triangle* tri4 = new Triangle("dach", 800, 350, 250, 100, Color{ 255,0,0,255 });
		Circle* circle2 = new Circle("okno prawe", 990, 425, 40, Color{ 0,162,232,255 });
		Circle* circle3 = new Circle("okno lewe", 860, 425, 40, Color{ 0,162,232,255 });
		Rectangle* rect6 = new Rectangle("komin", 1000, 250, 40, 100, Color{ 128,64,64,255 });
		Rectangle* rect7 = new Rectangle("drzwi", 890, 480, 70, 120, Color{ 128,64,64,255 });
		Rectangle* rect8 = new Rectangle("okno prawe pion", 988, 385, 4, 80, Color{ 192,192,192,255 });
		Rectangle* rect9 = new Rectangle("okno prawe poziom", 950, 423, 80, 4, Color{ 192,192,192,255 });
		Rectangle* rect10 = new Rectangle("okno lewe pion", 858, 385, 4, 80, Color{ 192,192,192,255 });
		Rectangle* rect11 = new Rectangle("okno lewe poziom", 820, 423, 80, 4, Color{ 192,192,192,255 });
		Circle* circle4 = new Circle("okno gorne", 925, 310, 30, Color{ 0,162,232,255 });
		Rectangle* rect12 = new Rectangle("okno gorne pion", 923, 280, 4, 60, Color{ 192,192,192,255 });
		Rectangle* rect13 = new Rectangle("okno gorne poziom", 895, 308, 60, 4, Color{ 192,192,192,255 });


		items.push_back(rect6);
		items.push_back(tri4);
		items.push_back(rect5);
		items.push_back(circle2);
		items.push_back(circle3);
		items.push_back(rect7);
		items.push_back(rect8);
		items.push_back(rect9);
		items.push_back(rect10);
		items.push_back(rect11);
		items.push_back(circle4);
		items.push_back(rect12);
		items.push_back(rect13);
		
		
        for (Shape* it : items)
        {
            it->Draw();
            delete it;
        }

        items.clear();
        //SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}