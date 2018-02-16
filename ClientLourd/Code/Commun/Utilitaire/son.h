
//Source:
/*http://www.roguebasin.com/index.php?title=Implementing_sound_in_C_and_C_Plus_Plus */

#pragma once

#include "../Externe/FMOD/Include/fmod.h" //FMOD Ex

class Son {
public:
	static void initialiser(void); //initialiser le son

	//sound control
	static void definirVolume(float v); //definir le volume courant de lecture
	static void charger(const char * filename); //charger un fichier son
	static void charger2(const char * filename); //charger un fichier son
	static void charger3(const char * filename); //charger un fichier son
	static void charger4(const char * filename); //charger un fichier son
	static void charger5(const char * filename); //charger un fichier son
	static void charger6(const char * filename); //charger un fichier son
	static void charger7(const char * filename); //charger un fichier son
	static void charger8(const char * filename); //charger un fichier son
	static void charger9(const char * filename); //charger un fichier son

	static void liberer(void); //liberer l'objet son

	static void jouer(bool pause = false); //jouer un son (peut demarer en pause; sans argument pour unpaused)
	static void jouer2(bool pause = false); //jouer un son (peut demarer en pause; sans argument pour unpaused)
	static void jouer3(bool pause = false); //jouer un son (peut demarer en pause; sans argument pour unpaused)
	static void jouer4(bool pause = false); //jouer un son (peut demarer en pause; sans argument pour unpaused)
	static void jouer5(bool pause = false); //jouer un son (peut demarer en pause; sans argument pour unpaused)
	static void jouer6(bool pause = false); //jouer un son (peut demarer en pause; sans argument pour unpaused)
	static void jouer7(bool pause = false); //jouer un son (peut demarer en pause; sans argument pour unpaused)
	static void jouer8(bool pause = false); //jouer un son (peut demarer en pause; sans argument pour unpaused)
	static void jouer9(bool pause = false); //jouer un son (peut demarer en pause; sans argument pour unpaused)

	//getters
	static bool obtenirSon(void); //verifier si le son est actif

	//setters
	static void setPause(int i, bool pause); //pause ou unpause le son
	static void setSon(bool son); //activer ou desactiver le son
	static void pauseSonSimulation();
	static void UnPauseSonSimulation();
	//inverseurs
	static void inverserSon(void); //actif/inactif
	static void inverserPause(void); //toggle pause ou non pause 

	static void initSimulation();
	static void initRobot();
	static void mettreAjour();

	//des variables statiques pour pauseSimulation
	static FMOD_BOOL p2;
	static FMOD_BOOL p3;
	static FMOD_BOOL p4;
	static FMOD_BOOL p7;


private:
	static bool actif; //etat d'activite du son
	static bool possible; //est-il possible de jouer le son
	static char * sonCourant;
	//attributs specifique a FMOD
	static FMOD_RESULT resultat;
	static FMOD_SYSTEM * fmodsystem;
	static FMOD_SOUND * son1;
	static FMOD_SOUND * son2;
	static FMOD_SOUND * son3;
	static FMOD_SOUND * son4;
	static FMOD_SOUND * son5;
	static FMOD_SOUND * son6;
	static FMOD_SOUND * son7;
	static FMOD_SOUND * son8;
	static FMOD_SOUND * son9;
	static FMOD_CHANNEL * channel;
	static FMOD_CHANNEL * channel2;
	static FMOD_CHANNEL * channel3;
	static FMOD_CHANNEL * channel4;
	static FMOD_CHANNEL * channel5;
	static FMOD_CHANNEL * channel6;
	static FMOD_CHANNEL * channel7;
	static FMOD_CHANNEL * channel8;
	static FMOD_CHANNEL * channel9;
};