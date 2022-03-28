#débugage avec gdb
-Pour les structures des entités et les listes chaînées (de type t_wave) gdb a été très utile pour voir précisémment d'ou pouvait provenir
les erreur de sgementation
-Plusieurs erreurs ont pu être corrigées grâce à gdb telles que :
-double free()
-problème lors de déréférencement de pointeurs (tenter d'accéder à un emplacement mémoire non alloué)

Solutions trouvées:
-vérifier dans chaque fonctions utilisant les structures que les pointeurs passés en paramètres soient différents de NULL
-Allouer et désallouer la mémoire dans le bon ordre et au bon moment