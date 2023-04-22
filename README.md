# AES-128-for-VIDEO-with-Cuda

Implémentation d'un chiffrement/déchiffrement d'un flux vidéo en temps réel via Cuda

Cette implémentation est un mélange d'une première implémentation que j'ai effectué pour du texte (cf https://github.com/inepsie/AES-128-for-TEXT-with-Cuda) et d'un programme de mon professeur M. Farès Belhadj qui utilise Cuda pour faire du traitement vidéo.

 Usage : ./simpleTexture <video_in_file | webcam> <out_file | screen> <0>
 Exemple 1 : ./simpleTexture webcam screen 0
 ---> La capture de la webcam est chiffré puis déchiffré puis affichée à l'écran
  Exemple 2 : ./simpleTexture dance.mp4 res.mp4 0
 ---> La vidéo dance.mp4 est chiffré puis déchiffré puis enregistré dans la vidéo res.mp4

 Le programme prend un flux vidéo en entrée, le chiffre puis le déchiffre, puis l'affiche à l'écran ou en fait un fichier vidéo.

 Les performances sont indiquées en direct. Nous pouvons constater que l'implémentation est assez rapide pour traiter des vidéos en temps réel.
