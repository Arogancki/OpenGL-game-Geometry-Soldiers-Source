#pragma once
#include "stdafx.h"

//silnik dzwieku
ISoundEngine* engine;

class hero;

// zmienne globalne

// zmienne szybkosci postaci
float mmes = 0.52;
float ggus = 0.46;
float mmis = 0.45;
float przewagagracza = 0.025;

// ZMIENE ZYCIA
int zyciepostaciMELE = 4000; 
int zyciepostaciMINE = 2000;
int zyciepostaciGUN = 3000;

int zasiegminy = 5; // zasiegi mini minerow

int mmnoznik = 1; // efekty w menu
// opcje w menu
bool bfullscreen = 0;
bool bkoniec = 0;
bool bsojusznicy = 0;
bool bsamotnik = 0;
bool bpomoc = 0;
int spomoc = 0;
bool ssojusznicy = 0;
bool ssamotnik = 0;
int wybrano = 0;
int postac = 0;
int licznikmenu = 0;// efekty w menu

int textanim1 = 1;// animacje znakow podczas gry
int textanim2 = 0;// animacje znakow podczas gry
int textanim3 = 0;// animacje znakow podczas gry
int textanim4 = 0;// animacje znakow podczas gry



hero *Gracz; // zmienna postaci gracza
bool keystate[256]; // zmienne okreslajace wcisnietosc klawiszy

int pauza = 0;// zmienna pauza
int czyarrow = 0; // on/off strzalka pomocy
int celownik; // on/off celownik dla gunera
int czylokacje = 0; // drukowanie startystyk graczy
int zycoika = 0; // efekt otrzymywania ciosu
float niebospin = 0;// obrot nieba
bool camen = 0; // pouszanie kamera podczas smierci
bool samotnicy; // tryb gry
float SecfromStart;// sekundy od poczatku gry
float maxwidth = 1000; // zmienne okreslajace rozmiar okna
float maxheight = 1000;// zmienne okreslajace rozmiar okna
bool bstart = 0;

int killgun = 0; // globalne kille podczas trybow druzynowych
int killmele = 0;// globalne kille podczas trybow druzynowych
int killmine = 0;// globalne kille podczas trybow druzynowych

// swiatlo 0 - globalne (sloneczko)
float l0_amb[] = { .6f, .6f, .6f, 1.0f };
float l0_dif[] = { .7f, .7f, .7f, 1.0f };
float l0_spe[] = { .95f, .95f, .95f, .950f };
float l0_pos[] = { .0f, 400.0f, .0f, 0.0f };

// swiatlo 1 - gunerow
float l1_pos[4] = { 99999, 99999,99999,1 }; //ustawiany przy strzelaniu
float l3_pos[4] = { 99999, 99999,99999,1 }; ; //ustawiany przy strzelaniu
float jasnosc_wybuchu = 0.3;
float l1_amb[] = { .9f, .9f, .9f, 1.0f };
float l1_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float l1_spe[] = { .905f, .905f,.905f, 1.0f };

// swiatlo 2 - Minerow 
float l2_pos[4] = { 99999, 99999,99999,1 }; ; // ustawiany przy wybuchach
float l4_pos[4] = { 99999, 99999,99999,1 }; ; // ustawiany przy wybuchach
float jasnosc_wybuchu2 = 0.2;
float l2_amb[] = { .9f, .9f, .9f, 1.0f };
float l2_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float l2_spe[] = { .905f, .905f,.905f, 1.0f };

// Struktury Globalne

// wektor 3d
struct vector3d
{
	float x, y, z;
};

//  kamery
struct SCameraState 
{
	vector3d pos; // pozycja kamery
	vector3d dir; // kierunek patrzenia (wektor jednostkowy)
	float speed; // mno¿nik zmian pozycji - "szybkoœæ" ruchów kamery
	int czyidzie = 0;
	int czyatakuje = 0;
};

// struktura pozycji myszki
struct Mouse
{
	int x;
	int y;
};

vector <hero*> heroses; // wektor postaci (graczy)
// Struktury globalne
SCameraState player; // struktura gracza (kamery)
Mouse mouse; // polozenie myszki

