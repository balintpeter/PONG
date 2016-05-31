#include <SDL.h>
#include <SDL_config_win32.h>
#include <SDL_image.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <math.h>
#include <time.h>


#define KERET PALYAX/33
#define PALYAX 660
#define PALYAY 360
#define FEKETE 0x00000FF
#define FEHER 0xFFFFFFFF
#define SZURKE 0xBABABAFF
#define CSIKX PALYAX/66
#define CSIKY (PALYAY-(5*RES))/6
#define RES PALYAY/18
#define PX PALYAX/33
#define PY PALYAY/3
#define XPOS PALYAX/33
#define SUGAR PALYAY/33
#define SPEED 1

void drawmap(SDL_Surface *screen)
{
	SDL_FillRect(screen, NULL, FEHER);
	boxColor(screen,KERET,KERET,KERET+PALYAX,KERET+PALYAY,FEKETE);
	boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,2+KERET+CSIKY*0+RES*0,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*1+RES*0,SZURKE);
	boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*1+RES*1,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*2+RES*1,SZURKE);
	boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*2+RES*2,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*3+RES*2,SZURKE);
	boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*3+RES*3,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*4+RES*3,SZURKE);
	boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*4+RES*4,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*5+RES*4,SZURKE);
	boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*5+RES*5,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*6+RES*5,SZURKE);
}

void drawpone(SDL_Surface *screen,int ypos, unsigned int szin)
{
	boxColor(screen,KERET+XPOS,KERET+ypos,KERET+XPOS+PX,KERET+ypos+PY,szin);

}

void erasero(SDL_Surface *screen,int ypos, unsigned int szin)
{
	boxColor(screen,KERET+XPOS,KERET+ypos,KERET+XPOS+PX,KERET+ypos+PY,szin);
}

void drawptwo(SDL_Surface *screen,int ypos, unsigned int szin)
{
	boxColor(screen,KERET+PALYAX-XPOS-PX,KERET+ypos,KERET+PALYAX-XPOS,KERET+ypos+PY,szin);
}

void erasert(SDL_Surface *screen,int ypos, unsigned int szin)
{
	boxColor(screen,KERET+PALYAX-XPOS-PX,KERET+ypos,KERET+PALYAX-XPOS,KERET+ypos+PY,szin);
}

void drawball(SDL_Surface *screen, int xpos, int ypos, unsigned int szin)
{
	filledCircleColor(screen,xpos,ypos,SUGAR,szin);
}

void eraseball(SDL_Surface *screen, int xpos, int ypos, unsigned int szin)
{
	filledCircleColor(screen,xpos,ypos,SUGAR,szin);
}

