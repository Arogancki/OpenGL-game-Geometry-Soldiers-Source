#pragma once
#include "stdafx.h"
#include "Mapa.h"


//odgrywanie dzwiekow
void PlaySound(const char* path, float sound_x, float sound_y, float sound_z)
{
	if (sound_x - Gracz->pos.x < -1000)
		sound_x = Gracz->pos.x - 2001 - sound_x;
	else
		if (sound_x - Gracz->pos.x > 1000)
			sound_x = Gracz->pos.x + 2001 - sound_x;
		else
			sound_x = Gracz->pos.x - sound_x;

	if (sound_z - Gracz->pos.z < -1000)
		sound_z = Gracz->pos.z - 2001 - sound_z;
	else
		if (sound_z - Gracz->pos.z > 1000)
			sound_z = Gracz->pos.z + 2001 - sound_z;
		else
			sound_z = Gracz->pos.z - sound_z;

	if (sqrtf(pow(sound_z, 2) + pow(sound_x, 2)) > 120)
		return;

	// sounds/dzwiek.wav
	engine->setListenerPosition({ Gracz->pos.x, Gracz->pos.y, Gracz->pos.z }, { Gracz->dir.x, Gracz->dir.y, Gracz->dir.z });
	engine->play3D(path, { Gracz->pos.x+sound_x, sound_y,  Gracz->pos.z+sound_z }, false, false, false); // plik, polozenie grania, czy petla, czy pauza, czy zwracanie wskaznika
}

void JustPlay(const char* path, bool loop)
{
	engine->setListenerPosition({ 0,0,0 }, { 0,0,1 });
	engine->play3D(path, { 0,0,1 }, loop, false, false); // plik, polozenie grania, czy petla, czy pauza, czy zwracanie wskaznika
}

// rysowanie napisow na ekranie
void drawText(int x, int y, std::string st, float q, float w, float e)
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);  // Tell opengl that we are doing project matrix work
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();  // Clear the matrix
	glOrtho(-128.0, 128.0, -128.0, 128.0, 0.0, 30.0);  // Setup an Ortho view
	glMatrixMode(GL_MODELVIEW);  // Tell opengl that we are doing model matrix work. (drawing)
	glLoadIdentity(); // Clear the model matrix
	glPushMatrix();
	glColor3f(q, w, e);
	glLoadIdentity();
	glRasterPos2i(x, y); // location to start printing text
	for (int i = 0; i < st.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, st[i]);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);  // Tell opengl that we are doing project matrix work
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void drawShape(int x, int y, int sx, int sy, CTexture* tex)
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);  // Tell opengl that we are doing project matrix work
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();  // Clear the matrix
	gluOrtho2D(0, 256, 256, 0);  // Setup an Ortho view
	glMatrixMode(GL_MODELVIEW);  // Tell opengl that we are doing model matrix work. (drawing)
	glLoadIdentity(); // Clear the model matrix
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y); // location to start printing text

						 //glClear(GL_DEPTH_BUFFER_BIT);
						 //glEnable(GL_BLEND);

	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, tex->GetId());
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex2f(x, y);
	glTexCoord2f(1, 1);
	glVertex2f(x + sx, y);
	glTexCoord2f(1, 0);
	glVertex2f(x + sx, y + sy);
	glTexCoord2f(0, 0);
	glVertex2f(x, y + sy);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	//glDisable(GL_BLEND);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);  // Tell opengl that we are doing project matrix work
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}


// Funkcje renderow
void OnRender2();
void OnRender3();
void OnRender4();

// Deklaracja obiektow drzew
GLuint stworz_drzewo1()
{
	GLuint drzewo1 = glGenLists(1);
	glNewList(drzewo1, GL_COMPILE);
	glPushMatrix();
	float extra[4];
	extra[0] = 0.3f;
	extra[1] = 0.1f;
	extra[2] = 0.0f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, extra);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	for (float j = 0; j < 23; j++)
	{
		glPushMatrix();
		glRotatef(-90, 1.0f, 0.0f, .0f);
		glutSolidTorus(1.0 - j*0.02, 0.5 - j*0.02, 12, 12);
		glPopMatrix();
		glTranslatef(0.0f, 0.5f, 0.0f);
	}
	glTranslatef(0.0f, 8.0f, 0.0f);
	extra[0] = .1f;
	extra[1] = 0.65f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, extra);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glutSolidSphere(9.0f, 8, 8);
	glPopMatrix();
	glPopMatrix();
	glEndList();
	return(drzewo1);
}

GLuint stworz_drzewo2()
{
	GLuint drzewo2 = glGenLists(1);
	glNewList(drzewo2, GL_COMPILE);
	glPushMatrix();
	float extra[4];
	extra[0] = 0.3f;
	extra[1] = 0.1f;
	extra[2] = 0.0f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, extra);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	for (float j = 0; j < 24; j++)
	{
		glPushMatrix();
		glRotatef(-90, 1.0f, 0.0f, .0f);
		glutSolidTorus(1.0 - j*0.02, 0.5 - j*0.02, 12, 12);
		glPopMatrix();
		glTranslatef(0.0f, 0.5f, 0.0f);
	}
	glTranslatef(0, -0.3, 0);
	extra[0] = .1f;
	extra[1] = 0.65f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, extra);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(7.0f, 24.0f, 8, 8);
	glPopMatrix();
	glPopMatrix();
	glEndList();
	return(drzewo2);
}

// obiekty ziemi
GLuint stworz_ziemieO()
{
	GLuint ziemia = glGenLists(1);
	glNewList(ziemia, GL_COMPILE);

	float extra[4];
	extra[0] = .0f;
	extra[1] = .4f;
	extra[2] = .1f;
	extra[3] = .0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, extra);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glBegin(GL_QUADS);
	float k = 0.01;
	float kk = 0.01;
	for (int i = -150; i < 2150; i += 20)
	{
		for (int j = -150; j < 2150; j += 20)
		{
			glTexCoord2f(k, kk);
			glVertex3f(i, 0.0f, j);

			glTexCoord2f(k + 0.1, kk);
			glVertex3f(i + 20, 0.0f, j);

			glTexCoord2f(k + 0.1, kk + 0.1);
			glVertex3f(i + 20, 0.0f, j + 20);

			glTexCoord2f(k, kk + 0.1);
			glVertex3f(i, 0.0f, j + 20);
			kk += 0.1;
		}
		kk = 0;
		k += 0.1;
	}

	glEnd();
	glPopMatrix();
	glEndList();
	return(ziemia);
}

CTexture* stworz_ziemieT()
{
	CTexture* ziemia = new CTexture("bitmap\\ziemia.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	ziemia->Load();
	return(ziemia);
}

// obiekty nieba
GLuint stworz_nieboO()
{
	GLuint niebo = glGenLists(1);
	glNewList(niebo, GL_COMPILE);

	float extra[4];
	extra[0] = .2f;
	extra[1] = .6f;
	extra[2] = 1.0f;
	extra[3] = .0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, extra);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glBegin(GL_QUADS);
	float k = 0.01;
	float kk = 0.01;
	for (int i = -200; i < 200; i += 20)
	{
		for (int j = -200; j < 200; j += 20)
		{
			glTexCoord2f(k, kk);
			glVertex3f(i, 0.0f, j);
			glTexCoord2f(k + 0.1, kk);
			glVertex3f(i + 20, 0.0f, j);
			glTexCoord2f(k + 0.1, kk + 0.1);
			glVertex3f(i + 20, 0.0f, j + 20);
			glTexCoord2f(k, kk + 0.1);
			glVertex3f(i, 0.0f, j + 20);
			kk += 0.1;
		}
		k += 0.1;
		kk = 0;
	}
	glEnd();
	glPopMatrix();
	glEndList();
	return(niebo);
}

CTexture* stworz_nieboT()
{
	CTexture* ziemia = new CTexture("bitmap\\niebo.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	ziemia->Load();
	return(ziemia);
}


//MYSZkA - obluga ruchu myszki
void tellposition(int x, int y)
{
	if (camen || pauza)
		return;
	float sensiy = abs(abs(mouse.y) - abs(y))*0.02;  // czym mniejsza tym wolniej
	float sensix = abs(abs(mouse.x) - abs(x))*0.02;// czym mniejsza tym wolniej
												   //sensix = fmod(sensix, 0.2);
	if (y < mouse.y) // w gore
	{
		float teta = asin(player.dir.y) + sensiy;
		if (teta < 1.0)
		{
			float fi = atan2((player.dir.x), (player.dir.z));
			player.dir.x = cos(teta)*sin(fi);
			player.dir.y = sin(teta);
			player.dir.z = cos(teta)*cos(fi);
		}
	}

	if (y > mouse.y)// w dolu
	{
		float teta = asin(player.dir.y) - sensiy;
		if (teta > -1.1)
		{
			float fi = atan2((player.dir.x), (player.dir.z));
			player.dir.x = cos(teta)*sin(fi);
			player.dir.y = sin(teta);
			player.dir.z = cos(teta)*cos(fi);
		}
	}

	if (x > mouse.x) // w prawo (e)
	{
		float fi = atan2((player.dir.x), (player.dir.z)) - sensix;
		float teta = asin(player.dir.y);
		player.dir.x = cos(teta)*sin(fi);
		player.dir.y = sin(teta);
		player.dir.z = cos(teta)*cos(fi);
	}

	if (x < mouse.x) // w lewo (q)
	{
		float fi = atan2((player.dir.x), (player.dir.z)) + sensix;
		float teta = asin(player.dir.y);
		player.dir.x = cos(teta)*sin(fi);
		player.dir.y = sin(teta);
		player.dir.z = cos(teta)*cos(fi);
	}

	// powrot w ekran jak ucieka kursor
	if (x <= -glutGet(GLUT_WINDOW_X) + 100 || (y) <= -glutGet(GLUT_WINDOW_Y) + 100 || x >= glutGet(GLUT_SCREEN_WIDTH) - glutGet(GLUT_WINDOW_X) - 100 || y >= glutGet(GLUT_SCREEN_HEIGHT) - glutGet(GLUT_WINDOW_Y) - 100)
	{
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		x = GLUT_SCREEN_WIDTH / 2;
		y = GLUT_SCREEN_HEIGHT / 2;
	}
	mouse.x = x;
	mouse.y = y;
}

void tellpositionm(int x, int y)
{
	if (maxwidth == 0)
		maxwidth = 1;

	if (maxheight == 0)
		maxheight = 1;

	if (licznikmenu > 2000)
	{
		float xxx = x / (maxwidth / 256);
		float yyy = y / (maxheight / 256);


		if (ssojusznicy || ssamotnik)
		{
			if (xxx > 25 && xxx < 85 && yyy>20 && yyy < 80)
				wybrano = 1;
			else
				if (xxx > 25 && xxx < 85 && yyy>180 && yyy < 240)
					wybrano = 3;
				else
					if (xxx > 25 && xxx < 85 && yyy>100 && yyy < 160)
						wybrano = 2;
					else
						wybrano = 0;
		}
		else
			wybrano = 0;

		if (!ssojusznicy && !ssamotnik && !spomoc)
		{

			if (xxx > 5 && xxx < 65 && yyy>156 && yyy < 216)
				bkoniec = 1;
			else
				bkoniec = 0;


			if (xxx > 191 && xxx < 251 && yyy>156 && yyy < 216)
				bpomoc = 1;
			else
				bpomoc = 0;

			if (xxx > 20 && xxx < 80 && yyy>55 && yyy < 115)
				bsamotnik = 1;
			else
				bsamotnik = 0;

			if (xxx > 176 && xxx < 236 && yyy>55 && yyy < 115)
				bsojusznicy = 1;
			else
				bsojusznicy = 0;
		}
	}



	mouse.x = x;
	mouse.y = y;
	//czy koniec
}

void OnKeyDown(unsigned char key, int x, int y);

// KLAWIATURA- Obs³uga wcisniecia puszczenia klawisza.
void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		OnKeyDown(key, x, y); // Emulacja zdarzenia zwi¹zanego z pojedynczym wciœniêciem klawisza
	}
	keystate[key] = true;
}

// klawiatura do menu - nic
void OnKeyPressM(unsigned char key, int x, int y) {
	keystate[key] = true;
}

void Menu();

// Obs³uga naszego w³asnego zdarzenia klawisza
void OnKeyDown(unsigned char key, int x, int y) {

	if (key == 27)  // ESC - wyjœcie do menu
	{
		pauza = 0;
		czyarrow = 0;
		celownik = 0;
		czylokacje = 0;
		zycoika = 0;
		niebospin = 0;
		camen = 0;
		map.~Mapa();
		for (int licznik = 0; licznik < heroses.size(); licznik++)
		{
			delete heroses[licznik];
		}
		heroses.clear();
		Menu();
	}
	if (key == 'p' || key == 'P')
		pauza = (pauza + 1) % 2;

	if (pauza)
		return;

	if (key == '2')
		Gracz->incraseatak();

	if (key == '1')
		Gracz->incraselife();

	if (key == '3' && Gracz->zycie != Gracz->calezycie)
		Gracz->heal();

	if (key == '4')
	{
		czyarrow = (czyarrow + 1) % 2;
		PlaySound("sounds/arr.wav", Gracz->pos.x,0, Gracz->pos.z);
	}

	// programistyczne
	if (key == 'y')
		czylokacje = (czylokacje + 1) % 2;

}

// Obs³uga zdarzenia puszczenia klawisza.
void OnKeyUp(unsigned char key, int x, int y) {
	keystate[key] = false;
	if (key<224)
		keystate[key + 32] = false;
	if (key>31)
		keystate[key - 32] = false;// ODPRONE NA PUSZCZENIE clk
	player.czyidzie = 0;
}

void GetGamepadInput();
// TIMER
void OnTimer(int id) {
	// Aby gracz nie uciekl z mapy
	player.pos.x = fmod((player.pos.x + 2001), 2001);
	player.pos.z = fmod((player.pos.z + 2001), 2001);

	// animacja ruchu gracza
	if (keystate['w'] || keystate['s'] || keystate['a'] || keystate['d'])
		player.czyidzie = 1;

	// Chcemy, by ta funkcja wywolala sie ponownie za 17ms.
	glutTimerFunc(18, OnTimer, 0);
}

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float)width / height, .01f, 400.0f);
	maxwidth = width;
	maxheight = height;
}

// funkcje rysujace
void rysujDrzewo(int x, int z, GLuint listid, int spin)
{
	glPushMatrix();
	glTranslatef(x, 0, z);
	glRotatef(spin, 0.0f, 1.0f, 0.0f); // obrot o randomowy kat przydzielany w mapie
	glCallList(listid);
	glPopMatrix();
}

void rysujDrzewa()
{
	for (int i = player.pos.x - 112; i < player.pos.x + 112; i += 4)
		for (int j = player.pos.z - 112; j < player.pos.z + 112; j += 4)
			if (map.mapatyp[(i + 2001) % 2001][(j + 2001) % 2001] == 5)
			{
				float xxx = map.drzewa[(i + 2001) % 2001][(j + 2001) % 2001].x, zzz = map.drzewa[(i + 2001) % 2001][(j + 2001) % 2001].z;

				if (xxx - player.pos.x >= 1900)
					xxx -= 2001;
				else
					if (player.pos.x - xxx >= 1900)
						xxx += 2001;

				if (zzz - player.pos.z >= 1900)
					zzz -= 2001;
				else
					if (player.pos.z - zzz >= 1900)
						zzz += 2001;
				rysujDrzewo(xxx, zzz, drzewo1, map.drzewa[(i + 2001) % 2001][(j + 2001) % 2001].y);
			}
			else
				if (map.mapatyp[(i + 2001) % 2001][(j + 2001) % 2001] == 2)
				{
					float xxx = map.drzewa[(i + 2001) % 2001][(j + 2001) % 2001].x, zzz = map.drzewa[(i + 2001) % 2001][(j + 2001) % 2001].z;

					if (xxx - player.pos.x >= 1900)
						xxx -= 2001;
					else
						if (player.pos.x - xxx >= 1900)
							xxx += 2001;

					if (zzz - player.pos.z >= 1900)
						zzz -= 2001;
					else
						if (player.pos.z - zzz >= 1900)
							zzz += 2001;
					rysujDrzewo(xxx, zzz, drzewo2, map.drzewa[(i + 2001) % 2001][(j + 2001) % 2001].y);
				}
}