// obiekty globalne
GLuint drzewo1;
GLuint drzewo2;
GLuint ziemiaO;
GLuint arrow;
GLuint nieboO;
CTexture* ziemiaT;
CTexture* nieboT;
CTexture *info;
CTexture *lvup;
CTexture *how;
CTexture *stick;
CTexture *stickH;
CTexture *dead;
CTexture *red;
CTexture *blue;
CTexture *grey;
CTexture *pauzat;
CTexture *mtitle;
CTexture *mtlo;
CTexture *koniec;
CTexture *pomoc;
CTexture *samotnik;
CTexture *sojusznicy;
CTexture *stronapomocy;
CTexture *wybierz;
CTexture *green;
CTexture *bar;
CTexture *guns;
CTexture *miner;
CTexture *loadning;
CTexture *gotowy;

// klasa stworzen - postaci - podstawa
class hero
{
public:
	char klasa;
	vector3d pos; // pozycja bohatera
	vector3d dir; // kierunek patrzenia (wektor jednostkowy)
	int how_long_dead;
	int liczniklv;
	int ostatnioatak;
	int czasoczekiwan;
	int silaataku; // moc atAKU
	int levelanimation;
	int calezycie;
	int reqexp;
	int preqexp;;
	int pointstospend;
	
	int virtual podajatak() = 0;
	void virtual heal() = 0;
	void virtual incraselife() = 0;
	void virtual incraseatak() = 0;
	void virtual odejmijzycie(int) = 0;
	void virtual rysuj(int, int) = 0;
	void virtual dodajkill() = 0;
	int zycie; // REPREZETOWANY TEZ JAKO OBRAONA
	float speed; // szybkosc poruszania
	int kills; // ilosc zabitych - drukowana tylko dla playera
	int mine_wybuch_stala[5];
	vector3d mine[5];
};

// klasa mapy
class Mapa
{
public:
	std::vector< std::vector<int> > mapatyp;

	std::vector< std::vector< vector3d > > drzewa;
	// 0- pusty,  2 - drzewo, 3 - granica drzewa 5-drzewo

	// wskaznik na czlowieka ktory zaminowal teren
	hero *bomby[2001][2001];
	int LICZNIKMIN[2001][2001];

	// wskazniki na kolesia na punkcie, ustawiane kiedy wejdzie on na pole
	hero *postac[2001][2001];

	// METODY
	Mapa(); // ustawienie mapy oraz losowe ustawienie drzew i krzakow
	~Mapa();
	// stare int x int z, nowe int x int z, oraz int postaci - 1(gun) - 2 (mine) - 3 (mele)
	int HeroCatch(int, int, int, int, hero*);	// sprawdza czy jest bomba oraz zapisuje gracza na nowej plytce podlogi

	int AmmoCatch(int, int, int, hero*); // tylko zwraca czy jest kolizja z drzewem lub odejmuje zycie playerowi
										 // 0 brak kolicji - nabuj leci dalej, 1 drzewo czyli konczymy lot, 2 - player bijemy jak inny od this

	void uwolni(int, int);
	// losuje pozycje startowa dla bota
	vector3d BotStart();
	int CanBotStart(int, int);
	void iniciuj();
	void Wst_bombe(float, float, hero*); // wstawia wskaznik na bombe]
	void usun_bombe(float, float);
	// zapisuije mape do pliku // usunac jak bedzie ok
	void getmap();

	// SOJUSZNICY
	int HeroCatch2(int, int, int, int, hero*);	// sprawdza czy jest bomba oraz zapisuje gracza na nowej plytce podlogi

	int AmmoCatch2(int, int, int, hero*); // tylko zwraca czy jest kolizja z drzewem lub odejmuje zycie playerowi
										  // 0 brak kolicji - nabuj leci dalej, 1 drzewo czyli konczymy lot, 2 - player bijemy jak inny od this

};

