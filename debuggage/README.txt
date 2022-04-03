#debuggage avec gcc
Toutes les images ici présentes sont des captures d'écran du jeu lancé avec gdb ou lors de la compilation avec gcc (warnings)
pour débugger.
Plusieurs erreurs de segmentations liées aux structures et aux fonctions qui manipulent ces structures (tout est fait avec des pointeurs)
ont pu être identifiées et corrigées avec l'aide de GDB :
-Certaines fonctions tentaient d'accéder à un emplacement mémoire interdit, corrompu ou inaccessible (problème d'allocation de mémoire)
-Doubles free (tenter de libérer deux fois de suites la mémoire à la même adresse)
-Problèmes de fuites de mémoires liées à la mauvaise gestion des listes chainées d'entités (waves) au début du codage du jeu
#correction de warning avec gcc
Beaucoup de warnings ont pu être remarqués et corrigés grâce à gcc
 