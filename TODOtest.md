
# Semgent 

* Segmentde taille 0 -> erreur 

**lineLineIntersection** : 
* Vérifier position qu'on connait, exemple X1(0,0) X2(2,2) et Y1(0,2) Y2(2,0) -> P(1,1)
* Deux même segments -> erreur 
* Deux Segments parrallèle -> erreur 
* Deux segments Colinéaire qui se chevauchent 

**isOnSegment** 
* Test normal X1(0,0) X2(2,2) P(1,1) -> True 

# Normal 
* Calculer une normale qu'on connait 

# Elevate 
* Calculer l'ecart type entre une courbe et son élévation
* **Lower** : Pas d'idée pour l'instant 

# Derivate 
* Pas d'idée pour l'instant 

# Decompose 
* Décomposer la courbe en A et B puis ecart type de la suite de A par rapport à B sur un temps t > 1 et inversement sur B avec T < 1  

# BezierRayIntersection 
**Naive et Newton** 
* Intersection aux points 0 et N de la courbe OK
* Intersection tangente/normale à 1 points 
* Intersection extrémité du segment sur la courbe 
* Bon nombre d'intersections OK 

**Newton**
* Essayer de le faire diverger 
* Donner un mauvais  first guess 
* Verifier que plusieurs intersections n'ont pas les mêmes coordonnées 

*Performances :*
* Précision Newton face à Naive 
* Temps de calcul Newton face à Naive 