void Mapa::iniciuj()
{

	int zalesienie = 1600 + (rand() % 1500); // POLECAM OD 1500 do 3000!!
	cout << "tworzenie mapy\n";

	vector3d temp3;
	temp3.x = 0;
	temp3.y = 0;
	temp3.z = 0;
	for (int i = 0; i < 2001; i++)
	{
		std::vector<int>  temp;
		std::vector<vector3d>  temp2;
		for (int j = 0; j < 2001; j++)
		{
			temp.push_back(0); // tworze mape bez niczego
			temp2.push_back(temp3);
			bomby[i][j] = NULL;
			postac[i][j] = NULL;
		}
		mapatyp.push_back(temp);
		drzewa.push_back(temp2);
	}

	for (int q = 0; q < zalesienie; q++) {

		int i, j;
		do
		{
			i = 0;
			j = 0;
			i = (rand() % 1991) + 6;
			j = (rand() % 1991) + 6;

		} while ((mapatyp[i][j] == 2) || (mapatyp[i + 3][j + 3] == 2) || (mapatyp[i][j + 3] == 2) || (mapatyp[i + 3][j] == 2) ||
			(mapatyp[i][j] == 3) || (mapatyp[i + 3][j + 3] == 3) || (mapatyp[i][j + 3] == 3) || (mapatyp[i + 3][j] == 3));


		for (int ii = i - 15; ii < i + 19; ii++)
			for (int jj = j - 15; jj < j + 19; jj++)
			{
				int x = (ii + 2001) % 2001;
				int y = (jj + 2001) % 2001;
				mapatyp[x][y] = 3;
			}
		if (rand() % 2)
		{
			int spin = rand() % 360;
			for (int ii = i; ii <= i + 3; ii++)
				for (int jj = j; jj <= j + 3; jj++)
				{
					mapatyp[ii][jj] = 2;
					drzewa[ii][jj].y = spin;
					drzewa[ii][jj].x = i + 2;
					drzewa[ii][jj].z = j + 2;
				}
		}
		else
		{
			int spin = rand() % 360;
			for (int ii = i; ii <= i + 3; ii++)
				for (int jj = j; jj <= j + 3; jj++)
				{
					mapatyp[ii][jj] = 5;
					drzewa[ii][jj].y = spin;
					drzewa[ii][jj].x = i + 2;
					drzewa[ii][jj].z = j + 2;
				}
		}

		//if (rand() % 2)
		//{
		//	drzewo2x.push_back(i);
		//	drzewo2z.push_back(j);
		//	drzewo2spin.push_back(rand()%360);
		//}
		//else
		//{
		//	drzewo1x.push_back(i);
		//	drzewo1z.push_back(j);
		//	drzewo1spin.push_back(rand() % 360);
		//}
	}

	for (int i = 0; i < mapatyp.size(); i++)
		for (int j = 0; j < mapatyp[i].size(); j++)
			if (mapatyp[i][j] == 3)
				mapatyp[i][j] = 0;
	cout << "stworzono mape\n";
}

void Mapa::usun_bombe(float x, float z)
{
	for (int ii = (int)x - zasiegminy-1; ii < (int)x + zasiegminy + 2; ii++)
		for (int jj = (int)z - zasiegminy-1; jj <(int)z + zasiegminy + 2; jj++)
		{
			int xx = (ii + 2001) % 2001;
			int zz = (jj + 2001) % 2001;
			bomby[(xx + 2001) % 2001][(zz + 2001) % 2001] = NULL;
		}
}

void Mapa::Wst_bombe(float x, float z, hero* ch)
{
	for (int ii = (int)x - zasiegminy; ii < (int)x + 1 + zasiegminy; ii++)
		for (int jj = (int)z - zasiegminy; jj <(int)z + zasiegminy + 1; jj++)
		{
			int xx = (ii + 2001) % 2001;
			int zz = (jj + 2001) % 2001;
			bomby[xx][zz] = ch;



			if (samotnicy==1) // gramy w samotnikow nie sprawdzamy czy partner
			{
				if (postac[xx][zz] != NULL && postac[xx][zz] != ch) // cos jest na bombie
				{
					postac[xx][zz]->odejmijzycie(bomby[xx][zz]->silaataku);
					if (postac[xx][zz]->zycie <= 0)
						bomby[xx][zz]->dodajkill();
					for (int i = 0; i < 5; i++)
					{
						if (bomby[xx][zz] != NULL)
							bomby[xx][zz]->mine_wybuch_stala[i] = 1;
					}
					for (int i = 0; i < 5; i++)
					{
						if (bomby[xx][zz] != NULL)
							usun_bombe(
								bomby[xx][zz]->mine[i].x,
								bomby[xx][zz]->mine[i].z);
					}
					return;
				}
			}
			else
			{
				if (postac[xx][zz] != NULL && bomby[xx][zz]->klasa != postac[xx][zz]->klasa) // wlazles na bombe
				{
					postac[xx][zz]->odejmijzycie(bomby[xx][zz]->silaataku);
					if (postac[xx][zz]->zycie <= 0)
					{
						if (bomby[xx][zz] != NULL)
							bomby[xx][zz]->dodajkill();
					}
					for (int i = 0; i < 5; i++)
					{
						if (bomby[xx][zz] != NULL) // wlazles na bombe
							bomby[xx][zz]->mine_wybuch_stala[i] = 1;
					}
					for (int i = 0; i < 5; i++)
					{
						if (bomby[xx][zz] != NULL) // wlazles na bombe
							usun_bombe(
								bomby[xx][zz]->mine[i].x,
								bomby[xx][zz]->mine[i].z);
					}
					return;
				}
			}




		}
}

