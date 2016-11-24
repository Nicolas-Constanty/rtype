// Le bloc ifdef suivant est la façon standard de créer des macros qui facilitent l'exportation 
// à partir d'une DLL. Tous les fichiers contenus dans cette DLL sont compilés avec le symbole MONSTER_EXPORTS
// défini sur la ligne de commande. Ce symbole ne doit pas être défini pour un projet
// qui utilisent cette DLL. De cette manière, les autres projets dont les fichiers sources comprennent ce fichier considèrent les fonctions 
// MONSTER_API comme étant importées à partir d'une DLL, tandis que cette DLL considère les symboles
// définis avec cette macro comme étant exportés.
#ifdef MONSTER_EXPORTS
#define MONSTER_API __declspec(dllexport)
#else
#define MONSTER_API __declspec(dllimport)
#endif

// Cette classe est exportée de Monster.dll
class MONSTER_API CMonster {
public:
	CMonster(void);
	// TODO: ajoutez ici vos méthodes.
};

extern MONSTER_API int nMonster;

MONSTER_API int fnMonster(void);