int ketjatekos(int scoreone,int scoretwo)
{
	int quit=0;
	int onemove=0,yopos=(PALYAY+KERET*2)/2-(PY/2);
	int twomove=0,ytpos=yopos;
	int ballx=100, bally=50,xspeed=1,yspeed=1;
	char strone[2],strtwo[2];
	SDL_Event ev;
	SDL_Surface *screen;
	SDL_Color szurke = {186, 186, 186};
	SDL_Rect hovao = { 0, 0, 0, 0 };
	SDL_Rect hovat = { 0, 0, 0, 0 };
	TTF_Font *font;
	SDL_Surface *felirato,*feliratt;
	//SDL INICIALIZÁLÁSA//
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	TTF_Init();
	screen=SDL_SetVideoMode(KERET+PALYAX+KERET,KERET+PALYAY+KERET,0,SDL_ANYFORMAT);
	if(!screen)
	{
		fprintf(stderr,"Nem sikerult megnyitni az ablakot!\n");
		exit(1);
	}

	SDL_WM_SetCaption("Pong","Pong");

	TTF_Init();
	font = TTF_OpenFont("arialbd.ttf", PALYAX/8);
	if (!font) {
		fprintf(stderr, "Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
		exit(2);
	}


	drawmap(screen);
	drawpone(screen, yopos,FEHER);
	drawptwo(screen, ytpos,FEHER);
	drawball(screen, ballx, bally, FEHER);

	//EREDMÉNYJELZŐ//
	sprintf(strone, "%d", scoreone);
	sprintf(strtwo, "%d", scoretwo);
	felirato = TTF_RenderUTF8_Blended(font,strone, szurke);
	feliratt = TTF_RenderUTF8_Blended(font,strtwo, szurke);
	hovat.x += PALYAX/2+PALYAX/7;
	hovao.x += PALYAX/2-PALYAX/7;
	hovao.y += KERET+PALYAY/8;
	hovat.y += KERET+PALYAY/8;
	SDL_BlitSurface(felirato, NULL, screen, &hovao);
	SDL_BlitSurface(feliratt, NULL, screen, &hovat);


	while(!quit)
	{
		SDL_Delay(3);

		while(SDL_PollEvent(&ev))
		{
			switch(ev.type)
			{
			case SDL_KEYDOWN:
				switch(ev.key.keysym.sym)
				{
					//PLAYER 1//
				case SDLK_w:
					onemove=1;
					break;

				case SDLK_s:
					onemove=-1;
					break;
					//PLAYER 2//
				case SDLK_UP:
					twomove=1;
					break;

				case SDLK_DOWN:
					twomove=-1;
					break;
				}
				break;

			case SDL_KEYUP:
				switch(ev.key.keysym.sym)
				{
					//PLAYER 1//
				case SDLK_w:
					if(onemove>0)
						onemove=0;
					break;

				case SDLK_s:
					if(onemove<0)
						onemove=0;
					break;

					//PLAYER 2//
				case SDLK_UP:
					if(twomove>0)
						twomove=0;
					break;

				case SDLK_DOWN:
					if(twomove<0)
						twomove=0;
					break;
				}
				break;
				//KILÉPÉS//
			case SDL_QUIT:
				quit=1;
				break;
			}
		}
		//CIKLUS VÉGÉN//
		//PÁLYA//
		boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,2+KERET+CSIKY*0+RES*0,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*1+RES*0,SZURKE);
		boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*1+RES*1,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*2+RES*1,SZURKE);
		boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*2+RES*2,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*3+RES*2,SZURKE);
		boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*3+RES*3,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*4+RES*3,SZURKE);
		boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*4+RES*4,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*5+RES*4,SZURKE);
		boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*5+RES*5,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*6+RES*5,SZURKE);
		//SZÖVEG//
		SDL_BlitSurface(felirato, NULL, screen, &hovao);
		SDL_BlitSurface(feliratt, NULL, screen, &hovat);
		//BALL//
		eraseball(screen,ballx,bally,FEKETE);
		if((bally+SUGAR>=KERET+PALYAY)||(bally-SUGAR-1<=KERET))
			yspeed=yspeed*-1;
		if(((ballx+SUGAR==KERET+PALYAX-XPOS-PX)&&((bally>=ytpos+KERET)&&(bally<=ytpos+PY+KERET)))||(((bally>=yopos+KERET)&&(bally<=yopos+PY+KERET))&&(ballx-SUGAR==KERET+XPOS+PX)))
			xspeed=xspeed*-1;
		ballx+=xspeed;
		bally+=yspeed;
		drawball(screen,ballx,bally,FEHER);
		if(ballx+SUGAR>=KERET+PALYAX)
			return 1;
		else if(ballx-SUGAR<=KERET)
			return -1;
		//PLAYER 1//
		if(onemove==1 && 0<yopos)
		{
			erasero(screen, yopos,FEKETE);
			yopos-=SPEED;
			drawpone(screen, yopos,FEHER);
		}
		else if(onemove==-1 && yopos<(PALYAY-PY))
		{
			erasero(screen, yopos,FEKETE);
			yopos+=SPEED;
			drawpone(screen, yopos,FEHER);
		}
		//PLAYER 2//
		if(twomove==1 && 0<ytpos)
		{
			erasert(screen, ytpos,FEKETE);
			ytpos-=SPEED;
			drawptwo(screen, ytpos,FEHER);
		}
		else if(twomove==-1 && ytpos<(PALYAY-PY))
		{
			erasert(screen, ytpos,FEKETE);
			ytpos+=SPEED;
			drawptwo(screen, ytpos,FEHER);
		}


		SDL_Flip(screen);
	}
	//PROGRAM BEZÁRÁSA//
	SDL_FreeSurface(felirato);
	SDL_FreeSurface(feliratt);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	return 0;
}