Mapa::Mapa()
{
	
}

Mapa::~Mapa()
{
	for (int i = 0; i<mapatyp.size(); i++)
		mapatyp[i].clear();
	mapatyp.clear();
	for (int i = 0; i<mapatyp.size(); i++)
		drzewa[i].clear();
	drzewa.clear();
}

vector3d Mapa::BotStart()
{

	int i, j, czy;
	do {
		czy = 0;

		i = ((rand() + 5) % 2001);
		j = ((rand() + 5) % 2001);

		for (int ii = i - 4; ii < i + 5; ii++)
			for (int jj = j - 4; jj < j + 5; jj++)
				if (mapatyp[(ii + 2001) % 2001][(jj + 2001) % 2001] == 2 || mapatyp[(ii + 2001) % 2001][(jj + 2001) % 2001] == 5 || postac[(ii + 2001) % 2001][(jj + 2001) % 2001] != NULL)
				{
					czy = 1;
					ii = i + 5;
					jj = j + 5;
				}
	} while (czy);
	vector3d retu;
	retu.x = i;
	retu.y = 05;
	retu.z = j;
	return(retu);
}

int Mapa::CanBotStart(int i, int j)
{

	int czy;
		czy = 0;

		for (int ii = i - 4; ii < i + 5; ii++)
			for (int jj = j - 4; jj < j + 5; jj++)
				if (mapatyp[(ii + 2001) % 2001][(jj + 2001) % 2001] == 2 || mapatyp[(ii + 2001) % 2001][(jj + 2001) % 2001] == 5 || postac[(ii + 2001) % 2001][(jj + 2001) % 2001] != NULL)
				{
					czy = 1;
					ii = i + 5;
					jj = j + 5;
				}
	return(czy);
}

void Mapa::getmap()
{
	std::ofstream outputFile("mapa.txt");
	if (!outputFile.is_open())
		return;
	for (int i = 0; i < mapatyp.size(); i++)
	{
		for (int j = 0; j < mapatyp[i].size(); j++)
		{
			if (mapatyp[i][j] == 0)
				outputFile << " ";
			if (mapatyp[i][j] == 2)
				outputFile << "#";
			if (mapatyp[i][j] == 3)
				outputFile << ".";
		}
		outputFile << std::endl;
	}
	std::cout << "affffffffhuuuuuuu";
	getchar();
}

int Mapa::HeroCatch(int starex, int starez, int nowex, int nowez, hero* aktualny)
{
	if (postac[(nowex + 2001) % 2001][(nowez + 2001) % 2001] != NULL)
		if (mapatyp[(nowex + 2001) % 2001][(nowez + 2001) % 2001] == 5 || mapatyp[(nowex + 2001) % 2001][(nowez + 2001) % 2001] == 2 || postac[(nowex + 2001) % 2001][(nowez + 2001) % 2001] != aktualny)
			return(1);

	for (int i = -4; i < 5; i++)
		for (int j = -4; j < 5; j++)
			postac[(starex + i + 2001) % 2001][(starez + j + 2001) % 2001] = NULL;

	for (int i = -4; i < 5; i++)
		for (int j = -4; j < 5; j++)
			postac[(nowex + i + 2001) % 2001][(nowez + j + 2001) % 2001] = aktualny;

	if (bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001] != NULL && bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001] != aktualny) // wlazles na bombe
	{
		aktualny->odejmijzycie(bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001]->silaataku);
		if (aktualny->zycie <= 0)
			bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001]->dodajkill();
		for (int i = 0; i < 5; i++)
		{
			if (bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001] != NULL) // wlazles na bombe
				bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001]->mine_wybuch_stala[i] = 1;
		}
		for (int i = 0; i < 5; i++)
		{
			if (bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001] != NULL) // wlazles na bombe
				usun_bombe(
					bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001]->mine[i].x,
					bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001]->mine[i].z);
		}
	}

	return(0);
}

