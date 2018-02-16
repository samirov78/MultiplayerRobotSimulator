#include "son.h"

bool Son::actif = true; 
bool Son::possible = true;
char * Son::sonCourant;

FMOD_RESULT Son::resultat;
FMOD_SYSTEM * Son::fmodsystem;
FMOD_SOUND * Son::son1;
FMOD_SOUND * Son::son2;
FMOD_SOUND * Son::son3;
FMOD_SOUND * Son::son4;
FMOD_SOUND * Son::son5;
FMOD_SOUND * Son::son6;
FMOD_SOUND * Son::son7;
FMOD_SOUND * Son::son8;
FMOD_SOUND * Son::son9;
FMOD_CHANNEL * Son::channel;
FMOD_CHANNEL * Son::channel2;
FMOD_CHANNEL * Son::channel3;
FMOD_CHANNEL * Son::channel4;
FMOD_CHANNEL * Son::channel5;
FMOD_CHANNEL * Son::channel6;
FMOD_CHANNEL * Son::channel7;
FMOD_CHANNEL * Son::channel8;
FMOD_CHANNEL * Son::channel9;
FMOD_BOOL Son::p2;
FMOD_BOOL Son::p3;
FMOD_BOOL Son::p4;
FMOD_BOOL Son::p7;


////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::initialiser(void)
///
/// Fonction pour initialiser le son
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::initialiser(void) {
	//create the sound system. If fails, sound is set to impossible
	resultat = FMOD_System_Create(&fmodsystem);
	if (resultat != FMOD_OK) possible = false;
	//if initialise the sound system. If fails, sound is set to impossible
	if (possible) resultat = FMOD_System_Init(fmodsystem, 8, FMOD_INIT_NORMAL, 0);
	if (resultat != FMOD_OK) possible = false;
	//sets initial sound volume (mute)
	if (possible) FMOD_Channel_SetVolume(channel, 0.0f);
	FMOD_Channel_SetLoopCount(channel, 1);
	//FMOD_Channel_SetLoopCount(channel8, 1);
	//FMOD_Channel_SetLoopCount(channel9, 1);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::definirVolume(float v)
///
/// Permet de regler le volume du son courant
///
/// @param[in]  v : volume.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::definirVolume(float v) {
	if (possible && actif && v >= 0.0f && v <= 1.0f) {
		FMOD_Channel_SetVolume(channel, v);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::charger(const char * filename)
///
/// Permet de charger un son
///
/// @param[in]  filename : nom
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::charger(const char * filename) {
	sonCourant = (char *)filename;
	if (possible && actif) {
		resultat = FMOD_Sound_Release(son1);
		resultat = FMOD_System_CreateSound(fmodsystem, sonCourant, FMOD_SOFTWARE, 0, &son1);
		if (resultat != FMOD_OK) possible = false;
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::charger2(const char * filename)
///
/// Permet de charger un son
///
/// @param[in]  filename : nom
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::charger2(const char * filename) {
	sonCourant = (char *)filename;
	if (possible && actif) {
		resultat = FMOD_Sound_Release(son2);
		resultat = FMOD_System_CreateSound(fmodsystem, sonCourant, FMOD_SOFTWARE, 0, &son2);
		if (resultat != FMOD_OK) possible = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::charger3(const char * filename)
///
/// Permet de charger un son
///
/// @param[in]  filename : nom
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::charger3(const char * filename) {
	sonCourant = (char *)filename;
	if (possible && actif) {
		resultat = FMOD_Sound_Release(son3);
		resultat = FMOD_System_CreateSound(fmodsystem, sonCourant, FMOD_SOFTWARE, 0, &son3);
		if (resultat != FMOD_OK) possible = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::charger4(const char * filename)
///
/// Permet de charger un son
///
/// @param[in]  filename : nom
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::charger4(const char * filename) {
	sonCourant = (char *)filename;
	if (possible && actif) {
		resultat = FMOD_Sound_Release(son4);
		resultat = FMOD_System_CreateSound(fmodsystem, sonCourant, FMOD_SOFTWARE, 0, &son4);
		if (resultat != FMOD_OK) possible = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::charger5(const char * filename)
///
/// Permet de charger un son
///
/// @param[in]  filename : nom
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::charger5(const char * filename) {
	sonCourant = (char *)filename;
	if (possible && actif) {
		resultat = FMOD_Sound_Release(son5);
		resultat = FMOD_System_CreateSound(fmodsystem, sonCourant, FMOD_SOFTWARE, 0, &son5);
		if (resultat != FMOD_OK) possible = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::charge6r(const char * filename)
///
/// Permet de charger un son
///
/// @param[in]  filename : nom
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::charger6(const char * filename) {
	sonCourant = (char *)filename;
	if (possible && actif) {
		resultat = FMOD_Sound_Release(son6);
		resultat = FMOD_System_CreateSound(fmodsystem, sonCourant, FMOD_SOFTWARE , 0, &son6);
		if (resultat != FMOD_OK) possible = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::charger7(const char * filename)
///
/// Permet de charger un son
///
/// @param[in]  filename : nom
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::charger7(const char * filename) {
	sonCourant = (char *)filename;
	if (possible && actif) {
		resultat = FMOD_Sound_Release(son7);
		resultat = FMOD_System_CreateSound(fmodsystem, sonCourant, FMOD_SOFTWARE, 0, &son7);
		if (resultat != FMOD_OK) possible = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::charger8(const char * filename)
///
/// Permet de charger un son
///
/// @param[in]  filename : nom
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::charger8(const char * filename) {
	sonCourant = (char *)filename;
	if (possible && actif) {
		resultat = FMOD_Sound_Release(son8);
		resultat = FMOD_System_CreateSound(fmodsystem, sonCourant, FMOD_SOFTWARE, 0, &son8);
		if (resultat != FMOD_OK) possible = false;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::charger9(const char * filename)
///
/// Permet de charger un son
///
/// @param[in]  filename : nom
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::charger9(const char * filename) {
	sonCourant = (char *)filename;
	if (possible && actif) {
		resultat = FMOD_Sound_Release(son9);
		resultat = FMOD_System_CreateSound(fmodsystem, sonCourant, FMOD_SOFTWARE, 0, &son9);
		if (resultat != FMOD_OK) possible = false;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::liberer(void)
///
/// Liberer les objets de type son
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::liberer(void) {

	// Pause sur l'ensemble des channel
	FMOD_Channel_SetPaused(channel, true);
	FMOD_Channel_SetPaused(channel2, true);
	FMOD_Channel_SetPaused(channel3, true);
	FMOD_Channel_SetPaused(channel4, true);
	FMOD_Channel_SetPaused(channel5, true);
	FMOD_Channel_SetPaused(channel6, true);
	FMOD_Channel_SetPaused(channel7, true);
	FMOD_Channel_SetPaused(channel8, true);
	FMOD_Channel_SetPaused(channel9, true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::jouer(bool pause)
///
/// Jouer un son
///
/// @param[in]  pause : arret temporaire
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::jouer(bool pause) {
	if (possible && actif) {
		resultat = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_REUSE, son1, pause, &channel);//channel
		FMOD_Channel_SetMode(channel, FMOD_LOOP_OFF);
		FMOD_Channel_SetVolume(channel, 0.3f);
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::jouer2(bool pause)
///
/// Jouer un son
///
/// @param[in]  pause : arret temporaire
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::jouer2(bool pause) {
	if (possible && actif) {
		resultat = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_REUSE, son2, pause, &channel8);//channel
		FMOD_Channel_SetMode(channel8, FMOD_LOOP_OFF);
		FMOD_Channel_SetVolume(channel8, 0.5f);
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::jouer3(bool pause)
///
/// Jouer un son
///
/// @param[in]  pause : arret temporaire
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::jouer3(bool pause) {
	if (possible && actif) {
		resultat = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_REUSE, son3, pause, &channel9); //channel
		FMOD_Channel_SetMode(channel9, FMOD_LOOP_OFF);
		FMOD_Channel_SetVolume(channel9, 0.5f);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::jouer4(bool pause)
///
/// Jouer un son
///
/// @param[in]  pause : arret temporaire
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::jouer4(bool pause) {
	if (possible && actif) {
		resultat = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_REUSE, son4, pause, &channel2);//avancer/reculer
		FMOD_Channel_SetMode(channel2, FMOD_LOOP_NORMAL);
		FMOD_Channel_SetVolume(channel2, 0.10f);
		//FMOD_Sound_SetLoopCount(son4, -1);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::jouer5(bool pause)
///
/// Jouer un son
///
/// @param[in]  pause : arret temporaire
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::jouer5(bool pause) {
	if (possible && actif) {
		resultat = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_REUSE, son5, pause, &channel3);//rotation
		FMOD_Channel_SetMode(channel3, FMOD_LOOP_NORMAL);
		FMOD_Channel_SetVolume(channel3, 0.10f);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::jouer6(bool pause)
///
/// Jouer un son
///
/// @param[in]  pause : arret temporaire
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::jouer6(bool pause) {
	if (possible && actif) {
		resultat = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_FREE, son6, pause, &channel7); //simulation
		FMOD_Channel_SetMode(channel7, FMOD_LOOP_NORMAL);
		FMOD_Channel_SetVolume(channel7, 1.0f);
		//FMOD_Sound_SetLoopCount(son6, -1);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::jouer7(bool pause)
///
/// Jouer un son
///
/// @param[in]  pause : arret temporaire
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::jouer7(bool pause) {
	if (possible && actif) {
		resultat = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_REUSE, son7, pause, &channel4);//deviation
		FMOD_Channel_SetMode(channel4, FMOD_LOOP_NORMAL);
		FMOD_Channel_SetVolume(channel4, 0.10f);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::jouer8(bool pause)
///
/// Jouer un son
///
/// @param[in]  pause : arret temporaire
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::jouer8(bool pause) {
	if (possible && actif) {
		resultat = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_REUSE, son8, pause, &channel5); //mode manuel
		FMOD_Channel_SetMode(channel5, FMOD_LOOP_OFF);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::jouer9(bool pause)
///
/// Jouer un son
///
/// @param[in]  pause : arret temporaire
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::jouer9(bool pause) {
	if (possible && actif) {
		resultat = FMOD_System_PlaySound(fmodsystem, FMOD_CHANNEL_REUSE, son9, pause, &channel6); //mode auto
		FMOD_Channel_SetMode(channel6, FMOD_LOOP_OFF);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::inverserSon(void)
///
/// activer ou desactiver le son
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::inverserSon(void) {
	actif = !actif;
	if (actif == true) { charger(sonCourant); jouer(); }
	if (actif == false) { liberer(); }
}

//pause or unpause the sound
////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::setPause(int i, bool pause)
///
/// pause et reprise son
///
/// @param[in]  i : canal
/// @param[in]  pause : pause ou reprise
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::setPause(int i, bool pause) {
	if (i == 2)
		FMOD_Channel_SetPaused(channel2, pause);
	if (i == 3)
		FMOD_Channel_SetPaused(channel3, pause);
	if (i == 4)
		FMOD_Channel_SetPaused(channel4, pause);
	if (i == 7)
		FMOD_Channel_SetPaused(channel7, pause);

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::setSon(bool s)
///
/// allumer ou eteindre son
///
/// @param[in]  s : start ou off
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::setSon(bool s) {
	actif = s;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::inverserPause(void)
///
/// activer ou desactiver pause
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::inverserPause(void) {
	FMOD_BOOL p;
	FMOD_Channel_GetPaused(channel, &p);
	FMOD_Channel_SetPaused(channel, !p);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool Son::obtenirSon(void)
///
/// obtenir etat son
///
///
/// @return l'etat du son.
///
////////////////////////////////////////////////////////////////////////
bool Son::obtenirSon(void) {
	return actif;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::initSimulation()
///
/// initialisation musique en mode simulation
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::initSimulation()
{
	charger6("media/son/mountain-fast.mp3"); //musique jouee lors de la simulation  ch7
	jouer6();
	initRobot();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::initRobot()
///
/// initialisation sons pour collision robot/objet en mode simulation
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::initRobot()
{
	charger("media/son/collisionPoteau.wav"); //ch1
	charger2("media/son/collision_mur.WAV");//ch8
	charger3("media/son/mur_invisible.mp3");//ch9
	charger4("media/son/avancer.wav"); //avancer/reculer  ch2
	charger5("media/son/rotation.wav"); //ch3
	charger7("media/son/deviation.wav");//ch4
	charger8("media/son/modeManuel.mp3");//ch5
	charger9("media/son/modeAutomatique.mp3");//ch6
	// jouer ces 3 sons mais en pause
	jouer4(true);
	jouer5(true);
	jouer7(true);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::mettreAjour()
///
/// Raffraichissement
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Son::mettreAjour()
{
	FMOD_System_Update(fmodsystem);
}

void Son::pauseSonSimulation()
{
	
	FMOD_Channel_GetPaused(channel2, &p2);
	FMOD_Channel_GetPaused(channel3, &p3);
	FMOD_Channel_GetPaused(channel4, &p4);
	FMOD_Channel_GetPaused(channel7, &p7);
	
	FMOD_Channel_SetPaused(channel2, true);
	FMOD_Channel_SetPaused(channel3, true);
	FMOD_Channel_SetPaused(channel4, true);
	FMOD_Channel_SetPaused(channel7, true);

}


void Son::UnPauseSonSimulation()
{
	FMOD_Channel_SetPaused(channel2, p2);
	FMOD_Channel_SetPaused(channel3, p3);
	FMOD_Channel_SetPaused(channel4, p4);
	FMOD_Channel_SetPaused(channel7, p7);
}
