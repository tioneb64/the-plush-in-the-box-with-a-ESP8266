Peluche dans la Boîte.

J'ai créé ce petit programme pour un jeu qui divertit beaucoup les enfants et l'ai construit avec 3 servomoteurs, un interrupteur et un ESP8266.

## Explication du jeu :
Le jeu est une boîte cubique dans laquelle se trouve un petit personnage. Sur le devant de la boîte, à mi-hauteur sur la gauche, il y a un interrupteur à bascule.
L'interrupteur est toujours orienté vers le bas. Lorsque les enfants lèvent l'interrupteur, la petite créature à l'intérieur de la boîte soulève le couvercle avec
sa tête et étend son bras vers la gauche pour abaisser l'interrupteur. Pour donner l'impression d'un être vivant, le programme réagit de manière aléatoire en
levant la tête, en bougeant le bras, ou en tournant la tête. La boîte peut s'ouvrir une fois ou plusieurs fois avant que le bras ne sorte et n'abaisse à nouveau
l'interrupteur. La peluche peut, par exemple, ouvrir le couvercle, tourner la tête dans les deux sens plusieurs fois, puis fermer la boîte avant de la rouvrir 
et d'abaisser rapidement l'interrupteur.

Voici un exemple visuel du résultat : https://www.youtube.com/watch?v=wlslwdB9Z4g

## Explication du montage :
Dans la boîte, il n'y a que la tête et le bras de la peluche. Le bras a la forme d'un demi-cercle. Le bras est monté sur un servomoteur qui le fait tourner pour 
abaisser l'interrupteur en sortant de la boîte. Le servomoteur du bras est collé à la face interne gauche de la boîte et tourne sur un axe vertical.

Un autre servomoteur est utilisé pour ouvrir et fermer le couvercle de la boîte. Il sert également à relever et abaisser la tête. Le servomoteur qui ouvre la boîte
et soulève la tête est collé à la face interne droite de la boîte et tourne sur un axe vertical. J'ai attaché une tige qui soulève le couvercle sur le servomoteur.
La tige tourne sur l'axe vertical du moteur. Une autre tige est attachée au même moteur avec un support. La deuxième tige est donc horizontale en bas de la boîte.

Sur la tige en bas de la boîte, qui monte lorsque le servomoteur sur la face droite tourne, un autre servomoteur est attaché. Ce troisième servomoteur tourne avec
un axe horizontal. Sur ce troisième servomoteur, la tête de la peluche est fixée.

Enfin, à l'intérieur de la boîte, fixée sur la face interne avant, se trouve une double diode qui s'allume lorsque la boîte s'ouvre.

## Alimentation électrique :
Pour l'alimentation, je voulais éviter de dépendre d'une source externe comme un transformateur. Ainsi, dans la boîte, j'ai utilisé 3 piles rechargeables AA de 1,5V
chacune, montées en série, me fournissant une tension de 4,5 V.

J'ai connecté l'adaptateur du module Semoic ESP8266 Serial ESP-01 Wi-Fi 3.3V 5V. Ce régulateur de tension fournit ensuite un 3,3 V stable à l'ESP8266.
Les servomoteurs sont directement connectés à leur broche +5 V, et la masse (GND) est reliée aux bornes des piles.
Enfin, les broches 12, 13 et 14 sont connectées aux servomoteurs, servant de sorties pour le couvercle, le bras et la tête, respectivement.
Elles sont connectées à la broche "signal" des servomoteurs.

La broche 11 est liée à l'interrupteur en entrée, et la broche 15 est connectée aux diodes. Les diodes sont alimentées par la sortie 3,3 V de l'ESP8266
et sont connectées à la masse (GND) de l'ESP8266. La GND de l'intérupteur est aussi connectée au GND de l'ESP8266.

Amusez-vous bien !!