int egyjatekos(int scoreone,int scoretwo)
{
	int quit=0;
	int onemove=0,yopos=(PALYAY+KERET*2)/2-(PY/2);
	int twomove=0,ytpos=yopos;
	int ballx, bally;
	double xspeed=1,yspeed=1,kitevoe,kitevok;
	char strone[2],strtwo[2];
	SDL_Event ev;
	SDL_Surface *screen;
	SDL_Color szurke = {186, 186, 186};
	SDL_Rect hovao = { 0, 0, 0, 0 };
	SDL_Rect hovat = { 0, 0, 0, 0 };
	TTF_Font *font;
	SDL_Surface *felirato,*feliratt;
	
	
	srand(time(NULL));
	kitevok=rand();
	yspeed=pow(-1,kitevok);
	ballx=KERET*2+rand() %(PALYAX-KERET*2);
	bally=KERET*2+rand() %(PALYAY-KERET*2);
	if(ballx<=(KERET+PALYAX/2))
		xspeed=1;
	else xspeed=-1;

	//SDL INICIALIZÁLÁSA//
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	TTF_Init();
	screen=SDL_SetVideoMode(KERET+PALYAX+KERET,KERET+PALYAY+KERET,0,SDL_ANYFORMAT);
	if(!screen)
	{
		fprintf(stderr,"Nem sikerult megnyitni az ablakot!\n");
		exit(1);
	}
	
	SDL_WM_SetCaption("Pong","Pong");

	TTF_Init();
	font = TTF_OpenFont("arialbd.ttf", PALYAX/8);
	if (!font) {
		fprintf(stderr, "Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
		exit(2);
	}


	drawmap(screen);
	drawpone(screen, yopos,FEHER);
	drawptwo(screen, ytpos,FEHER);
	drawball(screen, ballx, bally, FEHER);

	//EREDMÉNYJELZŐ//
	sprintf(strone, "%d", scoreone);
	sprintf(strtwo, "%d", scoretwo);
	felirato = TTF_RenderUTF8_Blended(font,strone, szurke);
	feliratt = TTF_RenderUTF8_Blended(font,strtwo, szurke);
	hovat.x += PALYAX/2+PALYAX/7;
	hovao.x += PALYAX/2-PALYAX/7;
	hovao.y += KERET+PALYAY/8;
	hovat.y += KERET+PALYAY/8;
	SDL_BlitSurface(felirato, NULL, screen, &hovao);
	SDL_BlitSurface(feliratt, NULL, screen, &hovat);


	while(!quit)
	{
		SDL_Delay(3);

		while(SDL_PollEvent(&ev))
		{
			switch(ev.type)
			{
			case SDL_KEYDOWN:
				switch(ev.key.keysym.sym)
				{
					//PLAYER 1//
				case SDLK_w:
					onemove=1;
					break;

				case SDLK_s:
					onemove=-1;
					break;
				}
				break;

			case SDL_KEYUP:
				switch(ev.key.keysym.sym)
				{
					//PLAYER 1//
				case SDLK_w:
					if(onemove>0)
						onemove=0;
					break;

				case SDLK_s:
					if(onemove<0)
						onemove=0;
					break;
				}
				break;
				//KILÉPÉS//
			case SDL_QUIT:
				quit=1;
				break;
			}
		}
		//CIKLUS VÉGÉN//
		//PÁLYA//
		boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,2+KERET+CSIKY*0+RES*0,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*1+RES*0,SZURKE);
		boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*1+RES*1,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*2+RES*1,SZURKE);
		boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*2+RES*2,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*3+RES*2,SZURKE);
		boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*3+RES*3,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*4+RES*3,SZURKE);
		boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*4+RES*4,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*5+RES*4,SZURKE);
		boxColor(screen,KERET+(PALYAX/2)-CSIKX/2,KERET+CSIKY*5+RES*5,KERET+(PALYAX/2)+CSIKX/2,KERET+CSIKY*6+RES*5,SZURKE);
		//SZÖVEG//
		SDL_BlitSurface(felirato, NULL, screen, &hovao);
		SDL_BlitSurface(feliratt, NULL, screen, &hovat);
		//BALL//
		eraseball(screen,ballx,bally,FEKETE);
		if((bally+SUGAR>=KERET+PALYAY)||(bally-SUGAR-1<=KERET))
			yspeed=yspeed*-1;
		if(((ballx+SUGAR==KERET+PALYAX-XPOS-PX-2)&&((bally>=ytpos+KERET)&&(bally<=ytpos+PY+KERET)))||(((bally>=yopos+KERET)&&(bally<=yopos+PY+KERET))&&(ballx-SUGAR==KERET+XPOS+PX+2)))
			{
				/*if(((bally>=ytpos+KERET)&&(bally<=ytpos+PY/3+KERET))||((bally>=yopos+KERET)&&(bally<=yopos+PY/3+KERET)))
				{
					xspeed=xspeed*-1;
					yspeed=-1;
				}
				else if(((bally>=ytpos+PY/3+KERET)&&(bally<=ytpos+2*PY/3+KERET))||((bally>=yopos+PY/3+KERET)&&(bally<=yopos+2*PY/3+KERET)))
				{
					xspeed=xspeed*-1;
				}
				else if(((bally>=ytpos+2*PY/3+KERET)&&(bally<=ytpos+PY+KERET))||((bally>=yopos+2*PY/3+KERET)&&(bally<=yopos+PY+KERET)))
				{
					xspeed=xspeed*-1;
					yspeed=1;
				}*/
				xspeed=xspeed*-1;
			}
		ballx+=xspeed;
		bally+=yspeed;
		drawball(screen,ballx,bally,FEHER);
		if(ballx+SUGAR>=KERET+PALYAX)
			return 1;
		else if(ballx-SUGAR<=KERET)
			return -1;
		//PLAYER 1//
		if(onemove==1 && 0<yopos)
		{
			erasero(screen, yopos,FEKETE);
			yopos-=SPEED;
			drawpone(screen, yopos,FEHER);
		}
		else if(onemove==-1 && yopos<(PALYAY-PY))
		{
			erasero(screen, yopos,FEKETE);
			yopos+=SPEED;
			drawpone(screen, yopos,FEHER);
		}
		//PLAYER 2//
		if(bally<ytpos+PY/2 && 0<ytpos && ballx>=KERET+2*PALYAX/3)
		{
			erasert(screen, ytpos,FEKETE);
			ytpos-=SPEED;
			drawptwo(screen, ytpos,FEHER);
		}
		else if(bally>ytpos+PY/2 && ytpos<(PALYAY-PY) && ballx>=KERET+2*PALYAX/3)
		{
			erasert(screen, ytpos,FEKETE);
			ytpos+=SPEED;
			drawptwo(screen, ytpos,FEHER);
		}
		SDL_Flip(screen);
	}
	//PROGRAM BEZÁRÁSA//
	SDL_FreeSurface(felirato);
	SDL_FreeSurface(feliratt);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	return 0;
}



int main(int argc, char *argv[]) {
	int scoreone=0,scoretwo=0,eredmeny;
	while (1)
	{
		//eredmeny=ketjatekos(scoreone,scoretwo);
		eredmeny=egyjatekos(scoreone,scoretwo);
		if(eredmeny==1)
			scoreone++;
		else if(eredmeny==-1)
			scoretwo++;
		else if(eredmeny==0)
		{
			return 0;
		}
		if(scoreone==5)
		{
			fprintf(stderr,"Az elso jatekos nyert!\n");
			return 0;
		}
		else if(scoretwo==5)
		{
			fprintf(stderr,"A masodik jatekos nyert!\n");
			return 0;
		}
	}
}