int Mapa::AmmoCatch(int xx, int yy, int zz, hero* aktualny)
{
	xx = (xx + 2001) % 2001;
	zz = (zz + 2001) % 2001;
	if ((mapatyp[xx][zz] == 5 || mapatyp[xx][zz] == 2) && yy <= 11) // jest kolizja
		return(1); // kolizja

	if (postac[xx][zz] != aktualny && postac[xx][zz] != NULL && (yy >= 0 && yy <= 10))
	{
		postac[xx][zz]->odejmijzycie(aktualny->silaataku);
		if (postac[xx][zz]->zycie <= 0)
			aktualny->dodajkill();
		return(1); // kolizja
	}

	//if (bomby[xx][zz] != NULL && yy == 0) // wysadzenie bomby
	//{
	//	for (int i = 0; i < 5; i++)
	//	{
	//		if (bomby[xx][zz] != NULL) // wysadzenie bomby
	//		{
	//			bomby[xx][zz]->mine_wybuch_stala[i] = 1;
	//			usun_bombe(
	//				bomby[xx][zz]->mine[i].x,
	//				bomby[xx][zz]->mine[i].z);
	//		}
	//	}
	//}

	return(0); // kolizja brak
}

void Mapa::uwolni(int starex, int starez)
{
	for (int i = -4; i < 5; i++)
		for (int j = -4; j < 5; j++)
			postac[(starex + i + 2001) % 2001][(starez + j + 2001) % 2001] = NULL;
}

int Mapa::HeroCatch2(int starex, int starez, int nowex, int nowez, hero* aktualny)
{
	if (postac[(nowex + 2001) % 2001][(nowez + 2001) % 2001] != NULL)
		if (mapatyp[(nowex + 2001) % 2001][(nowez + 2001) % 2001] == 5 ||mapatyp[(nowex + 2001) % 2001][(nowez + 2001) % 2001] == 2 ||postac[(nowex + 2001) % 2001][(nowez + 2001) % 2001] != aktualny)
			return(1);

	for (int i = -4; i < 5; i++)
		for (int j = -4; j < 5; j++)
			postac[(starex + i + 2001) % 2001][(starez + j + 2001) % 2001] = NULL;

	for (int i = -4; i < 5; i++)
		for (int j = -4; j < 5; j++)
			postac[(nowex + i + 2001) % 2001][(nowez + j + 2001) % 2001] = aktualny;

	if (bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001] != NULL && bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001]->klasa != aktualny->klasa) // wlazles na bombe
	{
		aktualny->odejmijzycie(bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001]->silaataku);
		if (aktualny->zycie <= 0)
		{
			if (bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001 ]!=NULL)
				bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001]->dodajkill();
		}
		for (int i = 0; i < 5; i++)
		{
			if (bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001] != NULL) // wlazles na bombe
				bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001]->mine_wybuch_stala[i] = 1;
		}
		for (int i = 0; i < 5; i++)
		{
			if (bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001] != NULL) // wlazles na bombe
				usun_bombe(
					bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001]->mine[i].x,
					bomby[(nowex + 2001) % 2001][(nowez + 2001) % 2001]->mine[i].z);
		}
	}

	return(0);
}

int Mapa::AmmoCatch2(int xx, int yy, int zz, hero* aktualny)
{
	xx = (xx + 2001) % 2001;
	zz = (zz + 2001) % 2001;
	if ((mapatyp[xx][zz] == 5 || mapatyp[xx][zz] == 2) && yy <= 11) // jest kolizja
		return(1); // kolizja

	if (postac[xx][zz] != aktualny && postac[xx][zz] != NULL && (yy >= 0 && yy <= 10))
	{
		if (postac[xx][zz]->klasa != aktualny->klasa)
		{
			if (postac[xx][zz] != NULL)
			{
				postac[xx][zz]->odejmijzycie(aktualny->silaataku);
				if (postac[xx][zz]->zycie <= 0)
					aktualny->dodajkill();
			}
		}
		return(1); // kolizja
	}

	//if (bomby[xx][zz] != NULL && yy == 0) // wysadzenie bomby
	//{
	//	for (int i = 0; i < 5; i++)
	//	{
	//		if (bomby[xx][zz] != NULL) // wysadzenie bomby
	//		{
	//			bomby[xx][zz]->mine_wybuch_stala[i] = 1;
	//			usun_bombe(
	//				bomby[xx][zz]->mine[i].x,
	//				bomby[xx][zz]->mine[i].z);
	//		}
	//	}
	//}

	return(0); // kolizja brak
}

Mapa map; // globalna zmienna reprezetujaca mape