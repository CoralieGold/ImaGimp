#ImaGimp

Imagimp est un programme qui permet de transformer une image au format ppm en ligne de commande.

---
### Comment transformer une image ? ###
Il faut se mettre dans le dossier principal du programme puis lancer un terminal. Après avoir compiler le programme à l'aide de "make", vous pouvez le tester en mettant la ligne suivante dans le terminal, et en remplaçant par les codes LUT et les paramètres souhaités :
./bin/imagimp images/monImage.ppm nomImageFinale CODELUT_1 Parametre_1 ... CODELUT_n Parametre_n

### Les codes LUT et leur paramètre ###
* ADDLUM [nombre de 0 à 255]  -> *Ajouter de la luminosité*
* DIMLUM [nombre de 0 à 255]  -> *Enleve de la luminosité*
* ADDCON [entre 1 et 5]       -> *Ajoute du contraste*
* DIMCON [entre 1 et 5]       -> *Enleve du contraste*
* INVERT 1                    -> *Inverse les couleurs*
* NB 1                        -> *Transforme en noir er blanc*
* SEPIA 1                     -> *Transforme en sépia*
* ROUGE 1 					  -> *Applique un filtre rouge*
* VERT 1 					  -> *Applique un filtre vert*
* BLEU 1 					  -> *Applique un filtre bleu*
* CYAN 1 					  -> *Applique un filtre cyan*
* MAGENTA 1 				  -> *Applique un filtre magenta*
* JAUNE 1 					  -> *Applique un filtre jaune*

### Comment ajouter ses propres images ? ###
Il est possible avec Gimp de convertir ses images en ppm. Il faut, lors de l'export, choisir le format "image PPM" et cocher "ASCII". Ensuite, il faut ouvrir son image sous un éditeur de code et supprimer la ligne de commentaire (la 2ème ligne, qui commence par "#", si elle existe), puis faire en sorte que la largeur de l'image et la hauteur ne dépassent pas 3 caractères (exemple : 510 390) pour la 2ème ligne. Si l'image fait 2 caractères en largeur ou en hauteur, il faut ajouter des espaces : "35  110" par exemple. Si tout cela a été réalisé correctement, vous pouvez appliquer vos modifications à l'aide du programme.