void rysujziemie()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, ziemiaT->GetId());
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glCallList(ziemiaO);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void rysujniebo()
{
	glPushMatrix();
	glTranslatef(player.pos.x, 40, player.pos.z);
	glEnable(GL_TEXTURE_2D);
	glRotatef(niebospin, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, nieboT->GetId());
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glCallList(nieboO);
	niebospin += 0.02;
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void rysujArrow()
{
	vector3d temp;
	float spinx = 0, spinz = 1;
	float minn = -2;
	for (int i = 0; i < heroses.size(); i++)
	{
		if (heroses[i] == Gracz || heroses[i]->how_long_dead>0)
			;
		else
		{

			if (Gracz->pos.x - heroses[i]->pos.x < -1000)
				temp.x = heroses[i]->pos.x - 2001 - Gracz->pos.x;
			else
				if (Gracz->pos.x - heroses[i]->pos.x > 1000)
					temp.x = heroses[i]->pos.x + 2001 - Gracz->pos.x;
				else
					temp.x = heroses[i]->pos.x - Gracz->pos.x;

			if (Gracz->pos.z - heroses[i]->pos.z < -1000)
				temp.z = heroses[i]->pos.z - 2001 - Gracz->pos.z;
			else
				if (Gracz->pos.z - heroses[i]->pos.z > 1000)
					temp.z = heroses[i]->pos.z + 2001 - Gracz->pos.z;
				else
					temp.z = heroses[i]->pos.z - Gracz->pos.z;

			temp.y = sqrtf(pow(temp.z, 2) + pow(temp.x, 2));
			if (temp.y < minn || minn <= -1)
			{
				minn = temp.y;

				spinx = temp.x / temp.y;
				spinz = temp.z / temp.y;
			}
		}
	}
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(Gracz->pos.x, Gracz->pos.y + 8.2, Gracz->pos.z);
	glRotatef(atan2(Gracz->dir.z, Gracz->dir.x)*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glTranslatef(0, 0, 1);
	glPushMatrix();
	glRotatef((atan2(spinz, spinx)*(-57.2957) + 90) - (atan2(Gracz->dir.z, Gracz->dir.x)*(-57.2957) + 90), 0.0f, 1.0f, 0.0f);
	glCallList(arrow);
	glPopMatrix();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void rysujArrow2()
{
	vector3d temp;
	float spinx = 0, spinz = 1;
	float minn = -2;
	for (int i = 0; i < heroses.size(); i++)
	{
		if (heroses[i]->klasa == Gracz->klasa || heroses[i]->how_long_dead>0)
			;
		else
		{

			if (Gracz->pos.x - heroses[i]->pos.x < -1000)
				temp.x = heroses[i]->pos.x - 2001 - Gracz->pos.x;
			else
				if (Gracz->pos.x - heroses[i]->pos.x > 1000)
					temp.x = heroses[i]->pos.x + 2001 - Gracz->pos.x;
				else
					temp.x = heroses[i]->pos.x - Gracz->pos.x;

			if (Gracz->pos.z - heroses[i]->pos.z < -1000)
				temp.z = heroses[i]->pos.z - 2001 - Gracz->pos.z;
			else
				if (Gracz->pos.z - heroses[i]->pos.z > 1000)
					temp.z = heroses[i]->pos.z + 2001 - Gracz->pos.z;
				else
					temp.z = heroses[i]->pos.z - Gracz->pos.z;

			temp.y = sqrtf(pow(temp.z, 2) + pow(temp.x, 2));
			if (temp.y < minn || minn <= -1)
			{
				minn = temp.y;

				spinx = temp.x / temp.y;
				spinz = temp.z / temp.y;
			}
		}
	}
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(Gracz->pos.x, Gracz->pos.y + 8.2, Gracz->pos.z);
	glRotatef(atan2(Gracz->dir.z, Gracz->dir.x)*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glTranslatef(0, 0, 1);
	glPushMatrix();
	glRotatef((atan2(spinz, spinx)*(-57.2957) + 90) - (atan2(Gracz->dir.z, Gracz->dir.x)*(-57.2957) + 90), 0.0f, 1.0f, 0.0f);
	glCallList(arrow);
	glPopMatrix();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

GLuint StworzArrow()
{
	GLuint ret = glGenLists(1);
	glNewList(ret, GL_COMPILE);
	glPushMatrix();
	glColor3f(0.6, 0.1, 0);
	glPushMatrix();
	glScalef(0.05, 0.05, 0.3);
	glutSolidCube(1);
	glPopMatrix();
	glColor3f(0.6, 0, 0);
	glTranslatef(0, 0, 0.15);
	glutSolidCone(0.103, 0.2502, 4, 2);
	glTranslatef(0, 0, -0.001);
	glColor3f(0.7, 0, 0);
	glutSolidCone(0.1, 0.25, 8, 2);
	glPopMatrix();
	glEndList();
	return(ret);
}

void DrukujStatystyki()
{

	for (int licznik = 0; licznik < heroses.size(); licznik++)
		drawText(40, -125 + (licznik * 5), std::to_string(licznik) + heroses[licznik]->klasa + "= " + std::to_string((int)heroses[licznik]->pos.x) + " x " + std::to_string((int)heroses[licznik]->pos.z) + " z=" + std::to_string((int)heroses[licznik]->zycie) + "/" + std::to_string((int)heroses[licznik]->calezycie) + " a=" + std::to_string((int)heroses[licznik]->silaataku) + " k=" + std::to_string((int)heroses[licznik]->kills), 1, 1, 1);

}


// POSTACIE - hero w mapie

class Mine : public hero
{
public:
	void dodajkill();
	int podajatak();
	void odejmijzycie(int);
	void heal();
	void incraselife();
	void incraseatak();
	float adu[4]; // Ambient  diffuse up
	float add[4];// Ambient  diffuse down
	float adm[4];// Ambient  diffuse up*down
	float spe[4]; //Specular
				  //int mine_wybuch_stala[5];
	Mine(float, float); // przekazujemy poziom x, z. y pozostaje bez zmian bo nie zmieniam wysokosci
	~Mine();
	void rysuj(int, int); // // uwzglednic przypadek kiedy punkty zycia sa 0 to bedzie uruchamiany dead
	void setcolors(float, float, float, float, float, float); // up r g b, down r g b
	void rysuj_wybuchy(/*hero* */);
private:
	void rysuj_dead();
	void rysuj_miny();
	int stala_ruchu_nog;
	int stala_ruchu_nog2;
	int stala_ruchu_atak;
	int rzutminy;
	int licznikmin;
	GLuint dislist;
	GLuint dislistBG;
	GLuint dislistMINE;
};

int Mine::podajatak()
{
	return(silaataku);
}

void Mine::dodajkill()
{
	PlaySound("sounds/lz.wav", pos.x, 0, pos.z);
	kills++;
	if (kills == reqexp - 2)
	{
		PlaySound("sounds/f.wav", pos.x, 0, pos.z);
		levelanimation = 1;
		textanim1 = 1;
		preqexp = reqexp - 2;
		reqexp += +liczniklv;
		liczniklv++;
		pointstospend++;
	}
}

void Mine::odejmijzycie(int points)
{
	zycie -= points;
	zycoika = glutGet(GLUT_ELAPSED_TIME) + 32;
	if (zycie <= 0)
		zycie = 0;
	else
	{
		int rando = rand() % 4;
		if (rando == 0)
			PlaySound("sounds/hi1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/hi2.wav", pos.x, 0, pos.z);
			else
				if (rando == 2)
					PlaySound("sounds/hi3.wav", pos.x, 0, pos.z);
				else
					PlaySound("sounds/hi4.wav", pos.x, 0, pos.z);
	}
}

Mine::~Mine()
{}

void Mine::setcolors(float cur, float cug, float cub, float cdr, float cdg, float cdb)
{
	adu[0] = cur;
	adu[1] = cug;
	adu[2] = cub;
	add[0] = cdr;
	add[1] = cdg;
	add[2] = cdb;
}

void Mine::rysuj_wybuchy(/*hero* */)
{
	for (int i = 0; i < 5; i++)
	{
		if (mine[i].y >= 99 || mine_wybuch_stala[i] == 0)
			goto x;

		float xxx = mine[i].x, zzz = mine[i].z;

		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;

		l2_pos[0] = xxx;
		l2_pos[1] = mine[i].y;
		l2_pos[2] = zzz;
		l2_pos[3] = 1.0;
		glEnable(GL_LIGHT2);

		glPushMatrix();
		glTranslatef(xxx, mine[i].y - 0.5, zzz);

		if (mine_wybuch_stala[i] == 1)
			PlaySound("sounds/ma2.wav", xxx, 0, zzz);

		float extra[4];
		extra[0] = 0.7f;
		extra[1] = 0.0f;
		extra[2] = 0.0f;
		extra[3] = 1.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
		glMaterialfv(GL_FRONT, GL_SPECULAR, extra);
		glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
		glutSolidSphere(0.5* hero::mine_wybuch_stala[i], 11, 11);
		glPopMatrix();



		hero::mine_wybuch_stala[i] += 4;

		if (hero::mine_wybuch_stala[i] >= 38)
		{
			mine[i].y = 100;
			hero::mine_wybuch_stala[i] = 0;
			glDisable(GL_LIGHT2);
		}

	x:;
	}
}

void Mine::rysuj_miny()
{
	for (int i = 0; i < 5; i++)
	{
		if (mine[i].y >= 99)
			goto x;



		float xxx = mine[i].x, zzz = mine[i].z;

		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;

		glPushMatrix();
		glTranslatef(xxx, mine[i].y - 0.5, zzz);
		glCallList(dislistMINE);
		glPopMatrix();

	x:;
	}
}

Mine::Mine(float startnax, float startnaz)
{
	klasa = 'i';
	for (int i = -2; i < 3; i++)
		for (int j = -2; j < 3; j++)
		{
			map.postac[((int)startnax + i + 2001) % 2001][((int)startnaz + j + 2001) % 2001] = this;
		}
	czasoczekiwan = 3000;
	silaataku = 1000;
	calezycie = zyciepostaciMINE;
	zycie = calezycie;
	how_long_dead = 0;

	levelanimation = 0;

	pointstospend = 3;
	reqexp = 3;
	preqexp = 0;

	liczniklv = 2;

	pos.x = 0.0f + startnax;
	pos.y = 0.5f;
	pos.z = 0.0f + startnaz;

	dir.x = 0.0f + startnax;
	dir.y = 0.0f;
	dir.z = -1.0f + startnaz;

	kills = 0;

	speed = mmis + przewagagracza;

	adu[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[3] = 1.0f;
	add[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[3] = 1.0f;
	spe[0] = 0.0f;
	spe[1] = 0.0f;
	spe[2] = 0.0f;
	spe[3] = 1.0f;
	adm[0] = adu[0] * add[0];
	adm[1] = adu[1] * add[1];
	adm[2] = adu[2] * add[2];
	adm[3] = adu[3] * add[3];

	stala_ruchu_atak = 0;
	stala_ruchu_nog = 0;
	stala_ruchu_nog2 = 0;
	rzutminy = 0;
	licznikmin = 0;
	for (int i = 0; i < 5; i++)
	{
		mine[i].x = 0;
		mine[i].y = 100;
		mine[i].z = 0;
		mine_wybuch_stala[i] = 0;
	}
	ostatnioatak = 0;

	//rysowanie

	float extra[4];

	extra[0] = .0f;
	extra[1] = 0.15f;
	extra[2] = 0.0f;
	extra[3] = 1.0f;
	dislistMINE = glGenLists(1);
	glNewList(dislistMINE, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	extra[0] = .8f;
	extra[1] = 0.2f;
	extra[2] = 0.2f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glutSolidSphere(.5f, 24, 24);
	glEndList();

	dislist = glGenLists(1);
	glNewList(dislist, GL_COMPILE);

	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// czapka

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();

	glTranslatef(0.0f, 9.6f, 0.0f);
	glPushMatrix();

	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(0.0f, 0.2f, 0.0f);
	glutSolidSphere(0.6, 12, 12);
	glPopMatrix();


	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja

	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .8f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	//maska

	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.2f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.2, 0.6, 24, 24);
	glPopMatrix();


	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();

	// BG

	dislistBG = glGenLists(1);
	glNewList(dislistBG, GL_COMPILE);

	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// czapka
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();

	glTranslatef(0.0f, 9.6f, 0.0f);
	glPushMatrix();

	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(0.0f, 0.2f, 0.0f);
	glutSolidSphere(0.6, 12, 12);
	glPopMatrix();


	// po unikalnych
	*/

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja
	/*
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja

	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .8f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	//maska

	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.2f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.2, 0.6, 24, 24);
	glPopMatrix();
	*/

	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();

}

void Mine::rysuj(int czy_idzie, int czy_atakuje)
{

	/*
	Dla botow
	if (player.pos.x>2000) player.pos.x -= 2000;
	else
	if (player.pos.x<0)	player.pos.x += 2000;
	if (player.pos.z>2000) player.pos.z -= 2000;
	else
	if (player.pos.z<0)	player.pos.z += 2000;
	*/
	if (zycie <= 0)
	{
		this->rysuj_miny();
		this->rysuj_wybuchy();
		this->rysuj_dead();
		return;
	}


	dir.x = player.dir.x;
	dir.y = player.dir.y;
	dir.z = player.dir.z;
	pos.x = player.pos.x;
	pos.y = player.pos.y - 8.5;
	pos.z = player.pos.z;

	/*
	dir.x =0;
	dir.y =0;
	dir.z =0;
	pos.x =0;
	pos.y = 0.5;
	pos.z =0;
	*/

	// dla botow inne


	if (keystate['w'] || keystate['W']) {
		float nowaposx = fmod((player.pos.x + (player.dir.x * speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z + (player.dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['s'] || keystate['S']) {
		float nowaposx = fmod((player.pos.x - (player.dir.x *speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z - (player.dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['d'] || keystate['D']) {
		float nowaposx = fmod((player.pos.x + (-player.dir.z*speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z + (player.dir.x * speed) + 2001), 2001);
		if (0 == map.HeroCatch(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['a'] || keystate['A']) {
		float nowaposx = fmod((player.pos.x - (-player.dir.z*speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z - (player.dir.x * speed) + 2001), 2001);
		if (0 == map.HeroCatch(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}


	this->rysuj_miny();
	this->rysuj_wybuchy();
	float fi = atan2(dir.z, dir.x);
	glTranslatef(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glTranslatef(0, 0, -0.4);
	glPushMatrix();
	// rysowanie podstawki
	// do stalych kolorow
	// kolory gory i dolu
	// unikalne

	// ramiona
	glCallList(dislistBG); // DLA BOTA INNACZEJ!!


						   // rysowanie nog 
	float extra[4];
	if (czy_idzie == 1 || stala_ruchu_nog != 0 || stala_ruchu_nog2 != 0)
	{
		if (stala_ruchu_nog2 == 0)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog > 45)
			{
				PlaySound("sounds/step1.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 1;
			}
		}
		if (stala_ruchu_nog2 == 1)
		{
			stala_ruchu_nog -= 4;
			if (stala_ruchu_nog < -45)
			{
				PlaySound("sounds/step12.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 2;
			}
		}
		if (stala_ruchu_nog2 == 2)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog == 0)
				stala_ruchu_nog2 = 0;
		}
	}

	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);
	glRotatef(0 + stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	glRotatef(0 - stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();

	// rysowanie reki + bron
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glTranslatef(-2.0f, 7.0f, 0.0f);
	if (stala_ruchu_atak != 0 || (czy_atakuje == 1 && ostatnioatak + czasoczekiwan< glutGet(GLUT_ELAPSED_TIME)))
	{
		// pobieram sekundy i jesli roznia sie mniej niz 2 
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME);
		if (stala_ruchu_atak == 0)
			stala_ruchu_atak = (-110);
		stala_ruchu_atak += 2;
		if (stala_ruchu_atak == -2)
			rzutminy = 1;
	}
	glRotatef(-30 + stala_ruchu_atak, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// bron
	glTranslatef(0.0f, -1.5f, 1.0f);
	if (rzutminy != 0)
	{
		glTranslatef(0.0f,
			0 - (rzutminy*0.2), 0 + (rzutminy*0.25)); // odleglosc animacji rzutu
		rzutminy++;
		if (rzutminy == 55)
		{
			PlaySound("sounds/ma1.wav", pos.x, 0, pos.z);
			if (mine[licznikmin].y != 100)
			{
				map.usun_bombe(mine[licznikmin].x, mine[licznikmin].z);
			}
			rzutminy = 0;
			mine_wybuch_stala[licznikmin] = 0;
			mine[licznikmin].x = fmod(((pos.x + 25 * dir.x) + 2001), 2001);
			mine[licznikmin].y = 0.5;
			mine[licznikmin].z = fmod(((pos.z + 25 * dir.z) + 2001), 2001);  // uwzglednic jak animacje ruchu - *0.x = +x

			map.Wst_bombe(mine[licznikmin].x, mine[licznikmin].z, this);

			licznikmin++;
			licznikmin %= 5;
		}
	}
	extra[0] = .0f;
	extra[1] = 0.15f;
	extra[2] = 0.0f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	extra[0] = .8f;
	extra[1] = 0.2f;
	extra[2] = 0.2f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glTranslatef(0.0f, 0.25f, 0.0f);
	glutSolidSphere(.5f, 24, 24);

	glPopMatrix();
}

void Mine::rysuj_dead()
{
	if (how_long_dead == 0)
	{
		map.uwolni(fmod(pos.x + 2001, 2001), fmod(pos.z + 2001, 2001));
		int rando = rand() % 3;
		if (rando == 0)
			PlaySound("sounds/die1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/die2.wav", pos.x, 0, pos.z);
			else
				PlaySound("sounds/die3.wav", pos.x, 0, pos.z);
	}
	if (how_long_dead > 1000)
	{// objekt ma znikac po 1000 sekundach
		this->~Mine(); // lub zycie =1000 nowe miejsce na mapie i howlong dead=0
		return;
	}
	how_long_dead++;
	// rysownie martwego

	// NIE Dla boty!!
	player.dir.y = -1.3;
	player.dir.z = dir.z;
	player.dir.x = dir.x;


	glTranslatef(pos.x, pos.y, pos.z);
	float fi = atan2(dir.z, dir.x);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	if (how_long_dead > 90)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glRotatef(how_long_dead, 1.0f, 0.0f, 0.0f);
		glRotatef(how_long_dead * 2, 0.0f, 1.0f, 0.0f);
	}

	//glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	float extra[4];

	glPushMatrix();
	// rysowanie podstawki

	// unikalne

	// ramiona
	glCallList(dislist);

	// rysowanie nog 
	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);

	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();
	// rysowanie reki broni
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glRotatef(-15.0f, .0f, 0.0f, 1.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();
}

void Mine::heal()
{
	if (pointstospend>0 && zycie>0)
	{
		PlaySound("sounds/heal.wav", pos.x, 0, pos.z);
		pointstospend--;
		zycie = calezycie;
	}
}

void Mine::incraselife()
{
	if (pointstospend>0)
	{
		PlaySound("sounds/lif.wav", pos.x, 0, pos.z);
		pointstospend--;
		calezycie *= 1.5;
	}
}

void Mine::incraseatak()
{
	if (pointstospend>0)
	{
		PlaySound("sounds/ata.wav", pos.x, 0, pos.z);
		pointstospend--;
		silaataku *= 1.5;
	}
}


class SMine : public hero
{
public:
	void dodajkill();
	int podajatak();
	void odejmijzycie(int);
	void heal();
	void incraselife();
	void incraseatak();
	float adu[4]; // Ambient  diffuse up
	float add[4];// Ambient  diffuse down
	float adm[4];// Ambient  diffuse up*down
	float spe[4]; //Specular
				  //int mine_wybuch_stala[5];
	SMine(float, float); // przekazujemy poziom x, z. y pozostaje bez zmian bo nie zmieniam wysokosci
	~SMine();
	void rysuj(int, int); // // uwzglednic przypadek kiedy punkty zycia sa 0 to bedzie uruchamiany dead
	void setcolors(float, float, float, float, float, float); // up r g b, down r g b
	void rysuj_wybuchy(/*hero* */);
private:
	void rysuj_dead();
	void rysuj_miny();
	int stala_ruchu_nog;
	int stala_ruchu_nog2;
	int stala_ruchu_atak;
	int rzutminy;
	int licznikmin;
	GLuint dislist;
	GLuint dislistBG;
	GLuint dislistMINE;
};

int SMine::podajatak()
{
	return(silaataku);
}

void SMine::dodajkill()
{
	killmine++;
}

void SMine::odejmijzycie(int points)
{
	zycie -= points;
	zycoika = glutGet(GLUT_ELAPSED_TIME) + 32;
	if (zycie <= 0)
		zycie = 0;
	else
	{
		int rando = rand() % 4;
		if (rando == 0)
			PlaySound("sounds/hi1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/hi2.wav", pos.x, 0, pos.z);
			else
				if (rando == 2)
					PlaySound("sounds/hi3.wav", pos.x, 0, pos.z);
				else
					PlaySound("sounds/hi4.wav", pos.x, 0, pos.z);
	}
}

SMine::~SMine()
{}

void SMine::setcolors(float cur, float cug, float cub, float cdr, float cdg, float cdb)
{
	adu[0] = cur;
	adu[1] = cug;
	adu[2] = cub;
	add[0] = cdr;
	add[1] = cdg;
	add[2] = cdb;
}

void SMine::rysuj_wybuchy(/*hero* */)
{
	for (int i = 0; i < 5; i++)
	{
		if (mine[i].y >= 99 || mine_wybuch_stala[i] == 0)
			goto x;

		float xxx = mine[i].x, zzz = mine[i].z;

		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;

		l2_pos[0] = xxx;
		l2_pos[1] = mine[i].y;
		l2_pos[2] = zzz;
		l2_pos[3] = 1.0;
		glEnable(GL_LIGHT2);

		glPushMatrix();
		glTranslatef(xxx, mine[i].y - 0.5, zzz);

		if (mine_wybuch_stala[i] == 1)
			PlaySound("sounds/ma2.wav", xxx, 0, zzz);

		float extra[4];
		extra[0] = 0.7f;
		extra[1] = 0.0f;
		extra[2] = 0.0f;
		extra[3] = 1.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
		glMaterialfv(GL_FRONT, GL_SPECULAR, extra);
		glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
		glutSolidSphere(0.5* hero::mine_wybuch_stala[i], 11, 11);
		glPopMatrix();



		hero::mine_wybuch_stala[i] += 4;

		if (hero::mine_wybuch_stala[i] >= 38)
		{
			mine[i].y = 100;
			hero::mine_wybuch_stala[i] = 0;
			glDisable(GL_LIGHT2);
		}

	x:;
	}
}

void SMine::rysuj_miny()
{
	for (int i = 0; i < 5; i++)
	{
		if (mine[i].y >= 99)
			goto x;



		float xxx = mine[i].x, zzz = mine[i].z;

		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;

		glPushMatrix();
		glTranslatef(xxx, mine[i].y - 0.5, zzz);
		glCallList(dislistMINE);
		glPopMatrix();

	x:;
	}
}

SMine::SMine(float startnax, float startnaz)
{
	klasa = 'i';
	for (int i = -2; i < 3; i++)
		for (int j = -2; j < 3; j++)
		{
			map.postac[((int)startnax + i + 2001) % 2001][((int)startnaz + j + 2001) % 2001] = this;
		}
	czasoczekiwan = 3000;
	silaataku = 1000;
	calezycie = zyciepostaciMINE;
	zycie = calezycie;
	how_long_dead = 0;

	levelanimation = 0;

	pointstospend = 3;
	reqexp = 3;
	preqexp = 0;

	liczniklv = 2;

	pos.x = 0.0f + startnax;
	pos.y = 0.5f;
	pos.z = 0.0f + startnaz;

	dir.x = 0.0f + startnax;
	dir.y = 0.0f;
	dir.z = -1.0f + startnaz;

	kills = 0;

	speed = mmis + przewagagracza;
	adu[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[3] = 1.0f;
	add[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[3] = 1.0f;
	spe[0] = 0.0f;
	spe[1] = 0.0f;
	spe[2] = 0.0f;
	spe[3] = 1.0f;
	adm[0] = adu[0] * add[0];
	adm[1] = adu[1] * add[1];
	adm[2] = adu[2] * add[2];
	adm[3] = adu[3] * add[3];

	stala_ruchu_atak = 0;
	stala_ruchu_nog = 0;
	stala_ruchu_nog2 = 0;
	rzutminy = 0;
	licznikmin = 0;
	for (int i = 0; i < 5; i++)
	{
		mine[i].x = 0;
		mine[i].y = 100;
		mine[i].z = 0;
		mine_wybuch_stala[i] = 0;
	}
	ostatnioatak = 0;

	//rysowanie

	float extra[4];

	extra[0] = .0f;
	extra[1] = 0.15f;
	extra[2] = 0.0f;
	extra[3] = 1.0f;
	dislistMINE = glGenLists(1);
	glNewList(dislistMINE, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	extra[0] = .8f;
	extra[1] = 0.2f;
	extra[2] = 0.2f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glutSolidSphere(.5f, 24, 24);
	glEndList();

	dislist = glGenLists(1);
	glNewList(dislist, GL_COMPILE);

	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// czapka

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();

	glTranslatef(0.0f, 9.6f, 0.0f);
	glPushMatrix();

	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(0.0f, 0.2f, 0.0f);
	glutSolidSphere(0.6, 12, 12);
	glPopMatrix();


	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja

	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .8f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	//maska

	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.2f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.2, 0.6, 24, 24);
	glPopMatrix();


	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();

	// BG

	dislistBG = glGenLists(1);
	glNewList(dislistBG, GL_COMPILE);

	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// czapka
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();

	glTranslatef(0.0f, 9.6f, 0.0f);
	glPushMatrix();

	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(0.0f, 0.2f, 0.0f);
	glutSolidSphere(0.6, 12, 12);
	glPopMatrix();


	// po unikalnych
	*/

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja
	/*
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja

	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .8f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	//maska

	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.2f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.2, 0.6, 24, 24);
	glPopMatrix();
	*/

	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();

}

void SMine::rysuj(int czy_idzie, int czy_atakuje)
{

	/*
	Dla botow
	if (player.pos.x>2000) player.pos.x -= 2000;
	else
	if (player.pos.x<0)	player.pos.x += 2000;
	if (player.pos.z>2000) player.pos.z -= 2000;
	else
	if (player.pos.z<0)	player.pos.z += 2000;
	*/
	if (zycie <= 0)
	{
		this->rysuj_miny();
		this->rysuj_wybuchy();
		this->rysuj_dead();
		return;
	}

	if (killmine != kills)
	{
		kills = killmine;
		PlaySound("sounds/lz.wav", pos.x, 0, pos.z);
	}

	if (killmine >= reqexp - 2)
	{
		PlaySound("sounds/f.wav", pos.x, 0, pos.z);
		levelanimation = 1;
		textanim1 = 1;
		preqexp = reqexp - 2;
		reqexp += +liczniklv;
		liczniklv++;
		pointstospend++;
	}

	dir.x = player.dir.x;
	dir.y = player.dir.y;
	dir.z = player.dir.z;
	pos.x = player.pos.x;
	pos.y = player.pos.y - 8.5;
	pos.z = player.pos.z;

	/*
	dir.x =0;
	dir.y =0;
	dir.z =0;
	pos.x =0;
	pos.y = 0.5;
	pos.z =0;
	*/

	// dla botow inne


	if (keystate['w'] || keystate['W']) {
		float nowaposx = fmod((player.pos.x + (player.dir.x * speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z + (player.dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['s'] || keystate['S']) {
		float nowaposx = fmod((player.pos.x - (player.dir.x *speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z - (player.dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['d'] || keystate['D']) {
		float nowaposx = fmod((player.pos.x + (-player.dir.z*speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z + (player.dir.x * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['a'] || keystate['A']) {
		float nowaposx = fmod((player.pos.x - (-player.dir.z*speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z - (player.dir.x * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}


	this->rysuj_miny();
	this->rysuj_wybuchy();
	float fi = atan2(dir.z, dir.x);
	glTranslatef(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glTranslatef(0, 0, -0.4);
	glPushMatrix();
	// rysowanie podstawki
	// do stalych kolorow
	// kolory gory i dolu
	// unikalne

	// ramiona
	glCallList(dislistBG); // DLA BOTA INNACZEJ!!


						   // rysowanie nog 
	float extra[4];
	if (czy_idzie == 1 || stala_ruchu_nog != 0 || stala_ruchu_nog2 != 0)
	{
		if (stala_ruchu_nog2 == 0)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog > 45)
			{
				PlaySound("sounds/step1.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 1;
			}
		}
		if (stala_ruchu_nog2 == 1)
		{
			stala_ruchu_nog -= 4;
			if (stala_ruchu_nog < -45)
			{
				PlaySound("sounds/step12.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 2;
			}
		}
		if (stala_ruchu_nog2 == 2)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog == 0)
				stala_ruchu_nog2 = 0;
		}
	}

	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);
	glRotatef(0 + stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	glRotatef(0 - stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();

	// rysowanie reki + bron
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glTranslatef(-2.0f, 7.0f, 0.0f);
	if (stala_ruchu_atak != 0 || (czy_atakuje == 1 && ostatnioatak + czasoczekiwan< glutGet(GLUT_ELAPSED_TIME)))
	{
		// pobieram sekundy i jesli roznia sie mniej niz 2 
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME);
		if (stala_ruchu_atak == 0)
			stala_ruchu_atak = (-110);
		stala_ruchu_atak += 2;
		if (stala_ruchu_atak == -2)
			rzutminy = 1;
	}
	glRotatef(-30 + stala_ruchu_atak, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// bron
	glTranslatef(0.0f, -1.5f, 1.0f);
	if (rzutminy != 0)
	{
		glTranslatef(0.0f,
			0 - (rzutminy*0.2), 0 + (rzutminy*0.25)); // odleglosc animacji rzutu
		rzutminy++;
		if (rzutminy == 55)
		{
			PlaySound("sounds/ma1.wav", pos.x, 0, pos.z);
			if (mine[licznikmin].y != 100)
			{
				map.usun_bombe(mine[licznikmin].x, mine[licznikmin].z);
			}
			rzutminy = 0;
			mine_wybuch_stala[licznikmin] = 0;
			mine[licznikmin].x = fmod(((pos.x + 25 * dir.x) + 2001), 2001);
			mine[licznikmin].y = 0.5;
			mine[licznikmin].z = fmod(((pos.z + 25 * dir.z) + 2001), 2001);  // uwzglednic jak animacje ruchu - *0.x = +x

			map.Wst_bombe(mine[licznikmin].x, mine[licznikmin].z, this);

			licznikmin++;
			licznikmin %= 5;
		}
	}
	extra[0] = .0f;
	extra[1] = 0.15f;
	extra[2] = 0.0f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	extra[0] = .8f;
	extra[1] = 0.2f;
	extra[2] = 0.2f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glTranslatef(0.0f, 0.25f, 0.0f);
	glutSolidSphere(.5f, 24, 24);

	glPopMatrix();
}

void SMine::rysuj_dead()
{
	if (how_long_dead == 0)
	{
		map.uwolni(fmod(pos.x + 2001, 2001), fmod(pos.z + 2001, 2001));
		int rando = rand() % 3;
		if (rando == 0)
			PlaySound("sounds/die1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/die2.wav", pos.x, 0, pos.z);
			else
				PlaySound("sounds/die3.wav", pos.x, 0, pos.z);
	}
	if (how_long_dead > 1000)
	{// objekt ma znikac po 1000 sekundach
		return;
	}
	how_long_dead++;
	// rysownie martwego

	// NIE Dla boty!!
	player.dir.y = -1.3;
	player.dir.z = dir.z;
	player.dir.x = dir.x;


	glTranslatef(pos.x, pos.y, pos.z);
	float fi = atan2(dir.z, dir.x);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	if (how_long_dead > 90)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glRotatef(how_long_dead, 1.0f, 0.0f, 0.0f);
		glRotatef(how_long_dead * 2, 0.0f, 1.0f, 0.0f);
	}

	//glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	float extra[4];

	glPushMatrix();
	// rysowanie podstawki

	// unikalne

	// ramiona
	glCallList(dislist);

	// rysowanie nog 
	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);

	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();
	// rysowanie reki broni
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glRotatef(-15.0f, .0f, 0.0f, 1.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();
}

void SMine::heal()
{
	if (pointstospend>0 && zycie>0)
	{
		PlaySound("sounds/heal.wav", pos.x, 0, pos.z);
		pointstospend--;
		zycie = calezycie;
	}
}

void SMine::incraselife()
{
	if (pointstospend>0)
	{
		PlaySound("sounds/lif.wav", pos.x, 0, pos.z);
		pointstospend--;
		calezycie *= 1.5;
	}
}

void SMine::incraseatak()
{
	if (pointstospend>0)
	{
		PlaySound("sounds/ata.wav", pos.x, 0, pos.z);
		pointstospend--;
		silaataku *= 1.5;
	}
}


class BMine : public hero
{
public:
	int strona;
	float smialosc;
	void dodajkill();
	int podajatak();
	void odejmijzycie(int);
	void heal();
	void incraselife();
	void incraseatak();

	vector3d victimpos; // pozycja bohatera
	vector3d temp; // pozycja bohatera
	float adu[4]; // Ambient  diffuse up
	float add[4];// Ambient  diffuse down
	float adm[4];// Ambient  diffuse up*down
	float spe[4]; //Specular
				  //int mine_wybuch_stala[5];
	BMine(float, float); // przekazujemy poziom x, z. y pozostaje bez zmian bo nie zmieniam wysokosci
	~BMine();
	void rysuj(int, int); // // uwzglednic przypadek kiedy punkty zycia sa 0 to bedzie uruchamiany dead
	void setcolors(float, float, float, float, float, float); // up r g b, down r g b
	void rysuj_wybuchy(/*hero* */);
	void dodajkille(int);
private:
	void rysuj_dead();
	void rysuj_miny();
	int stala_ruchu_nog;
	int stala_ruchu_nog2;
	int stala_ruchu_atak;
	int rzutminy;
	int licznikmin;
	GLuint dislist;
	GLuint dislistMINE;
};

int BMine::podajatak()
{
	return(silaataku);
}

void BMine::dodajkill()
{
	kills++;
	if (kills >= reqexp - 2)
	{
		preqexp = reqexp - 2;
		reqexp += +liczniklv;
		liczniklv++;
		pointstospend++;
	}
}

void BMine::odejmijzycie(int points)
{
	zycie -= points;
	if (zycie <= 0)
		zycie = 0;
	else
	{
		int rando = rand() % 4;
		if (rando == 0)
			PlaySound("sounds/hi1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/hi2.wav", pos.x, 0, pos.z);
			else
				if (rando == 2)
					PlaySound("sounds/hi3.wav", pos.x, 0, pos.z);
				else
					PlaySound("sounds/hi4.wav", pos.x, 0, pos.z);
	}
}

BMine::~BMine()
{}

void BMine::setcolors(float cur, float cug, float cub, float cdr, float cdg, float cdb)
{
	adu[0] = cur;
	adu[1] = cug;
	adu[2] = cub;
	add[0] = cdr;
	add[1] = cdg;
	add[2] = cdb;
}

void BMine::rysuj_wybuchy(/*hero* */)
{
	for (int i = 0; i < 5; i++)
	{
		if (mine[i].y >= 99 || mine_wybuch_stala[i] == 0)
			goto x;

		float xxx = mine[i].x, zzz = mine[i].z;

		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;

		l4_pos[0] = xxx;
		l4_pos[1] = mine[i].y;
		l4_pos[2] = zzz;
		l4_pos[3] = 1.0;
		glEnable(GL_LIGHT4);

		glPushMatrix();
		glTranslatef(xxx, mine[i].y - 0.5, zzz);

		if (mine_wybuch_stala[i] == 1)
			PlaySound("sounds/ma2.wav", xxx, 0, zzz);

		float extra[4];
		extra[0] = 0.7f;
		extra[1] = 0.0f;
		extra[2] = 0.0f;
		extra[3] = 1.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
		glMaterialfv(GL_FRONT, GL_SPECULAR, extra);
		glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
		glutSolidSphere(0.5* hero::mine_wybuch_stala[i], 11, 11);
		glPopMatrix();



		hero::mine_wybuch_stala[i] += 4;

		if (hero::mine_wybuch_stala[i] >= 38)
		{
			mine[i].y = 100;
			hero::mine_wybuch_stala[i] = 0;
			glDisable(GL_LIGHT4);
		}

	x:;
	}
}

void BMine::rysuj_miny()
{
	for (int i = 0; i < 5; i++)
	{
		if (mine[i].y >= 99)
			goto x;

		float xxx = mine[i].x, zzz = mine[i].z;

		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;

		glPushMatrix();
		glTranslatef(xxx, mine[i].y - 0.5, zzz);
		glCallList(dislistMINE);
		glPopMatrix();

	x:;
	}
}

BMine::BMine(float startnax, float startnaz)
{

	klasa = 'i';
	smialosc = (rand() % 1000)*0.01;

	for (int i = -2; i < 3; i++)
		for (int j = -2; j < 3; j++)
		{
			map.postac[((int)startnax + i + 2001) % 2001][((int)startnaz + j + 2001) % 2001] = this;
		}

	czasoczekiwan = 3000;
	silaataku = 1000;
	calezycie = zyciepostaciMINE;
	zycie = calezycie;
	how_long_dead = 0;

	levelanimation = 0;

	pointstospend = 3;
	reqexp = 3;
	preqexp = 0;

	liczniklv = 2;

	pos.x = 0.0f + startnax;
	pos.y = 0.5f;
	pos.z = 0.0f + startnaz;

	dir.x = 0.0f + startnax;
	dir.y = 0.0f;
	dir.z = -1.0f + startnaz;

	kills = 0;

	speed = mmis;
	adu[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[3] = 1.0f;
	add[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[3] = 1.0f;
	spe[0] = 0.0f;
	spe[1] = 0.0f;
	spe[2] = 0.0f;
	spe[3] = 1.0f;
	adm[0] = adu[0] * add[0];
	adm[1] = adu[1] * add[1];
	adm[2] = adu[2] * add[2];
	adm[3] = adu[3] * add[3];


	stala_ruchu_atak = 0;
	stala_ruchu_nog = 0;
	stala_ruchu_nog2 = 0;
	rzutminy = 0;
	licznikmin = 0;
	for (int i = 0; i < 5; i++)
	{
		mine[i].x = 0;
		mine[i].y = 100;
		mine[i].z = 0;
		mine_wybuch_stala[i] = 0;
	}
	ostatnioatak = 0;

	//rysowanie

	float extra[4];

	extra[0] = .0f;
	extra[1] = 0.15f;
	extra[2] = 0.0f;
	extra[3] = 1.0f;
	dislistMINE = glGenLists(1);
	glNewList(dislistMINE, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	extra[0] = .8f;
	extra[1] = 0.2f;
	extra[2] = 0.2f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glutSolidSphere(.5f, 24, 24);
	glEndList();

	dislist = glGenLists(1);
	glNewList(dislist, GL_COMPILE);

	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// czapka

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();

	glTranslatef(0.0f, 9.6f, 0.0f);
	glPushMatrix();

	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(0.0f, 0.2f, 0.0f);
	glutSolidSphere(0.6, 12, 12);
	glPopMatrix();


	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja

	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .8f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	//maska

	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.2f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.2, 0.6, 24, 24);
	glPopMatrix();


	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();

	/*// BG

	dislistBG = glGenLists(1);
	glNewList(dislistBG, GL_COMPILE);

	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// czapka
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();

	glTranslatef(0.0f, 9.6f, 0.0f);
	glPushMatrix();

	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(0.0f, 0.2f, 0.0f);
	glutSolidSphere(0.6, 12, 12);
	glPopMatrix();


	// po unikalnych


	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja
	/*
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja

	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .8f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	//maska

	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.2f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.2, 0.6, 24, 24);
	glPopMatrix();


	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();
	*/
}

void BMine::rysuj(int czy_idzie, int czy_atakuje)
{
	czy_idzie = 1;
	czy_atakuje = 0;
	if (zycie <= 0)
	{
		this->rysuj_miny();
		this->rysuj_wybuchy();
		this->rysuj_dead();
		return;
	}

	// znajdywanie celu

	float minn = -2;

	for (int i = 0; i < heroses.size(); i++)
	{
		if (heroses[i] == this || heroses[i]->how_long_dead>0)
			;
		else
		{
			if (pos.x - heroses[i]->pos.x < -1000)
				temp.x = heroses[i]->pos.x - 2001 - pos.x;
			else
				if (pos.x - heroses[i]->pos.x > 1000)
					temp.x = heroses[i]->pos.x + 2001 - pos.x;
				else
					temp.x = heroses[i]->pos.x - pos.x;

			if (pos.z - heroses[i]->pos.z < -1000)
				temp.z = heroses[i]->pos.z - 2001 - pos.z;
			else
				if (pos.z - heroses[i]->pos.z > 1000)
					temp.z = heroses[i]->pos.z + 2001 - pos.z;
				else
					temp.z = heroses[i]->pos.z - pos.z;


			temp.y = sqrtf(pow(temp.z, 2) + pow(temp.x, 2));


			if (temp.y < minn || minn <= -1)
			{
				minn = temp.y;
				victimpos.x = heroses[i]->pos.x;
				victimpos.z = heroses[i]->pos.z;
				victimpos.y = temp.y; // odleglosc miedzy ludzikami

				dir.y = 0;
				dir.x = temp.x / temp.y;
				dir.z = temp.z / temp.y;
			}
		}
	}

	temp.y = victimpos.y;
	if (pointstospend>0)
		if (zycie <= calezycie*0.4)
			heal();
		else
			if (rand() % 2)
				incraselife();
			else
				incraseatak();


	// dla botow inne

	if (temp.y>20 + smialosc)// podchodzi
	{
		float nowaposx = fmod((pos.x + (dir.x *speed) + 2001), 2001);
		float nowaposz = fmod((pos.z + (dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
		{
			pos.x = nowaposx;
			pos.z = nowaposz;
		}
		else
		{ // nie da sie do przodu
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 2;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 300;
			}

			if (strona == 1)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
				if (strona == 0)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
				else
					czy_idzie = 0;
		}
		if (temp.y < 90)
		{
			if (rand() % 30 == 0)
				czy_atakuje = 1;
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 3;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 700;
			}
			if (strona == 0)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
				if (strona == 1)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
		}
	}
	else
	{
		czy_atakuje = 1;
		if (temp.y < 20 + smialosc) // ucieka
		{
			float nowaposx = fmod((pos.x - (dir.x *speed) + 2001), 2001);
			float nowaposz = fmod((pos.z - (dir.z * speed) + 2001), 2001);
			if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
			{
				pos.x = nowaposx;
				pos.z = nowaposz;
			}
			else
			{
				if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
				{
					strona = rand() % 2;
					levelanimation = glutGet(GLUT_ELAPSED_TIME) + 300;
				}
				if (strona == 0)
				{
					nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
				else
					if (strona == 1)
					{
						nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
						nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
						if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
						{
							pos.x = nowaposx;
							pos.z = nowaposz;
						}
						else
							strona = 3;
					}
					else
						czy_idzie = 0;
			}
		}
		else
		{

			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 2;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 1000;
			}
			if (strona == 0)
			{
				float	nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				float nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
			{
				if (strona == 1)
				{
					float nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					float nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
				else
					czy_idzie = 0;
			}
		}
	}




	float xxx = pos.x, zzz = pos.z;

	if (xxx - player.pos.x >= 1900)
		xxx -= 2001;
	else
		if (player.pos.x - xxx >= 1900)
			xxx += 2001;

	if (zzz - player.pos.z >= 1900)
		zzz -= 2001;
	else
		if (player.pos.z - zzz >= 1900)
			zzz += 2001;

	this->rysuj_miny();
	this->rysuj_wybuchy();
	float fi = atan2(dir.z, dir.x);
	glTranslatef(xxx, pos.y, zzz);

	float extra[4];
	// Pasek zycia
	glPushMatrix();
	glTranslatef(0, 11.5, 0);
	glRotatef(atan2(Gracz->dir.z, Gracz->dir.x)*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	extra[0] = 1.0f - (0.04*(kills - Gracz->kills));
	extra[1] = 0.0f;
	extra[2] = 0.0f + (0.01*(kills - Gracz->kills));
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glScalef(5.0*((float)zycie / (float)calezycie), 0.5, 1);
	glutSolidCube(1);
	glPopMatrix();


	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	// rysowanie podstawki
	// do stalych kolorow
	// kolory gory i dolu
	// unikalne

	
	// ramiona
	glCallList(dislist); // DLA BOTA INNACZEJ!!


						 // rysowanie nog 

	if (czy_idzie == 1 || stala_ruchu_nog != 0 || stala_ruchu_nog2 != 0)
	{
		if (stala_ruchu_nog2 == 0)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog > 45)
			{
				PlaySound("sounds/step1.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 1;
			}
		}
		if (stala_ruchu_nog2 == 1)
		{
			stala_ruchu_nog -= 4;
			if (stala_ruchu_nog < -45)
			{
				PlaySound("sounds/step12.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 2;
			}
		}
		if (stala_ruchu_nog2 == 2)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog == 0)
				stala_ruchu_nog2 = 0;
		}
	}

	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);
	glRotatef(0 + stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	glRotatef(0 - stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();

	// rysowanie reki + bron
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glTranslatef(-2.0f, 7.0f, 0.0f);
	if (stala_ruchu_atak != 0 || (czy_atakuje == 1 && ostatnioatak + czasoczekiwan< glutGet(GLUT_ELAPSED_TIME)))
	{
		// pobieram sekundy i jesli roznia sie mniej niz 2 
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME);
		if (stala_ruchu_atak == 0)
			stala_ruchu_atak = (-110);
		stala_ruchu_atak += 2;
		if (stala_ruchu_atak == -2)
			rzutminy = 1;
	}
	glRotatef(-30 + stala_ruchu_atak, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// bron
	glTranslatef(0.0f, -1.5f, 1.0f);
	if (rzutminy != 0)
	{
		glTranslatef(0.0f,
			0 - (rzutminy*0.2), 0 + (rzutminy*0.25)); // odleglosc animacji rzutu
		rzutminy++;
		if (rzutminy == 55)
		{
			PlaySound("sounds/ma1.wav", pos.x, 0, pos.z);
			if (mine[licznikmin].y != 100)
			{
				map.usun_bombe(mine[licznikmin].x, mine[licznikmin].z);
			}
			rzutminy = 0;
			mine_wybuch_stala[licznikmin] = 0;
			mine[licznikmin].x = fmod(((pos.x + 25 * dir.x) + 2001), 2001);
			mine[licznikmin].y = 0.5;
			mine[licznikmin].z = fmod(((pos.z + 25 * dir.z) + 2001), 2001);  // uwzglednic jak animacje ruchu - *0.x = +x

			map.Wst_bombe(mine[licznikmin].x, mine[licznikmin].z, this);

			licznikmin++;
			licznikmin %= 5;
		}
	}
	extra[0] = .0f;
	extra[1] = 0.15f;
	extra[2] = 0.0f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	extra[0] = .8f;
	extra[1] = 0.2f;
	extra[2] = 0.2f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glTranslatef(0.0f, 0.25f, 0.0f);
	glutSolidSphere(.5f, 24, 24);

	glPopMatrix();
}

void BMine::rysuj_dead()
{
	if (how_long_dead == 0)
	{
		map.uwolni(fmod(pos.x + 2001, 2001), fmod(pos.z + 2001, 2001));
		int rando = rand() % 3;
		if (rando == 0)
			PlaySound("sounds/die1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/die2.wav", pos.x, 0, pos.z);
			else
				PlaySound("sounds/die3.wav", pos.x, 0, pos.z);
	}
	if (how_long_dead > 1000)
	{// objekt ma znikac po 1000 sekundach

		pos = map.BotStart();
		pos.y = 0.5;
		zycie = calezycie;
		for (int i = -2; i < 3; i++)
			for (int j = -2; j < 3; j++)
				map.postac[((int)pos.x + i + 2001) % 2001][((int)pos.z + j + 2001) % 2001] = this;
		for (int i = 0; i < 5; i++)
		{
			map.usun_bombe(mine[i].x, mine[i].z);
			mine[i].x = 0;
			mine[i].y = 100;
			mine[i].z = 0;
			mine_wybuch_stala[i] = 0;
		}
		how_long_dead = 0;
		stala_ruchu_atak = 0;
		stala_ruchu_nog = 0;
		stala_ruchu_nog2 = 0;
		rzutminy = 0;
		licznikmin = 0;
		ostatnioatak = 0;

		dir.x = 0.0f + pos.x;
		dir.y = 0.0f;
		dir.z = -1.0f + pos.z;
		return;
	}
	how_long_dead++;
	// rysownie martwego

	// NIE Dla boty!!


	float xxx = pos.x, zzz = pos.z;

	if (xxx - player.pos.x >= 1900)
		xxx -= 2001;
	else
		if (player.pos.x - xxx >= 1900)
			xxx += 2001;

	if (zzz - player.pos.z >= 1900)
		zzz -= 2001;
	else
		if (player.pos.z - zzz >= 1900)
			zzz += 2001;


	glTranslatef(xxx, pos.y, zzz);
	float fi = atan2(dir.z, dir.x);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	if (how_long_dead > 90)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glRotatef(how_long_dead, 1.0f, 0.0f, 0.0f);
		glRotatef(how_long_dead * 2, 0.0f, 1.0f, 0.0f);
	}

	//glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	float extra[4];

	glPushMatrix();
	// rysowanie podstawki

	// unikalne

	// ramiona
	glCallList(dislist);

	// rysowanie nog 
	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);

	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();
	// rysowanie reki broni
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glRotatef(-15.0f, .0f, 0.0f, 1.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();
}

void BMine::heal()
{
	if (pointstospend>0 && zycie>0)
	{
		pointstospend--;
		zycie = calezycie;
	}
}

void BMine::incraselife()
{
	if (pointstospend>0)
	{
		pointstospend--;
		calezycie *= 1.5;
	}
}

void BMine::incraseatak()
{
	if (pointstospend>0)
	{
		pointstospend--;
		silaataku *= 1.5;
	}
}

void BMine::dodajkille(int ilosc)
{
	for (int i = 0; i < ilosc; i++)
		dodajkill();
}


class SBMine : public hero
{
public:
	int strona;
	float smialosc;
	void dodajkill();
	int podajatak();
	void odejmijzycie(int);
	void heal();
	void incraselife();
	void incraseatak();

	vector3d victimpos; // pozycja bohatera
	vector3d temp; // pozycja bohatera
	float adu[4]; // Ambient  diffuse up
	float add[4];// Ambient  diffuse down
	float adm[4];// Ambient  diffuse up*down
	float spe[4]; //Specular
				  //int mine_wybuch_stala[5];
	SBMine(float, float); // przekazujemy poziom x, z. y pozostaje bez zmian bo nie zmieniam wysokosci
	~SBMine();
	void rysuj(int, int); // // uwzglednic przypadek kiedy punkty zycia sa 0 to bedzie uruchamiany dead
	void setcolors(float, float, float, float, float, float); // up r g b, down r g b
	void rysuj_wybuchy(/*hero* */);
	void dodajkille(int);
private:
	void rysuj_dead();
	void rysuj_miny();
	int stala_ruchu_nog;
	int stala_ruchu_nog2;
	int stala_ruchu_atak;
	int rzutminy;
	int licznikmin;
	GLuint dislist;
	GLuint dislistMINE;
};

int SBMine::podajatak()
{
	return(silaataku);
}

void SBMine::dodajkill()
{
	killmine++;
}

void SBMine::odejmijzycie(int points)
{
	zycie -= points;
	if (zycie <= 0)
		zycie = 0;
	else
	{
		int rando = rand() % 4;
		if (rando == 0)
			PlaySound("sounds/hi1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/hi2.wav", pos.x, 0, pos.z);
			else
				if (rando == 2)
					PlaySound("sounds/hi3.wav", pos.x, 0, pos.z);
				else
					PlaySound("sounds/hi4.wav", pos.x, 0, pos.z);
	}
}

SBMine::~SBMine()
{}

void SBMine::setcolors(float cur, float cug, float cub, float cdr, float cdg, float cdb)
{
	adu[0] = cur;
	adu[1] = cug;
	adu[2] = cub;
	add[0] = cdr;
	add[1] = cdg;
	add[2] = cdb;
}

void SBMine::rysuj_wybuchy(/*hero* */)
{
	for (int i = 0; i < 5; i++)
	{
		if (mine[i].y >= 99 || mine_wybuch_stala[i] == 0)
			goto x;


		float xxx = mine[i].x, zzz = mine[i].z;

		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;

		l4_pos[0] = xxx;
		l4_pos[1] = mine[i].y;
		l4_pos[2] = zzz;
		l4_pos[3] = 1.0;
		glEnable(GL_LIGHT4);

		glPushMatrix();
		glTranslatef(xxx, mine[i].y - 0.5, zzz);

		if (mine_wybuch_stala[i] == 1)
			PlaySound("sounds/ma2.wav", xxx, 0, zzz);

		float extra[4];
		extra[0] = 0.7f;
		extra[1] = 0.0f;
		extra[2] = 0.0f;
		extra[3] = 1.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
		glMaterialfv(GL_FRONT, GL_SPECULAR, extra);
		glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
		glutSolidSphere(0.5* hero::mine_wybuch_stala[i], 11, 11);
		glPopMatrix();



		hero::mine_wybuch_stala[i] += 4;

		if (hero::mine_wybuch_stala[i] >= 38)
		{
			mine[i].y = 100;
			hero::mine_wybuch_stala[i] = 0;
			glDisable(GL_LIGHT4);
		}

	x:;
	}
}

void SBMine::rysuj_miny()
{
	for (int i = 0; i < 5; i++)
	{
		if (mine[i].y >= 99)
			goto x;

		float xxx = mine[i].x, zzz = mine[i].z;

		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;

		glPushMatrix();
		glTranslatef(xxx, mine[i].y - 0.5, zzz);
		glCallList(dislistMINE);
		glPopMatrix();

	x:;
	}
}

SBMine::SBMine(float startnax, float startnaz)
{

	klasa = 'i';
	smialosc = (rand() % 1000)*0.01;

	for (int i = -2; i < 3; i++)
		for (int j = -2; j < 3; j++)
		{
			map.postac[((int)startnax + i + 2001) % 2001][((int)startnaz + j + 2001) % 2001] = this;
		}

	czasoczekiwan = 3000;
	silaataku = 1000;
	calezycie = zyciepostaciMINE;
	zycie = calezycie;
	how_long_dead = 0;

	levelanimation = 0;

	pointstospend = 3;
	reqexp = 3;
	preqexp = 0;

	liczniklv = 2;

	pos.x = 0.0f + startnax;
	pos.y = 0.5f;
	pos.z = 0.0f + startnaz;

	dir.x = 0.0f + startnax;
	dir.y = 0.0f;
	dir.z = -1.0f + startnaz;

	kills = 0;

	speed = mmis;
	adu[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[3] = 1.0f;
	add[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[3] = 1.0f;
	spe[0] = 0.0f;
	spe[1] = 0.0f;
	spe[2] = 0.0f;
	spe[3] = 1.0f;
	adm[0] = adu[0] * add[0];
	adm[1] = adu[1] * add[1];
	adm[2] = adu[2] * add[2];
	adm[3] = adu[3] * add[3];


	stala_ruchu_atak = 0;
	stala_ruchu_nog = 0;
	stala_ruchu_nog2 = 0;
	rzutminy = 0;
	licznikmin = 0;
	for (int i = 0; i < 5; i++)
	{
		mine[i].x = 0;
		mine[i].y = 100;
		mine[i].z = 0;
		mine_wybuch_stala[i] = 0;
	}
	ostatnioatak = 0;

	//rysowanie

	float extra[4];

	extra[0] = .0f;
	extra[1] = 0.15f;
	extra[2] = 0.0f;
	extra[3] = 1.0f;
	dislistMINE = glGenLists(1);
	glNewList(dislistMINE, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	extra[0] = .8f;
	extra[1] = 0.2f;
	extra[2] = 0.2f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glutSolidSphere(.5f, 24, 24);
	glEndList();

	dislist = glGenLists(1);
	glNewList(dislist, GL_COMPILE);

	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// czapka

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();

	glTranslatef(0.0f, 9.6f, 0.0f);
	glPushMatrix();

	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(0.0f, 0.2f, 0.0f);
	glutSolidSphere(0.6, 12, 12);
	glPopMatrix();


	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja

	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .8f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	//maska

	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.2f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.2, 0.6, 24, 24);
	glPopMatrix();


	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();

	/*// BG

	dislistBG = glGenLists(1);
	glNewList(dislistBG, GL_COMPILE);

	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.25f, 7.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// czapka
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();

	glTranslatef(0.0f, 9.6f, 0.0f);
	glPushMatrix();

	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(0.0f, 0.2f, 0.0f);
	glutSolidSphere(0.6, 12, 12);
	glPopMatrix();


	// po unikalnych


	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja
	/*
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja

	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .8f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	//maska

	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.2f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.2, 0.6, 24, 24);
	glPopMatrix();


	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();
	*/
}

void SBMine::rysuj(int czy_idzie, int czy_atakuje)
{
	czy_idzie = 1;
	czy_atakuje = 0;
	if (zycie <= 0)
	{
		this->rysuj_miny();
		this->rysuj_wybuchy();
		this->rysuj_dead();
		return;
	}

	kills = killmine;
	if (killmine >= reqexp - 2)
	{
		preqexp = reqexp - 2;
		reqexp += +liczniklv;
		liczniklv++;
		pointstospend++;
	}

	// znajdywanie celu

	float minn = -2;

	for (int i = 0; i < heroses.size(); i++)
	{
		if (heroses[i]->klasa == klasa || heroses[i]->how_long_dead>0)
			;
		else
		{
			if (pos.x - heroses[i]->pos.x < -1000)
				temp.x = heroses[i]->pos.x - 2001 - pos.x;
			else
				if (pos.x - heroses[i]->pos.x > 1000)
					temp.x = heroses[i]->pos.x + 2001 - pos.x;
				else
					temp.x = heroses[i]->pos.x - pos.x;

			if (pos.z - heroses[i]->pos.z < -1000)
				temp.z = heroses[i]->pos.z - 2001 - pos.z;
			else
				if (pos.z - heroses[i]->pos.z > 1000)
					temp.z = heroses[i]->pos.z + 2001 - pos.z;
				else
					temp.z = heroses[i]->pos.z - pos.z;


			temp.y = sqrtf(pow(temp.z, 2) + pow(temp.x, 2));


			if (temp.y < minn || minn <= -1)
			{
				minn = temp.y;
				victimpos.x = heroses[i]->pos.x;
				victimpos.z = heroses[i]->pos.z;
				victimpos.y = temp.y; // odleglosc miedzy ludzikami

				dir.y = 0;
				dir.x = temp.x / temp.y;
				dir.z = temp.z / temp.y;
			}
		}
	}

	temp.y = victimpos.y;
	if (pointstospend>0)
		if (zycie <= calezycie*0.4)
			heal();
		else
			if (rand() % 2)
				incraselife();
			else
				incraseatak();


	// dla botow inne

	if (temp.y>20 + smialosc)// podchodzi
	{
		float nowaposx = fmod((pos.x + (dir.x *speed) + 2001), 2001);
		float nowaposz = fmod((pos.z + (dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
		{
			pos.x = nowaposx;
			pos.z = nowaposz;
		}
		else
		{ // nie da sie do przodu
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 2;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 300;
			}

			if (strona == 1)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
				if (strona == 0)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
				else
					czy_idzie = 0;
		}
		if (temp.y < 90)
		{
			if (rand() % 30 == 0)
				czy_atakuje = 1;
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 3;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 700;
			}
			if (strona == 0)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
				if (strona == 1)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
		}
	}
	else
	{
		czy_atakuje = 1;
		if (temp.y < 20 + smialosc) // ucieka
		{
			float nowaposx = fmod((pos.x - (dir.x *speed) + 2001), 2001);
			float nowaposz = fmod((pos.z - (dir.z * speed) + 2001), 2001);
			if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
			{
				pos.x = nowaposx;
				pos.z = nowaposz;
			}
			else
			{
				if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
				{
					strona = rand() % 2;
					levelanimation = glutGet(GLUT_ELAPSED_TIME) + 300;
				}
				if (strona == 0)
				{
					nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
				else
					if (strona == 1)
					{
						nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
						nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
						if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
						{
							pos.x = nowaposx;
							pos.z = nowaposz;
						}
						else
							strona = 3;
					}
					else
						czy_idzie = 0;
			}
		}
		else
		{

			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 2;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 1000;
			}
			if (strona == 0)
			{
				float	nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				float nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
			{
				if (strona == 1)
				{
					float nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					float nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
				else
					czy_idzie = 0;
			}
		}
	}




	float xxx = pos.x, zzz = pos.z;

	if (xxx - player.pos.x >= 1900)
		xxx -= 2001;
	else
		if (player.pos.x - xxx >= 1900)
			xxx += 2001;

	if (zzz - player.pos.z >= 1900)
		zzz -= 2001;
	else
		if (player.pos.z - zzz >= 1900)
			zzz += 2001;

	this->rysuj_miny();
	this->rysuj_wybuchy();
	float fi = atan2(dir.z, dir.x);
	glTranslatef(xxx, pos.y, zzz);

	float extra[4];
	// Pasek zycia
	glPushMatrix();
	glTranslatef(0, 11.5, 0);
	glRotatef(atan2(Gracz->dir.z, Gracz->dir.x)*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	extra[0] = 1.0f - (0.04*(kills - Gracz->kills));
	extra[1] = 0.0f;
	extra[2] = 0.0f + (0.01*(kills - Gracz->kills));
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glScalef(5.0*((float)zycie / (float)calezycie), 0.5, 1);
	glutSolidCube(1);
	glPopMatrix();


	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	// rysowanie podstawki
	// do stalych kolorow
	// kolory gory i dolu
	// unikalne

	// ramiona
	glCallList(dislist); // DLA BOTA INNACZEJ!!


						 // rysowanie nog 

	if (czy_idzie == 1 || stala_ruchu_nog != 0 || stala_ruchu_nog2 != 0)
	{
		if (stala_ruchu_nog2 == 0)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog > 45)
			{
				PlaySound("sounds/step1.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 1;
			}
		}
		if (stala_ruchu_nog2 == 1)
		{
			stala_ruchu_nog -= 4;
			if (stala_ruchu_nog < -45)
			{
				PlaySound("sounds/step12.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 2;
			}
		}
		if (stala_ruchu_nog2 == 2)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog == 0)
				stala_ruchu_nog2 = 0;
		}
	}

	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);
	glRotatef(0 + stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	glRotatef(0 - stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();

	// rysowanie reki + bron
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glTranslatef(-2.0f, 7.0f, 0.0f);
	if (stala_ruchu_atak != 0 || (czy_atakuje == 1 && ostatnioatak + czasoczekiwan< glutGet(GLUT_ELAPSED_TIME)))
	{
		// pobieram sekundy i jesli roznia sie mniej niz 2 
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME);
		if (stala_ruchu_atak == 0)
			stala_ruchu_atak = (-110);
		stala_ruchu_atak += 2;
		if (stala_ruchu_atak == -2)
			rzutminy = 1;
	}
	glRotatef(-30 + stala_ruchu_atak, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// bron
	glTranslatef(0.0f, -1.5f, 1.0f);
	if (rzutminy != 0)
	{
		glTranslatef(0.0f,
			0 - (rzutminy*0.2), 0 + (rzutminy*0.25)); // odleglosc animacji rzutu
		rzutminy++;
		if (rzutminy == 55)
		{
			PlaySound("sounds/ma1.wav", pos.x, 0, pos.z);
			if (mine[licznikmin].y != 100)
			{
				map.usun_bombe(mine[licznikmin].x, mine[licznikmin].z);
			}
			rzutminy = 0;
			mine_wybuch_stala[licznikmin] = 0;
			mine[licznikmin].x = fmod(((pos.x + 25 * dir.x) + 2001), 2001);
			mine[licznikmin].y = 0.5;
			mine[licznikmin].z = fmod(((pos.z + 25 * dir.z) + 2001), 2001);  // uwzglednic jak animacje ruchu - *0.x = +x

			map.Wst_bombe(mine[licznikmin].x, mine[licznikmin].z, this);

			licznikmin++;
			licznikmin %= 5;
		}
	}
	extra[0] = .0f;
	extra[1] = 0.15f;
	extra[2] = 0.0f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glPushMatrix();
	glScalef(2.0f, 0.5f, 2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	extra[0] = .8f;
	extra[1] = 0.2f;
	extra[2] = 0.2f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glTranslatef(0.0f, 0.25f, 0.0f);
	glutSolidSphere(.5f, 24, 24);

	glPopMatrix();
}

void SBMine::rysuj_dead()
{
	if (how_long_dead == 0)
	{
		map.uwolni(fmod(pos.x + 2001, 2001), fmod(pos.z + 2001, 2001));
		int rando = rand() % 3;
		if (rando == 0)
			PlaySound("sounds/die1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/die2.wav", pos.x, 0, pos.z);
			else
				PlaySound("sounds/die3.wav", pos.x, 0, pos.z);
	}
	if (how_long_dead > 1000)
	{// objekt ma znikac po 1000 sekundach


		pos = map.BotStart();
		pos.y = 0.5;
		zycie = calezycie;
		for (int i = -2; i < 3; i++)
			for (int j = -2; j < 3; j++)
				map.postac[((int)pos.x + i + 2001) % 2001][((int)pos.z + j + 2001) % 2001] = this;
		for (int i = 0; i < 5; i++)
		{
			map.usun_bombe(mine[i].x, mine[i].z);
			mine[i].x = 0;
			mine[i].y = 100;
			mine[i].z = 0;
			mine_wybuch_stala[i] = 0;
		}
		how_long_dead = 0;
		stala_ruchu_atak = 0;
		stala_ruchu_nog = 0;
		stala_ruchu_nog2 = 0;
		rzutminy = 0;
		licznikmin = 0;
		ostatnioatak = 0;

		dir.x = 0.0f + pos.x;
		dir.y = 0.0f;
		dir.z = -1.0f + pos.z;
		return;
	}
	how_long_dead++;
	// rysownie martwego

	// NIE Dla boty!!


	float xxx = pos.x, zzz = pos.z;

	if (xxx - player.pos.x >= 1900)
		xxx -= 2001;
	else
		if (player.pos.x - xxx >= 1900)
			xxx += 2001;

	if (zzz - player.pos.z >= 1900)
		zzz -= 2001;
	else
		if (player.pos.z - zzz >= 1900)
			zzz += 2001;


	glTranslatef(xxx, pos.y, zzz);
	float fi = atan2(dir.z, dir.x);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	if (how_long_dead > 90)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glRotatef(how_long_dead, 1.0f, 0.0f, 0.0f);
		glRotatef(how_long_dead * 2, 0.0f, 1.0f, 0.0f);
	}

	//glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	float extra[4];

	glPushMatrix();
	// rysowanie podstawki

	// unikalne

	// ramiona
	glCallList(dislist);

	// rysowanie nog 
	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);

	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();
	// rysowanie reki broni
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glRotatef(-15.0f, .0f, 0.0f, 1.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();
}

void SBMine::heal()
{
	if (pointstospend>0 && zycie>0)
	{
		pointstospend--;
		zycie = calezycie;
	}
}

void SBMine::incraselife()
{
	if (pointstospend>0)
	{
		pointstospend--;
		calezycie *= 1.5;
	}
}

void SBMine::incraseatak()
{
	if (pointstospend>0)
	{
		pointstospend--;
		silaataku *= 1.5;
	}
}

void SBMine::dodajkille(int ilosc)
{
	for (int i = 0; i < ilosc; i++)
		dodajkill();
}




class Mele : public hero
{
public:
	void dodajkill();
	int podajatak();
	void odejmijzycie(int);
	void heal();
	void incraselife();
	void incraseatak();
	float adu[4]; // Ambient  diffuse up
	float add[4];// Ambient  diffuse down
	float adm[4];// Ambient  diffuse up*down
	float spe[4]; //Specular
	Mele(float, float); // przekazujemy poziom x, z. y pozostaje bez zmian bo nie zmieniam wysokosci
	~Mele();
	void rysuj(int, int); // // uwzglednic przypadek kiedy punkty zycia sa 0 to bedzie uruchamiany dead
	void setcolors(float, float, float, float, float, float); // up r g b, down r g b
private:
	void rysuj_dead();// x y z
	int stala_ruchu_nog;
	int stala_ruchu_nog2;
	int stala_ruchu_atak;
	GLuint dislist;
	GLuint dislistBG;
};

int Mele::podajatak()
{
	return(silaataku);
}

void Mele::dodajkill()
{
	PlaySound("sounds/lz.wav", pos.x, 0, pos.z);
	kills++;
	if (kills == reqexp - 2)
	{
		PlaySound("sounds/f.wav", pos.x, 0, pos.z);
		levelanimation = 1;
		textanim1 = 1;
		preqexp = reqexp - 2;
		reqexp += +liczniklv;
		liczniklv++;
		pointstospend++;
	}
}

void Mele::odejmijzycie(int points)
{
	zycie -= points;
	zycoika = glutGet(GLUT_ELAPSED_TIME) + 32;
	if (zycie <= 0)
		zycie = 0;
	else
	{
		int rando = rand() % 4;
		if (rando == 0)
			PlaySound("sounds/he1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/he2.wav", pos.x, 0, pos.z);
			else
				if (rando == 2)
					PlaySound("sounds/he3.wav", pos.x, 0, pos.z);
				else
					PlaySound("sounds/he4.wav", pos.x, 0, pos.z);
	}
}

Mele::~Mele()
{}

void Mele::setcolors(float cur, float cug, float cub, float cdr, float cdg, float cdb)
{
	adu[0] = cur;
	adu[1] = cug;
	adu[2] = cub;
	add[0] = cdr;
	add[1] = cdg;
	add[2] = cdb;
}

Mele::Mele(float startnax, float startnaz)
{
	klasa = 'e';
	for (int i = -2; i < 3; i++)
		for (int j = -2; j < 3; j++)
			map.postac[((int)startnax + i + 2001) % 2001][((int)startnaz + j + 2001) % 2001] = this;
	czasoczekiwan = 500;
	silaataku = 500;
	calezycie = zyciepostaciMELE;
	zycie = calezycie;
	how_long_dead = 0;

	levelanimation = 0;

	pointstospend = 3;
	reqexp = 3;
	preqexp = 0;

	liczniklv = 2;

	pos.x = 0.0f + startnax;
	pos.y = 0.5f;
	pos.z = 0.0f + startnaz;
	dir.x = 0.0f + startnax;
	dir.y = 0.0f;
	dir.z = -1.0f + startnaz;

	kills = 0;

	speed = mmes + przewagagracza;

	adu[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[3] = 1.0f;
	add[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[3] = 1.0f;
	spe[0] = 0.0f;
	spe[1] = 0.0f;
	spe[2] = 0.0f;
	spe[3] = 1.0f;
	adm[0] = adu[0] * add[0];
	adm[1] = adu[1] * add[1];
	adm[2] = adu[2] * add[2];
	adm[3] = adu[3] * add[3];

	stala_ruchu_atak = 0;
	stala_ruchu_nog = 0;
	stala_ruchu_nog2 = 0;

	ostatnioatak = 0;

	float extra[4];
	dislist = glGenLists(1);
	glNewList(dislist, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// czapka

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glutSolidSphere(1.1f, 24, 24);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = 0.9f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.87f);
	glScalef(0.6f, 0.15f, 0.2f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();

	dislistBG = glGenLists(1);
	glNewList(dislistBG, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// czapka
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glutSolidSphere(1.1f, 24, 24);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();
	*/
	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	/*
	// szyja
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = 0.9f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.87f);
	glScalef(0.6f, 0.15f, 0.2f);
	glutSolidCube(1.0f);
	glPopMatrix();
	*/
	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();

}

void Mele::rysuj(int czy_idzie, int czy_atakuje)
{
	if (zycie <= 0)
	{
		this->rysuj_dead();
		return;
	}

	dir.x = player.dir.x;
	dir.y = player.dir.y;
	dir.z = player.dir.z;
	pos.x = player.pos.x;
	pos.y = player.pos.y - 8.5;
	pos.z = player.pos.z;

	/*
	dir.x = 0;
	dir.y = 0;
	dir.z = 0;
	pos.x = 0;
	pos.y = 0.5;
	pos.z = 0;
	*/
	/* rysowanie uderzenia
	for (int i = 0; i < dupa.size(); i++)
	{
	glPushMatrix();
	glTranslatef(uderzenia[i].x,uderzenia[i].y, uderzenia[i].z);
	glutSolidCube(1);
	glPopMatrix();
	}
	*/

	if (keystate['w'] || keystate['W']) {
		float nowaposx = fmod((player.pos.x + (player.dir.x * speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z + (player.dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['s'] || keystate['S']) {
		float nowaposx = fmod((player.pos.x - (player.dir.x *speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z - (player.dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['d'] || keystate['D']) {
		float nowaposx = fmod((player.pos.x + (-player.dir.z*speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z + (player.dir.x * speed) + 2001), 2001);
		if (0 == map.HeroCatch(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['a'] || keystate['A']) {
		float nowaposx = fmod((player.pos.x - (-player.dir.z*speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z - (player.dir.x * speed) + 2001), 2001);
		if (0 == map.HeroCatch(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}

	float fi = atan2(dir.z, dir.x);
	glTranslatef(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glTranslatef(0, 0, -0.4);
	float extra[4];
	glPushMatrix();
	// rysowanie podstawki

	// unikalne
	glCallList(dislistBG);
	// ramiona

	// rysowanie nog 
	if (czy_idzie == 1 || stala_ruchu_nog != 0 || stala_ruchu_nog2 != 0)
	{
		if (stala_ruchu_nog2 == 0)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog > 45)
			{
				PlaySound("sounds/step2.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 1;
			}
		}
		if (stala_ruchu_nog2 == 1)
		{
			stala_ruchu_nog -= 4;
			if (stala_ruchu_nog < -45)
			{
				PlaySound("sounds/step22.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 2;
			}
		}
		if (stala_ruchu_nog2 == 2)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog == 0)
				stala_ruchu_nog2 = 0;
		}
	}

	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);
	glRotatef(0 + stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	glRotatef(0 - stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();

	// rysowanie reki + bron
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	if (stala_ruchu_atak != 0 || (czy_atakuje == 1 && ostatnioatak + czasoczekiwan < glutGet(GLUT_ELAPSED_TIME)))
	{
		// pobieram sekundy i jesli roznia sie mniej niz 2 
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME);
		if (stala_ruchu_atak == 0)
			stala_ruchu_atak = (-140);
		stala_ruchu_atak += 7;
	}

	//atak
	if (stala_ruchu_atak == (-7))
	{
		PlaySound("sounds/ea.wav", pos.x, 0, pos.z);
		// zadaj obrazenia tym przed toba na 15 odleglosci
		vector <hero*> dobicia;
		for (int i = 10; i > 1; i--)
			for (int j = 5; j > -6; j--)
			{
				int xx = (int((pos.x + dir.x * i) + (dir.z*j)) + 2001) % 2001, zz = (int((pos.z + dir.z * i) + (dir.x*j)) + 2001) % 2001;
				/* do rysowania uderznia
				vector3d nic;
				nic.x = xx;
				nic.y = 6;
				nic.z = zz;
				uderzenia.push_back(nic);
				*/
				if (map.postac[xx][zz] != NULL && map.postac[xx][zz] != this)
				{
					// sprawdzenie czy juz byl
					int czyjuzjest = 0;
					for (int k = 0; k < dobicia.size(); k++)
						if (map.postac[xx][zz] == dobicia[k])
						{
							czyjuzjest = 1;
							break;
						}
					if (czyjuzjest == 0)
						dobicia.push_back(map.postac[xx][zz]);
				}
				//map.postac[xx][zz]->odejmijzycie(podajatak()); //
			}
		for (int k = 0; k < dobicia.size(); k++)
		{
			dobicia[k]->odejmijzycie(podajatak());
			if (dobicia[k]->zycie <= 0)
				dodajkill();
		}
	}
	glRotatef(0 + stala_ruchu_atak, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// bron
	glPushMatrix();
	extra[0] = 0.65f;
	extra[1] = 0.65f;
	extra[2] = 0.65f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.0f, -1.1f, 3.0f);
	glScalef(.7f, 0.7f, 8.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glTranslatef(0.0f, -1.1f, 1.0f);
	extra[0] = 0.9f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(.35f, 1.5f, 14, 14);
	glPopMatrix();
	for (int i = 0; i < 11; i++)
	{
		glTranslatef(0.0f, 0.0f, 0.5f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(.35f, 1.5f, 14, 14);

		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(.35f, 1.5f, 14, 14);
		glPopMatrix();
	}

	glPopMatrix();
}

void Mele::rysuj_dead()
{
	if (how_long_dead == 0)
	{
		map.uwolni(fmod(pos.x + 2001, 2001), fmod(pos.z + 2001, 2001));
		int rando = rand() % 3;
		if (rando == 0)
			PlaySound("sounds/die1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/die2.wav", pos.x, 0, pos.z);
			else
				PlaySound("sounds/die3.wav", pos.x, 0, pos.z);
	}
	if (how_long_dead > 1000)
	{// objekt ma znikac po 1000 sekundach
		this->~Mele(); // lub zycie =1000 nowe miejsce na mapie i howlong dead=0
		return;
	}
	else
		how_long_dead++;
	// rysownie martwego
	// nie dla botow
	player.dir.y = -1.3;
	player.dir.z = dir.z;
	player.dir.x = dir.x;


	glTranslatef(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
	float fi = atan2(dir.z, dir.x);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	if (how_long_dead > 90)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glRotatef(how_long_dead, 1.0f, 0.0f, 0.0f);
		glRotatef(how_long_dead * 2, 0.0f, 1.0f, 0.0f);
	}

	//glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	float extra[4];
	glPushMatrix();
	// rysowanie podstawki

	// unikalne

	// ramiona
	glCallList(dislist);

	// rysowanie nog 
	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);

	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();
	// rysowanie reki broni
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glRotatef(-15.0f, .0f, 0.0f, 1.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();
}

void Mele::heal()
{
	if (pointstospend>0 && zycie > 0)
	{
		PlaySound("sounds/heal.wav", pos.x, 0, pos.z);
		pointstospend--;
		zycie = calezycie;
	}
}

void Mele::incraselife()
{
	if (pointstospend>0)
	{
		PlaySound("sounds/lif.wav", pos.x, 0, pos.z);
		pointstospend--;
		calezycie *= 1.5;
	}
}

void Mele::incraseatak()
{
	if (pointstospend>0)
	{
		PlaySound("sounds/ata.wav", pos.x, 0, pos.z);
		pointstospend--;
		silaataku *= 1.5;
	}
}


class SMele : public hero
{
public:
	void dodajkill();
	int podajatak();
	void odejmijzycie(int);
	void heal();
	void incraselife();
	void incraseatak();
	float adu[4]; // Ambient  diffuse up
	float add[4];// Ambient  diffuse down
	float adm[4];// Ambient  diffuse up*down
	float spe[4]; //Specular
	SMele(float, float); // przekazujemy poziom x, z. y pozostaje bez zmian bo nie zmieniam wysokosci
	~SMele();
	void rysuj(int, int); // // uwzglednic przypadek kiedy punkty zycia sa 0 to bedzie uruchamiany dead
	void setcolors(float, float, float, float, float, float); // up r g b, down r g b
private:
	void rysuj_dead();// x y z
	int stala_ruchu_nog;
	int stala_ruchu_nog2;
	int stala_ruchu_atak;
	GLuint dislist;
	GLuint dislistBG;
};

int SMele::podajatak()
{
	return(silaataku);
}

void SMele::dodajkill()
{
	killmele++;

}

void SMele::odejmijzycie(int points)
{
	zycie -= points;
	zycoika = glutGet(GLUT_ELAPSED_TIME) + 32;
	if (zycie <= 0)
		zycie = 0;
	else
	{
		int rando = rand() % 4;
		if (rando == 0)
			PlaySound("sounds/he1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/he2.wav", pos.x, 0, pos.z);
			else
				if (rando == 2)
					PlaySound("sounds/he3.wav", pos.x, 0, pos.z);
				else
					PlaySound("sounds/he4.wav", pos.x, 0, pos.z);
	}
}

SMele::~SMele()
{}

void SMele::setcolors(float cur, float cug, float cub, float cdr, float cdg, float cdb)
{
	adu[0] = cur;
	adu[1] = cug;
	adu[2] = cub;
	add[0] = cdr;
	add[1] = cdg;
	add[2] = cdb;
}

SMele::SMele(float startnax, float startnaz)
{
	klasa = 'e';
	for (int i = -2; i < 3; i++)
		for (int j = -2; j < 3; j++)
			map.postac[((int)startnax + i + 2001) % 2001][((int)startnaz + j + 2001) % 2001] = this;
	czasoczekiwan = 500;
	silaataku = 500;
	calezycie = zyciepostaciMELE;
	zycie = calezycie;
	how_long_dead = 0;

	levelanimation = 0;

	pointstospend = 3;
	reqexp = 3;
	preqexp = 0;

	liczniklv = 2;

	pos.x = 0.0f + startnax;
	pos.y = 0.5f;
	pos.z = 0.0f + startnaz;
	dir.x = 0.0f + startnax;
	dir.y = 0.0f;
	dir.z = -1.0f + startnaz;

	kills = 0;

	speed = mmes + przewagagracza;

	adu[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[3] = 1.0f;
	add[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[3] = 1.0f;
	spe[0] = 0.0f;
	spe[1] = 0.0f;
	spe[2] = 0.0f;
	spe[3] = 1.0f;
	adm[0] = adu[0] * add[0];
	adm[1] = adu[1] * add[1];
	adm[2] = adu[2] * add[2];
	adm[3] = adu[3] * add[3];

	stala_ruchu_atak = 0;
	stala_ruchu_nog = 0;
	stala_ruchu_nog2 = 0;

	ostatnioatak = 0;

	float extra[4];
	dislist = glGenLists(1);
	glNewList(dislist, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// czapka

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glutSolidSphere(1.1f, 24, 24);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = 0.9f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.87f);
	glScalef(0.6f, 0.15f, 0.2f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();

	dislistBG = glGenLists(1);
	glNewList(dislistBG, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// czapka
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glutSolidSphere(1.1f, 24, 24);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();
	*/
	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	/*
	// szyja
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = 0.9f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.87f);
	glScalef(0.6f, 0.15f, 0.2f);
	glutSolidCube(1.0f);
	glPopMatrix();
	*/
	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();

}

void SMele::rysuj(int czy_idzie, int czy_atakuje)
{
	if (zycie <= 0)
	{
		this->rysuj_dead();
		return;
	}

	if (killmele != kills)
	{
		kills = killmele;
		PlaySound("sounds/lz.wav", pos.x, 0, pos.z);
	}

	if (killmele >= reqexp - 2)
	{
		PlaySound("sounds/f.wav", pos.x, 0, pos.z);
		levelanimation = 1;
		textanim1 = 1;
		preqexp = reqexp - 2;
		reqexp += +liczniklv;
		liczniklv++;
		pointstospend++;
	}

	dir.x = player.dir.x;
	dir.y = player.dir.y;
	dir.z = player.dir.z;
	pos.x = player.pos.x;
	pos.y = player.pos.y - 8.5;
	pos.z = player.pos.z;

	/*
	dir.x = 0;
	dir.y = 0;
	dir.z = 0;
	pos.x = 0;
	pos.y = 0.5;
	pos.z = 0;
	*/
	/* rysowanie uderzenia
	for (int i = 0; i < dupa.size(); i++)
	{
	glPushMatrix();
	glTranslatef(uderzenia[i].x,uderzenia[i].y, uderzenia[i].z);
	glutSolidCube(1);
	glPopMatrix();
	}
	*/

	if (keystate['w'] || keystate['W']) {
		float nowaposx = fmod((player.pos.x + (player.dir.x * speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z + (player.dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['s'] || keystate['S']) {
		float nowaposx = fmod((player.pos.x - (player.dir.x *speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z - (player.dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['d'] || keystate['D']) {
		float nowaposx = fmod((player.pos.x + (-player.dir.z*speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z + (player.dir.x * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['a'] || keystate['A']) {
		float nowaposx = fmod((player.pos.x - (-player.dir.z*speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z - (player.dir.x * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}

	float fi = atan2(dir.z, dir.x);
	glTranslatef(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glTranslatef(0, 0, -0.4);
	float extra[4];
	glPushMatrix();
	// rysowanie podstawki

	// unikalne
	glCallList(dislistBG);
	// ramiona

	// rysowanie nog 
	if (czy_idzie == 1 || stala_ruchu_nog != 0 || stala_ruchu_nog2 != 0)
	{
		if (stala_ruchu_nog2 == 0)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog > 45)
			{
				PlaySound("sounds/step2.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 1;
			}
		}
		if (stala_ruchu_nog2 == 1)
		{
			stala_ruchu_nog -= 4;
			if (stala_ruchu_nog < -45)
			{
				PlaySound("sounds/step22.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 2;
			}
		}
		if (stala_ruchu_nog2 == 2)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog == 0)
				stala_ruchu_nog2 = 0;
		}
	}

	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);
	glRotatef(0 + stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	glRotatef(0 - stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();

	// rysowanie reki + bron
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	if (stala_ruchu_atak != 0 || (czy_atakuje == 1 && ostatnioatak + czasoczekiwan < glutGet(GLUT_ELAPSED_TIME)))
	{
		// pobieram sekundy i jesli roznia sie mniej niz 2 
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME);
		if (stala_ruchu_atak == 0)
			stala_ruchu_atak = (-140);
		stala_ruchu_atak += 7;
	}

	//atak
	if (stala_ruchu_atak == (-7))
	{
		PlaySound("sounds/ea.wav", pos.x, 0, pos.z);
		// zadaj obrazenia tym przed toba na 15 odleglosci
		vector <hero*> dobicia;
		for (int i = 10; i > 1; i--)
			for (int j = 5; j > -6; j--)
			{
				int xx = (int((pos.x + dir.x * i) + (dir.z*j)) + 2001) % 2001, zz = (int((pos.z + dir.z * i) + (dir.x*j)) + 2001) % 2001;
				/* do rysowania uderznia
				vector3d nic;
				nic.x = xx;
				nic.y = 6;
				nic.z = zz;
				uderzenia.push_back(nic);
				*/
				if (map.postac[xx][zz] != NULL && map.postac[xx][zz]->klasa != klasa)
				{
					// sprawdzenie czy juz byl
					int czyjuzjest = 0;
					for (int k = 0; k < dobicia.size(); k++)
						if (map.postac[xx][zz] == dobicia[k])
						{
							czyjuzjest = 1;
							break;
						}
					if (czyjuzjest == 0)
						dobicia.push_back(map.postac[xx][zz]);
				}
				//map.postac[xx][zz]->odejmijzycie(podajatak()); //
			}
		for (int k = 0; k < dobicia.size(); k++)
		{
			dobicia[k]->odejmijzycie(podajatak());
			if (dobicia[k]->zycie <= 0)
				dodajkill();
		}
	}
	glRotatef(0 + stala_ruchu_atak, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// bron
	glPushMatrix();
	extra[0] = 0.65f;
	extra[1] = 0.65f;
	extra[2] = 0.65f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.0f, -1.1f, 3.0f);
	glScalef(.7f, 0.7f, 8.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glTranslatef(0.0f, -1.1f, 1.0f);
	extra[0] = 0.9f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(.35f, 1.5f, 14, 14);
	glPopMatrix();
	for (int i = 0; i < 11; i++)
	{
		glTranslatef(0.0f, 0.0f, 0.5f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(.35f, 1.5f, 14, 14);

		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(.35f, 1.5f, 14, 14);
		glPopMatrix();
	}

	glPopMatrix();
}

void SMele::rysuj_dead()
{
	if (how_long_dead == 0)
	{
		map.uwolni(fmod(pos.x + 2001, 2001), fmod(pos.z + 2001, 2001));
		int rando = rand() % 3;
		if (rando == 0)
			PlaySound("sounds/die1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/die2.wav", pos.x, 0, pos.z);
			else
				PlaySound("sounds/die3.wav", pos.x, 0, pos.z);
	}
	if (how_long_dead > 1000)
	{// objekt ma znikac po 1000 sekundach
		return;
	}
	else
		how_long_dead++;
	// rysownie martwego
	// nie dla botow
	player.dir.y = -1.3;
	player.dir.z = dir.z;
	player.dir.x = dir.x;


	glTranslatef(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
	float fi = atan2(dir.z, dir.x);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	if (how_long_dead > 90)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glRotatef(how_long_dead, 1.0f, 0.0f, 0.0f);
		glRotatef(how_long_dead * 2, 0.0f, 1.0f, 0.0f);
	}

	//glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	float extra[4];
	glPushMatrix();
	// rysowanie podstawki

	// unikalne

	// ramiona
	glCallList(dislist);

	// rysowanie nog 
	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);

	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();
	// rysowanie reki broni
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glRotatef(-15.0f, .0f, 0.0f, 1.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();
}

void SMele::heal()
{
	if (pointstospend>0 && zycie > 0)
	{
		PlaySound("sounds/heal.wav", pos.x, 0, pos.z);
		pointstospend--;
		zycie = calezycie;
	}
}

void SMele::incraselife()
{
	if (pointstospend>0)
	{
		PlaySound("sounds/lif.wav", pos.x, 0, pos.z);
		pointstospend--;
		calezycie *= 1.5;
	}
}

void SMele::incraseatak()
{
	if (pointstospend>0)
	{
		PlaySound("sounds/ata.wav", pos.x, 0, pos.z);
		pointstospend--;
		silaataku *= 1.5;
	}
}


class BMele : public hero
{
public:
	int losowaniebledu2;
	bool ucieka;
	float blad;
	int losowaniebledu;
	vector3d victimpos; // pozycja bohatera
	vector3d temp; // pozycja bohatera
	int strona;
	void dodajkill();
	int podajatak();
	void odejmijzycie(int);
	void heal();
	void incraselife();
	void incraseatak();
	float adu[4]; // Ambient  diffuse up
	float add[4];// Ambient  diffuse down
	float adm[4];// Ambient  diffuse up*down
	float spe[4]; //Specular
	BMele(float, float); // przekazujemy poziom x, z. y pozostaje bez zmian bo nie zmieniam wysokosci
	~BMele();
	void rysuj(int, int); // // uwzglednic przypadek kiedy punkty zycia sa 0 to bedzie uruchamiany dead
	void setcolors(float, float, float, float, float, float); // up r g b, down r g b
	void dodajkille(int);
private:
	void rysuj_dead();// x y z
	int stala_ruchu_nog;
	int stala_ruchu_nog2;
	int stala_ruchu_atak;
	GLuint dislist;
};

int BMele::podajatak()
{
	return(silaataku);
}

void BMele::dodajkill()
{
	kills++;
	if (kills >= reqexp - 2)
	{
		levelanimation = 1;
		preqexp = reqexp - 2;
		reqexp += +liczniklv;
		liczniklv++;
		pointstospend++;
	}
}

void BMele::odejmijzycie(int points)
{
	zycie -= points;
	if (zycie <= 0)
		zycie = 0;
	else
	{
		int rando = rand() % 4;
		if (rando == 0)
			PlaySound("sounds/he1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/he2.wav", pos.x, 0, pos.z);
			else
				if (rando == 2)
					PlaySound("sounds/he3.wav", pos.x, 0, pos.z);
				else
					PlaySound("sounds/he4.wav", pos.x, 0, pos.z);
	}
}

BMele::~BMele()
{}

void BMele::setcolors(float cur, float cug, float cub, float cdr, float cdg, float cdb)
{
	adu[0] = cur;
	adu[1] = cug;
	adu[2] = cub;
	add[0] = cdr;
	add[1] = cdg;
	add[2] = cdb;
}

BMele::BMele(float startnax, float startnaz)
{
	klasa = 'e';
	for (int i = -2; i < 3; i++)
		for (int j = -2; j < 3; j++)
			map.postac[((int)startnax + i + 2001) % 2001][((int)startnaz + j + 2001) % 2001] = this;
	czasoczekiwan = 500;
	silaataku = 500;
	calezycie = zyciepostaciMELE;
	zycie = calezycie;
	how_long_dead = 0;

	losowaniebledu = 0;
	losowaniebledu2 = 0;

	levelanimation = 0;

	pointstospend = 3;
	reqexp = 3;
	preqexp = 0;

	liczniklv = 2;

	pos.x = 0.0f + startnax;
	pos.y = 0.5f;
	pos.z = 0.0f + startnaz;
	dir.x = 0.0f + startnax;
	dir.y = 0.0f;
	dir.z = -1.0f + startnaz;

	kills = 0;

	speed = mmes;

	adu[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[3] = 1.0f;
	add[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[3] = 1.0f;
	spe[0] = 0.0f;
	spe[1] = 0.0f;
	spe[2] = 0.0f;
	spe[3] = 1.0f;
	adm[0] = adu[0] * add[0];
	adm[1] = adu[1] * add[1];
	adm[2] = adu[2] * add[2];
	adm[3] = adu[3] * add[3];

	stala_ruchu_atak = 0;
	stala_ruchu_nog = 0;
	stala_ruchu_nog2 = 0;

	ostatnioatak = 0;

	float extra[4];
	dislist = glGenLists(1);
	glNewList(dislist, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// czapka

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glutSolidSphere(1.1f, 24, 24);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = 0.9f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.87f);
	glScalef(0.6f, 0.15f, 0.2f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();

	/*
	dislistBG = glGenLists(1);
	glNewList(dislistBG, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// czapka
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glutSolidSphere(1.1f, 24, 24);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	/*
	// szyja
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = 0.9f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.87f);
	glScalef(0.6f, 0.15f, 0.2f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();
	*/
}

void BMele::rysuj(int czy_idzie, int czy_atakuje)
{
	czy_atakuje = 0;
	czy_idzie = 1;
	if (zycie <= 0)
	{
		this->rysuj_dead();
		return;
	}

	// znajdywanie celu

	float minn = -2;

	for (int i = 0; i < heroses.size(); i++)
	{
		if (heroses[i] == this || heroses[i]->how_long_dead>0)
			;
		else
		{
			if (pos.x - heroses[i]->pos.x < -1000)
				temp.x = heroses[i]->pos.x - 2001 - pos.x;
			else
				if (pos.x - heroses[i]->pos.x > 1000)
					temp.x = heroses[i]->pos.x + 2001 - pos.x;
				else
					temp.x = heroses[i]->pos.x - pos.x;

			if (pos.z - heroses[i]->pos.z < -1000)
				temp.z = heroses[i]->pos.z - 2001 - pos.z;
			else
				if (pos.z - heroses[i]->pos.z > 1000)
					temp.z = heroses[i]->pos.z + 2001 - pos.z;
				else
					temp.z = heroses[i]->pos.z - pos.z;


			temp.y = sqrtf(pow(temp.z, 2) + pow(temp.x, 2));


			if (temp.y < minn || minn <= -1)
			{
				minn = temp.y;
				victimpos.x = heroses[i]->pos.x;
				victimpos.z = heroses[i]->pos.z;
				victimpos.y = temp.y; // odleglosc miedzy ludzikami

				dir.y = 0;
				dir.x = temp.x / temp.y;
				dir.z = temp.z / temp.y;
			}
		}
	}

	temp.y = victimpos.y;
	if (pointstospend>0)
		if (zycie <= calezycie*0.4)
			heal();
		else
			if (rand() % 2)
				incraselife();
			else
				incraseatak();


	/* rysowanie uderzenia
	for (int i = 0; i < dupa.size(); i++)
	{
	glPushMatrix();
	glTranslatef(uderzenia[i].x,uderzenia[i].y, uderzenia[i].z);
	glutSolidCube(1);
	glPopMatrix();
	}
	*/

	// poruszanie sie
	// dla botow inne
	if (losowaniebledu < glutGet(GLUT_ELAPSED_TIME))
	{
		losowaniebledu = glutGet(GLUT_ELAPSED_TIME) + 500 + (rand() % 500);
		blad = (rand() % 700)*0.01;
		ucieka = 0;
	}

	if (temp.y> 8 + blad && ucieka == 0)// podchodzi
	{
		if (temp.y < 13 + blad)
			czy_atakuje = 1;
		float nowaposx = fmod((pos.x + (dir.x *speed) + 2001), 2001);
		float nowaposz = fmod((pos.z + (dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
		{
			pos.x = nowaposx;
			pos.z = nowaposz;
		}
		else
		{ // nie da sie do przodu
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 2;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 300;
			}

			if (strona == 1)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
				if (strona == 0)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
				else
					czy_idzie = 0;
		}
		if (temp.y < 90)
		{
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 3;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 500;
			}
			if (strona == 0)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
				if (strona == 1)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
		}
	}
	else
	{
		czy_atakuje = 1;
		if (losowaniebledu2 < glutGet(GLUT_ELAPSED_TIME))
		{
			losowaniebledu2 = glutGet(GLUT_ELAPSED_TIME) + 250 + (rand() % 350);
			ucieka = rand() % 2;
		}
		if (ucieka) // ucieka
		{
			czy_idzie = 0;
			float nowaposx = fmod((pos.x - (dir.x *speed) + 2001), 2001);
			float nowaposz = fmod((pos.z - (dir.z * speed) + 2001), 2001);
			if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
			{
				pos.x = nowaposx;
				pos.z = nowaposz;
				czy_idzie = 1;
			}
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 2;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 300;
			}
			if (strona == 0)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
					czy_idzie = 1;
				}
				else
					strona = 1;
			}
			else
				if (strona == 1)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
						czy_idzie = 1;
					}
					else
						strona = 0;
				}
		}





		else
		{

			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 2;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 1000;
			}
			if (strona == 0)
			{
				float	nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				float nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
			{
				if (strona == 1)
				{
					float nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					float nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
				else
					czy_idzie = 0;
			}
		}
	}



	float xxx = pos.x, zzz = pos.z;

	if (xxx - player.pos.x >= 1900)
		xxx -= 2001;
	else
		if (player.pos.x - xxx >= 1900)
			xxx += 2001;

	if (zzz - player.pos.z >= 1900)
		zzz -= 2001;
	else
		if (player.pos.z - zzz >= 1900)
			zzz += 2001;


	float fi = atan2(dir.z, dir.x);
	glTranslatef(xxx, pos.y, zzz);

	float extra[4];
	// Pasek zycia
	glPushMatrix();
	glTranslatef(0, 11.5, 0);
	glRotatef(atan2(Gracz->dir.z, Gracz->dir.x)*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	extra[0] = 1.0f - (0.04*(kills - Gracz->kills));
	extra[1] = 0.0f;
	extra[2] = 0.0f + (0.01*(kills - Gracz->kills));
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glScalef(5.0*((float)zycie / (float)calezycie), 0.5, 1);
	glutSolidCube(1);
	glPopMatrix();

	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glTranslatef(0, 0, -0.4);
	glPushMatrix();
	// rysowanie podstawki

	// unikalne
	glCallList(dislist);
	// ramiona

	// rysowanie nog 
	if (czy_idzie == 1 || stala_ruchu_nog != 0 || stala_ruchu_nog2 != 0)
	{
		if (stala_ruchu_nog2 == 0)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog > 45)
			{
				PlaySound("sounds/step2.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 1;
			}
		}
		if (stala_ruchu_nog2 == 1)
		{
			stala_ruchu_nog -= 4;
			if (stala_ruchu_nog < -45)
			{
				PlaySound("sounds/step22.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 2;
			}
		}
		if (stala_ruchu_nog2 == 2)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog == 0)
				stala_ruchu_nog2 = 0;
		}
	}

	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);
	glRotatef(0 + stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	glRotatef(0 - stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();

	// rysowanie reki + bron
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	if (stala_ruchu_atak != 0 || (czy_atakuje == 1 && ostatnioatak + czasoczekiwan < glutGet(GLUT_ELAPSED_TIME)))
	{
		// pobieram sekundy i jesli roznia sie mniej niz 2 
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME);
		if (stala_ruchu_atak == 0)
			stala_ruchu_atak = (-140);
		stala_ruchu_atak += 7;
	}

	//atak
	if (stala_ruchu_atak == (-7))
	{
		PlaySound("sounds/ea.wav", pos.x, 0, pos.z);
		// zadaj obrazenia tym przed toba na 15 odleglosci
		vector <hero*> dobicia;
		for (int i = 8; i > 1; i--)
			for (int j = 5; j > -6; j--)
			{
				int xx = (int((pos.x + dir.x * i) + (dir.z*j)) + 2001) % 2001, zz = (int((pos.z + dir.z * i) + (dir.x*j)) + 2001) % 2001;
				/* do rysowania uderznia
				vector3d nic;
				nic.x = xx;
				nic.y = 6;
				nic.z = zz;
				uderzenia.push_back(nic);
				*/
				if (map.postac[xx][zz] != NULL && map.postac[xx][zz] != this)
				{
					// sprawdzenie czy juz byl
					int czyjuzjest = 0;
					for (int k = 0; k < dobicia.size(); k++)
						if (map.postac[xx][zz] == dobicia[k])
						{
							czyjuzjest = 1;
							break;
						}
					if (czyjuzjest == 0)
						dobicia.push_back(map.postac[xx][zz]);
				}
				//map.postac[xx][zz]->odejmijzycie(podajatak()); //
			}
		for (int k = 0; k < dobicia.size(); k++)
		{
			dobicia[k]->odejmijzycie(silaataku);
			if (dobicia[k]->zycie <= 0)
				dodajkill();
		}
	}
	glRotatef(0 + stala_ruchu_atak, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// bron
	glPushMatrix();
	extra[0] = 0.65f;
	extra[1] = 0.65f;
	extra[2] = 0.65f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.0f, -1.1f, 3.0f);
	glScalef(.7f, 0.7f, 8.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glTranslatef(0.0f, -1.1f, 1.0f);
	extra[0] = 0.9f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(.35f, 1.5f, 14, 14);
	glPopMatrix();
	for (int i = 0; i < 11; i++)
	{
		glTranslatef(0.0f, 0.0f, 0.5f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(.35f, 1.5f, 14, 14);

		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(.35f, 1.5f, 14, 14);
		glPopMatrix();
	}

	glPopMatrix();
}

void BMele::rysuj_dead()
{
	if (how_long_dead == 0)
	{
		map.uwolni(fmod(pos.x + 2001, 2001), fmod(pos.z + 2001, 2001));
		int rando = rand() % 3;
		if (rando == 0)
			PlaySound("sounds/die1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/die2.wav", pos.x, 0, pos.z);
			else
				PlaySound("sounds/die3.wav", pos.x, 0, pos.z);
	}
	if (how_long_dead > 1000)
	{// objekt ma znikac po 1000 sekundach

		pos = map.BotStart();
		pos.y = 0.5;
		zycie = calezycie;
		for (int i = -2; i < 3; i++)
			for (int j = -2; j < 3; j++)
				map.postac[((int)pos.x + i + 2001) % 2001][((int)pos.z + j + 2001) % 2001] = this;
		how_long_dead = 0;
		stala_ruchu_atak = 0;
		stala_ruchu_nog = 0;
		stala_ruchu_nog2 = 0;
		ostatnioatak = 0;

		dir.x = 0.0f + pos.x;
		dir.y = 0.0f;
		dir.z = -1.0f + pos.z;
		return;
	}
	else
		how_long_dead++;
	// rysownie martwego
	// nie dla botow


	float xxx = pos.x, zzz = pos.z;
	if (xxx - player.pos.x >= 1900)
		xxx -= 2001;
	else
		if (player.pos.x - xxx >= 1900)
			xxx += 2001;

	if (zzz - player.pos.z >= 1900)
		zzz -= 2001;
	else
		if (player.pos.z - zzz >= 1900)
			zzz += 2001;

	glTranslatef(xxx, pos.y, zzz);
	float fi = atan2(dir.z, dir.x);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	if (how_long_dead > 90)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glRotatef(how_long_dead, 1.0f, 0.0f, 0.0f);
		glRotatef(how_long_dead * 2, 0.0f, 1.0f, 0.0f);
	}

	//glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	float extra[4];
	glPushMatrix();
	// rysowanie podstawki

	// unikalne

	// ramiona
	glCallList(dislist);

	// rysowanie nog 
	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);

	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();
	// rysowanie reki broni
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glRotatef(-15.0f, .0f, 0.0f, 1.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();
}

void BMele::heal()
{
	if (pointstospend>0 && zycie > 0)
	{
		pointstospend--;
		zycie = calezycie;
	}
}

void BMele::incraselife()
{
	if (pointstospend>0)
	{
		pointstospend--;
		calezycie *= 1.5;
	}
}

void BMele::incraseatak()
{
	if (pointstospend>0)
	{
		pointstospend--;
		silaataku *= 1.5;
	}
}

void BMele::dodajkille(int ilosc)
{
	for (int i = 0; i < ilosc; i++)
		dodajkill();
}


class SBMele : public hero
{
public:
	int losowaniebledu2;
	bool ucieka;
	float blad;
	int losowaniebledu;
	vector3d victimpos; // pozycja bohatera
	vector3d temp; // pozycja bohatera
	int strona;
	void dodajkill();
	int podajatak();
	void odejmijzycie(int);
	void heal();
	void incraselife();
	void incraseatak();
	float adu[4]; // Ambient  diffuse up
	float add[4];// Ambient  diffuse down
	float adm[4];// Ambient  diffuse up*down
	float spe[4]; //Specular
	SBMele(float, float); // przekazujemy poziom x, z. y pozostaje bez zmian bo nie zmieniam wysokosci
	~SBMele();
	void rysuj(int, int); // // uwzglednic przypadek kiedy punkty zycia sa 0 to bedzie uruchamiany dead
	void setcolors(float, float, float, float, float, float); // up r g b, down r g b
	void dodajkille(int);
private:
	void rysuj_dead();// x y z
	int stala_ruchu_nog;
	int stala_ruchu_nog2;
	int stala_ruchu_atak;
	GLuint dislist;
};

int SBMele::podajatak()
{
	return(silaataku);
}

void SBMele::dodajkill()
{
	killmele++;
}

void SBMele::odejmijzycie(int points)
{
	zycie -= points;
	if (zycie <= 0)
		zycie = 0;
	else
	{
		int rando = rand() % 4;
		if (rando == 0)
			PlaySound("sounds/he1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/he2.wav", pos.x, 0, pos.z);
			else
				if (rando == 2)
					PlaySound("sounds/he3.wav", pos.x, 0, pos.z);
				else
					PlaySound("sounds/he4.wav", pos.x, 0, pos.z);
	}
}

SBMele::~SBMele()
{}

void SBMele::setcolors(float cur, float cug, float cub, float cdr, float cdg, float cdb)
{
	adu[0] = cur;
	adu[1] = cug;
	adu[2] = cub;
	add[0] = cdr;
	add[1] = cdg;
	add[2] = cdb;
}

SBMele::SBMele(float startnax, float startnaz)
{
	klasa = 'e';
	for (int i = -2; i < 3; i++)
		for (int j = -2; j < 3; j++)
			map.postac[((int)startnax + i + 2001) % 2001][((int)startnaz + j + 2001) % 2001] = this;
	czasoczekiwan = 500;
	silaataku = 500;
	calezycie = zyciepostaciMELE;
	zycie = calezycie;
	how_long_dead = 0;

	losowaniebledu = 0;
	losowaniebledu2 = 0;

	levelanimation = 0;

	pointstospend = 3;
	reqexp = 3;
	preqexp = 0;

	liczniklv = 2;

	pos.x = 0.0f + startnax;
	pos.y = 0.5f;
	pos.z = 0.0f + startnaz;
	dir.x = 0.0f + startnax;
	dir.y = 0.0f;
	dir.z = -1.0f + startnaz;

	kills = 0;

	speed = mmes;

	adu[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[3] = 1.0f;
	add[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[3] = 1.0f;
	spe[0] = 0.0f;
	spe[1] = 0.0f;
	spe[2] = 0.0f;
	spe[3] = 1.0f;
	adm[0] = adu[0] * add[0];
	adm[1] = adu[1] * add[1];
	adm[2] = adu[2] * add[2];
	adm[3] = adu[3] * add[3];

	stala_ruchu_atak = 0;
	stala_ruchu_nog = 0;
	stala_ruchu_nog2 = 0;

	ostatnioatak = 0;

	float extra[4];
	dislist = glGenLists(1);
	glNewList(dislist, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// czapka

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glutSolidSphere(1.1f, 24, 24);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = 0.9f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.87f);
	glScalef(0.6f, 0.15f, 0.2f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();

	/*
	dislistBG = glGenLists(1);
	glNewList(dislistBG, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// czapka
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glutSolidSphere(1.1f, 24, 24);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.2f);
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 2.0f, 14, 14);
	glPopMatrix();

	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	/*
	// szyja
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = .8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy
	extra[0] = .1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glutSolidSphere(.15f, 24, 24);
	glPopMatrix();

	// Usta
	extra[0] = 0.9f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.87f);
	glScalef(0.6f, 0.15f, 0.2f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glEndList();
	*/
}

void SBMele::rysuj(int czy_idzie, int czy_atakuje)
{
	czy_atakuje = 0;
	czy_idzie = 1;
	if (zycie <= 0)
	{
		this->rysuj_dead();
		return;
	}

	kills = killmele;
	if (killmele >= reqexp - 2)
	{
		levelanimation = 1;
		preqexp = reqexp - 2;
		reqexp += +liczniklv;
		liczniklv++;
		pointstospend++;
	}

	// znajdywanie celu

	float minn = -2;

	for (int i = 0; i < heroses.size(); i++)
	{
		if (heroses[i]->klasa == klasa || heroses[i]->how_long_dead>0)
			;
		else
		{
			if (pos.x - heroses[i]->pos.x < -1000)
				temp.x = heroses[i]->pos.x - 2001 - pos.x;
			else
				if (pos.x - heroses[i]->pos.x > 1000)
					temp.x = heroses[i]->pos.x + 2001 - pos.x;
				else
					temp.x = heroses[i]->pos.x - pos.x;

			if (pos.z - heroses[i]->pos.z < -1000)
				temp.z = heroses[i]->pos.z - 2001 - pos.z;
			else
				if (pos.z - heroses[i]->pos.z > 1000)
					temp.z = heroses[i]->pos.z + 2001 - pos.z;
				else
					temp.z = heroses[i]->pos.z - pos.z;


			temp.y = sqrtf(pow(temp.z, 2) + pow(temp.x, 2));


			if (temp.y < minn || minn <= -1)
			{
				minn = temp.y;
				victimpos.x = heroses[i]->pos.x;
				victimpos.z = heroses[i]->pos.z;
				victimpos.y = temp.y; // odleglosc miedzy ludzikami

				dir.y = 0;
				dir.x = temp.x / temp.y;
				dir.z = temp.z / temp.y;
			}
		}
	}

	temp.y = victimpos.y;
	if (pointstospend>0)
		if (zycie <= calezycie*0.4)
			heal();
		else
			if (rand() % 2)
				incraselife();
			else
				incraseatak();


	/* rysowanie uderzenia
	for (int i = 0; i < dupa.size(); i++)
	{
	glPushMatrix();
	glTranslatef(uderzenia[i].x,uderzenia[i].y, uderzenia[i].z);
	glutSolidCube(1);
	glPopMatrix();
	}
	*/

	// poruszanie sie
	// dla botow inne
	if (losowaniebledu < glutGet(GLUT_ELAPSED_TIME))
	{
		losowaniebledu = glutGet(GLUT_ELAPSED_TIME) + 500 + (rand() % 500);
		blad = (rand() % 700)*0.01;
		ucieka = 0;
	}

	if (temp.y> 8 + blad && ucieka == 0)// podchodzi
	{
		if (temp.y < 11 + blad)
			czy_atakuje = 1;
		float nowaposx = fmod((pos.x + (dir.x *speed) + 2001), 2001);
		float nowaposz = fmod((pos.z + (dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
		{
			pos.x = nowaposx;
			pos.z = nowaposz;
		}
		else
		{ // nie da sie do przodu
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 2;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 300;
			}

			if (strona == 1)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
				if (strona == 0)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
				else
					czy_idzie = 0;
		}
		if (temp.y < 90)
		{
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 3;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 700;
			}
			if (strona == 0)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
				if (strona == 1)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
		}
	}
	else
	{
		czy_atakuje = 1;
		if (losowaniebledu2 < glutGet(GLUT_ELAPSED_TIME))
		{
			losowaniebledu2 = glutGet(GLUT_ELAPSED_TIME) + 250 + (rand() % 350);
			ucieka = rand() % 2;
		}
		if (ucieka) // ucieka
		{
			czy_idzie = 0;
			float nowaposx = fmod((pos.x - (dir.x *speed) + 2001), 2001);
			float nowaposz = fmod((pos.z - (dir.z * speed) + 2001), 2001);
			if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
			{
				pos.x = nowaposx;
				pos.z = nowaposz;
				czy_idzie = 1;
			}
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 2;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 300;
			}
			if (strona == 0)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
					czy_idzie = 1;
				}
				else
					strona = 1;
			}
			else
				if (strona == 1)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
						czy_idzie = 1;
					}
					else
						strona = 0;
				}
		}
		else
		{

			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 2;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 1000;
			}
			if (strona == 0)
			{
				float	nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				float nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
			{
				if (strona == 1)
				{
					float nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					float nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
				else
					czy_idzie = 0;
			}
		}
	}



	float xxx = pos.x, zzz = pos.z;

	if (xxx - player.pos.x >= 1900)
		xxx -= 2001;
	else
		if (player.pos.x - xxx >= 1900)
			xxx += 2001;

	if (zzz - player.pos.z >= 1900)
		zzz -= 2001;
	else
		if (player.pos.z - zzz >= 1900)
			zzz += 2001;


	float fi = atan2(dir.z, dir.x);
	glTranslatef(xxx, pos.y, zzz);

	float extra[4];
	// Pasek zycia
	glPushMatrix();
	glTranslatef(0, 11.5, 0);
	glRotatef(atan2(Gracz->dir.z, Gracz->dir.x)*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	extra[0] = 1.0f - (0.04*(kills - Gracz->kills));
	extra[1] = 0.0f;
	extra[2] = 0.0f + (0.01*(kills - Gracz->kills));
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glScalef(5.0*((float)zycie / (float)calezycie), 0.5, 1);
	glutSolidCube(1);
	glPopMatrix();

	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glTranslatef(0, 0, -0.4);
	glPushMatrix();
	// rysowanie podstawki

	// unikalne
	glCallList(dislist);
	// ramiona

	// rysowanie nog 
	if (czy_idzie == 1 || stala_ruchu_nog != 0 || stala_ruchu_nog2 != 0)
	{
		if (stala_ruchu_nog2 == 0)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog > 45)
			{
				PlaySound("sounds/step2.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 1;
			}
		}
		if (stala_ruchu_nog2 == 1)
		{
			stala_ruchu_nog -= 4;
			if (stala_ruchu_nog < -45)
			{
				PlaySound("sounds/step22.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 2;
			}
		}
		if (stala_ruchu_nog2 == 2)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog == 0)
				stala_ruchu_nog2 = 0;
		}
	}

	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);
	glRotatef(0 + stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	glRotatef(0 - stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();

	// rysowanie reki + bron
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	if (stala_ruchu_atak != 0 || (czy_atakuje == 1 && ostatnioatak + czasoczekiwan < glutGet(GLUT_ELAPSED_TIME)))
	{
		// pobieram sekundy i jesli roznia sie mniej niz 2 
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME);
		if (stala_ruchu_atak == 0)
			stala_ruchu_atak = (-140);
		stala_ruchu_atak += 7;
	}

	//atak
	if (stala_ruchu_atak == (-7))
	{
		PlaySound("sounds/ea.wav", pos.x, 0, pos.z);
		// zadaj obrazenia tym przed toba na 15 odleglosci
		vector <hero*> dobicia;
		for (int i = 8; i > 1; i--)
			for (int j = 5; j > -6; j--)
			{
				int xx = (int((pos.x + dir.x * i) + (dir.z*j)) + 2001) % 2001, zz = (int((pos.z + dir.z * i) + (dir.x*j)) + 2001) % 2001;
				/* do rysowania uderznia
				vector3d nic;
				nic.x = xx;
				nic.y = 6;
				nic.z = zz;
				uderzenia.push_back(nic);
				*/
				if (map.postac[xx][zz] != NULL &&  map.postac[xx][zz]->klasa != klasa)
				{
					// sprawdzenie czy juz byl
					int czyjuzjest = 0;
					for (int k = 0; k < dobicia.size(); k++)
						if (map.postac[xx][zz] == dobicia[k])
						{
							czyjuzjest = 1;
							break;
						}
					if (czyjuzjest == 0)
						dobicia.push_back(map.postac[xx][zz]);
				}
				//map.postac[xx][zz]->odejmijzycie(podajatak()); //
			}
		for (int k = 0; k < dobicia.size(); k++)
		{
			dobicia[k]->odejmijzycie(silaataku);
			if (dobicia[k]->zycie <= 0)
				dodajkill();
		}
	}
	glRotatef(0 + stala_ruchu_atak, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// bron
	glPushMatrix();
	extra[0] = 0.65f;
	extra[1] = 0.65f;
	extra[2] = 0.65f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.0f, -1.1f, 3.0f);
	glScalef(.7f, 0.7f, 8.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glTranslatef(0.0f, -1.1f, 1.0f);
	extra[0] = 0.9f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(.35f, 1.5f, 14, 14);
	glPopMatrix();
	for (int i = 0; i < 11; i++)
	{
		glTranslatef(0.0f, 0.0f, 0.5f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(.35f, 1.5f, 14, 14);

		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(.35f, 1.5f, 14, 14);
		glPopMatrix();
	}

	glPopMatrix();
}

void SBMele::rysuj_dead()
{
	if (how_long_dead == 0)
	{
		map.uwolni(fmod(pos.x + 2001, 2001), fmod(pos.z + 2001, 2001));
		int rando = rand() % 3;
		if (rando == 0)
			PlaySound("sounds/die1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/die2.wav", pos.x, 0, pos.z);
			else
				PlaySound("sounds/die3.wav", pos.x, 0, pos.z);
	}
	if (how_long_dead > 1000)
	{// objekt ma znikac po 1000 sekundach

		pos = map.BotStart();
		pos.y = 0.5;
		zycie = calezycie;
		for (int i = -2; i < 3; i++)
			for (int j = -2; j < 3; j++)
				map.postac[((int)pos.x + i + 2001) % 2001][((int)pos.z + j + 2001) % 2001] = this;
		how_long_dead = 0;
		stala_ruchu_atak = 0;
		stala_ruchu_nog = 0;
		stala_ruchu_nog2 = 0;
		ostatnioatak = 0;

		dir.x = 0.0f + pos.x;
		dir.y = 0.0f;
		dir.z = -1.0f + pos.z;
		return;
	}
	else
		how_long_dead++;
	// rysownie martwego
	// nie dla botow


	float xxx = pos.x, zzz = pos.z;
	if (xxx - player.pos.x >= 1900)
		xxx -= 2001;
	else
		if (player.pos.x - xxx >= 1900)
			xxx += 2001;

	if (zzz - player.pos.z >= 1900)
		zzz -= 2001;
	else
		if (player.pos.z - zzz >= 1900)
			zzz += 2001;

	glTranslatef(xxx, pos.y, zzz);
	float fi = atan2(dir.z, dir.x);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	if (how_long_dead > 90)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glRotatef(how_long_dead, 1.0f, 0.0f, 0.0f);
		glRotatef(how_long_dead * 2, 0.0f, 1.0f, 0.0f);
	}

	//glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	float extra[4];
	glPushMatrix();
	// rysowanie podstawki

	// unikalne

	// ramiona
	glCallList(dislist);

	// rysowanie nog 
	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);

	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();
	// rysowanie reki broni
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glRotatef(-15.0f, .0f, 0.0f, 1.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();
}

void SBMele::heal()
{
	if (pointstospend>0 && zycie > 0)
	{
		pointstospend--;
		zycie = calezycie;
	}
}

void SBMele::incraselife()
{
	if (pointstospend>0)
	{
		pointstospend--;
		calezycie *= 1.5;
	}
}

void SBMele::incraseatak()
{
	if (pointstospend>0)
	{
		pointstospend--;
		silaataku *= 1.5;
	}
}

void SBMele::dodajkille(int ilosc)
{
	for (int i = 0; i < ilosc; i++)
		dodajkill();
}



class Gun : public hero
{
public:
	int podajatak();
	void odejmijzycie(int);
	void dodajkill();
	void heal();
	void incraselife();
	void incraseatak();
	float adu[4]; // Ambient  diffuse up
	float add[4];// Ambient  diffuse down
	float adm[4];// Ambient  diffuse up*down
	float spe[4]; //Specular
	vector3d ammopos[10];
	vector3d ammostartpos[10];
	vector3d ammodir[10];
	Gun(float, float); // przekazujemy poziom x, z. y pozostaje bez zmian bo nie zmieniam wysokosci
	~Gun();
	void rysuj(int, int); // // uwzglednic przypadek kiedy punkty zycia sa 0 to bedzie uruchamiany dead
	void setcolors(float, float, float, float, float, float); // up r g b, down r g b
private:
	void rysuj_dead();
	void rysuj_ammo();
	int stala_ruchu_nog;
	int stala_ruchu_nog2;
	int stala_ruchu_atak;
	int licznikammo;
	GLuint dislist;
	GLuint dislistBG;
};

int Gun::podajatak()
{
	return(silaataku);
}

void Gun::odejmijzycie(int points)
{
	zycie -= points;
	zycoika = glutGet(GLUT_ELAPSED_TIME) + 32;
	if (zycie <= 0)
		zycie = 0;
	else
	{
		int rando = rand() % 4;
		if (rando == 0)
			PlaySound("sounds/hg1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/hg2.wav", pos.x, 0, pos.z);
			else
				if (rando == 2)
					PlaySound("sounds/hg3.wav", pos.x, 0, pos.z);
				else
					PlaySound("sounds/hg4.wav", pos.x, 0, pos.z);
	}
}

void Gun::dodajkill()
{
	PlaySound("sounds/lz.wav", pos.x, 0, pos.z);
	kills++;
	if (kills == reqexp - 2)
	{
		PlaySound("sounds/f.wav", pos.x, 0, pos.z);
		levelanimation = 1;
		textanim1 = 1;
		preqexp = reqexp - 2;
		reqexp += +liczniklv;
		liczniklv++;
		pointstospend++;
	}
}

Gun::~Gun()
{}

void Gun::setcolors(float cur, float cug, float cub, float cdr, float cdg, float cdb)
{
	adu[0] = cur;
	adu[1] = cug;
	adu[2] = cub;
	add[0] = cdr;
	add[1] = cdg;
	add[2] = cdb;
}

Gun::Gun(float startnax, float startnaz)
{
	klasa = 'u';
	for (int i = -2; i < 3; i++)
		for (int j = -2; j < 3; j++)
			map.postac[((int)startnax + i + 2001) % 2001][((int)startnaz + j + 2001) % 2001] = this;
	silaataku = 250;
	calezycie = zyciepostaciGUN;
	zycie = calezycie;
	how_long_dead = 0;
	czasoczekiwan = 750;
	levelanimation = 0;

	pointstospend = 3;
	reqexp = 3;
	preqexp = 0;

	liczniklv = 2;

	pos.x = 0.0f + startnax;
	pos.y = 0.5f;
	pos.z = 0.0f + startnaz;

	dir.x = 0.0f + startnax;
	dir.y = 0.0f;
	dir.z = -1.0f + startnaz;

	kills = 0;

	speed = ggus + przewagagracza;
	adu[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[3] = 1.0f;
	add[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[3] = 1.0f;
	spe[0] = 0.0f;
	spe[1] = 0.0f;
	spe[2] = 0.0f;
	spe[3] = 1.0f;
	adm[0] = adu[0] * add[0];
	adm[1] = adu[1] * add[1];
	adm[2] = adu[2] * add[2];
	adm[3] = adu[3] * add[3];


	stala_ruchu_atak = 0;
	stala_ruchu_nog = 0;
	stala_ruchu_nog2 = 0;
	licznikammo = 0;
	for (int i = 0; i < 9; i++)
	{
		ammopos[i].x = 0;
		ammopos[i].y = -10;
		ammopos[i].z = 0;
	}
	ostatnioatak = 0;

	float extra[4];

	dislist = glGenLists(1);
	glNewList(dislist, GL_COMPILE);


	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.17f);
	glutSolidSphere(1.12f, 6, 6);
	glPopMatrix();


	// ramiona
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glutSolidSphere(.8f, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glutSolidSphere(0.8f, 12, 12);
	glPopMatrix();

	// lancuch
	glPushMatrix();
	extra[0] = 0.01f;
	extra[1] = 0.01f;
	extra[2] = 0.01f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	// czapka


	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja

	///*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy

	glPushMatrix();
	extra[0] = 0.1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// Usta 
	extra[0] = 0.6f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.86f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();




	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glEndList();

	dislistBG = glGenLists(1);
	glNewList(dislistBG, GL_COMPILE);

	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.17f);
	glutSolidSphere(1.12f, 6, 6);
	glPopMatrix();
	*/

	// ramiona
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glutSolidSphere(.8f, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glutSolidSphere(0.8f, 12, 12);
	glPopMatrix();

	// lancuch
	glPushMatrix();
	extra[0] = 0.01f;
	extra[1] = 0.01f;
	extra[2] = 0.01f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	// czapka


	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja

	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy

	glPushMatrix();
	extra[0] = 0.1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// Usta
	extra[0] = 0.6f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.86f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	*/


	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glEndList();
}

void Gun::rysuj_ammo()
{
	float extra[4];
	extra[0] = 0.18f;
	extra[1] = 0.08f;
	extra[2] = 0.08f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	// poruszanie sie w przod kuli
	for (int i = 0; i < 10; i++)
	{
		if (ammopos[i].y <= (-9))
			goto x;

		if (abs(ammostartpos[i].z - ammopos[i].z)>150)
			ammopos[i].y = (-10);
		if (abs(ammostartpos[i].x - ammopos[i].x)>150)
			ammopos[i].y = (-10);

		// nie dziala przez sciane
		float xxx = ammopos[i].x, zzz = ammopos[i].z;

		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;

		glPushMatrix();
		glTranslatef(xxx, ammopos[i].y, zzz);
		glutSolidSphere(.2f, 24, 24);
		glPopMatrix();

		// TU SPRAWDZAM CZY KOGOS TRAFIA!!
		// przelot przez od poczatku starej odleglosci do nowej
		for (float q = 0; q <= speed * 8; q++)
		{
			unsigned int xx = fmod(ceil(((ammopos[i].x + (ammodir[i].x * q)) + 2001)), 2001), yy = fmod(((ammopos[i].y + (ammodir[i].y * q)) + 2001), 2001), zz = fmod(ceil(((ammopos[i].z + (ammodir[i].z * q)) + 2001)), 2001);
			if (map.AmmoCatch(xx, yy, zz, this) == 1)
				// kolizja - zabieranie zycia obsluzone w funkcji
			{
				ammopos[i].y = -10;
				goto x;
			}
		}
		// brak kolizji
		ammopos[i].x += ammodir[i].x * (speed * 8); // ~pociask.speed
		ammopos[i].y += ammodir[i].y * (speed * 8); // ~pociask.speed
		ammopos[i].z += ammodir[i].z * (speed * 8); // ~pociask.speed


	x:;
	}
}

void Gun::rysuj(int czy_idzie, int czy_atakuje)
{
	if (zycie <= 0)
	{
		this->rysuj_ammo();
		this->rysuj_dead();
		return;
	}

	//celowanik dla gunera
	if (celownik && !czy_idzie)
	{
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef((Gracz->pos.x + Gracz->dir.x * 3) - Gracz->dir.z * 2, 6, (Gracz->pos.z + Gracz->dir.z * 3) + Gracz->dir.x * 2);
		glRotatef(atan2(Gracz->dir.z, Gracz->dir.x)*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
		glRotatef(asin(player.dir.y)*(-57.2957), 1.0f, 0.0f, 0.0f);
		glColor3f(0.6, 0.6, 0.6);
		glScalef(0.02, 0.02, 100);
		glutSolidCube(1);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	dir.x = player.dir.x;
	dir.y = player.dir.y;
	dir.z = player.dir.z;
	pos.x = player.pos.x;
	pos.y = player.pos.y - 8.5;
	pos.z = player.pos.z;

	/*
	dir.x =0;
	dir.y =0;
	dir.z =0;
	pos.x =0;
	pos.y =0.5;
	pos.z =0;
	*/


	if (keystate['w'] || keystate['W']) {
		float nowaposx = fmod((player.pos.x + (player.dir.x * speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z + (player.dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['s'] || keystate['S']) {
		float nowaposx = fmod((player.pos.x - (player.dir.x *speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z - (player.dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['d'] || keystate['D']) {
		float nowaposx = fmod((player.pos.x + (-player.dir.z*speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z + (player.dir.x * speed) + 2001), 2001);
		if (0 == map.HeroCatch(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['a'] || keystate['A']) {
		float nowaposx = fmod((player.pos.x - (-player.dir.z*speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z - (player.dir.x * speed) + 2001), 2001);
		if (0 == map.HeroCatch(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}



	this->rysuj_ammo();
	float fi = atan2(dir.z, dir.x);
	glTranslatef(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	// rysowanie podstawki
	float extra[4];
	// unikalne
	glTranslatef(0, 0, -0.4);
	glCallList(dislistBG);
	// rysowanie nog 
	if (czy_idzie == 1 || stala_ruchu_nog != 0 || stala_ruchu_nog2 != 0)
	{
		if (stala_ruchu_nog2 == 0)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog > 45)
			{
				PlaySound("sounds/step3.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 1;
			}
		}
		if (stala_ruchu_nog2 == 1)
		{
			stala_ruchu_nog -= 4;
			if (stala_ruchu_nog < -45)
			{
				PlaySound("sounds/step32.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 2;
			}
		}
		if (stala_ruchu_nog2 == 2)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog == 0)
				stala_ruchu_nog2 = 0;
		}
	}

	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);
	glRotatef(0 + stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	glRotatef(0 - stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	// rysowanie reki
	glPushMatrix();
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	if (stala_ruchu_atak != 0 || ((czy_atakuje == 1) && ostatnioatak + czasoczekiwan< glutGet(GLUT_ELAPSED_TIME)))
	{
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME);
		if (stala_ruchu_atak == 0)
			stala_ruchu_atak = 31;
		stala_ruchu_atak -= 1;
	}

	glPushMatrix();
	glRotatef(0 + stala_ruchu_atak, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.0f, 0.0f);
	glScalef(0.8f, 2.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glTranslatef(.0f, -1.6f, 1.0f - stala_ruchu_atak*0.03);
	glPushMatrix();
	glScalef(0.8f, 0.8f, 1.5f);
	glutSolidCube(1.0f);
	glPopMatrix();

	//bron
	glPushMatrix();
	glTranslatef(.0f, 0.0f, 0.3f);
	extra[0] = 0.1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glScalef(0.6f, 2.0f, 0.6f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(.0f, 0.7f, 0.6f);
	glPushMatrix();
	glScalef(0.6f, .7f, 1.5f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(.0f, 0.0f, 0.1f);
	glPushMatrix();
	extra[0] = 0.2f;
	extra[1] = 0.2f;
	extra[2] = 0.2f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glScalef(0.2f, .2f, 1.4f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();

	// zapisanie wspolrzednych do strzalu z uwzglednieniem polozenia pistoletu
	if (stala_ruchu_atak == 30)
	{
		PlaySound("sounds/ga.wav", pos.x, 0, pos.z);
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME); // t w swietle
									// przesuniecie wylotu naboju
									// w przod w bok
		ammopos[licznikammo].x = (pos.x + dir.x * 3) - dir.z * 2;
		ammopos[licznikammo].z = (pos.z + dir.z * 3) + dir.x * 2;

		// w gore
		ammopos[licznikammo].y = 6.0;

		// ustawienie kierunku lotu
		if (czy_idzie == 1) // randomowe przesuwanie naboju
		{
			float fi = atan2((dir.x), (player.dir.z)) + (((rand() % 71) - 35)*0.01);
			float teta = asin(player.dir.y) + (((rand() % 61) - 30)*0.005);
			ammodir[licznikammo].x = cos(teta)*sin(fi);
			ammodir[licznikammo].y = sin(teta);
			ammodir[licznikammo].z = cos(teta)*cos(fi);
		}
		else
		{
			ammodir[licznikammo].x = dir.x;
			ammodir[licznikammo].y = dir.y;
			ammodir[licznikammo].z = dir.z;
		}

		ammostartpos[licznikammo].x = ammopos[licznikammo].x;
		ammostartpos[licznikammo].y = ammopos[licznikammo].y;
		ammostartpos[licznikammo].z = ammopos[licznikammo].z;
		// podanie wartosci dl=blysku
		l1_pos[0] = ammopos[licznikammo].x;
		l1_pos[1] = ammopos[licznikammo].y;
		l1_pos[2] = ammopos[licznikammo].z;
		l1_pos[3] = 1.0;
		glEnable(GL_LIGHT1);

		if (licznikammo == 9)
			licznikammo = 0;
		else
			licznikammo++;
	}
	// wylaczenie blysku
	if (stala_ruchu_atak <= 2)
	{
		glDisable(GL_LIGHT1);
	}
	glPopMatrix();

	glPopMatrix();
}

void Gun::rysuj_dead()
{
	if (how_long_dead == 0)
	{
		map.uwolni(fmod(pos.x + 2001, 2001), fmod(pos.z + 2001, 2001));
		int rando = rand() % 3;
		if (rando == 0)
			PlaySound("sounds/die1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/die2.wav", pos.x, 0, pos.z);
			else
				PlaySound("sounds/die3.wav", pos.x, 0, pos.z);
	}
	if (how_long_dead > 1000)
	{// objekt ma znikac po 1000 sekundach
		this->~Gun(); // lub zycie =1000 nowe miejsce na mapie i howlong dead=0
		return;
	}
	else
		how_long_dead++;
	// rysownie martwego
	// nie dla botow
	player.dir.y = -1.3;
	player.dir.z = dir.z;
	player.dir.x = dir.x;


	glTranslatef(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
	float fi = atan2(dir.z, dir.x);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	if (how_long_dead > 90)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glRotatef(how_long_dead, 1.0f, 0.0f, 0.0f);
		glRotatef(how_long_dead * 2, 0.0f, 1.0f, 0.0f);
	}

	//glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	float extra[4];
	glPushMatrix();
	// rysowanie podstawki

	// unikalne

	// ramiona
	glCallList(dislist);

	// rysowanie nog 
	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);

	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();
	// rysowanie reki broni
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glRotatef(-15.0f, .0f, 0.0f, 1.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();
}

void Gun::heal()
{
	if (pointstospend>0 && zycie > 0)
	{
		PlaySound("sounds/heal.wav", pos.x, 0, pos.z);
		pointstospend--;
		zycie = calezycie;
	}
}

void Gun::incraselife()
{
	if (pointstospend>0)
	{
		PlaySound("sounds/lif.wav", pos.x, 0, pos.z);
		pointstospend--;
		calezycie *= 1.5;
	}
}

void Gun::incraseatak()
{
	if (pointstospend>0)
	{
		PlaySound("sounds/ata.wav", pos.x, 0, pos.z);
		pointstospend--;
		silaataku *= 1.5;
	}
}


class SGun : public hero
{
public:
	int podajatak();
	void odejmijzycie(int);
	void dodajkill();
	void heal();
	void incraselife();
	void incraseatak();
	float adu[4]; // Ambient  diffuse up
	float add[4];// Ambient  diffuse down
	float adm[4];// Ambient  diffuse up*down
	float spe[4]; //Specular
	vector3d ammopos[10];
	vector3d ammostartpos[10];
	vector3d ammodir[10];
	SGun(float, float); // przekazujemy poziom x, z. y pozostaje bez zmian bo nie zmieniam wysokosci
	~SGun();
	void rysuj(int, int); // // uwzglednic przypadek kiedy punkty zycia sa 0 to bedzie uruchamiany dead
	void setcolors(float, float, float, float, float, float); // up r g b, down r g b
private:
	void rysuj_dead();
	void rysuj_ammo();
	int stala_ruchu_nog;
	int stala_ruchu_nog2;
	int stala_ruchu_atak;
	int licznikammo;
	GLuint dislist;
	GLuint dislistBG;
};

int SGun::podajatak()
{
	return(silaataku);
}

void SGun::odejmijzycie(int points)
{
	zycie -= points;
	zycoika = glutGet(GLUT_ELAPSED_TIME) + 32;
	if (zycie <= 0)
		zycie = 0;
	else
	{
		int rando = rand() % 4;
		if (rando == 0)
			PlaySound("sounds/hg1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/hg2.wav", pos.x, 0, pos.z);
			else
				if (rando == 2)
					PlaySound("sounds/hg3.wav", pos.x, 0, pos.z);
				else
					PlaySound("sounds/hg4.wav", pos.x, 0, pos.z);
	}
}

void SGun::dodajkill()
{
	killgun++;
}

SGun::~SGun()
{}

void SGun::setcolors(float cur, float cug, float cub, float cdr, float cdg, float cdb)
{
	adu[0] = cur;
	adu[1] = cug;
	adu[2] = cub;
	add[0] = cdr;
	add[1] = cdg;
	add[2] = cdb;
}

SGun::SGun(float startnax, float startnaz)
{
	klasa = 'u';
	for (int i = -2; i < 3; i++)
		for (int j = -2; j < 3; j++)
			map.postac[((int)startnax + i + 2001) % 2001][((int)startnaz + j + 2001) % 2001] = this;
	silaataku = 250;
	calezycie = zyciepostaciGUN;
	zycie = calezycie;
	how_long_dead = 0;
	czasoczekiwan = 750;
	levelanimation = 0;

	pointstospend = 3;
	reqexp = 3;
	preqexp = 0;

	liczniklv = 2;

	pos.x = 0.0f + startnax;
	pos.y = 0.5f;
	pos.z = 0.0f + startnaz;

	dir.x = 0.0f + startnax;
	dir.y = 0.0f;
	dir.z = -1.0f + startnaz;

	kills = 0;

	speed = ggus + przewagagracza;
	adu[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[3] = 1.0f;
	add[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[3] = 1.0f;
	spe[0] = 0.0f;
	spe[1] = 0.0f;
	spe[2] = 0.0f;
	spe[3] = 1.0f;
	adm[0] = adu[0] * add[0];
	adm[1] = adu[1] * add[1];
	adm[2] = adu[2] * add[2];
	adm[3] = adu[3] * add[3];


	stala_ruchu_atak = 0;
	stala_ruchu_nog = 0;
	stala_ruchu_nog2 = 0;
	licznikammo = 0;
	for (int i = 0; i < 9; i++)
	{
		ammopos[i].x = 0;
		ammopos[i].y = -10;
		ammopos[i].z = 0;
	}
	ostatnioatak = 0;

	float extra[4];

	dislist = glGenLists(1);
	glNewList(dislist, GL_COMPILE);


	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.17f);
	glutSolidSphere(1.12f, 6, 6);
	glPopMatrix();


	// ramiona
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glutSolidSphere(.8f, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glutSolidSphere(0.8f, 12, 12);
	glPopMatrix();

	// lancuch
	glPushMatrix();
	extra[0] = 0.01f;
	extra[1] = 0.01f;
	extra[2] = 0.01f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	// czapka


	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja

	///*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy

	glPushMatrix();
	extra[0] = 0.1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// Usta 
	extra[0] = 0.6f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.86f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();




	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glEndList();

	dislistBG = glGenLists(1);
	glNewList(dislistBG, GL_COMPILE);

	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.17f);
	glutSolidSphere(1.12f, 6, 6);
	glPopMatrix();
	*/

	// ramiona
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glutSolidSphere(.8f, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glutSolidSphere(0.8f, 12, 12);
	glPopMatrix();

	// lancuch
	glPushMatrix();
	extra[0] = 0.01f;
	extra[1] = 0.01f;
	extra[2] = 0.01f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	// czapka


	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja

	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy

	glPushMatrix();
	extra[0] = 0.1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// Usta
	extra[0] = 0.6f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.86f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	*/


	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glEndList();
}

void SGun::rysuj_ammo()
{
	float extra[4];
	extra[0] = 0.18f;
	extra[1] = 0.08f;
	extra[2] = 0.08f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	// poruszanie sie w przod kuli
	for (int i = 0; i < 10; i++)
	{
		if (ammopos[i].y <= (-9))
			goto x;

		if (abs(ammostartpos[i].z - ammopos[i].z)>150)
			ammopos[i].y = (-10);
		if (abs(ammostartpos[i].x - ammopos[i].x)>150)
			ammopos[i].y = (-10);

		// nie dziala przez sciane
		float xxx = ammopos[i].x, zzz = ammopos[i].z;

		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;

		glPushMatrix();
		glTranslatef(xxx, ammopos[i].y, zzz);
		glutSolidSphere(.2f, 24, 24);
		glPopMatrix();

		// TU SPRAWDZAM CZY KOGOS TRAFIA!!
		// przelot przez od poczatku starej odleglosci do nowej
		for (float q = 0; q <= speed * 8; q++)
		{
			unsigned int xx = fmod(ceil(((ammopos[i].x + (ammodir[i].x * q)) + 2001)), 2001), yy = fmod(((ammopos[i].y + (ammodir[i].y * q)) + 2001), 2001), zz = fmod(ceil(((ammopos[i].z + (ammodir[i].z * q)) + 2001)), 2001);
			if (map.AmmoCatch2(xx, yy, zz, this) == 1)
				// kolizja - zabieranie zycia obsluzone w funkcji
			{
				ammopos[i].y = -10;
				goto x;
			}
		}
		// brak kolizji
		ammopos[i].x += ammodir[i].x * (speed * 8); // ~pociask.speed
		ammopos[i].y += ammodir[i].y * (speed * 8); // ~pociask.speed
		ammopos[i].z += ammodir[i].z * (speed * 8); // ~pociask.speed


	x:;
	}
}

void SGun::rysuj(int czy_idzie, int czy_atakuje)
{
	if (zycie <= 0)
	{
		this->rysuj_ammo();
		this->rysuj_dead();
		return;
	}

	if (killgun != kills)
	{
		kills = killgun;
		PlaySound("sounds/lz.wav", pos.x, 0, pos.z);
	}

	if (killgun >= reqexp - 2)
	{
		PlaySound("sounds/f.wav", pos.x, 0, pos.z);
		levelanimation = 1;
		textanim1 = 1;
		preqexp = reqexp - 2;
		reqexp += +liczniklv;
		liczniklv++;
		pointstospend++;
	}

	//celowanik dla gunera
	if (celownik && !czy_idzie)
	{
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef((Gracz->pos.x + Gracz->dir.x * 3) - Gracz->dir.z * 2, 6, (Gracz->pos.z + Gracz->dir.z * 3) + Gracz->dir.x * 2);
		glRotatef(atan2(Gracz->dir.z, Gracz->dir.x)*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
		glRotatef(asin(player.dir.y)*(-57.2957), 1.0f, 0.0f, 0.0f);
		glColor3f(0.6, 0.6, 0.6);
		glScalef(0.02, 0.02, 100);
		glutSolidCube(1);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	dir.x = player.dir.x;
	dir.y = player.dir.y;
	dir.z = player.dir.z;
	pos.x = player.pos.x;
	pos.y = player.pos.y - 8.5;
	pos.z = player.pos.z;

	/*
	dir.x =0;
	dir.y =0;
	dir.z =0;
	pos.x =0;
	pos.y =0.5;
	pos.z =0;
	*/


	if (keystate['w'] || keystate['W']) {
		float nowaposx = fmod((player.pos.x + (player.dir.x * speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z + (player.dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['s'] || keystate['S']) {
		float nowaposx = fmod((player.pos.x - (player.dir.x *speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z - (player.dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['d'] || keystate['D']) {
		float nowaposx = fmod((player.pos.x + (-player.dir.z*speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z + (player.dir.x * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}
	if (keystate['a'] || keystate['A']) {
		float nowaposx = fmod((player.pos.x - (-player.dir.z*speed) + 2001), 2001);
		float nowaposz = fmod((player.pos.z - (player.dir.x * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(player.pos.x, player.pos.z, nowaposx, nowaposz, this))
		{
			player.pos.x = nowaposx;
			player.pos.z = nowaposz;
		}
	}



	this->rysuj_ammo();
	float fi = atan2(dir.z, dir.x);
	glTranslatef(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	// rysowanie podstawki
	float extra[4];
	// unikalne
	glTranslatef(0, 0, -0.4);
	glCallList(dislistBG);
	// rysowanie nog 
	if (czy_idzie == 1 || stala_ruchu_nog != 0 || stala_ruchu_nog2 != 0)
	{
		if (stala_ruchu_nog2 == 0)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog > 45)
			{
				PlaySound("sounds/step3.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 1;
			}
		}
		if (stala_ruchu_nog2 == 1)
		{
			stala_ruchu_nog -= 4;
			if (stala_ruchu_nog < -45)
			{
				PlaySound("sounds/step32.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 2;
			}
		}
		if (stala_ruchu_nog2 == 2)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog == 0)
				stala_ruchu_nog2 = 0;
		}
	}

	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);
	glRotatef(0 + stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	glRotatef(0 - stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	// rysowanie reki
	glPushMatrix();
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	if (stala_ruchu_atak != 0 || ((czy_atakuje == 1) && ostatnioatak + czasoczekiwan< glutGet(GLUT_ELAPSED_TIME)))
	{
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME);
		if (stala_ruchu_atak == 0)
			stala_ruchu_atak = 31;
		stala_ruchu_atak -= 1;
	}

	glPushMatrix();
	glRotatef(0 + stala_ruchu_atak, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.0f, 0.0f);
	glScalef(0.8f, 2.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glTranslatef(.0f, -1.6f, 1.0f - stala_ruchu_atak*0.03);
	glPushMatrix();
	glScalef(0.8f, 0.8f, 1.5f);
	glutSolidCube(1.0f);
	glPopMatrix();

	//bron
	glPushMatrix();
	glTranslatef(.0f, 0.0f, 0.3f);
	extra[0] = 0.1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glScalef(0.6f, 2.0f, 0.6f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(.0f, 0.7f, 0.6f);
	glPushMatrix();
	glScalef(0.6f, .7f, 1.5f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(.0f, 0.0f, 0.1f);
	glPushMatrix();
	extra[0] = 0.2f;
	extra[1] = 0.2f;
	extra[2] = 0.2f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glScalef(0.2f, .2f, 1.4f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();

	// zapisanie wspolrzednych do strzalu z uwzglednieniem polozenia pistoletu
	if (stala_ruchu_atak == 30)
	{
		PlaySound("sounds/ga.wav", pos.x, 0, pos.z);
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME); // t w swietle
									// przesuniecie wylotu naboju
									// w przod w bok
		ammopos[licznikammo].x = (pos.x + dir.x * 3) - dir.z * 2;
		ammopos[licznikammo].z = (pos.z + dir.z * 3) + dir.x * 2;

		// w gore
		ammopos[licznikammo].y = 6.0;

		// ustawienie kierunku lotu
		if (czy_idzie == 1) // randomowe przesuwanie naboju
		{
			float fi = atan2((dir.x), (player.dir.z)) + (((rand() % 71) - 35)*0.01);
			float teta = asin(player.dir.y) + (((rand() % 61) - 30)*0.005);
			ammodir[licznikammo].x = cos(teta)*sin(fi);
			ammodir[licznikammo].y = sin(teta);
			ammodir[licznikammo].z = cos(teta)*cos(fi);
		}
		else
		{
			ammodir[licznikammo].x = dir.x;
			ammodir[licznikammo].y = dir.y;
			ammodir[licznikammo].z = dir.z;
		}

		ammostartpos[licznikammo].x = ammopos[licznikammo].x;
		ammostartpos[licznikammo].y = ammopos[licznikammo].y;
		ammostartpos[licznikammo].z = ammopos[licznikammo].z;
		// podanie wartosci dl=blysku
		l1_pos[0] = ammopos[licznikammo].x;
		l1_pos[1] = ammopos[licznikammo].y;
		l1_pos[2] = ammopos[licznikammo].z;
		l1_pos[3] = 1.0;
		glEnable(GL_LIGHT1);

		if (licznikammo == 9)
			licznikammo = 0;
		else
			licznikammo++;
	}
	// wylaczenie blysku
	if (stala_ruchu_atak <= 2)
	{
		glDisable(GL_LIGHT1);
	}
	glPopMatrix();

	glPopMatrix();
}

void SGun::rysuj_dead()
{
	if (how_long_dead == 0)
	{
		map.uwolni(fmod(pos.x + 2001, 2001), fmod(pos.z + 2001, 2001));
		int rando = rand() % 3;
		if (rando == 0)
			PlaySound("sounds/die1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/die2.wav", pos.x, 0, pos.z);
			else
				PlaySound("sounds/die3.wav", pos.x, 0, pos.z);
	}
	if (how_long_dead > 1000)
	{// objekt ma znikac po 1000 sekundach
		return;
	}
	else
		how_long_dead++;
	// rysownie martwego
	// nie dla botow
	player.dir.y = -1.3;
	player.dir.z = dir.z;
	player.dir.x = dir.x;


	glTranslatef(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);
	float fi = atan2(dir.z, dir.x);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	if (how_long_dead > 90)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glRotatef(how_long_dead, 1.0f, 0.0f, 0.0f);
		glRotatef(how_long_dead * 2, 0.0f, 1.0f, 0.0f);
	}

	//glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	float extra[4];
	glPushMatrix();
	// rysowanie podstawki

	// unikalne

	// ramiona
	glCallList(dislist);

	// rysowanie nog 
	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);

	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();
	// rysowanie reki broni
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glRotatef(-15.0f, .0f, 0.0f, 1.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();
}

void SGun::heal()
{
	if (pointstospend>0 && zycie > 0)
	{
		PlaySound("sounds/heal.wav", pos.x, 0, pos.z);
		pointstospend--;
		zycie = calezycie;
	}
}

void SGun::incraselife()
{
	if (pointstospend>0)
	{
		PlaySound("sounds/lif.wav", pos.x, 0, pos.z);
		pointstospend--;
		calezycie *= 1.5;
	}
}

void SGun::incraseatak()
{
	if (pointstospend>0)
	{
		PlaySound("sounds/ata.wav", pos.x, 0, pos.z);
		pointstospend--;
		silaataku *= 1.5;
	}
}


class BGun : public hero
{
public:
	vector3d victimpos; // pozycja bohatera
	vector3d temp; // pozycja bohatera
	int strona;
	float smialosc;
	void dodajkille(int);
	int podajatak();
	void odejmijzycie(int);
	void dodajkill();
	void heal();
	void incraselife();
	void incraseatak();
	float adu[4]; // Ambient  diffuse up
	float add[4];// Ambient  diffuse down
	float adm[4];// Ambient  diffuse up*down
	float spe[4]; //Specular
	vector3d ammopos[10];
	vector3d ammostartpos[10];
	vector3d ammodir[10];
	BGun(float, float); // przekazujemy poziom x, z. y pozostaje bez zmian bo nie zmieniam wysokosci
	~BGun();
	void rysuj(int, int); // // uwzglednic przypadek kiedy punkty zycia sa 0 to bedzie uruchamiany dead
	void setcolors(float, float, float, float, float, float); // up r g b, down r g b
private:
	void rysuj_dead();
	void rysuj_ammo();
	int stala_ruchu_nog;
	int stala_ruchu_nog2;
	int stala_ruchu_atak;
	int licznikammo;
	GLuint dislist;
};

int BGun::podajatak()
{
	return(silaataku);
}

void BGun::odejmijzycie(int points)
{
	zycie -= points;
	if (zycie <= 0)
		zycie = 0;
	else
	{
		int rando = rand() % 4;
		if (rando == 0)
			PlaySound("sounds/hg1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/hg2.wav", pos.x, 0, pos.z);
			else
				if (rando == 2)
					PlaySound("sounds/hg3.wav", pos.x, 0, pos.z);
				else
					PlaySound("sounds/hg4.wav", pos.x, 0, pos.z);
	}
}

void BGun::dodajkill()
{
	kills++;
	if (kills >= reqexp - 2)
	{
		levelanimation = 1;
		preqexp = reqexp - 2;
		reqexp += +liczniklv;
		liczniklv++;
		pointstospend++;
	}
}

BGun::~BGun()
{}

void BGun::setcolors(float cur, float cug, float cub, float cdr, float cdg, float cdb)
{
	adu[0] = cur;
	adu[1] = cug;
	adu[2] = cub;
	add[0] = cdr;
	add[1] = cdg;
	add[2] = cdb;
}

BGun::BGun(float startnax, float startnaz)
{
	smialosc = (rand() % 2000)*0.01;
	klasa = 'u';
	for (int i = -2; i < 3; i++)
		for (int j = -2; j < 3; j++)
			map.postac[((int)startnax + i + 2001) % 2001][((int)startnaz + j + 2001) % 2001] = this;
	silaataku = 250;
	calezycie = zyciepostaciGUN;
	zycie = calezycie;
	how_long_dead = 0;
	czasoczekiwan = 750;
	levelanimation = 0;

	pointstospend = 3;
	reqexp = 3;
	preqexp = 0;

	liczniklv = 2;

	pos.x = 0.0f + startnax;
	pos.y = 0.5f;
	pos.z = 0.0f + startnaz;

	dir.x = 0.0f + startnax;
	dir.y = 0.0f;
	dir.z = -1.0f + startnaz;

	kills = 0;

	speed = ggus;
	adu[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[3] = 1.0f;
	add[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[3] = 1.0f;
	spe[0] = 0.0f;
	spe[1] = 0.0f;
	spe[2] = 0.0f;
	spe[3] = 1.0f;
	adm[0] = adu[0] * add[0];
	adm[1] = adu[1] * add[1];
	adm[2] = adu[2] * add[2];
	adm[3] = adu[3] * add[3];


	stala_ruchu_atak = 0;
	stala_ruchu_nog = 0;
	stala_ruchu_nog2 = 0;
	licznikammo = 0;
	for (int i = 0; i < 9; i++)
	{
		ammopos[i].x = 0;
		ammopos[i].y = -10;
		ammopos[i].z = 0;
	}
	ostatnioatak = 0;

	float extra[4];

	dislist = glGenLists(1);
	glNewList(dislist, GL_COMPILE);


	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.17f);
	glutSolidSphere(1.12f, 6, 6);
	glPopMatrix();


	// ramiona
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glutSolidSphere(.8f, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glutSolidSphere(0.8f, 12, 12);
	glPopMatrix();

	// lancuch
	glPushMatrix();
	extra[0] = 0.01f;
	extra[1] = 0.01f;
	extra[2] = 0.01f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	// czapka


	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja

	///*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy

	glPushMatrix();
	extra[0] = 0.1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// Usta 
	extra[0] = 0.6f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.86f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();




	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glEndList();
	/*
	dislistBG = glGenLists(1);
	glNewList(dislistBG, GL_COMPILE);

	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.17f);
	glutSolidSphere(1.12f, 6, 6);
	glPopMatrix();


	// ramiona
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glutSolidSphere(.8f, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glutSolidSphere(0.8f, 12, 12);
	glPopMatrix();

	// lancuch
	glPushMatrix();
	extra[0] = 0.01f;
	extra[1] = 0.01f;
	extra[2] = 0.01f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	// czapka


	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja

	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy

	glPushMatrix();
	extra[0] = 0.1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// Usta
	extra[0] = 0.6f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.86f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();




	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glEndList();
	*/
}

void BGun::rysuj_ammo()
{
	float extra[4];
	extra[0] = 0.18f;
	extra[1] = 0.08f;
	extra[2] = 0.08f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	// poruszanie sie w przod kuli
	for (int i = 0; i < 10; i++)
	{
		if (ammopos[i].y <= (-9))
			goto x;

		if (abs(ammostartpos[i].z - ammopos[i].z)>150)
			ammopos[i].y = (-10);
		if (abs(ammostartpos[i].x - ammopos[i].x)>150)
			ammopos[i].y = (-10);

		// nie dziala przez sciane
		float xxx = ammopos[i].x, zzz = ammopos[i].z;

		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;

		glPushMatrix();
		glTranslatef(xxx, ammopos[i].y, zzz);
		glutSolidSphere(.2f, 24, 24);
		glPopMatrix();

		// TU SPRAWDZAM CZY KOGOS TRAFIA!!
		// przelot przez od poczatku starej odleglosci do nowej
		for (float q = 0; q <= speed * 8; q++)
		{
			unsigned int xx = fmod(ceil(((ammopos[i].x + (ammodir[i].x * q)) + 2001)), 2001), yy = fmod(((ammopos[i].y + (ammodir[i].y * q)) + 2001), 2001), zz = fmod(ceil(((ammopos[i].z + (ammodir[i].z * q)) + 2001)), 2001);
			if (map.AmmoCatch(xx, yy, zz, this) == 1)
				// kolizja - zabieranie zycia obsluzone w funkcji
			{
				ammopos[i].y = -10;
				goto x;
			}
		}
		// brak kolizji
		ammopos[i].x += ammodir[i].x * (speed * 8); // ~pociask.speed
		ammopos[i].y += ammodir[i].y * (speed * 8); // ~pociask.speed
		ammopos[i].z += ammodir[i].z * (speed * 8); // ~pociask.speed


	x:;
	}
}

void BGun::rysuj(int czy_idzie, int czy_atakuje)
{
	czy_idzie = 1;
	czy_atakuje = 0;
	if (zycie <= 0)
	{
		this->rysuj_ammo();
		this->rysuj_dead();
		return;
	}

	// znajdywanie celu

	float minn = -2;

	for (int i = 0; i < heroses.size(); i++)
	{
		if (heroses[i] == this || heroses[i]->how_long_dead>0)
			;
		else
		{
			if (pos.x - heroses[i]->pos.x < -1000)
				temp.x = heroses[i]->pos.x - 2001 - pos.x;
			else
				if (pos.x - heroses[i]->pos.x > 1000)
					temp.x = heroses[i]->pos.x + 2001 - pos.x;
				else
					temp.x = heroses[i]->pos.x - pos.x;

			if (pos.z - heroses[i]->pos.z < -1000)
				temp.z = heroses[i]->pos.z - 2001 - pos.z;
			else
				if (pos.z - heroses[i]->pos.z > 1000)
					temp.z = heroses[i]->pos.z + 2001 - pos.z;
				else
					temp.z = heroses[i]->pos.z - pos.z;


			temp.y = sqrtf(pow(temp.z, 2) + pow(temp.x, 2));


			if (temp.y < minn || minn <= -1)
			{
				minn = temp.y;
				victimpos.x = heroses[i]->pos.x;
				victimpos.z = heroses[i]->pos.z;
				victimpos.y = temp.y; // odleglosc miedzy ludzikami

				dir.y = 0;
				dir.x = temp.x / temp.y;
				dir.z = temp.z / temp.y;
			}
		}
	}

	temp.y = victimpos.y;
	if (pointstospend>0)
		if (zycie <= calezycie*0.4)
			heal();
		else
			if (rand() % 2)
				incraselife();
			else
				incraseatak();


	if (temp.y> 30 + smialosc)// podchodzi
	{
		float nowaposx = fmod((pos.x + (dir.x *speed) + 2001), 2001);
		float nowaposz = fmod((pos.z + (dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
		{
			pos.x = nowaposx;
			pos.z = nowaposz;
		}
		else
		{ // nie da sie do przodu
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 2;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 300;
			}

			if (strona == 1)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
				if (strona == 0)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
				else
					czy_idzie = 0;
		}
		if (temp.y < 90)
		{
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 3;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 500;
			}
			if (strona == 0)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
				if (strona == 1)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
		}
	}
	else
	{
		czy_atakuje = 1;
		if (temp.y < 25 + smialosc) // ucieka
		{
			float nowaposx = fmod((pos.x - (dir.x *speed) + 2001), 2001);
			float nowaposz = fmod((pos.z - (dir.z * speed) + 2001), 2001);
			if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
			{
				pos.x = nowaposx;
				pos.z = nowaposz;
			}
			else
			{
				if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
				{
					strona = rand() % 2;
					levelanimation = glutGet(GLUT_ELAPSED_TIME) + 300;
				}
				if (strona == 0)
				{
					nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
				else
					if (strona == 1)
					{
						nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
						nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
						if (0 == map.HeroCatch(pos.x, pos.z, nowaposx, nowaposz, this))
						{
							pos.x = nowaposx;
							pos.z = nowaposz;
						}
						else
							strona = 3;
					}
					else
						czy_idzie = 0;
			}
		}
		czy_idzie = 0;
	}

	float xxx = pos.x, zzz = pos.z;

	if (xxx - player.pos.x >= 1900)
		xxx -= 2001;
	else
		if (player.pos.x - xxx >= 1900)
			xxx += 2001;

	if (zzz - player.pos.z >= 1900)
		zzz -= 2001;
	else
		if (player.pos.z - zzz >= 1900)
			zzz += 2001;



	this->rysuj_ammo();
	float fi = atan2(dir.z, dir.x);
	glTranslatef(xxx, pos.y, zzz);

	float extra[4];
	// Pasek zycia
	glPushMatrix();
	glTranslatef(0, 11.5, 0);
	glRotatef(atan2(Gracz->dir.z, Gracz->dir.x)*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	extra[0] = 1.0f - (0.04*(kills - Gracz->kills));
	extra[1] = 0.0f;
	extra[2] = 0.0f + (0.01*(kills - Gracz->kills));
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glScalef(5.0*((float)zycie / (float)calezycie), 0.5, 1);
	glutSolidCube(1);
	glPopMatrix();

	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	// rysowanie podstawki
	
	// unikalne
	glTranslatef(0, 0, -0.4);
	glCallList(dislist);
	// rysowanie nog 
	if (czy_idzie == 1 || stala_ruchu_nog != 0 || stala_ruchu_nog2 != 0)
	{
		if (stala_ruchu_nog2 == 0)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog > 45)
			{
				PlaySound("sounds/step3.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 1;
			}
		}
		if (stala_ruchu_nog2 == 1)
		{
			stala_ruchu_nog -= 4;
			if (stala_ruchu_nog < -45)
			{
				PlaySound("sounds/step32.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 2;
			}
		}
		if (stala_ruchu_nog2 == 2)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog == 0)
				stala_ruchu_nog2 = 0;
		}
	}

	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);
	glRotatef(0 + stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	glRotatef(0 - stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	// rysowanie reki
	glPushMatrix();
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	if (stala_ruchu_atak != 0 || ((czy_atakuje == 1) && ostatnioatak + czasoczekiwan< glutGet(GLUT_ELAPSED_TIME)))
	{
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME);
		if (stala_ruchu_atak == 0)
			stala_ruchu_atak = 31;
		stala_ruchu_atak -= 1;
	}

	glPushMatrix();
	glRotatef(stala_ruchu_atak, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.0f, 0.0f);
	glScalef(0.8f, 2.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glTranslatef(.0f, -1.6f, 1.0f - stala_ruchu_atak*0.03);
	glPushMatrix();
	glScalef(0.8f, 0.8f, 1.5f);
	glutSolidCube(1.0f);
	glPopMatrix();

	//bron
	glPushMatrix();
	glTranslatef(.0f, 0.0f, 0.3f);
	extra[0] = 0.1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glScalef(0.6f, 2.0f, 0.6f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(.0f, 0.7f, 0.6f);
	glPushMatrix();
	glScalef(0.6f, .7f, 1.5f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(.0f, 0.0f, 0.1f);
	glPushMatrix();
	extra[0] = 0.2f;
	extra[1] = 0.2f;
	extra[2] = 0.2f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glScalef(0.2f, .2f, 1.4f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();

	// zapisanie wspolrzednych do strzalu z uwzglednieniem polozenia pistoletu
	if (stala_ruchu_atak == 30)
	{
		PlaySound("sounds/ga.wav", pos.x, 0, pos.z);
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME); // t w swietle
									// przesuniecie wylotu naboju
									// w przod w bok
		ammopos[licznikammo].x = (pos.x + dir.x * 3) - dir.z * 2;;
		ammopos[licznikammo].z = (pos.z + dir.z * 3) + dir.x * 2;

		// w gore
		ammopos[licznikammo].y = 6.0;

		// ustawienie kierunku lotu

		if (czy_idzie == 1) // randomowe przesuwanie naboju
		{
			float fi = atan2((dir.x), (player.dir.z)) + (((rand() % 71) - 35)*0.01);
			float teta = asin(player.dir.y) + (((rand() % 61) - 30)*0.005);
			ammodir[licznikammo].x = cos(teta)*sin(fi);
			ammodir[licznikammo].y = sin(teta);
			ammodir[licznikammo].z = cos(teta)*cos(fi);
		}
		else
		{
			ammodir[licznikammo].x = dir.x;
			ammodir[licznikammo].y = dir.y;
			ammodir[licznikammo].z = dir.z;
		}

		ammostartpos[licznikammo].x = ammopos[licznikammo].x;
		ammostartpos[licznikammo].y = ammopos[licznikammo].y;
		ammostartpos[licznikammo].z = ammopos[licznikammo].z;
		// podanie wartosci dl=blysku

		xxx = ammopos[licznikammo].x, zzz = ammopos[licznikammo].z;
		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;
		l3_pos[0] = xxx;
		l3_pos[1] = ammopos[licznikammo].y;
		l3_pos[2] = zzz;
		l3_pos[3] = 1.0;
		glEnable(GL_LIGHT3);

		if (licznikammo == 9)
			licznikammo = 0;
		else
			licznikammo++;
	}
	// wylaczenie blysku
	if (stala_ruchu_atak <= 2)
	{
		glDisable(GL_LIGHT3);
	}
	glPopMatrix();

	glPopMatrix();
}

void BGun::rysuj_dead()
{
	if (how_long_dead == 0)
	{
		map.uwolni(fmod(pos.x + 2001, 2001), fmod(pos.z + 2001, 2001));
		int rando = rand() % 3;
		if (rando == 0)
			PlaySound("sounds/die1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/die2.wav", pos.x, 0, pos.z);
			else
				PlaySound("sounds/die3.wav", pos.x, 0, pos.z);
	}
	if (how_long_dead > 1000)
	{
		if (how_long_dead > 1000)
		{// objekt ma znikac po 1000 sekundach

			pos = map.BotStart();
			pos.y = 0.5;
			zycie = calezycie;
			for (int i = -2; i < 3; i++)
				for (int j = -2; j < 3; j++)
					map.postac[((int)pos.x + i + 2001) % 2001][((int)pos.z + j + 2001) % 2001] = this;
			for (int i = 0; i < 9; i++)
			{
				ammopos[i].x = 0;
				ammopos[i].y = -10;
				ammopos[i].z = 0;
			}
			how_long_dead = 0;
			stala_ruchu_atak = 0;
			stala_ruchu_nog = 0;
			stala_ruchu_nog2 = 0;
			licznikammo = 0;
			ostatnioatak = 0;

			dir.x = 0.0f + pos.x;
			dir.y = 0.0f;
			dir.z = -1.0f + pos.z;
			return;
		}
	}
	else
		how_long_dead++;
	// rysownie martwego

	float xxx = pos.x, zzz = pos.z;
	if (xxx - player.pos.x >= 1900)
		xxx -= 2001;
	else
		if (player.pos.x - xxx >= 1900)
			xxx += 2001;

	if (zzz - player.pos.z >= 1900)
		zzz -= 2001;
	else
		if (player.pos.z - zzz >= 1900)
			zzz += 2001;

	glTranslatef(xxx, pos.y, zzz);
	float fi = atan2(dir.z, dir.x);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	if (how_long_dead > 90)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glRotatef(how_long_dead, 1.0f, 0.0f, 0.0f);
		glRotatef(how_long_dead * 2, 0.0f, 1.0f, 0.0f);
	}

	//glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	float extra[4];
	glPushMatrix();
	// rysowanie podstawki

	// unikalne

	// ramiona
	glCallList(dislist);

	// rysowanie nog 
	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);

	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();
	// rysowanie reki broni
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glRotatef(-15.0f, .0f, 0.0f, 1.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();
}

void BGun::heal()
{
	if (pointstospend>0 && zycie > 0)
	{
		pointstospend--;
		zycie = calezycie;
	}
}

void BGun::incraselife()
{
	if (pointstospend>0)
	{
		pointstospend--;
		calezycie *= 1.5;
	}
}

void BGun::incraseatak()
{
	if (pointstospend>0)
	{
		pointstospend--;
		silaataku *= 1.5;
	}
}

void BGun::dodajkille(int ilosc)
{
	for (int i = 0; i < ilosc; i++)
		dodajkill();
}


class SBGun : public hero
{
public:
	vector3d victimpos; // pozycja bohatera
	vector3d temp; // pozycja bohatera
	int strona;
	float smialosc;
	void dodajkille(int);
	int podajatak();
	void odejmijzycie(int);
	void dodajkill();
	void heal();
	void incraselife();
	void incraseatak();
	float adu[4]; // Ambient  diffuse up
	float add[4];// Ambient  diffuse down
	float adm[4];// Ambient  diffuse up*down
	float spe[4]; //Specular
	vector3d ammopos[10];
	vector3d ammostartpos[10];
	vector3d ammodir[10];
	SBGun(float, float); // przekazujemy poziom x, z. y pozostaje bez zmian bo nie zmieniam wysokosci
	~SBGun();
	void rysuj(int, int); // // uwzglednic przypadek kiedy punkty zycia sa 0 to bedzie uruchamiany dead
	void setcolors(float, float, float, float, float, float); // up r g b, down r g b
private:
	void rysuj_dead();
	void rysuj_ammo();
	int stala_ruchu_nog;
	int stala_ruchu_nog2;
	int stala_ruchu_atak;
	int licznikammo;
	GLuint dislist;
};

int SBGun::podajatak()
{
	return(silaataku);
}

void SBGun::odejmijzycie(int points)
{
	zycie -= points;
	if (zycie <= 0)
		zycie = 0;
	else
	{
		int rando = rand() % 4;
		if (rando == 0)
			PlaySound("sounds/hg1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/hg2.wav", pos.x, 0, pos.z);
			else
				if (rando == 2)
					PlaySound("sounds/hg3.wav", pos.x, 0, pos.z);
				else
					PlaySound("sounds/hg4.wav", pos.x, 0, pos.z);
	}
}

void SBGun::dodajkill()
{
	killgun++;
}

SBGun::~SBGun()
{}

void SBGun::setcolors(float cur, float cug, float cub, float cdr, float cdg, float cdb)
{
	adu[0] = cur;
	adu[1] = cug;
	adu[2] = cub;
	add[0] = cdr;
	add[1] = cdg;
	add[2] = cdb;
}

SBGun::SBGun(float startnax, float startnaz)
{
	smialosc = (rand() % 2000)*0.01;
	klasa = 'u';
	for (int i = -2; i < 3; i++)
		for (int j = -2; j < 3; j++)
			map.postac[((int)startnax + i + 2001) % 2001][((int)startnaz + j + 2001) % 2001] = this;
	silaataku = 250;
	calezycie = zyciepostaciGUN;
	zycie = calezycie;
	how_long_dead = 0;
	czasoczekiwan = 750;
	levelanimation = 0;

	pointstospend = 3;
	reqexp = 3;
	preqexp = 0;

	liczniklv = 2;

	pos.x = 0.0f + startnax;
	pos.y = 0.5f;
	pos.z = 0.0f + startnaz;

	dir.x = 0.0f + startnax;
	dir.y = 0.0f;
	dir.z = -1.0f + startnaz;

	kills = 0;

	speed = ggus;

	adu[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	adu[3] = 1.0f;
	add[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	add[3] = 1.0f;
	spe[0] = 0.0f;
	spe[1] = 0.0f;
	spe[2] = 0.0f;
	spe[3] = 1.0f;
	adm[0] = adu[0] * add[0];
	adm[1] = adu[1] * add[1];
	adm[2] = adu[2] * add[2];
	adm[3] = adu[3] * add[3];


	stala_ruchu_atak = 0;
	stala_ruchu_nog = 0;
	stala_ruchu_nog2 = 0;
	licznikammo = 0;
	for (int i = 0; i < 9; i++)
	{
		ammopos[i].x = 0;
		ammopos[i].y = -10;
		ammopos[i].z = 0;
	}
	ostatnioatak = 0;

	float extra[4];

	dislist = glGenLists(1);
	glNewList(dislist, GL_COMPILE);


	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.17f);
	glutSolidSphere(1.12f, 6, 6);
	glPopMatrix();


	// ramiona
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glutSolidSphere(.8f, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glutSolidSphere(0.8f, 12, 12);
	glPopMatrix();

	// lancuch
	glPushMatrix();
	extra[0] = 0.01f;
	extra[1] = 0.01f;
	extra[2] = 0.01f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	// czapka


	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja

	///*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy

	glPushMatrix();
	extra[0] = 0.1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// Usta 
	extra[0] = 0.6f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.86f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();




	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glEndList();
	/*
	dislistBG = glGenLists(1);
	glNewList(dislistBG, GL_COMPILE);

	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adm);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.2f, -0.17f);
	glutSolidSphere(1.12f, 6, 6);
	glPopMatrix();


	// ramiona
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.75f, 7.0f, 0.0f);
	glutSolidSphere(.8f, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.75f, 7.0f, 0.0f);
	glutSolidSphere(0.8f, 12, 12);
	glPopMatrix();

	// lancuch
	glPushMatrix();
	extra[0] = 0.01f;
	extra[1] = 0.01f;
	extra[2] = 0.01f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8f, 7.f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.3, 0.3, 24, 24);
	glPopMatrix();

	// czapka


	// po unikalnych

	// krocze hehehe
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 3.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// brzuch
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// szyja

	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, adu);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, adu);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 7.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// glowa
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	// szyja
	glPushMatrix();
	glTranslatef(0.0f, 7.75f, 0.0f);
	glScalef(0.8f, 0.9f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// oczy

	glPushMatrix();
	extra[0] = 0.1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, 9.18f, 0.82f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// Usta
	extra[0] = 0.6f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, 8.79f, 0.86f);
	glScalef(0.7f, 0.1f, 0.3f);
	glutSolidCube(1.0f);
	glPopMatrix();




	// uda
	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 3.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// lewa reka (nieruchoma)
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(2.0f, 5.5f, 0.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glEndList();
	*/
}

void SBGun::rysuj_ammo()
{
	float extra[4];
	extra[0] = 0.18f;
	extra[1] = 0.08f;
	extra[2] = 0.08f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	// poruszanie sie w przod kuli
	for (int i = 0; i < 10; i++)
	{
		if (ammopos[i].y <= (-9))
			goto x;

		if (abs(ammostartpos[i].z - ammopos[i].z)>150)
			ammopos[i].y = (-10);
		if (abs(ammostartpos[i].x - ammopos[i].x)>150)
			ammopos[i].y = (-10);

		// nie dziala przez sciane
		float xxx = ammopos[i].x, zzz = ammopos[i].z;

		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;

		glPushMatrix();
		glTranslatef(xxx, ammopos[i].y, zzz);
		glutSolidSphere(.2f, 24, 24);
		glPopMatrix();

		// TU SPRAWDZAM CZY KOGOS TRAFIA!!
		// przelot przez od poczatku starej odleglosci do nowej
		for (float q = 0; q <= speed * 8; q++)
		{
			unsigned int xx = fmod(ceil(((ammopos[i].x + (ammodir[i].x * q)) + 2001)), 2001), yy = fmod(((ammopos[i].y + (ammodir[i].y * q)) + 2001), 2001), zz = fmod(ceil(((ammopos[i].z + (ammodir[i].z * q)) + 2001)), 2001);
			if (map.AmmoCatch2(xx, yy, zz, this) == 1)
				// kolizja - zabieranie zycia obsluzone w funkcji
			{
				ammopos[i].y = -10;
				goto x;
			}
		}
		// brak kolizji
		ammopos[i].x += ammodir[i].x * (speed * 8); // ~pociask.speed
		ammopos[i].y += ammodir[i].y * (speed * 8); // ~pociask.speed
		ammopos[i].z += ammodir[i].z * (speed * 8); // ~pociask.speed


	x:;
	}
}

void SBGun::rysuj(int czy_idzie, int czy_atakuje)
{
	czy_idzie = 1;
	czy_atakuje = 0;
	if (zycie <= 0)
	{
		this->rysuj_ammo();
		this->rysuj_dead();
		return;
	}

	kills = killgun;
	if (killgun >= reqexp - 2)
	{
		levelanimation = 1;
		preqexp = reqexp - 2;
		reqexp += +liczniklv;
		liczniklv++;
		pointstospend++;
	}

	// znajdywanie celu

	float minn = -2;

	for (int i = 0; i < heroses.size(); i++)
	{
		if (heroses[i]->how_long_dead>0 || heroses[i]->klasa == klasa)
			;
		else
		{
			if (pos.x - heroses[i]->pos.x < -1000)
				temp.x = heroses[i]->pos.x - 2001 - pos.x;
			else
				if (pos.x - heroses[i]->pos.x > 1000)
					temp.x = heroses[i]->pos.x + 2001 - pos.x;
				else
					temp.x = heroses[i]->pos.x - pos.x;

			if (pos.z - heroses[i]->pos.z < -1000)
				temp.z = heroses[i]->pos.z - 2001 - pos.z;
			else
				if (pos.z - heroses[i]->pos.z > 1000)
					temp.z = heroses[i]->pos.z + 2001 - pos.z;
				else
					temp.z = heroses[i]->pos.z - pos.z;


			temp.y = sqrtf(pow(temp.z, 2) + pow(temp.x, 2));


			if (temp.y < minn || minn <= -1)
			{
				minn = temp.y;
				victimpos.x = heroses[i]->pos.x;
				victimpos.z = heroses[i]->pos.z;
				victimpos.y = temp.y; // odleglosc miedzy ludzikami

				dir.y = 0;
				dir.x = temp.x / temp.y;
				dir.z = temp.z / temp.y;
			}
		}
	}

	temp.y = victimpos.y;
	if (pointstospend>0)
		if (zycie <= calezycie*0.4)
			heal();
		else
			if (rand() % 2)
				incraselife();
			else
				incraseatak();


	if (temp.y> 30 + smialosc)// podchodzi
	{
		float nowaposx = fmod((pos.x + (dir.x *speed) + 2001), 2001);
		float nowaposz = fmod((pos.z + (dir.z * speed) + 2001), 2001);
		if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
		{
			pos.x = nowaposx;
			pos.z = nowaposz;
		}
		else
		{ // nie da sie do przodu
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 2;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 300;
			}

			if (strona == 1)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
				if (strona == 0)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
		}
		if (temp.y < 90)
		{
			if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
			{
				strona = rand() % 3;
				levelanimation = glutGet(GLUT_ELAPSED_TIME) + 700;
			}
			if (strona == 0)
			{
				nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
				nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
				if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
				{
					pos.x = nowaposx;
					pos.z = nowaposz;
				}
				else
					strona = 3;
			}
			else
				if (strona == 1)
				{
					nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
		}
	}
	else
	{
		czy_atakuje = 1;
		if (temp.y < 25 + smialosc) // ucieka
		{
			float nowaposx = fmod((pos.x - (dir.x *speed) + 2001), 2001);
			float nowaposz = fmod((pos.z - (dir.z * speed) + 2001), 2001);
			if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
			{
				pos.x = nowaposx;
				pos.z = nowaposz;
			}
			else
			{
				if (levelanimation < glutGet(GLUT_ELAPSED_TIME))
				{
					strona = rand() % 2;
					levelanimation = glutGet(GLUT_ELAPSED_TIME) + 300;
				}
				if (strona == 0)
				{
					nowaposx = fmod((pos.x + (-dir.z*speed) + 2001), 2001);
					nowaposz = fmod((pos.z + (dir.x * speed) + 2001), 2001);
					if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
					{
						pos.x = nowaposx;
						pos.z = nowaposz;
					}
					else
						strona = 3;
				}
				else
					if (strona == 1)
					{
						nowaposx = fmod((pos.x - (-dir.z*speed) + 2001), 2001);
						nowaposz = fmod((pos.z - (dir.x * speed) + 2001), 2001);
						if (0 == map.HeroCatch2(pos.x, pos.z, nowaposx, nowaposz, this))
						{
							pos.x = nowaposx;
							pos.z = nowaposz;
						}
						else
							strona = 3;
					}
					else
						czy_idzie = 0;
			}
		}
		else
			czy_idzie = 0;
	}

	float xxx = pos.x, zzz = pos.z;

	if (xxx - player.pos.x >= 1900)
		xxx -= 2001;
	else
		if (player.pos.x - xxx >= 1900)
			xxx += 2001;

	if (zzz - player.pos.z >= 1900)
		zzz -= 2001;
	else
		if (player.pos.z - zzz >= 1900)
			zzz += 2001;



	this->rysuj_ammo();
	float fi = atan2(dir.z, dir.x);
	float extra[4];
	glTranslatef(xxx, pos.y, zzz);

	// Pasek zycia
	glPushMatrix();
	glTranslatef(0, 11.5, 0);
	glRotatef(atan2(Gracz->dir.z, Gracz->dir.x)*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	extra[0] = 1.0f - (0.04*(kills - Gracz->kills));
	extra[1] = 0.0f;
	extra[2] = 0.0f + (0.01*(kills - Gracz->kills));
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glScalef(5.0*((float)zycie / (float)calezycie), 0.5, 1);
	glutSolidCube(1);
	glPopMatrix();

	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	// rysowanie podstawki
	
	// unikalne
	glTranslatef(0, 0, -0.4);
	glCallList(dislist);
	// rysowanie nog 
	if (czy_idzie == 1 || stala_ruchu_nog != 0 || stala_ruchu_nog2 != 0)
	{
		if (stala_ruchu_nog2 == 0)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog > 45)
			{
				PlaySound("sounds/step3.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 1;
			}
		}
		if (stala_ruchu_nog2 == 1)
		{
			stala_ruchu_nog -= 4;
			if (stala_ruchu_nog < -45)
			{
				PlaySound("sounds/step32.wav", pos.x, 0, pos.z);
				stala_ruchu_nog2 = 2;
			}
		}
		if (stala_ruchu_nog2 == 2)
		{
			stala_ruchu_nog += 4;
			if (stala_ruchu_nog == 0)
				stala_ruchu_nog2 = 0;
		}
	}

	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);
	glRotatef(0 + stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	glRotatef(0 - stala_ruchu_nog, 1.0f, 0.0f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	// rysowanie reki
	glPushMatrix();
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	if (stala_ruchu_atak != 0 || ((czy_atakuje == 1) && ostatnioatak + czasoczekiwan< glutGet(GLUT_ELAPSED_TIME)))
	{
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME);
		if (stala_ruchu_atak == 0)
			stala_ruchu_atak = 31;
		stala_ruchu_atak -= 1;
	}

	glPushMatrix();
	glRotatef(0 + stala_ruchu_atak, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.0f, 0.0f);
	glScalef(0.8f, 2.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glTranslatef(.0f, -1.6f, 1.0f - stala_ruchu_atak*0.03);
	glPushMatrix();
	glScalef(0.8f, 0.8f, 1.5f);
	glutSolidCube(1.0f);
	glPopMatrix();

	//bron
	glPushMatrix();
	glTranslatef(.0f, 0.0f, 0.3f);
	extra[0] = 0.1f;
	extra[1] = 0.1f;
	extra[2] = 0.1f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glScalef(0.6f, 2.0f, 0.6f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(.0f, 0.7f, 0.6f);
	glPushMatrix();
	glScalef(0.6f, .7f, 1.5f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(.0f, 0.0f, 0.1f);
	glPushMatrix();
	extra[0] = 0.2f;
	extra[1] = 0.2f;
	extra[2] = 0.2f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glScalef(0.2f, .2f, 1.4f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();

	// zapisanie wspolrzednych do strzalu z uwzglednieniem polozenia pistoletu
	if (stala_ruchu_atak == 30)
	{
		PlaySound("sounds/ga.wav", pos.x, 0, pos.z);
		ostatnioatak = glutGet(GLUT_ELAPSED_TIME); // t w swietle
									// przesuniecie wylotu naboju
									// w przod w bok
		ammopos[licznikammo].x = (pos.x + dir.x * 3) - dir.z * 2;;
		ammopos[licznikammo].z = (pos.z + dir.z * 3) + dir.x * 2;

		// w gore
		ammopos[licznikammo].y = 6.0;

		// ustawienie kierunku lotu

		if (czy_idzie == 1) // randomowe przesuwanie naboju
		{
			float fi = atan2((dir.x), (player.dir.z)) + (((rand() % 71) - 35)*0.01);
			float teta = asin(player.dir.y) + (((rand() % 61) - 30)*0.005);
			ammodir[licznikammo].x = cos(teta)*sin(fi);
			ammodir[licznikammo].y = sin(teta);
			ammodir[licznikammo].z = cos(teta)*cos(fi);
		}
		else
		{
			ammodir[licznikammo].x = dir.x;
			ammodir[licznikammo].y = dir.y;
			ammodir[licznikammo].z = dir.z;
		}

		ammostartpos[licznikammo].x = ammopos[licznikammo].x;
		ammostartpos[licznikammo].y = ammopos[licznikammo].y;
		ammostartpos[licznikammo].z = ammopos[licznikammo].z;
		// podanie wartosci dl=blysku

		xxx = ammopos[licznikammo].x, zzz = ammopos[licznikammo].z;
		if (xxx - player.pos.x >= 1900)
			xxx -= 2001;
		else
			if (player.pos.x - xxx >= 1900)
				xxx += 2001;

		if (zzz - player.pos.z >= 1900)
			zzz -= 2001;
		else
			if (player.pos.z - zzz >= 1900)
				zzz += 2001;
		l3_pos[0] = xxx;
		l3_pos[1] = ammopos[licznikammo].y;
		l3_pos[2] = zzz;
		l3_pos[3] = 1.0;
		glEnable(GL_LIGHT3);

		if (licznikammo == 9)
			licznikammo = 0;
		else
			licznikammo++;
	}
	// wylaczenie blysku
	if (stala_ruchu_atak <= 2)
	{
		glDisable(GL_LIGHT3);
	}
	glPopMatrix();

	glPopMatrix();
}

void SBGun::rysuj_dead()
{
	if (how_long_dead == 0)
	{
		map.uwolni(fmod(pos.x + 2001, 2001), fmod(pos.z + 2001, 2001));
		int rando = rand() % 3;
		if (rando == 0)
			PlaySound("sounds/die1.wav", pos.x, 0, pos.z);
		else
			if (rando == 1)
				PlaySound("sounds/die2.wav", pos.x, 0, pos.z);
			else
				PlaySound("sounds/die3.wav", pos.x, 0, pos.z);
	}
	if (how_long_dead > 1000)
	{
		if (how_long_dead > 1000)
		{// objekt ma znikac po 1000 sekundach

		
			pos = map.BotStart();
			pos.y = 0.5;
			zycie = calezycie;
			for (int i = -2; i < 3; i++)
				for (int j = -2; j < 3; j++)
					map.postac[((int)pos.x + i + 2001) % 2001][((int)pos.z + j + 2001) % 2001] = this;
			for (int i = 0; i < 9; i++)
			{
				ammopos[i].x = 0;
				ammopos[i].y = -10;
				ammopos[i].z = 0;
			}
			how_long_dead = 0;
			stala_ruchu_atak = 0;
			stala_ruchu_nog = 0;
			stala_ruchu_nog2 = 0;
			licznikammo = 0;
			ostatnioatak = 0;

			dir.x = 0.0f + pos.x;
			dir.y = 0.0f;
			dir.z = -1.0f + pos.z;
			return;
		}
	}
	else
		how_long_dead++;
	// rysownie martwego

	float xxx = pos.x, zzz = pos.z;
	if (xxx - player.pos.x >= 1900)
		xxx -= 2001;
	else
		if (player.pos.x - xxx >= 1900)
			xxx += 2001;

	if (zzz - player.pos.z >= 1900)
		zzz -= 2001;
	else
		if (player.pos.z - zzz >= 1900)
			zzz += 2001;

	glTranslatef(xxx, pos.y, zzz);
	float fi = atan2(dir.z, dir.x);
	glRotatef(fi*(-57.2957) + 90, 0.0f, 1.0f, 0.0f);
	if (how_long_dead > 90)
	{
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glRotatef(how_long_dead, 1.0f, 0.0f, 0.0f);
		glRotatef(how_long_dead * 2, 0.0f, 1.0f, 0.0f);
	}

	//glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	float extra[4];
	glPushMatrix();
	// rysowanie podstawki

	// unikalne

	// ramiona
	glCallList(dislist);

	// rysowanie nog 
	glPushMatrix();
	glTranslatef(-1.0f, 2.1f, 0.0f);

	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);
	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.0f, 2.1f, 0.0f);
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(0.0f, -0.9f, 0.0f);

	glScalef(0.8f, 2.1f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, add);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, add);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glPushMatrix();
	glTranslatef(.0f, -2.2f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glPopMatrix();
	// rysowanie reki broni
	extra[0] = 0.8f;
	extra[1] = 0.5f;
	extra[2] = 0.5f;
	extra[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, extra);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, extra);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glTranslatef(-2.0f, 7.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glPushMatrix();
	glRotatef(-15.0f, .0f, 0.0f, 1.0f);
	glScalef(0.8f, 3.0f, 0.8f);
	glutSolidCube(1.0f);
	glPopMatrix();


	glPopMatrix();
}

void SBGun::heal()
{
	if (pointstospend>0 && zycie > 0)
	{
		pointstospend--;
		zycie = calezycie;
	}
}

void SBGun::incraselife()
{
	if (pointstospend>0)
	{
		pointstospend--;
		calezycie *= 1.5;
	}
}

void SBGun::incraseatak()
{
	if (pointstospend>0)
	{
		pointstospend--;
		silaataku *= 1.5;
	}
}

void SBGun::dodajkille(int ilosc)
{
	for (int i = 0; i < ilosc; i++)
		dodajkill();
}

// przyciski myszki
void OnMouseClick(int button, int state, int x, int y)
{
	if (pauza)
		return;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == 0)
		{
			player.czyatakuje = 1;
		}
		else
			player.czyatakuje = 0;
		// x y pozycje myszki, state =0 kiedy naciskam, 1 kiedy puszczam, button ... :D
	}
	
	if (button == GLUT_LEFT_BUTTON && heroses.size() == 1 && SecfromStart!=0 && player.czyatakuje==1)
	{// tworenie wrogow - 3 postacie kazdje klasy razem z graczem
		vector3d start;
		
		int j = 4; // ZMIENNA OKRESLAJACA ILOSC LUDZI OKRESLONEGO TYPU!!!!!!!!!!!!!!!!!!!
		int k = j;

		if (samotnicy == 1)
		{
			// resp dla samotnikow
			if (Gracz->klasa == 'e')
				j--;
			for (int i = 0; i < j; i++)
			{
				start = map.BotStart();
				heroses.push_back(new BMele(start.x, start.z));
			}
			j = k;

			if (Gracz->klasa == 'i')
				j--;
			for (int i = 0; i < j; i++)
			{
				start = map.BotStart();
				heroses.push_back(new BMine(start.x, start.z));
			}
			j = k;

			if (Gracz->klasa == 'u')
				j--;
			for (int i = 0; i < j; i++)
			{
				start = map.BotStart();
				heroses.push_back(new BGun(start.x, start.z));
			}
		}
		else
		{
			if (Gracz->klasa == 'e')
			{
				j--;
				start.z= Gracz->pos.z;
				start.x = Gracz->pos.x = ((int)Gracz->pos.x + 2011) % 2001;
			}
			else
			{
				start = map.BotStart();
			}
			for (int i = 0; i < j; i++)
			{
				heroses.push_back(new SBMele(start.x, start.z));
				do {
					start.x = ((int)start.x + 2011) % 2001;
				} while (map.CanBotStart(start.x, start.z));
			}
			j = k;

			if (Gracz->klasa == 'i')
			{
				j--;
				start.z = Gracz->pos.z;
				start.x = Gracz->pos.x = ((int)Gracz->pos.x + 2011) % 2001;
			}
			else
			{
				start = map.BotStart();
			}
			for (int i = 0; i < j; i++)
			{
				heroses.push_back(new SBMine(start.x, start.z));
				do {
					start.x = ((int)start.x + 2011) % 2001;
				} while (map.CanBotStart(start.x, start.z));
			}
			j = k;

			if (Gracz->klasa == 'u')
			{
				j--;
				start.z = Gracz->pos.z;
				start.x = Gracz->pos.x= ((int)Gracz->pos.x + 2011)%2001;
			}
			else
			{
				start = map.BotStart();
			}
			for (int i = 0; i < j; i++)
			{
				heroses.push_back(new SBGun(start.x, start.z));
				do {
					start.x = ((int)start.x + 2011) % 2001;
				} while (map.CanBotStart(start.x, start.z));
			}
		}
		bstart = 1;
	}

	if (button == GLUT_RIGHT_BUTTON && Gracz->klasa == 'u') // celownik dla ganera
	{
		if (state == 0)
		{
			celownik = 1;
		}
		else
			celownik = 0;
	}
}

void OnMouseClickm(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == 0)
	{
		if (wybrano == 3)
		{
			JustPlay("sounds/switch.wav", false);
			postac = 3;
			return;
		}
		if (wybrano == 2)
		{
			JustPlay("sounds/switch.wav", false);
			postac = 2;
			return;
		}
		if (wybrano == 1)
		{
			JustPlay("sounds/switch.wav", false);
			postac = 1;
			return;
		}
		if (bsojusznicy)
		{
			JustPlay("sounds/switch.wav", false);
			if (!wybrano && ssojusznicy)
			{
				ssojusznicy = 0;
				return;
			}
			ssojusznicy = 1;
			return;
		}

		if (bsamotnik)
		{
			JustPlay("sounds/switch.wav", false);
			if (!wybrano && ssamotnik)
			{
				ssamotnik = 0;
				return;
			}
			ssamotnik = 1;
			return;
		}


		if (spomoc == 1)
		{
			JustPlay("sounds/switch.wav", false);
			spomoc = 0;
			return;
		}

		if (bpomoc)
		{
			JustPlay("sounds/switch.wav", false);
			spomoc = 1;
			return;
		}


		if (bkoniec)
		{
			JustPlay("sounds/switch.wav", false);
			glutLeaveMainLoop();
		}
	}
}

// Przygotowania do renderowania oraz funkcje obslugujace

void Menu()
{
	textanim2 = 0;
	SecfromStart = 0;
	glutDisplayFunc(OnRender3);
	glutReshapeFunc(OnReshape);

	glutKeyboardFunc(OnKeyPressM);
	glutKeyboardUpFunc(OnKeyUp);

	glutSetCursor(GLUT_CURSOR_DESTROY);
	glutMouseFunc(OnMouseClickm); // obsluga przyciskow myszy
	glutWarpPointer(maxwidth / 2, maxheight / 2); // kursor na srodku 
	mouse.x = GLUT_WINDOW_WIDTH/2; // poczatkowe polozenie kursora
	mouse.y = GLUT_WINDOW_HEIGHT / 2;
	glutMotionFunc(tellpositionm);
	glutPassiveMotionFunc(tellpositionm);

	// Timer
	glutTimerFunc(17, OnTimer, 0); // wywoluje sie co 17 ms

	glEnable(GL_DEPTH_TEST); // test glebokosci



	mmnoznik = 1;
	bkoniec = 0;
	bsojusznicy = 0;
	bsamotnik = 0;
	bpomoc = 0;
	spomoc = 0;
	ssojusznicy = 0;
	ssamotnik = 0;
	wybrano = 0;
	postac = 0;
	licznikmenu = 0;

	JustPlay("sounds/menu.wav", true);
	glutMainLoop();
}

void Samotnicy(int klasastartowa)
{
	samotnicy = 1;
	textanim4 = 0;
	glutDisplayFunc(OnRender2);
	glutReshapeFunc(OnReshape);

	// Timer
	glutTimerFunc(17, OnTimer, 0); // wywoluje sie co 17 ms

	glEnable(GL_DEPTH_TEST); // test glebokosci


	// Inicjalizacja kamery:
	player.pos.x = 0.0f;
	player.pos.y = 9.0f;
	player.pos.z = .0f;

	player.dir.x = 0.0f;
	player.dir.y = 0.0f;
	player.dir.z = -1.0f;


	// Ustawiamy komponent ambient naszej sceny - wartosc niezalezna od swiatla (warto zresetowac)
	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	// 
	glEnable(GL_LIGHTING); // Wlaczenie oswietlenia
	glShadeModel(GL_SMOOTH); // Wybor techniki cieniowania
	glEnable(GL_LIGHT0); // Wlaczenie 0-go zrodla swiatla

	glEnable(GL_NORMALIZE);

	//stowrzenie list
	drzewo1 = stworz_drzewo1();
	drzewo2 = stworz_drzewo2();
	ziemiaO = stworz_ziemieO();
	ziemiaT = stworz_ziemieT();
	nieboO = stworz_nieboO();
	nieboT = stworz_nieboT();
	arrow = StworzArrow();

	// Mgla - oraz
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f); // kolor okna
	glEnable(GL_FOG);
	float gl_fogcolor[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, gl_fogcolor);
	glFogf(GL_FOG_START, 0.1f);
	glFogf(GL_FOG_END, 95.0f);

	map.iniciuj();
	
	engine->stopAllSounds(); // zatrzymanie muzyki w menu w menu
	if (klasastartowa == 1)
	{
		Gracz = new Mine(0, 0);
		PlaySound("sounds/is.wav", 0, 0, 0);
	}
	else
	{
		if (klasastartowa == 2)
		{
			Gracz = new Mele(0, 0);
			PlaySound("sounds/es.wav", 0, 0, 0);
		}
		else
		{
			Gracz = new Gun(0, 0);
			PlaySound("sounds/gs.wav", 0, 0, 0);
		}
	}
	heroses.push_back(Gracz);

	// klawiatura
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	
	player.speed = Gracz->speed;

	// myszka
	glutMouseFunc(OnMouseClick); // obsluga przyciskow myszy
	glutSetCursor(GLUT_CURSOR_NONE); //ukrycie kursora
	glutWarpPointer(GLUT_SCREEN_WIDTH / 2, GLUT_SCREEN_HEIGHT / 2); // kursor na srodku 
	mouse.x = GLUT_SCREEN_WIDTH / 2; // poczatkowe polozenie kursora
	mouse.y = GLUT_SCREEN_HEIGHT / 2;
	glutMotionFunc(tellposition);
	glutPassiveMotionFunc(tellposition);

	glutMainLoop();
}

void Sojusznicy(int klasastartowa)
{
	samotnicy = 0;
	textanim4 = 0;
	killgun = 0;
	killmele = 0;
	killmine = 0;

	glutDisplayFunc(OnRender4);
	glutReshapeFunc(OnReshape);

	// Timer
	glutTimerFunc(17, OnTimer, 0); // wywoluje sie co 17 ms

	glEnable(GL_DEPTH_TEST); // test glebokosci

	 // Inicjalizacja kamery:
	player.pos.x = 0.0f;
	player.pos.y = 9.0f;
	player.pos.z = .0f;

	player.dir.x = 0.0f;
	player.dir.y = 0.0f;
	player.dir.z = -1.0f;


	// Ustawiamy komponent ambient naszej sceny - wartosc niezalezna od swiatla (warto zresetowac)
	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	// 
	glEnable(GL_LIGHTING); // Wlaczenie oswietlenia
	glShadeModel(GL_SMOOTH); // Wybor techniki cieniowania
	glEnable(GL_LIGHT0); // Wlaczenie 0-go zrodla swiatla

	glEnable(GL_NORMALIZE);

	//stowrzenie list
	drzewo1 = stworz_drzewo1();
	drzewo2 = stworz_drzewo2();
	ziemiaO = stworz_ziemieO();
	ziemiaT = stworz_ziemieT();
	nieboO = stworz_nieboO();
	nieboT = stworz_nieboT();
	arrow = StworzArrow();

	// Mgla - oraz
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f); // kolor okna
	glEnable(GL_FOG);
	float gl_fogcolor[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, gl_fogcolor);
	glFogf(GL_FOG_START, 0.1f);
	glFogf(GL_FOG_END, 95.0f);

	map.iniciuj();

	engine->stopAllSounds(); // zatrzymanie muzyki w menu w menu
	switch (klasastartowa)
	{
	case 1:
		Gracz = new SMine(0, 0);
		PlaySound("sounds/is.wav", 0, 0, 0);
		break;
	case 2:
		Gracz = new SMele(0, 0);
		PlaySound("sounds/es.wav", 0, 0, 0);
		break;
	case 3:
		Gracz = new SGun(0, 0);
		PlaySound("sounds/gs.wav", 0, 0, 0);
		break;
	}
	heroses.push_back(Gracz);

	// klawiatura
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);

	player.speed = Gracz->speed;

	// myszka
	glutMouseFunc(OnMouseClick); // obsluga przyciskow myszy
	glutSetCursor(GLUT_CURSOR_NONE); //ukrycie kursora
	glutWarpPointer(GLUT_SCREEN_WIDTH / 2, GLUT_SCREEN_HEIGHT / 2); // kursor na srodku 
	mouse.x = GLUT_SCREEN_WIDTH / 2; // poczatkowe polozenie kursora
	mouse.y = GLUT_SCREEN_HEIGHT / 2;
	glutMotionFunc(tellposition);
	glutPassiveMotionFunc(tellposition);

	glutMainLoop();
}

void OnRender3()
{
	SecfromStart = glutGet(GLUT_ELAPSED_TIME);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (postac>10)
	{
		if (ssojusznicy)
			Sojusznicy(postac - 10);
		else
			Samotnicy(postac - 10);
	}


	if (postac == 1 || postac == 2 || postac == 3)
		if (ssojusznicy)
		{
			postac += 10;
			drawShape(0, 0, 256, 256, loadning);
		}
		else
		{
			postac += 10;
			drawShape(0, 0, 256, 256, loadning);
		}

	if (spomoc)
		drawShape(0, 0, 256, 256, stronapomocy);

	if (ssojusznicy || ssamotnik)
	{
		drawShape(25, 20, 60, 60, miner);
		drawShape(25, 100, 60, 60, bar);
		drawShape(25, 180, 60, 60, guns);
		if (wybrano == 1)
			drawShape(23, 18, 65, 65, green);
		else
			if (wybrano == 2)
				drawShape(23, 98, 65, 65, green);
			else
				if (wybrano == 3)
					drawShape(23, 178, 65, 65, green);
		drawShape(0, 0, 256, 256, wybierz);

	}

	drawShape(88, 5, 80, 60, mtitle);


	if (licznikmenu<2000)
	{
		drawShape(5, 356 - (licznikmenu / 10), 60, 60, koniec);
		drawShape(30, 400 - (licznikmenu / 10), 10, 70, stick);
		drawShape(191, 356 - (licznikmenu / 10), 60, 60, pomoc);
		drawShape(216, 400 - (licznikmenu / 10), 10, 70, stick);

		drawShape(376 - (licznikmenu / 10), 55, 60, 60, sojusznicy);
		drawShape(430 - (licznikmenu / 10), 80, 70, 10, stickH);

		drawShape(-180 + (licznikmenu / 10), 55, 60, 60, samotnik);
		drawShape(-210 + (licznikmenu / 10), 80, 70, 10, stickH);
	}
	else
	{
		drawShape(5, 156, 60, 60, koniec);
		drawShape(30, 200, 10, 70, stick);
		drawShape(191, 156, 60, 60, pomoc);
		drawShape(216, 200, 10, 70, stick);

		drawShape(176, 55, 60, 60, sojusznicy);
		drawShape(230, 80, 70, 10, stickH);

		drawShape(20, 55, 60, 60, samotnik);
		drawShape(-10, 80, 70, 10, stickH);

	}
	if (bkoniec)
		drawShape(3, 153, 65, 65, green);
	if (bpomoc)
		drawShape(189, 154, 65, 65, green);
	if (bsojusznicy)
		drawShape(174, 53, 65, 65, green);
	if (bsamotnik)
		drawShape(18, 53, 65, 65, green);

	drawShape(mmnoznik-- % 24790 / 50, 0, 750, 256, mtlo);

	// podpis
																																																																																																																											drawText(-128, -125, "by Artur Ziemba 2016", 0, 0, 0);
																																																																																																																											licznikmenu += 3;

	//while (glutGet(GLUT_ELAPSED_TIME) < SecfromStart + 1) // zapewnia generowanie klatek co ~0.001 sek
		//;

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void OnRender2()
{
	// samotnicy
	SecfromStart = glutGet(GLUT_ELAPSED_TIME);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (pauza) // funckja pauza
	{
		drawShape(0, 0, 256, 256, pauzat);
		goto finish;
	}

	// bang
	if (zycoika>glutGet(GLUT_ELAPSED_TIME))
	{
		drawShape(0, 0, 4, 256, red);
		drawShape(0, 0, 256, 5, red);
		drawShape(252, 0, 4, 256, red);
		drawShape(0, 251, 256, 5, red);
	}


	// Ustawienie kamery na podstawie jej stanu przechowywanego w zmiennej player. - lub BOT EHEHHEE
	///*
	gluLookAt(
		player.pos.x, player.pos.y, player.pos.z, // Pozycja kamery
		player.pos.x + player.dir.x, player.pos.y + player.dir.y, player.pos.z + player.dir.z, // Punkt na ktory patrzy kamera (pozycja + kierunek)
		0.0f, 1.0f, 0.0f // Wektor wyznaczajacy pion
		);
	//*/
	/*
	int czas = 10000;
	gluLookAt(
	heroses[((glutGet(GLUT_ELAPSED_TIME) / czas) % (heroses.size() - 1)) + 1]->pos.x, heroses[((glutGet(GLUT_ELAPSED_TIME) / czas) % (heroses.size() - 1)) + 1]->pos.y+14, heroses[((glutGet(GLUT_ELAPSED_TIME) /czas) % (heroses.size() - 1)) + 1]->pos.z, // Pozycja kamery
	heroses[((glutGet(GLUT_ELAPSED_TIME) / czas) % (heroses.size() - 1)) + 1]->pos.x + heroses[((glutGet(GLUT_ELAPSED_TIME) /czas) % (heroses.size() - 1)) + 1]->dir.x, heroses[((glutGet(GLUT_ELAPSED_TIME) / czas) % (heroses.size() - 1)) + 1]->pos.y+14 + heroses[((glutGet(GLUT_ELAPSED_TIME) / czas) % (heroses.size() - 1)) + 1]->dir.y, heroses[((glutGet(GLUT_ELAPSED_TIME) /czas) % (heroses.size() - 1)) + 1]->pos.z + heroses[((glutGet(GLUT_ELAPSED_TIME) / czas) % (heroses.size() - 1)) + 1]->dir.z, // Punkt na ktory patrzy kamera (pozycja + kierunek)
	0.0f, 1.0f, 0.0f // Wektor wyznaczajacy pion
	);
	*/

	// swiatlo globalne
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
	glPopMatrix();

	// swiatlo gunerow

	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_AMBIENT, l1_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1_dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l1_spe);
	glLightfv(GL_LIGHT1, GL_POSITION, l1_pos);
	glPopMatrix();

	// tlumienie 
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, jasnosc_wybuchu);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);

	// bgun
	glPushMatrix();
	glLightfv(GL_LIGHT3, GL_AMBIENT, l1_amb);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, l1_dif);
	glLightfv(GL_LIGHT3, GL_SPECULAR, l1_spe);
	glLightfv(GL_LIGHT3, GL_POSITION, l3_pos);
	glPopMatrix();

	// tlumienie 
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, jasnosc_wybuchu);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.0f);

	// swiatlo Minerow

	glPushMatrix();
	glLightfv(GL_LIGHT2, GL_AMBIENT, l2_amb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, l2_dif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, l2_spe);
	glLightfv(GL_LIGHT2, GL_POSITION, l2_pos);
	glPopMatrix();

	// tlumienie 	  
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, jasnosc_wybuchu2);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0f);

	// swiatlo BMinerow

	glPushMatrix();
	glLightfv(GL_LIGHT4, GL_AMBIENT, l2_amb);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, l2_dif);
	glLightfv(GL_LIGHT4, GL_SPECULAR, l2_spe);
	glLightfv(GL_LIGHT4, GL_POSITION, l4_pos);
	glPopMatrix();

	// tlumienie 	  
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, jasnosc_wybuchu2);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.0f);

	// rysowanie postaci
	for (int licznik = 0; licznik < heroses.size(); licznik++)
	{
		glPushMatrix();
		heroses[licznik]->rysuj(player.czyidzie, player.czyatakuje);
		glPopMatrix();
	}
	if (bstart == 1)
	{
		engine->stopAllSounds();
		if (Gracz->klasa=='u')
		{
			PlaySound("sounds/ga.wav", Gracz->pos.x, 0, Gracz->pos.z);
			Gracz->zycie = zyciepostaciGUN;
		}
		if (Gracz->klasa == 'e')
		{
			Gracz->zycie = zyciepostaciMELE;
		}
		if (Gracz->klasa == 'i')
		{
			PlaySound("sounds/ia.wav", Gracz->pos.x, 0, Gracz->pos.z);
			Gracz->zycie = zyciepostaciMINE;
		}
		bstart = 0;
		zycoika = 0;
	}

	rysujziemie();
	rysujniebo();

	rysujDrzewa();



	// rysowanie interfejsu gracza
	// info
	// paski
	drawShape(17, 7, 21 * ((float)Gracz->zycie / (float)Gracz->calezycie), 11, red);
	if (((float)(glutGet(GLUT_ELAPSED_TIME) - Gracz->ostatnioatak) / (float)Gracz->czasoczekiwan) < 1)
		drawShape(17, 25, 21 * ((float)(glutGet(GLUT_ELAPSED_TIME) - Gracz->ostatnioatak) / (float)Gracz->czasoczekiwan), 10, blue);
	else
		drawShape(17, 25, 21, 10, blue);
	drawShape(17, 43, 1 + (20 * ((float)(Gracz->kills - Gracz->preqexp) / (float)(Gracz->reqexp - Gracz->preqexp - 2))), 10, grey);
	// info
	drawShape(2, 2, 38, 56, info);
	drawText(-110., 116, std::to_string(Gracz->zycie), 0, 0, 0);
	drawText(-103., 112, std::to_string(Gracz->calezycie), 0, 0, 0);
	drawText(-108, 95, std::to_string(Gracz->silaataku), 0, 0, 0);
	drawText(-108, 79, std::to_string(Gracz->kills), 0, 0, 0);

	if (Gracz->zycie > 0)
	{
		// lvup
		if (Gracz->levelanimation != 0)
		{
			if (Gracz->levelanimation < 100)
			{
				drawShape(256 - Gracz->levelanimation, 5, 60, 60, lvup);
				drawShape(300 - Gracz->levelanimation, 30, 70, 10, stickH);
			}
			else
			{
				drawShape(156 + ((rand() % 4) - 2), 5 + ((rand() % 4) - 2), 60, 60, lvup);
				drawShape(200 + ((rand() % 4) - 2), 30 + ((rand() % 4) - 2), 70, 10, stickH);
				if (Gracz->levelanimation > 200) // jak dlugo sie giba
					textanim1 = (-1);
			}
			Gracz->levelanimation += textanim1;
		}

		// podpowiedzi o punktach
		if (Gracz->pointstospend > 0 || textanim2 != 0)
		{
			if (textanim2 < 96)
			{
				drawShape(5, 256 - textanim2, 60, 60, how);
				drawShape(30, 300 - textanim2, 10, 70, stick);
				textanim2++;
			}
			else
			{
				drawShape(5, 160, 60, 60, how);
				drawShape(30, 204, 10, 70, stick);
			}

			if (Gracz->pointstospend == 0)
				textanim2 -= 2;
		}
		// wysiwetlanie jak wydac punkty
	}
	else
	{
		camen = 1;
		czyarrow = 0;
		if (textanim3 < 96)
		{
			drawShape(5, 256 - textanim3, 60, 60, dead);
			drawShape(30, 300 - textanim3, 10, 70, stick);
			textanim3++;
		}
		else
		{
			drawShape(5, 160, 60, 60, dead);
			drawShape(30, 204, 10, 70, stick);
		}
	}
	// info jak zaczac
	if (textanim4>=0)
	{
		if (textanim4 < 96)
		{
			drawShape(191, 256 - textanim4, 60, 60, gotowy);
			drawShape(216, 300 - textanim4, 10, 70, stick);
			textanim4++;
		}
		else
		{
			drawShape(191, 160, 60, 60, gotowy);
			drawShape(216, 204, 10, 70, stick);
		}

		if (heroses.size() > 1)
			textanim4 -= 2;
	}

	// koniec rysowanie interfejsu gracza

	if (Gracz->how_long_dead >99)
	{
		pauza = 0;
		czyarrow = 0;
		celownik = 0;
		czylokacje = 0;
		zycoika = 0;
		niebospin = 0;
		camen = 0;
		map.~Mapa();
		for (int licznik = 0; licznik < heroses.size(); licznik++)
		{
			delete heroses[licznik];
		}
		heroses.clear();
		Menu();
	}

	// drukowanie lokacji
	if (czylokacje)
		DrukujStatystyki();

	if (czyarrow)
		rysujArrow();


finish:
	while (glutGet(GLUT_ELAPSED_TIME) < SecfromStart + 16) // zapewnia generowanie klatek co ~0.016 sek
		;
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

}

void OnRender4()
{
	//sojusznicy

	SecfromStart = glutGet(GLUT_ELAPSED_TIME);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (pauza) // funckja pauza
	{
		drawShape(0, 0, 256, 256, pauzat);
		mouse.x = GLUT_SCREEN_WIDTH / 2;
		mouse.y = GLUT_SCREEN_HEIGHT / 2;
		goto finish;
	}

	// bang
	if (zycoika>glutGet(GLUT_ELAPSED_TIME))
	{
		drawShape(0, 0, 4, 256, red);
		drawShape(0, 0, 256, 5, red);
		drawShape(252, 0, 4, 256, red);
		drawShape(0, 251, 256, 5, red);
	}


	// Ustawienie kamery na podstawie jej stanu przechowywanego w zmiennej player. - lub BOT EHEHHEE
	///*
	gluLookAt(
		player.pos.x, player.pos.y, player.pos.z, // Pozycja kamery
		player.pos.x + player.dir.x, player.pos.y + player.dir.y, player.pos.z + player.dir.z, // Punkt na ktory patrzy kamera (pozycja + kierunek)
		0.0f, 1.0f, 0.0f // Wektor wyznaczajacy pion
		);
	//*/
	/*
	int czas = 10000;
	gluLookAt(
	heroses[((glutGet(GLUT_ELAPSED_TIME) / czas) % (heroses.size() - 1)) + 1]->pos.x, heroses[((glutGet(GLUT_ELAPSED_TIME) / czas) % (heroses.size() - 1)) + 1]->pos.y+14, heroses[((glutGet(GLUT_ELAPSED_TIME) /czas) % (heroses.size() - 1)) + 1]->pos.z, // Pozycja kamery
	heroses[((glutGet(GLUT_ELAPSED_TIME) / czas) % (heroses.size() - 1)) + 1]->pos.x + heroses[((glutGet(GLUT_ELAPSED_TIME) /czas) % (heroses.size() - 1)) + 1]->dir.x, heroses[((glutGet(GLUT_ELAPSED_TIME) / czas) % (heroses.size() - 1)) + 1]->pos.y+14 + heroses[((glutGet(GLUT_ELAPSED_TIME) / czas) % (heroses.size() - 1)) + 1]->dir.y, heroses[((glutGet(GLUT_ELAPSED_TIME) /czas) % (heroses.size() - 1)) + 1]->pos.z + heroses[((glutGet(GLUT_ELAPSED_TIME) / czas) % (heroses.size() - 1)) + 1]->dir.z, // Punkt na ktory patrzy kamera (pozycja + kierunek)
	0.0f, 1.0f, 0.0f // Wektor wyznaczajacy pion
	);
	*/

	// swiatlo globalne
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
	glPopMatrix();

	// swiatlo gunerow

	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_AMBIENT, l1_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1_dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l1_spe);
	glLightfv(GL_LIGHT1, GL_POSITION, l1_pos);
	glPopMatrix();

	// tlumienie 
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, jasnosc_wybuchu);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);

	// bgun
	glPushMatrix();
	glLightfv(GL_LIGHT3, GL_AMBIENT, l1_amb);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, l1_dif);
	glLightfv(GL_LIGHT3, GL_SPECULAR, l1_spe);
	glLightfv(GL_LIGHT3, GL_POSITION, l3_pos);
	glPopMatrix();

	// tlumienie 
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, jasnosc_wybuchu);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.0f);

	// swiatlo Minerow

	glPushMatrix();
	glLightfv(GL_LIGHT2, GL_AMBIENT, l2_amb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, l2_dif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, l2_spe);
	glLightfv(GL_LIGHT2, GL_POSITION, l2_pos);
	glPopMatrix();

	// tlumienie 	  
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, jasnosc_wybuchu2);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0f);

	// swiatlo BMinerow

	glPushMatrix();
	glLightfv(GL_LIGHT4, GL_AMBIENT, l2_amb);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, l2_dif);
	glLightfv(GL_LIGHT4, GL_SPECULAR, l2_spe);
	glLightfv(GL_LIGHT4, GL_POSITION, l4_pos);
	glPopMatrix();

	// tlumienie 	  
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, jasnosc_wybuchu2);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.0f);

	// rysowanie postaci
	for (int licznik = 0; licznik < heroses.size(); licznik++)
	{
		glPushMatrix();
		heroses[licznik]->rysuj(player.czyidzie, player.czyatakuje);
		glPopMatrix();
	}
	// blad na relase z zyciem
	if (bstart == 1)
	{
		engine->stopAllSounds();
		if (Gracz->klasa == 'u')
		{
			PlaySound("sounds/ga.wav", Gracz->pos.x, 0, Gracz->pos.z);
			Gracz->zycie = zyciepostaciGUN;
		}
		if (Gracz->klasa == 'e')
		{
			Gracz->zycie = zyciepostaciMELE;
		}
		if (Gracz->klasa == 'i')
		{
			PlaySound("sounds/ia.wav", Gracz->pos.x, 0, Gracz->pos.z);
			Gracz->zycie = zyciepostaciMINE;
		}
		bstart = 0;
		zycoika = 0;
	}

	rysujziemie();
	rysujniebo();

	rysujDrzewa();



	// rysowanie interfejsu gracza
	// info
	// paski
	drawShape(17, 7, 21 * ((float)Gracz->zycie / (float)Gracz->calezycie), 11, red);
	if (((float)(glutGet(GLUT_ELAPSED_TIME) - Gracz->ostatnioatak) / (float)Gracz->czasoczekiwan) < 1)
		drawShape(17, 25, 21 * ((float)(glutGet(GLUT_ELAPSED_TIME) - Gracz->ostatnioatak) / (float)Gracz->czasoczekiwan), 10, blue);
	else
		drawShape(17, 25, 21, 10, blue);

	drawShape(17, 43, 1 + (20 * ((float)(Gracz->kills - Gracz->preqexp) / (float)(Gracz->reqexp - Gracz->preqexp - 2))), 10, grey);

	// info
	drawShape(2, 2, 38, 56, info);
	drawText(-110., 116, std::to_string(Gracz->zycie), 0, 0, 0);
	drawText(-103., 112, std::to_string(Gracz->calezycie), 0, 0, 0);
	drawText(-108, 95, std::to_string(Gracz->silaataku), 0, 0, 0);
	drawText(-108, 79, std::to_string(Gracz->kills), 0, 0, 0);


	if (Gracz->zycie > 0)
	{
		// lvup
		if (Gracz->levelanimation != 0)
		{
			if (Gracz->levelanimation < 100)
			{
				drawShape(256 - Gracz->levelanimation, 5, 60, 60, lvup);
				drawShape(300 - Gracz->levelanimation, 30, 70, 10, stickH);
			}
			else
			{
				drawShape(156 + ((rand() % 4) - 2), 5 + ((rand() % 4) - 2), 60, 60, lvup);
				drawShape(200 + ((rand() % 4) - 2), 30 + ((rand() % 4) - 2), 70, 10, stickH);
				if (Gracz->levelanimation > 200) // jak dlugo sie giba
					textanim1 = (-1);
			}
			Gracz->levelanimation += textanim1;
		}

		// podpowiedzi o punktach
		if (Gracz->pointstospend > 0 || textanim2 != 0)
		{
			if (textanim2 < 96)
			{
				drawShape(5, 256 - textanim2, 60, 60, how);
				drawShape(30, 300 - textanim2, 10, 70, stick);
				textanim2++;
			}
			else
			{
				drawShape(5, 160, 60, 60, how);
				drawShape(30, 204, 10, 70, stick);
			}

			if (Gracz->pointstospend == 0)
				textanim2 -= 2;
		}
		// wysiwetlanie jak wydac punkty
	}
	else
	{
		camen = 1;
		czyarrow = 0;
		if (textanim3 < 96)
		{
			drawShape(5, 256 - textanim3, 60, 60, dead);
			drawShape(30, 300 - textanim3, 10, 70, stick);
			textanim3++;
		}
		else
		{
			drawShape(5, 160, 60, 60, dead);
			drawShape(30, 204, 10, 70, stick);
		}
	}
	// info jak zaczac
	if (textanim4 >= 0)
	{
		if (textanim4 < 96)
		{
			drawShape(191, 256 - textanim4, 60, 60, gotowy);
			drawShape(216, 300 - textanim4, 10, 70, stick);
			textanim4++;
		}
		else
		{
			drawShape(191, 160, 60, 60, gotowy);
			drawShape(216, 204, 10, 70, stick);
		}

		if (heroses.size() > 1)
			textanim4 -= 2;
	}
	// koniec rysowanie interfejsu gracza

	if (Gracz->how_long_dead >99)
	{
		pauza = 0;
		czyarrow = 0;
		celownik = 0;
		czylokacje = 0;
		zycoika = 0;
		niebospin = 0;
		camen = 0;
		map.~Mapa();
		for (int licznik = 0; licznik < heroses.size(); licznik++)
		{
			delete heroses[licznik];
		}
		heroses.clear();
		Menu();
	}

	// drukowanie lokacji
	if (czylokacje)
		DrukujStatystyki();

	if (czyarrow)
		rysujArrow2();

finish:
	while (glutGet(GLUT_ELAPSED_TIME) < SecfromStart + 16) // zapewnia generowanie klatek co ~0.016 sek
		;
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
