#ImaGimp

Imagimp est un programme qui permet de transformer une image au format ppm en ligne de commande.

---
### Comment transformer une image ?

./bin/imagimp images/monImages.ppm CODELUT Parametre CODELUT Parametre

### Les LUT ###
* ADDLUM [nombre de 0 à 255] 	-> *Ajouter de la luminosité*
* DIMLUM [nombre de 0 à 255]  -> *Enleve de la luminosité*
* ADDCON [entre 1 et 3]       -> *Ajoute du contraste*
* DIMCON [entre 1 et 3]       -> *Enleve du contraste*
* INVERT 1                    -> *Inverse les couleurs*
* NB 1                        -> *Transforme en noir er blanc*
* SEPIA 1                     -> *Transforme en sépia*
